from django.contrib import admin
from handle.models import File,FileAdmin

# Register your models here.

admin.site.register(File,FileAdmin)
