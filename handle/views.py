# coding=utf-8
from django.shortcuts import render, render_to_response
from django.http import HttpResponse,HttpResponseRedirect
from django.views.generic import ListView
from handle.models import File
from django import forms
from login.models import User
import commands
import os
from multiprocessing import Process
import MySQLdb


# Create your class here.
class FileList(ListView):
	model = File
	context_object_name = 'file_list'  
	template_name = 'overview.html'	
	paginate_by = 10 


class UploadFileForm(forms.Form):
	user = forms.CharField(label = 'User Name', max_length =100)
	filefield = forms.FileField(label = 'Upload File')


class AnalysisForm(forms.Form):
	filename = forms.CharField(label='文件:',max_length=100)
	mode = forms.CharField(label='模型:',max_length=1)
	folder = forms.CharField(label='模型文件夹:',max_length=50)
	res_file = forms.CharField(label='结果文件:',max_length=50)
	user_dict = forms.CharField(label='用户信息文件夹:',required=False)


# Create your views here.
def upload(req):
	if req.method == 'POST':
		form = UploadFileForm(req.POST, req.FILES)
		if form.is_valid():
			return HttpResponse('ok')
	else:
		username=req.COOKIES.get('username','')
		form = UploadFileForm(initial={'user':username})
	
	return render_to_response('upload.html',{'formset':form})



def file_upload(req):
	if req.method == 'POST':
		form = UploadFileForm(req.POST, req.FILES)
		if form.is_valid():
			print 'true'
			username = form.cleaned_data['user']
			filefield = form.cleaned_data['filefield']
			
			# check the username is exist
			user = User.objects.filter(username__exact=username)
			if user.__len__() == 1:
				# exist
				f = File()
				f.user = user[0]
				f.filename = filefield
				f.status = '1'
				f.save()
				print f.filename.name
			
				return HttpResponseRedirect('/enlu/handle/?username=%s' % user)
			else :
				print 'the username does not exist!'
				return render_to_response('upload.html',{'formset':form})
		else:
			print 'form is not valid!'
			return render_to_response('upload.html',{'formset':form})
	else:
		print 'req.method != POST'




def analysis(req):
	if req.method == 'POST':
		form = AnalysisForm(req.POST)
		if form.is_valid():
			# 需要添加用户来共同限制
			filename = form.cleaned_data['filename']
			paras ={}
			paras['filename']='media/'+filename
			paras['mode'] = form.cleaned_data['mode']
			paras['folder'] = form.cleaned_data['folder']
			# create output folder
			(outdir,ty) = os.path.splitext(paras['filename'])
			if not os.path.exists(outdir):
				os.makedirs(outdir)
			paras['res_file'] = os.path.join(outdir,form.cleaned_data['res_file'])
			paras['user_dict'] = form.cleaned_data['user_dict']
			print str(paras)
			files = File.objects.filter(filename=filename)
			if files.__len__() == 1:
				# begin to analysis
				File.objects.filter(filename=filename).update(status = '2')
				File.objects.filter(filename=filename).update(parameters = str(paras))
			#	files[0].save()

				# analysising
				print 'analysising============'
				#print process(paras)
				#p = Process(target = protext, args=(str(paras),))
				p = Process(target = prom, args=(paras['filename'],paras['mode'],paras['folder'],paras['res_file'],paras['user_dict']))
				p.start()
				
			else:
				print 'the file objects are more than one.'

			return HttpResponseRedirect('/enlu/handle/')
	else:
		filename = req.GET.get('file')
		if not filename:
			return HttpResponseRedirect("/enlu/login/")
		init_par = {'mode':'1','folder':'model','res_file':'result.txt'}
		init_par['filename']=filename
		form = AnalysisForm(initial=init_par)
	
	return render_to_response('analysis.html',{'form':form})


def prom(filename,mode,folder,res_file,user_dict):
	print "starting child process with id:" , os.getpid()
	paras = {'filename':filename, 'mode':mode, 'folder':folder, 'res_file':res_file, 'user_dict':user_dict}
	print paras['filename'],paras['mode'],paras['folder'],paras['res_file']
	cmd = "sh runthis.sh "+paras['filename']+" "+paras['mode']+" "+paras['folder']+" "+paras['res_file']+" "+paras['user_dict']
	print cmd
	(status, output) = commands.getstatusoutput(cmd)
	sta = '0'
	name = paras['filename'].replace('media/','')
	res_link = ""
	if status:
		print output
		sta = '1'
	else:
		(path,basename) = os.path.split(paras['res_file'])
		(sta,out) = commands.getstatusoutput('ls -1t '+path+' | head -1')
		print "analysised==========="
		# save
		res_link = os.path.join(path,out)+'/ANALYSIS_Performance.html'
		sta = '3'
		#files = File.objects.filter(filename=name)
		#print files[0].filename
		#File.objects.filter(filename=name).update(status = '3')
		#File.objects.filter(filename=name).update(result_link = res_link)
	#db operator
	db = MySQLdb.connect("localhost","root","root","enlu")
	cursor = db.cursor()
	if sta == '3':
		sql = "UPDATE handle_file set status='"+sta+"' , result_link='"+res_link+"' where filename='"+name+"'"
	else:
		sql = "UPDATE handle_file set status='"+sta+"' where filename='"+name+"'"
	print sql
	try:
		cursor.execute(sql)
		db.commit()
	except:
		db.rollback()

	db.close()
	print sta




def show(req,paths):
	(path,basename) = os.path.split(paths)
	parts=path.split()
	cmd = "rm templates/* ; cp media/"+parts[0]+"\ "+parts[1]+"/* templates/"
	print cmd
	(status, output) = commands.getstatusoutput(cmd)
	if status:
		print "rm error"
		return HttpResponseRedirect('/enlu/handle/')
	else:
		return render_to_response(basename)
