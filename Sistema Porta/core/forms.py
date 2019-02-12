from django import forms
from .models import pessoa

class EditPessoa(forms.ModelForm):

    class Meta:
        model = pessoa
        fields = ('nome', 'key', 'ativado', 'segunda','terca', 'quarta', 'quinta', 'sexta', 'sabado', 'domingo')