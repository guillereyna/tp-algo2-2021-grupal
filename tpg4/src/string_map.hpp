
#include "string_map.h"

template <typename T>
string_map<T>::string_map(){
    raiz = nullptr;
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    if (this->raiz != nullptr) {
        (this->raiz)->borrar_todo();
    }
    if (d.raiz == nullptr) { return *this; }
    this->raiz = new Nodo();
    if ((d.raiz)->definicion){
        (this->raiz)->definicion = new T(*((d.raiz)->definicion));
    }
    (this->raiz)->copiar(d.raiz);
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    if (this->raiz != nullptr) { (this->raiz)->borrar_todo(); }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}

template <typename  T>
void string_map<T>::insert(const pair<string, T>& p) {
    if (count(p.first) == 0) _size++;
    if (this->raiz == nullptr) raiz = new Nodo();
    (this->raiz)->_insert(p, 0);
    _claves.push_back(p.first);
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    return (this->raiz)->_count(clave, 0);
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    return (this->raiz)->_at(clave, 0);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    return (this->raiz)->_at(clave, 0);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    (this->raiz)->_erase(clave);
    if (this->_size == 1) {
        delete raiz;
        this->raiz = nullptr;
    }
    _size--;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return raiz == nullptr;
}

template<typename T>
const vector<string> string_map<T>::claves() const {
    return _claves;
}

/* * * * * * * * * * * * * *
 *   OPERACIONES DE NODO   *
 * * * * * * * * * * * * * */

template <typename T>
string_map<T>::Nodo::Nodo(T* d) : siguientes(127, nullptr), definicion(d) {}

template <typename T>
string_map<T>::Nodo::Nodo() : siguientes(127, nullptr), definicion(nullptr) {}

template <typename T>
int string_map<T>::Nodo::_count(const string& clave, const int& i) const{

    // Diccionario vacío.
    if (this == nullptr) return 0;

    // Estoy en la última posición.
    if (i == clave.length()) {
        if (this->definicion != nullptr) return 1;
        else return 0;
    }
    // No estoy en la última posición.
    if (this->siguientes[int(clave[i])] != nullptr) {
        return (this->siguientes[int(clave[i])])->_count(clave, i+1);
    }
    return 0;
}

template <typename T>
T& string_map<T>::Nodo::_at(const string& clave, const int& i) const {
    // Estoy en la útima posición.
    if (i == clave.length()) {
        return *(this->definicion);

    // No estoy en la última posición.
    } else {
        return (this->siguientes[int(clave[i])])->_at(clave, i + 1);
    }
}

template <typename T>
void string_map<T>::Nodo::_insert(const pair<string, T>& p, const int& i) {
    // Estoy en la última posición.
    if (i == p.first.length()) {
        delete this->definicion;
        this->definicion = new T(p.second);

    // No hay más nodos.
    } else if (this->siguientes[int(p.first[i])] == nullptr) {
        this->agregarClaveDesde(p, i);

    // No estoy en la última posición y hay nodos.
    } else {
        (this->siguientes[int(p.first[i])])->_insert(p, i+1);
    }
}

template <typename T>
void string_map<T>::Nodo::_erase(const string& clave) {
    int i = 0;

    Nodo* ultimo = this->ultimo_importante(clave, i);
    // Si el último importante es la última letra de la palabra
    // significa que tengo que borrar únicamente la definición.
    if (i == clave.length()) {
        delete ultimo->definicion;
        ultimo->definicion = nullptr;
        return;
    }
    Nodo* desde = ultimo->siguientes[int(clave[i])];
    ultimo->siguientes[int(clave[i])] = nullptr;
    i++;
    while (i < clave.length()) {
        Nodo* aux = desde->siguientes[int(clave[i])];
        delete desde;
        desde = aux;
        i++;
    }
    delete desde->definicion;
    delete desde;
}

template <typename T>
typename string_map<T>::Nodo* string_map<T>::Nodo::ultimo_importante(const string& clave, int &k) {
    Nodo* ultimo = this;
    Nodo* actual = this;
    int i = 0;
    while (i < clave.length()) {
        if (actual->cantHijos() > 1 || actual->definicion != nullptr) {
            ultimo = actual;
            k = i;
        }
        actual = actual->siguientes[int(clave[i])];
        i++;
    }
    if (actual->cantHijos() > 0) {
        k = clave.length();
        return actual;
    }
    return ultimo;
}

template <typename T>
int string_map<T>::Nodo::cantHijos() {
    int res = 0;
    for (int i = 0; i < 127; i++) {
        if (this->siguientes[i] != nullptr) res++;
    }
    return res;
}

template <typename T>
void string_map<T>::Nodo::borrar_todo() {
    for (int i=0; i < 127; i++) {
        if (this->siguientes[i] != nullptr) {
            Nodo* aux = this->siguientes[i];
            if (aux->definicion != nullptr) delete aux->definicion;
            aux->borrar_todo();
        }
    }
    delete this;
}

template <typename T>
void string_map<T>::Nodo::agregarClaveDesde(const pair<string, T>& p, const int& i) {
    if (i == p.first.length()) {
        this->definicion =  new T(p.second);
    } else {
        this->siguientes[int(p.first[i])] = new Nodo();
        this->siguientes[int(p.first[i])]->agregarClaveDesde(p, i + 1);
    }
}

template <typename T>
void string_map<T>::Nodo::copiar(Nodo* d) {
    for (int i=0; i < 127; i++) {
        if (d->siguientes[int(i)] != nullptr) {
            this->siguientes[int(i)] = new Nodo();
            if ((d->siguientes[int(i)])->definicion) {
                (this->siguientes[int(i)])->definicion = new T(*(d->siguientes[int(i)])->definicion);
            }
            (this->siguientes[int(i)])->copiar(d->siguientes[int(i)]);
        }
    }
}