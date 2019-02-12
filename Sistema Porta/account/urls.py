from django.urls import path
from django.contrib.auth import views as auth_views

urlpatterns = [
    path('', auth_views.LoginView.as_view()), # new
]