from django.db import models
from django.utils import timezone
# Create your models here.

class pessoa(models.Model):
    nome = models.CharField(max_length=150)
    key = models.CharField(max_length=15)
    ativado = models.BooleanField()
    segunda = models.BooleanField()
    terca = models.BooleanField()
    quarta = models.BooleanField()
    quinta = models.BooleanField()
    sexta = models.BooleanField()
    sabado = models.BooleanField()
    domingo = models.BooleanField()
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

