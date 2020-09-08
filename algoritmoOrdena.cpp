//Luis Cano Irigoyen - A00827178 - 7/Sept/2020
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <iomanip> 
using namespace std;

#include "Fraccion.h"

template<class T>
vector<T> cambio(vector<T> &lista, int a, int b){
    T temp = lista[a];
    lista[a] = lista[b];
    lista[b] = temp;
}

template<class T>
vector<T> ordenaIntercambio(vector<T> lista, int &comparaciones, int &intercambios){
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
    clock_t start, end;
    start = clock();
    for (int i=0; i<lista.size()-1; i++){
        for (int j=0; j<lista.size()-i-1; j++){
            comparaciones++;
            if (lista[j+1] < lista[j]){
                intercambios++;
                cambio(lista, j+1, j);
            }
        }
    }
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
    return lista;
}

template<class T>
vector<T> seleccionDirecta(vector<T> lista, int &comparaciones, int &intercambios){
    clock_t start, end;
    start = clock();
    T min;
    int pos;
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
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
    return lista;
}

template<class T>
vector<T> ordenaInsercion(vector<T> lista, int &comparaciones, int &intercambios){
    clock_t start, end;
    start = clock();
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
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
    return lista;
}

template<class T>
void Merge(vector<T> &lista, int inicio, int medio, int fin, int &comparaciones){
    int i, j, k;
    int f1 = medio - inicio + 1;
    int f2 = fin - medio;
    vector<T> izq;
    vector<T> der;
    for (i=0; i < f1; i++){
        izq.push_back(lista[inicio+i]);
    }
    for (j=0; j < f2; j++){
        der.push_back(lista[medio+1+j]);
    }
    i = 0;
    j = 0;
    k = inicio;
    while(i < f1 && j < f2){
        comparaciones++;
        if (izq[i] <= der[j]){
            lista[k] = izq[i];
            i++;
        }else {
            lista[k] = der[j];
            j++;
        }
        k++;
    }
    while (i < f1) { 
        comparaciones++;
        lista[k] = izq[i]; 
        i++; 
        k++; 
    } 
    while (j < f2) { 
        comparaciones++;
        lista[k] = der[j]; 
        j++; 
        k++; 
    } 
}

template<class T>
void ordenaMerge(vector<T> &lista, int inicio, int fin, int &comparaciones){
    if (inicio < fin) { 
        comparaciones++;
        int medio = inicio + (fin - inicio) / 2; 
        ordenaMerge(lista, inicio, medio, comparaciones); 
        ordenaMerge(lista, medio + 1, fin, comparaciones); 
        Merge(lista, inicio, medio, fin, comparaciones); 
    } 
}

template<class T>
int particion(vector<T> &lista, int inf, int sup, int &comparaciones){
    T pivote = lista[sup];
    int i = (inf - 1);
    for (int j = inf; j <= sup- 1; j++){
        comparaciones++;
        if (lista[j] <= pivote)
        {
            i++;
            cambio(lista, i, j);
        }
    }
    cambio(lista, i+1, sup);
    return (i + 1);
}

template <class T>
void quickSort(vector<T> &lista, int inf, int sup, int &comparaciones){
    if (inf < sup)
    {
        comparaciones++;
        int pa = particion(lista, inf, sup, comparaciones);
        quickSort(lista, inf, pa - 1, comparaciones);
        quickSort(lista, pa + 1, sup, comparaciones);
    }
}

template<class T>
int busquedaSecuencial(vector<T> lista, T n, int &comparaciones){
    clock_t start, end;
    start = clock();
    int pos = 0;
    for (auto i: lista){
        comparaciones++;
        if(i == n){
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            return pos;
        }
        pos++;
    }
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
    return -1;
}

template<class T>
int busquedaBinaria(vector<T> lista, T n, int &comparaciones){
    clock_t start, end;
    start = clock();
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
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            return mid;
        }
    }
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
    return -1;
}

void vectorNumerosRand(vector<int> &lista, int cant, int max){
    lista.clear();
    srand (time(NULL));
    for (int i=0; i<cant; i++){
        lista.push_back(rand() % max + 1);
    }
}

void vectorCharsRand(vector<char> &lista, int cant){
    lista.clear();
    srand (time(NULL));
    int r;
    for (int i=0; i<cant; i++) {
        r = rand() % 26;
        lista.push_back('a' + r);
    }
}

void vectorString(vector<string> &lista, int cantidad, char t) {
    lista.clear();
    string valor;
    if (t == 'c'){
        for (int i=0;i<cantidad;i++) {
            cout << "Teclea una palabra: " << endl;
            cin >> valor;
            lista.push_back(valor);
        }
    }
}

void vectorFracc(vector<Fraccion> &lista, int cantidad, char t) {
    lista.clear();
    int numerador, denominador;
    if (t == 'd'){
        for (int i=0;i<cantidad;i++) {
            cout << "Teclea el numerador: " << endl;
            cin >> numerador;
            cout << "Teclea el denominador: " << endl;
            cin >> denominador;
            lista.push_back(Fraccion(numerador,denominador));
        }
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
    char type = 'a';
    cout << "-- Creacion de Lista --" << endl;
    cout << "Que tipo de elementos quieres?" << endl;
    cout << "a - int" << endl;
    cout << "b - char" << endl;
    cout << "c - string" << endl;
    cout << "d - fraccion" <<  endl << ">> ";
    cin >> type;
    cout << "Cuantos elementos quieres?" << endl << ">> ";
    cin >> cant;
    vector<int> listaA;
    vectorNumerosRand(listaA, cant, 100);
    vector<char> listaB;
    vectorCharsRand(listaB, cant);
    vector<string> listaC;
    vectorString(listaC, cant, type);
    vector<Fraccion> listaD;
    vectorFracc(listaD, cant, type);

    cout << "Lista: " << endl;
    if (type == 'a') {
        cout << "int" << endl;
        Mostrar(listaA);
    }else if (type == 'b'){
        cout << "char" << endl;
        Mostrar(listaB);
    }else if (type == 'c'){
        Mostrar(listaC);
    }else if (type == 'd'){
        Mostrar(listaD);
    }else {
        return 0;
    }
    cout << endl;

    vector<int> listarandA;
    listarandA = listaA;
    vector<char> listarandB;
    listarandB = listaB;
    vector<string> listarandC;
    listarandC = listaC;
    vector<Fraccion> listarandD;
    listarandD = listaD;

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
        cout << "m - Mostrar lista original" << endl;
        cout << "h - Ayuda (mostrar este menu)" << endl;
        cout << "s - Salir" << endl << endl;
    }
    cout << ">> ";
    cin >> opt;

    listaA = listarandA;
    listaB = listarandB;
    listaC = listarandC;
    listaD = listarandD;
    comparaciones = 0;
    intercambios = 0;
    
    switch(opt){
    case 'a': {
        switch(type){
        case 'a':{
            clock_t start, end;
            start = clock();
            listaA = ordenaIntercambio(listaA, comparaciones, intercambios);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            cout << "Lista ordenada (Intercambio): " << endl;
            Mostrar(listaA);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        case 'b': {
            clock_t start, end;
            start = clock();
            listaB = ordenaIntercambio(listaB, comparaciones, intercambios);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            cout << "Lista ordenada (Intercambio): " << endl;
            Mostrar(listaB);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        case 'c': {
            clock_t start, end;
            start = clock();
            listaC = ordenaIntercambio(listaC, comparaciones, intercambios);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            cout << "Lista ordenada (Intercambio): " << endl;
            Mostrar(listaC);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        case 'd': {
            clock_t start, end;
            start = clock();
            listaD = ordenaIntercambio(listaD, comparaciones, intercambios);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            cout << "Lista ordenada (Intercambio): " << endl;
            Mostrar(listaD);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        default:
            break;
        }
        break;
    }
    case 'b': {
        switch(type){
        case 'a':{
            listaA = ordenaBurbuja(listaA, comparaciones, intercambios);
            cout << "Lista ordenada (Burbuja): " << endl;
            Mostrar(listaA);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        case 'b': {
            listaB = ordenaBurbuja(listaB, comparaciones, intercambios);
            cout << "Lista ordenada (Burbuja): " << endl;
            Mostrar(listaB);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        case 'c': {
            listaC = ordenaBurbuja(listaC, comparaciones, intercambios);
            cout << "Lista ordenada (Burbuja): " << endl;
            Mostrar(listaC);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        case 'd': {
            listaC = ordenaBurbuja(listaC, comparaciones, intercambios);
            cout << "Lista ordenada (Burbuja): " << endl;
            Mostrar(listaC);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        default:
            listaD = ordenaBurbuja(listaD, comparaciones, intercambios);
            cout << "Lista ordenada (Burbuja): " << endl;
            Mostrar(listaD);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        break;
    }
    case 'c': {
        switch(type){
        case 'a':{
            listaA = seleccionDirecta(listaA, comparaciones, intercambios);
            cout << "Lista ordenada (Seleccion Directa): " << endl;
            Mostrar(listaA);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        case 'b': {
            listaB = seleccionDirecta(listaB, comparaciones, intercambios);
            cout << "Lista ordenada (Seleccion Directa): " << endl;
            Mostrar(listaB);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        case 'c': {
            listaC = seleccionDirecta(listaC, comparaciones, intercambios);
            cout << "Lista ordenada (Seleccion Directa): " << endl;
            Mostrar(listaC);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        case 'd': {
            listaD = seleccionDirecta(listaD, comparaciones, intercambios);
            cout << "Lista ordenada (Seleccion Directa): " << endl;
            Mostrar(listaD);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        default:
            break;
        }
        break;
    }
    case 'd': {
        switch(type){
        case 'a':{
            listaA = ordenaInsercion(listaA, comparaciones, intercambios);
            cout << "Lista ordenada (Insercion): " << endl;
            Mostrar(listaA);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        case 'b': {
            listaB = ordenaInsercion(listaB, comparaciones, intercambios);
            cout << "Lista ordenada (Insercion): " << endl;
            Mostrar(listaB);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        case 'c': {
            listaC = ordenaInsercion(listaC, comparaciones, intercambios);
            cout << "Lista ordenada (Insercion): " << endl;
            Mostrar(listaC);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        case 'd': {
            listaD = ordenaInsercion(listaD, comparaciones, intercambios);
            cout << "Lista ordenada (Insercion): " << endl;
            Mostrar(listaD);
            cout << "Comparaciones: " << comparaciones << endl;
            cout << "Intercambios: " << intercambios << endl;
            break;
        }
        default:
            break;
        }
        break;
    }
    case 'e': {
        switch(type){
        case 'a':{
            clock_t start, end;
            start = clock();
            ordenaMerge(listaA, 0, listaA.size()-1, comparaciones);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            cout << "Lista ordenada (Merge): " << endl;
            Mostrar(listaA);
            cout << "Comparaciones: " << comparaciones << endl;
            break;
        }
        case 'b': {
            clock_t start, end;
            start = clock();
            ordenaMerge(listaB, 0, listaA.size()-1, comparaciones);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            cout << "Lista ordenada (Merge): " << endl;
            Mostrar(listaB);
            cout << "Comparaciones: " << comparaciones << endl;
            break;
        }
        case 'c': {
            clock_t start, end;
            start = clock();
            ordenaMerge(listaC, 0, listaA.size()-1, comparaciones);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            cout << "Lista ordenada (Merge): " << endl;
            Mostrar(listaC);
            cout << "Comparaciones: " << comparaciones << endl;
            break;
        }
        case 'd': {
            clock_t start, end;
            start = clock();
            ordenaMerge(listaD, 0, listaA.size()-1, comparaciones);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            cout << "Lista ordenada (Merge): " << endl;
            Mostrar(listaD);
            cout << "Comparaciones: " << comparaciones << endl;
            break;
        }
        default:
            break;
        }
        break;
    }
    case 'f': {
        switch(type){
        case 'a':{
            clock_t start, end;
            start = clock();
            quickSort(listaA, 0, listaA.size()-1, comparaciones);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            cout << "Lista ordenada (Quick Sort): " << endl;
            Mostrar(listaA);
            cout << "Comparaciones: " << comparaciones << endl;
            break;
        }
        case 'b': {
            clock_t start, end;
            start = clock();
            quickSort(listaB, 0, listaB.size()-1, comparaciones);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            cout << "Lista ordenada (Quick Sort): " << endl;
            Mostrar(listaB);
            cout << "Comparaciones: " << comparaciones << endl;
            break;
        }
        case 'c': {
            clock_t start, end;
            start = clock();
            quickSort(listaC, 0, listaC.size()-1, comparaciones);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            cout << "Lista ordenada (Quick Sort): " << endl;
            Mostrar(listaC);
            cout << "Comparaciones: " << comparaciones << endl;
            break;
        }
        case 'd': {
            clock_t start, end;
            start = clock();
            quickSort(listaD, 0, listaD.size()-1, comparaciones);
            end = clock();
            double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
            cout << "Execution time: " << fixed << time_taken << setprecision(5) << " sec " << endl;
            cout << "Lista ordenada (Quick Sort): " << endl;
            Mostrar(listaD);
            cout << "Comparaciones: " << comparaciones << endl;
            break;
        }
        default:
            break;
        }
        break;
    }
    case '1': {
        switch(type){
        case 'a':{
            int nA, pos;
            cout << "Que numero quieres buscar en la lista? (secuencial) " << endl << ">> ";
            cin >> nA;
            cout << "Lista:" << endl;
            Mostrar(listaA);
            pos = busquedaSecuencial(listaA, nA, comparaciones);
            if (pos != -1){
                cout << "Posicion del numero: [" << pos << "]" << endl;
            }else {
                cout << "Numero no en la lista" << endl;
            }
            break;
        }
        case 'b': {
            char nB;
            int pos;
            cout << "Que letra quieres buscar en la lista? (secuencial) " << endl << ">> ";
            cin >> nB;
            cout << "Lista:" << endl;
            Mostrar(listaB);
            pos = busquedaSecuencial(listaB, nB, comparaciones);
            if (pos != -1){
                cout << "Posicion de la letra: [" << pos << "]" << endl;
            }else {
                cout << "Letra no en la lista" << endl;
            }
            break;
        }
        case 'c': {
            string nC;
            int pos;
            cout << "Que palabra quieres buscar en la lista? (secuencial) " << endl << ">> ";
            cin >> nC;
            cout << "Lista:" << endl;
            Mostrar(listaC);
            pos = busquedaSecuencial(listaC, nC, comparaciones);
            if (pos != -1){
                cout << "Posicion de la palabra: [" << pos << "]" << endl;
            }else {
                cout << "Palabra no en la lista" << endl;
            }
            break;
        }
        case 'd': {
            int numerador, denominador;
            int pos;
            cout << "Que fraccion quieres buscar en la lista? (secuencial) " << endl << ">> ";
            cout << "Teclea el numerador: " << endl;
            cin >> numerador;
            cout << "Teclea el denominador: " << endl;
            cin >> denominador;
            Fraccion nD(numerador, denominador);
            cout << "Lista:" << endl;
            Mostrar(listaD);
            pos = busquedaSecuencial(listaD, nD, comparaciones);
            if (pos != -1){
                cout << "Posicion de la fraccion: [" << pos << "]" << endl;
            }else {
                cout << "Fraccion no en la lista" << endl;
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    case '2': {
        switch(type){
        case 'a':{
            int nA, pos;
            listaA = ordenaInsercion(listaA, comparaciones, intercambios);
            comparaciones = 0;
            cout << "Que numero quieres buscar en la lista? (binaria) " << endl << ">> ";
            cin >> nA;
            cout << "Lista:" << endl;
            Mostrar(listaA);
            pos = busquedaBinaria(listaA, nA, comparaciones);
            if (pos != -1){
                cout << "Posicion del numero: [" << pos << "]" << endl;
            }else {
                cout << "Numero no en la lista" << endl;
            }
            break;
        }
        case 'b': {
            char nB;
            int pos;
            listaB = ordenaInsercion(listaB, comparaciones, intercambios);
            comparaciones = 0;
            cout << "Que letra quieres buscar en la lista? (binaria) " << endl << ">> ";
            cin >> nB;
            cout << "Lista:" << endl;
            Mostrar(listaB);
            pos = busquedaBinaria(listaB, nB, comparaciones);
            if (pos != -1){
                cout << "Posicion de la letra: [" << pos << "]" << endl;
            }else {
                cout << "Letra no en la lista" << endl;
            }
            break;
        }
        case 'c': {
            string nC;
            int pos;
            listaC = ordenaInsercion(listaC, comparaciones, intercambios);
            comparaciones = 0;
            cout << "Que palabra quieres buscar en la lista? (binaria) " << endl << ">> ";
            cin >> nC;
            cout << "Lista:" << endl;
            Mostrar(listaC);
            pos = busquedaBinaria(listaC, nC, comparaciones);
            if (pos != -1){
                cout << "Posicion de la palabra: [" << pos << "]" << endl;
            }else {
                cout << "Palabra no en la lista" << endl;
            }
            break;
        }
        case 'd': {
            int numerador, denominador;
            int pos;
            listaD = ordenaInsercion(listaD, comparaciones, intercambios);
            comparaciones = 0;
            cout << "Que fraccion quieres buscar en la lista? (binaria) " << endl;
            cout << "Teclea el numerador: " << endl;
            cin >> numerador;
            cout << "Teclea el denominador: " << endl;
            cin >> denominador;
            Fraccion nD(numerador, denominador);
            cout << "Lista:" << endl;
            Mostrar(listaD);
            pos = busquedaBinaria(listaD, nD, comparaciones);
            if (pos != -1){
                cout << "Posicion de la fraccion: [" << pos << "]" << endl;
            }else {
                cout << "Fraccion no en la lista" << endl;
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    case 'm': {
        switch(type){
        case 'a':{
            Mostrar(listarandA);
            break;
        }
        case 'b': {
            Mostrar(listarandB);
            break;
        }
        case 'c': {
            Mostrar(listarandC);
            break;
        }
        case 'd': {
            Mostrar(listarandD);
            break;
        }
        default:
            break;
        }
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
