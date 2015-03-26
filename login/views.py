# coding=utf-8
from django.shortcuts import render,render_to_response
from django import forms
from django.http import HttpResponse,HttpResponseRedirect
from login.models import User
from handle.view import FileList

# Create your views here.

class UserForm(forms.Form):
	name = forms.CharField(label='用户名:',max_length=20)
	pawd = forms.CharField(label='密码:',widget=forms.PasswordInput())

def login(req):
	if req.method == 'POST':	# method
		form = UserForm(req.POST)	# bind data
		if form.is_valid():	# va;od data
			# get username & password
			username = form.cleaned_data['name']
			password = form.cleaned_data['pawd']
			# get password of user from database
			user = User.objects.filter(username__exact=username)	
			if user.__len__() >= 1  :
				if user[0].password == password :
					return HttpResponseRedirect('/enlu/handle/?username=%s' % username)
				#	return render_to_response('overview.html',{})
				else :
				#	return HttpResponse('<script>alert("密码错误!")</script>')
					return render_to_response('login.html',{'form':form, 'message':'密码错误!'})
			else:
				return render_to_response('login.html',{'form':form , 'message' : '没有该用户!'})
			#	HttpResponse('<script>alert("没有该用户!")</script>')
		#		return render_to_response('showMessage.html',{'message':'没有该用户!'})
		#	print form.cleaned_data	# get data
	else :
		form = UserForm()

	return render_to_response('login.html',{'form' : form})
