from django.db import models
from django.contrib import admin


# Create your models here.


class User(models.Model):
	username = models.CharField(max_length=50, primary_key=True)
	password = models.CharField(max_length=50)
	
	def __unicode__(self):
		return self.username
	# show style

class UserAdmin(admin.ModelAdmin):
	list_display = ('username','password')
