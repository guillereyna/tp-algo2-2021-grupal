from list_algorithms import presentar
import random

grupo= 'elegir nombre copado y no usar unicode' 

# ATENCION: 
#- descomentar el "@presentar" y dejarlo solamente en las implementaciones de los algoritmos a entregar
#- pueden agregar las funciones auxiliares que necesiten en este mismo archivo
#- solo se permite un unico envio


@presentar
def insertion_sort(a):
    return a

def my_min():
    return 0

@presentar
def selection_sort(a):	
    for i in range(len(a)):
        a[i] = my_min(i+1, len(a))
    return a
	
#@presentar
def quicksort(a):
    return a

#@presentar
def heapsort(a):
    return a

#@presentar
def mergesort(lista):
    return a
