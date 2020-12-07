#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <math.h>
#include <chrono>
#include <ctime>
using namespace std;

#include "Graph.h"

int main()
{
    //Variables iniciales
    /*Tuve problemas al correr el código con la bitacoraACT4_3, esto a pesar de verificar que funcionara
    bien con casos diferentes, guardando todos los datos en el Grafo con su Tabla Hashing de manera correcta y 
    encontrando un IP específico con el uso del findData de HashQ.h.

    Al intentar correr el código con la bitacoraACT4_3, el código simplemente dejaba de correr en diferentes puntos:
    Dejo de correr antes de entrar al graph, antes de crear la hash table en el graph, dentro del constructor del
    hash, mas adelante dentrod el constructos del graph...
    Pero siempre parando el código por completo tras pocos segundos (menos de 10s) y solamente al correrlo con la 
    bitacoraACT4_3, con archivos más pequeños siempre funcionó.

    Por esta razon el código se corre con una version reducida de la bitacora, bitacoraAcT4_test.
    Ambos archivos se incluyen en el .zip (original y prueba) por si se desea probar con la bitacora original, 
    solo hay que comentar la linea del test y descomentar la linea de la original... */
    ifstream bitacora ("bitacoraACT4_test.txt");
    //ifstream bitacora ("bitacoraACT4_3.txt");
    string mes, diaS, hora, ipO, puertoO, ipD, puertoD, razon, nS, mS, ipV;
    int n, m, dia;
    vector<string> vertices;
    vector<vector<string>> list;
    vector<string> li;

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
            }
        }
    }
    //list.pop_back();
    
    //Creación de Lista de Adyacencias con todos los IPs de Origen y Destino
    //La clase de Graph está modificada para ordenarse como un Hash Table con Quadratic Probing
    Graph<string> graph(list, vertices, n, m);

    //Interfaz de usuario
    //Su función principal es imprimir las adyacencias de un IP dado (a)
    //Cuenta con las funciones para imprimir la Lista de Adyacencias y el Hash Cuadrático en archivos de salida
    char opt = 'h';
    char optP;
    string data;
    while (opt != 'x') {
        if (opt == 'h') {
            cout << "       -- Menu --       " << endl;
            cout << "________________________" << endl << endl;
            cout << "Lista de adyacencias" << endl;
            cout << "   a - Print Adyacencias de un IP" << endl;
            cout << "   b - Print Graph" << endl;
            cout << "   c - Print Hash Quadratic" << endl << endl;
            cout << "h - Mostrar este Menu" << endl;
            cout << "x - Salir del programa" << endl << endl;
        }
        cout << ">> ";
        cin >> opt;
        optP = 'n';
        switch (opt) {
            case 'a' : {
                cout << "Escribe el IP del cual quieras obtener sus adyacencias: " << endl;
                cout << "(Si estas usando el archivo de test puedes encontrar los IPs posibles en bitacoraACT4_test.txt)" << endl;
                cin >> data;
                auto end = chrono::system_clock::now();
                time_t end_time = chrono::system_clock::to_time_t(end);
                cout << endl << "Resultados de consulta realizada en - " << ctime(&end_time) << endl;
                cout << "Adyacencias de " << data << " :" << endl;
                graph.printVertice(data);
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
            case 'c' : {
                cout << "El Hash Quadratic se imprimira de manera ordenada en un nuevo archivo llamado printHash.txt" << endl;
                cout << "Desea continuar? (s/n) >> ";
                cin >> optP;
                if (optP == 's' || optP == 'S') {
                    graph.printHash();
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
