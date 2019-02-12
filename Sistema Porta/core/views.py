from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from django.shortcuts import render, get_object_or_404, redirect
from django.utils import timezone
from .models import log, pessoa
from .postMqtt import postMQTT
from .forms import EditPessoa


def index(request):
    log_list = log.objects.filter(created_date__lte=timezone.now()).order_by('-created_date')
    page = request.GET.get('page', 1)

    paginator = Paginator(log_list, 25)
    try:
        logs = paginator.page(page)
    except PageNotAnInteger:
        logs = paginator.page(1)
    except EmptyPage:
        logs = paginator.page(paginator.num_pages)

    return render(request, 'core/index.html', {'logs': logs})


def list_pessoa(request):
    pessoas = pessoa.objects.filter(created_date__lte=timezone.now()).order_by('nome')
    return render(request, 'core/pessoas.html', {'pessoas': pessoas})

def pessoa_edit(request, pk):
    post = get_object_or_404(pessoa, pk=pk)
    if request.method == "POST":
        form = EditPessoa(request.POST, instance=post)
        if form.is_valid():
            post = form.save(commit=False)
            post.save()
            return redirect('list_pessoa')
    else:
        form = EditPessoa(instance=post)
    return render(request, 'core/edit.html', {'form': form})

def abrir(request):
    postMQTT("abrir")
    aux = log()
    aux.key = get_object_or_404(pessoa, nome="Liberado pelo sistema")
    aux.save()
    logs = log.objects.filter(created_date__lte=timezone.now()).order_by('-created_date')
    return render(request, 'core/index.html', {'logs': logs})

def atualizar(request):
    postMQTT("atualizar")
    logs = log.objects.filter(created_date__lte=timezone.now()).order_by('-created_date')
    return render(request, 'core/index.html', {'logs': logs})

