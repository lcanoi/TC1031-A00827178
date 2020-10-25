// Luis Cano Irigoyen  -  A00827178  -  25-Oct-2020  -  TC1031.10
// Act 3.4 - Actividad Integral de BST (Evidencia Competencia)
#include <iostream>
using namespace std;
#include <conio.h>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>

#include "Heap.h"
#include "datos.h"
#include "accesos.h"

//Función de Heap sort
//Hace uso de la función downSort en Heap.h para ordenar la lista
//Puede ordenarse de manera ascendiente o descendiente
template<class T>
void HeapSort(DoublyLinkedList<T>& list, char order) {
    Heap<T> heapAux(list);
    list.clear();
    while (!heapAux.isEmpty()) {
        if (order == 'a') {
            list.addFirst(heapAux.remove());
        } else {
            list.addLast(heapAux.remove());
        }
    }
}

//Función groupIP
//Llena la lista de accesos con los IPs diferentes y la cantidad de veces que fue accedido cada uno
void groupIp(DoublyLinkedList<datos> aux, DoublyLinkedList<accesos>& listA) {
    string current, prev;
    prev = "";
    int cant, n;
    n = 0;
    for (int i = 1; i <= aux.getSize(); i++) {
        current = aux[i].ip.substr(0, aux[i].ip.find(":"));
        if (current != prev) {
            cant = 1;
            listA.addLast(accesos(current, cant));
            prev = current;
            n++;
        } else {
            listA[n].cant = ++cant;
        }
    }
}

int main()
{
    //Variables iniciales
    ifstream bitacora ("bitacora2.txt");
    string mes, diaS, hora, ip, razon;
    int dia;
    DoublyLinkedList<datos> listD;

    cout << endl << "Favor de esperar unos segundos mientras ordenamos los datos ..." << endl << endl;

    //Almacenamiento de datos en la Doubly Linked List
    if(bitacora.is_open()){
        while (!bitacora.eof()){
            getline(bitacora, mes, ' ');
            getline(bitacora, diaS, ' ');
            dia = stoi(diaS);
            getline(bitacora, hora, ' ');
            getline(bitacora, ip, ' ');
            getline(bitacora, razon, '\n');
            listD.addLast(datos(mes, dia, hora, ip, razon));
        }
    }

    //Heap sort de los datos en listD ordenados acendientemente por su ip:port
    HeapSort(listD, 'a');

    //Agrupación de registros por su ip (sin considerar su port)
    DoublyLinkedList<accesos> listA;
    groupIp(listD, listA);

    //Almacenamiento de los datos de listA en un Binary Heap
    Heap<accesos> heapA(listA);
    
    //Impresión de los 5 IPs con más accesos
    auto end = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "Resultados de consulta realizada en - " << ctime(&end_time) << endl;
    cout << "Los 5 IPs con mas accesos fallidos:" << endl << endl;
    cout << "IP              Cantidad" << endl;
    accesos A;
    for (int i = 0; i < 5; i++) {
        A = heapA.remove();
        cout << A.ip << "   " << A.cant << endl;
    }
    
    cout << endl << "Presiona Enter para continuar...";
    getch();
    cout << endl << endl;

    bitacora.close();

    cout << "... Cerrando programa ..." << endl << endl;

    return 0;
}
