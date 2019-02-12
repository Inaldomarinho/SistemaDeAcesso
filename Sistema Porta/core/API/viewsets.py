from rest_framework.response import Response
from rest_framework.viewsets import ModelViewSet
from core.models import pessoa, log
from .serializers import PessoaSerializer, LogSerializer
from django.shortcuts import get_object_or_404

class PessoaViewSet(ModelViewSet):
    """
    A simple ViewSet for viewing and editing accounts.
    """
    queryset = pessoa.objects.filter(ativado = True)
    serializer_class = PessoaSerializer
    http_method_names = ['get', 'post']


class LogsViewSet(ModelViewSet):
    
    queryset = log.objects.all()
    serializer_class = LogSerializer
    http_method_names = ['post']

    def create(self, request, *args, **kwargs):
       try:
        aux = log()
        aux.key = get_object_or_404(pessoa, key=request.data['key'])
        aux.save()
        return  Response({'status' : 'sucesso'})
       except:
        return Response({'status': request.data})
