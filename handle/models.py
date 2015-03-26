# coding=utf-8
from django.db import models
from login.models import User
from django.contrib import admin

# Create your models here.


status_choices = (
	('1','uploaded'),
	('2','analysising'),
	('3','complete'),
)


class File(models.Model):
	user = models.ForeignKey(User)
	filename = models.CharField(max_length=100)
	status = models.CharField(max_length=1, choices=status_choices)
	parameters = models.CharField(max_length=50)
	result_link = models.CharField(max_length=100)
#	upload_time = models.DateTimeField(auto_now=False, auto_now_add=True)

	def __str__(self):
		return self.filename

class FileAdmin(admin.ModelAdmin):
	list_display = ('filename','user','status','parameters','result_link')
