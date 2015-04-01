#coding=utf-8
from django.shortcuts import render, render_to_response
from django.views.generic import ListView
from handle.models import File
from django import forms


# Create your class here.
class FileList(ListView):
	model = File
	context_object_name = 'file_list'  
	template_name = 'overview.html'	
	paginate_by = 3 


class UploadFileForm(forms.Form):
	user = forms.CharField(label = 'User Name', max_length =100)
	filefield = forms.FileField(label = 'Upload File')


# Create your views here.
def upload(req):
	if req.method == 'POST':
		form = UploadFileForm(req.POST, req.FILES)
		if form.is_valid():
			return HttpResponse('ok')
	else:
		form = UploadFileForm()
	
	return render_to_response('upload.html',{'formset':form})
			
