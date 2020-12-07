#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <math.h>
using namespace std;

#include "Graph.h"

int funcHashing(string data, int size, int &key) {
    // Define key
    key = 0;
    for (auto c : data) {
        key += abs(int(c));
    }
    return key%size; // Residual
}

int main()
{
    //Variables iniciales
    ifstream bitacora ("bitacoraACT4_test.txt");
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
    list.pop_back();
    
    //Creación de Lista de Adyacencias con todos los IPs de Origen y Destino
    Graph<string> graph(list, vertices, n, m);

    graph.print();
    graph.test();
    return 0;
}
