from django.contrib import admin
from login.models import User,UserAdmin

# Register your models here.

admin.site.register(User,UserAdmin)

