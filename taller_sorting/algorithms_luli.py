from list_algorithms import presentar
import random

grupo= 'elegir nombre copado y no usar unicode'

# ATENCION:
#- descomentar el "@presentar" y dejarlo solamente en las implementaciones de los algoritmos a entregar
#- pueden agregar las funciones auxiliares que necesiten en este mismo archivo
#- solo se permite un unico envio

# 0.76
@presentar
def insertion_sort(a):
    for i in range(1, len(a)):
        e = a[i]
        j = i-1
        while j >= 0 and e < a[j]:
            a[j+1] = a[j]
            j -= 1
        a[j+1] = e
    return a

def swap_min(a, i):
    j = min(enumerate(a[i:]), key = lambda p : p[1])[0] + i
    a[i], a[j] = a[j], a[i]

# 0.51
@presentar
def selection_sort(a):
    [swap_min(a, i) for i in range(len(a))]
    return a

# 0.00 algo falló
@presentar
def quicksort(a):
    if len(a) < 2: return a
    pivot = a[len(a)//2]
    L = quicksort([e for e in a if e < pivot])
    R = quicksort([e for e in a if e > pivot])
    return L + [pivot] + R

#@presentar
def heapsort(a):
    return a

# 1.23
@presentar
def mergesort(lista):
    if len(lista) < 2:
        return lista
    m = len(lista) // 2
    L = mergesort(lista[:m])
    R = mergesort(lista[m:])
    lista = []

    i = j = 0
    while i < len(L) and j < len(R):
        if L[i] < R[j]:
            lista.append(L[i])
            i += 1
        else:
            lista.append(R[j])
            j += 1

    lista += L[i:]
    lista += R[j:]

    return lista
