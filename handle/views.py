#coding=utf-8
from django.shortcuts import render
from django.views.generic import ListView
from handle.models import File
from django import forms


# Create your views here.



class FileList(ListView):
	model = File
	context_object_name = 'file_list'  
	template_name = 'overview.html'	
	paginate_by = 3 


# file upload
class UploadFileForm(form.Form):
	filefield = forms.FileField(label = 'Upload File')
