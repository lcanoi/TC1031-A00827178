#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>
#include <bits/stdc++.h>

using namespace std;

#include "Graph.h"
#include "Heap.h"
#include "datos.h"
#include "adyacencias.h"

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
//Llena la lista de adyacencias con los IPs diferentes y la cantidad de IPs adyacentes de cada uno
void groupIp(DoublyLinkedList<datos> aux, DoublyLinkedList<adyacencias>& listA) {
    string current, prev;
    prev = "";
    int cant, n;
    n = 0;
    for (int i = 1; i <= aux.getSize(); i++) {
        current = aux[i].ipO;
        if (current != prev) {
            cant = 1;
            listA.addLast(adyacencias(current, cant));
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
    ifstream bitacora ("bitacoraACT4_3.txt");
    string mes, diaS, hora, ipO, puertoO, ipD, puertoD, razon, nS, mS, ipV;
    int n, m, dia;
    vector<string> vertices;
    vector<vector<string>> list;
    vector<string> li;
    DoublyLinkedList<datos> listD;

    cout << endl << "Favor de esperar unos segundos mientras ordenamos los datos ..." << endl << endl;

    //Almacenamiento de los datos de la bitacora
    int i = 0;
    if(bitacora.is_open()){
        while (!bitacora.eof()){
            if (i==0) {
                getline(bitacora, nS, ' ');
                n = stoi(nS);
                getline(bitacora, mS, '\n');
                m = stoi(mS);
                i++;
            }
            else if (i<=n) {
                getline(bitacora, ipV, '\n');
                vertices.push_back(ipV);
                i++;
            }
            else if (i>n) {
                getline(bitacora, mes, ' ');
                getline(bitacora, diaS, ' ');
                dia = stoi(diaS);
                getline(bitacora, hora, ' ');
                getline(bitacora, ipO, ':');
                getline(bitacora, puertoO, ' ');
                getline(bitacora, ipD, ':');
                getline(bitacora, puertoD, ' ');
                getline(bitacora, razon, '\n');
                li.push_back(ipO);
                li.push_back(ipD);
                list.push_back(li);
                li.clear();
                listD.addLast(datos(mes, dia, hora, ipO, puertoO, ipD, puertoD, razon));
            }
        }
    }

    //Creación de Lista de Adyacencias con todos los IPs de Origen y Destino
    Graph<string> graph(list, n, m);

    //Los datos de listD se ordenan por su ip origen
    //Luego se agrupan los registros por su ip origen (vertice) con la cantidad de adyacencias que tiene
    HeapSort(listD, 'a');
    DoublyLinkedList<adyacencias> listA;
    groupIp(listD, listA);

    //Almacenamiento de los datos de listA en un Binary Heap
    Heap<adyacencias> heapA(listA);
    
    char opt = 'h';
    char optP = 'n';
    while (opt != 'x') {
        if (opt == 'h') {
            cout << "       -- Menu --       " << endl;
            cout << "________________________" << endl << endl;
            cout << "Lista de adyacencias" << endl;
            cout << "   a - IP con mas Adyacencias" << endl;
            cout << "   b - Print Graph" << endl << endl;
            cout << "h - Mostrar este Menu" << endl;
            cout << "x - Salir del programa" << endl << endl;
        }
        cout << ">> ";
        cin >> opt;
        switch (opt) {
            case 'a' : {
                //Impresión del IP con mas Adyacencias
                auto end = chrono::system_clock::now();
                time_t end_time = chrono::system_clock::to_time_t(end);
                cout << "Resultados de consulta realizada en - " << ctime(&end_time) << endl;
                cout << "IP con mas adyacentes:" << endl << endl;
                cout << "IP  Cantidad" << endl;
                adyacencias A = heapA.remove();
                cout << A.ipO << "   " << A.cant << endl << endl;
                cout << "Adyacencias de {" << A.ipO << "}" << endl;
                graph.printVertice(A.ipO);
                cout << endl << endl;
                system("pause");
                break;
            }
            case 'b' : {
                
                cout << "La Lista de Adyacencias se imprimira de manera ordenada en un nuevo archivo llamado printLista.txt" << endl;
                cout << "Desea continuar? (s/n) >> ";
                cin >> optP;
                if (optP == 's' || optP == 'S') {
                    graph.print();
                    cout << "Archivo Listo" << endl;
                } else {
                    cout << "Operacion Cancelada..." << endl;
                }
                break;
            }
            default:
                break;
        }
        cout << endl;
    }

    bitacora.close();

    cout << endl << "... Cerrando programa ..." << endl << endl;

    return 0;
}
