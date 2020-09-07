#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <time.h> 
using namespace std;

#include "Timer.h"
#include "Fraccion.h"

template<class T>
vector<T> cambio(vector<T> &lista, int a, int b){
    T temp = lista[a];
    lista[a] = lista[b];
    lista[b] = temp;
}

template<class T>
vector<T> ordenaIntercambio(vector<T> lista, int &comparaciones, int &intercambios){
    Timer tiempo;
    for (int i=0; i<lista.size(); i++){
        for (int j=i+1; j<lista.size(); j++){
            comparaciones++;
            if (lista[i] > lista[j]){
                intercambios++;
                cambio(lista, i, j);
            }
        }
    }
    return lista;
}

template<class T>
vector<T> ordenaBurbuja(vector<T> lista, int &comparaciones, int &intercambios){
    Timer tiempo;
    for (int i=0; i<lista.size()-1; i++){
        for (int j=0; j<lista.size()-i-1; j++){
            comparaciones++;
            if (lista[j+1] < lista[j]){
                intercambios++;
                cambio(lista, j+1, j);
            }
        }
    }
    return lista;
}

template<class T>
vector<T> seleccionDirecta(vector<T> lista, int &comparaciones, int &intercambios){
    Timer tiempo;
    int min, n, pos;
    pos = 0;
    for (int i=0; i<lista.size(); i++){
        min = lista[i];
        for (int j=0+i; j<lista.size(); j++){
            comparaciones++;
            if (lista[j] <= min){
                min = lista[j];
                pos = j;
            }
        }
        intercambios++;
        cambio(lista, i, pos);
    }
    return lista;
}

template<class T>
vector<T> ordenaInsercion(vector<T> lista, int &comparaciones, int &intercambios){
    Timer tiempo;
    int j;
    for (int i=1; i<lista.size(); i++){
        j = i;
        comparaciones++;
        while (lista[j] < lista[j-1] && j > 0){
            intercambios++;
            cambio(lista, j, j-1);
            j--;
        }
    }
    return lista;
}

template<class T>
void Merge(vector<T> &lista, int inicio, int medio, int fin){
    vector<T> listaI;
    vector<T> listaD;
    int pos,f1,f2,i,j;
    pos = inicio;
    f1 = medio - inicio + 1;
    f2 = fin - medio;
    for (i=0; i<f1; i++){
        listaI.push_back(lista[inicio+1]);
    }
    for (j=0; j<f2; j++){
        listaD.push_back(lista[medio+1+j]);
    }
    i=0;
    j=0;
    while(i<f1 && j<f2){
        if (listaI[i]<=listaD[j]){
            lista[pos] = listaI[i];
            i++;
        }else {
            lista[pos] = listaD[j];
            j++;
        }
        pos++;
    }
    while (i<f1){
        lista[pos] = listaI[i];
        i++;
        pos++;
    }
    while (j<f2){
        lista[pos] = listaD[j];
        j++;
        pos++;
    }
}

template<class T>
vector<T> ordenaMerge(vector<T> lista, int inicio, int fin, int &comparaciones){
    //Timer tiempo;
    if (inicio < fin) {
        comparaciones++;
        int medio = (inicio + fin) / 2;
        ordenaMerge(lista, inicio, medio, comparaciones);
        ordenaMerge(lista, medio+1, fin, comparaciones);

        Merge(lista, inicio, medio, fin);
    }
    return lista;
}

template<class T>
int particion(vector<T> &lista, int inf, int sup){
    int pivote = lista[sup];
    int i = (inf - 1);
    for (size_t j = inf; j <= sup- 1; j++){

        if (lista[j] < pivote)
        {
            i++;
            cambio(lista, i, j);
        }
    }
    cambio(lista, i+1, sup);
    return (i + 1);
}

template <class T>
vector<T> quickSort(vector<T> lista, int inf, int sup, int &comparaciones){
    //Timer tiempo;
    if (inf < sup)
    {
        int pi = particion(lista, inf, sup);
        quickSort(lista, inf, pi - 1, comparaciones);
        quickSort(lista, pi + 1, sup, comparaciones);
    }
    return lista;
}

template<class T>
int busquedaSecuencial(vector<T> lista, int n, int &comparaciones){
    Timer tiempo;
    int pos = 0;
    for (auto i: lista){
        comparaciones++;
        if(i == n){
            return pos;
        }
        pos++;
    }
    return -1;
}

template<class T>
int busquedaBinaria(vector<T> lista, int n, int &comparaciones){
    Timer tiempo;
    int mid, low, high;
    low = 0;
    high = lista.size();
    while (low <= high){
        mid = (low + high) / 2;
        comparaciones++;
        if (n < lista[mid]){
            high = mid - 1;
        } else if (n > lista[mid]){
            low = mid + 1;
        } else{
            return mid;
        }
    }
    return -1;
}

template<class T>
void vectorNumerosRand(vector<T> &lista, int cant, int max){
    srand (time(NULL));
    for (int i=0; i<cant; i++){
        lista.push_back(rand() % max + 1);
    }
}

template<class T>
void vectorCharsRand(vector<T> &lista, int cant){
    srand (time(NULL));
    int r;
    for (int i=0; i<cant; i++) {
        r = rand() % 26;
        lista.push_back('a' + r);
    }
}

void vectorFraccRand(vector<Fraccion> &lista, int cantidad) {
    lista.clear();
    int numerador, denominador;
    for (int i=0;i<cantidad;i++) {
        cout << "Teclea el numerador: " << endl;
        cin >> numerador;
        cout << "Teclea el denominador: " << endl;
        cin >> denominador;
        lista.push_back(Fraccion(numerador,denominador));
    }
}

void vectorStringRand(vector<string> &lista, int cantidad) {
    lista.clear();
    string valor;
    for (int i=0;i<cantidad;i++) {
        cout << "Teclea una palabra: " << endl;
        cin >> valor;
        lista.push_back(valor);
    }
}

template<class T>
void Mostrar(vector<T> lista){
    for (int i=0; i<lista.size(); i++){
        cout << lista[i] << " ";
    }
    cout << endl;
}

int main()
{
    int cant, comparaciones, intercambios;
    char opt = 'h';
    cout << "-- Creacion de Lista --" << endl;
    cout << "Cuantos elementos quieres?" << endl << ">> ";
    cin >> cant;
    vector<int> lista;
    vectorNumerosRand(lista, cant, 100);
    // vector<char> lista;
    // vectorCharsRand(lista, cant);

    cout << "Lista aleatoria: " << endl;
    Mostrar(lista);
    cout << endl;

    vector<int> listarand;
    //vector<char> listarand;
    listarand = lista;

    while (opt != 's'){
    if (opt == 'h') {
        cout << "   Menu   " << endl;
        cout << "----------" << endl;
        cout << "a - Ordena Intercambio" << endl;
        cout << "b - Ordena Burbuja" << endl;
        cout << "c - Seleccion Directa" << endl;
        cout << "d - Ordena Insercion" << endl;
        cout << "e - Ordena Merge" << endl;
        cout << "f - Quick Sort" << endl;
        cout << "1 - Busqueda Secuencial" << endl;
        cout << "2 - Busqueda Binaria" << endl;
        cout << "m - Mostrar lista" << endl;
        cout << "h - Ayuda (mostrar este menu)" << endl;
        cout << "s - Salir" << endl << endl;
    }
    cout << ">> ";
    cin >> opt;

    lista = listarand;
    comparaciones = 0;
    intercambios = 0;
    
    switch(opt){
    case 'a': {
        lista = ordenaIntercambio(lista, comparaciones, intercambios);
        cout << "Lista ordenada (Intercambio): " << endl;
        Mostrar(lista);
        cout << "Comparaciones: " << comparaciones << endl;
        cout << "Intercambios: " << intercambios << endl;
        break;
    }
    case 'b': {
        lista = ordenaBurbuja(lista, comparaciones, intercambios);
        cout << "Lista ordenada (Burbuja): " << endl;
        Mostrar(lista);
        cout << "Comparaciones: " << comparaciones << endl;
        cout << "Intercambios: " << intercambios << endl;
        break;
    }
    case 'c': {
        lista = seleccionDirecta(lista, comparaciones, intercambios);
        cout << "Lista ordenada (Seleccion Directa): " << endl;
        Mostrar(lista);
        cout << "Comparaciones: " << comparaciones << endl;
        cout << "Intercambios: " << intercambios << endl;
        break;
    }
    case 'd': {
        lista = ordenaInsercion(lista, comparaciones, intercambios);
        cout << "Lista ordenada (Insercion): " << endl;
        Mostrar(lista);
        cout << "Comparaciones: " << comparaciones << endl;
        cout << "Intercambios: " << intercambios << endl;
        break;
    }
    case 'e': {
        lista = ordenaMerge(lista, 0, lista.size(), comparaciones);
        cout << "Lista ordenada (Merge): " << endl;
        Mostrar(lista);
        cout << "Comparaciones: " << comparaciones << endl;
        break;
    }
    case 'f': {
        lista = quickSort(lista, 0, lista.size(), comparaciones);
        cout << "Lista ordenada (Quick Sort): " << endl;
        cout << "Comparaciones: " << comparaciones << endl;
        break;
    }
    case '1': {
        int n, pos;
        cout << "Que numero quieres buscar en la lista? (secuencial) " << endl << ">> ";
        cin >> n;
        cout << "Lista:" << endl;
        Mostrar(lista);
        pos = busquedaSecuencial(lista, n, comparaciones);
        if (pos != -1){
            cout << "Posicion del numero: [" << pos << "]" << endl;
        }else {
            cout << "Numero no en la lista" << endl;
        }
        break;
    }
    case '2': {
        int n, pos;
        lista = ordenaInsercion(lista, comparaciones, intercambios);
        comparaciones = 0;
        cout << "Que numero quieres buscar en la lista? (binaria) " << endl << ">> ";
        cin >> n;
        cout << "Lista:" << endl;
        Mostrar(lista);
        pos = busquedaBinaria(lista, n, comparaciones);
        if (pos != -1){
            cout << "Posicion del numero: [" << pos << "]" << endl;
        }else {
            cout << "Numero no en la lista" << endl;
        }
        break;
    }
    case 'm': {
        Mostrar(listarand);
        break;
    }
    default:
        break;
    }
    cout << endl << endl;
    }
    cout << "Bye" << endl;
    
    return 0;
}
