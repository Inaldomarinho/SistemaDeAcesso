from rest_framework.response import Response
from rest_framework.viewsets import ModelViewSet
from core.models import pessoa, log
from .serializers import PessoaSerializer, LogSerializer
from django.shortcuts import get_object_or_404

class PessoaViewSet(ModelViewSet):
    """
    A simple ViewSet for viewing and editing accounts.
    """
    queryset = pessoa.objects.filter(ativado=True).order_by('nome')
    serializer_class = PessoaSerializer
    http_method_names = ['get',]

    def list(self, request, *args, **kwargs):

       key = request.GET.get('key' or None)
       if key != None:
           try:
            aux = pessoa()
            aux.nome = "Cadastrado pela tranca"
            aux.key = key
            aux.save()
            return  Response({'status' : 'sucesso'})
           except:
            return Response({'status': 'falha'})
       else:
           pessoas = pessoa.objects.filter(ativado=True).order_by('nome')
           data = PessoaSerializer(pessoas, many=True).data
           return Response(data)



class LogsViewSet(ModelViewSet):
    
    queryset = log.objects.all()
    serializer_class = LogSerializer
    http_method_names = ['get']

    def list(self, request, *args, **kwargs):

        key = request.GET.get('key' or None)

        if key != None:
           try:
            aux = log()
            aux.key = get_object_or_404(pessoa, key=key)
            aux.save()
            return Response({'status': 'sucesso'})
           except:
            return Response({'status': 'falha'})
        else:
            return Response({'key': 'Insira uma key válida nesse campo'})