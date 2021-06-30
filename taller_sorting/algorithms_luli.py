from list_algorithms import presentar
import random

grupo= 'tomarAgua'

# ATENCION:
#- descomentar el "@presentar" y dejarlo solamente en las implementaciones de los algoritmos a entregar
#- pueden agregar las funciones auxiliares que necesiten en este mismo archivo
#- solo se permite un unico envio

# 0.75
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
    j = 0
    for k in range(len(a)):
        if a[k] < a[j]:
            j = k

    a[i], a[j] = a[j], a[i]

# 0.75
@presentar
def selection_sort(a):
    for i in range(len(a)):
        swap_min(a, i)
    return a

# 3.41
@presentar
def quicksort(a):
    n = len(a)
    if n < 2: return a
    pivot = a[n//2]
    c = k = i = j = 0
    for e in a:
        if e == pivot: c+=1
        if e < pivot: k+=1
    L = a.crear_temporal(k)
    R = a.crear_temporal(n-k-1)
    for e in a:
        if e < pivot:
            L[i] = e
            i+=1
        if e > pivot:
            R[j] = e
            j+=1
    return quicksort(L) + c*[pivot] + quicksort(R)

def downheap(a, n, i):
    continuar = True
    p = i
    while (continuar):
        izq = 2 * i + 1
        der = izq + 1
        if izq < n and a[i] < a[izq]:
            p = izq
        if der < n and a[p] < a[der]:
            p = der
        if p == i or p >= n: continuar = False
        a[i], a[p] = a[p], a[i]
        i = p

# 6.89
@presentar
def heapsort(a):
    n = len(a)
    for i in range(n//2 - 1, -1, -1):
        downheap(a, n, i)
    #[downheap(a, n, i) for i in range(n // 2 - 1, -1, -1)]
    for i in range(n-1, 0, -1):
        a[i], a[0] = a[0], a[i]
        downheap(a, i, 0)
    return a

# 3.97
@presentar
def mergesort(lista):
    n = len(lista)
    if n < 2:
        return lista
    m = n // 2
    L = mergesort(lista[:m])
    R = mergesort(lista[m:])
    result = lista.crear_temporal()

    k = i = j = 0
    while i < m and j < n-m:
        if L[i] < R[j]:
            result[k] = L[i]
            i += 1
        else:
            result[k] = R[j]
            j += 1
        k += 1

    return result[:k] + L[i:] + R[j:]
