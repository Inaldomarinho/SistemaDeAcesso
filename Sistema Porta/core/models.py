from django.db import models
from django.utils import timezone
# Create your models here.

class pessoa(models.Model):
    nome = models.CharField(max_length=150)
    key = models.CharField(max_length=14, unique=True)
    ativado = models.BooleanField(default=False)
    segunda = models.BooleanField(default=True)
    terca = models.BooleanField(default=True)
    quarta = models.BooleanField(default=True)
    quinta = models.BooleanField(default=True)
    sexta = models.BooleanField(default=True)
    sabado = models.BooleanField(default=True)
    domingo = models.BooleanField(default=True)
    created_date = models.DateTimeField(
        default=timezone.now)

    def __str__(self):
        return self.nome

    class Meta:
        verbose_name = 'Pessoa'
        verbose_name_plural = 'Pessoas'
        ordering = ['created_date']


class log(models.Model):
    key = models.ForeignKey(pessoa, on_delete=models.CASCADE)
    created_date = models.DateTimeField(
        default=timezone.now)

    class Meta:
        verbose_name = 'Log'
        verbose_name_plural = 'Logs'
        ordering = ['created_date']

