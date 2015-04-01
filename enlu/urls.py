from django.conf.urls import include, url
from django.contrib import admin
from handle.views import FileList

urlpatterns = [
    # Examples:
    # url(r'^$', 'enlu.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^admin/', include(admin.site.urls)),
    url(r'^enlu/login/$','login.views.login'),
    url(r'^enlu/handle/$',FileList.as_view(),name='overview'),
    url(r'^enlu/upload/$','handle.views.upload'),
]
