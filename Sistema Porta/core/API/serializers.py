from rest_framework.serializers import ModelSerializer
from core.models import pessoa, log

class PessoaSerializer(ModelSerializer):

    class Meta:
        model = pessoa
        fields = ('nome', 'key', 'segunda', 'terca', 'quarta', 'quinta', 'sexta', 'sabado', 'domingo')



class LogSerializer(ModelSerializer):

    class Meta:
        model = log
        fields = ('key',)
