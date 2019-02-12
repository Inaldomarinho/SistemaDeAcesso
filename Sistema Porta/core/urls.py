from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('pessoas/', views.list_pessoa, name='list_pessoa'),
    path('pessoas/<int:pk>/edit/', views.pessoa_edit, name='pessoa_edit'),
    path('pessoas/abrir/', views.abrir, name='abrir'),
    path('pessoas/atualizar/', views.atualizar, name='atualizar'),
]