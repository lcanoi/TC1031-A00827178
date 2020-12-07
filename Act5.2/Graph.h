#ifndef Graph_H
#define Graph_H

#include "HashQ.h"

template<class T>
class Graph {
private:
    vector<vector<T>> adjList;
    vector<T> vertices;
    HashQ hashVertices;
    int qtyVertices;
    int qtyEdges;
    int findVertex(T vertex, vector<T> verticesTemp);
    void dfsR(T vertex, vector<bool> &status);
public:
    Graph(vector<vector<T>> list, vector<T> vert, int qtyVertices, int qtyEdges);
    void print();
    void printVertice(T ip);
    void bfs();
    void dfs();
    void printHash();
};

//Constructor
//Crea una Hash Table con los vertices
//Luego crea la lista de vertices y la lista de adyacencias organizadas en el orden de la Hash Table
template<class T>
Graph<T>::Graph(vector<vector<T>> list, vector<T> vert, int qtyVertices, int qtyEdges){
    HashQ tempV(vert);
    hashVertices = tempV;
    this->qtyVertices = qtyVertices;
    this->qtyEdges = qtyEdges;
    int source = 0;
    int target = 1;

    for (int i = 0; i<qtyVertices; i++) {
        vertices.push_back(hashVertices.dataInIndex(i));
    }

    vector< vector<T> > listTemp(qtyVertices);
    adjList = listTemp;
    vector<T> vertTemp;
    for (vector<T> edge : list){
        T temp = edge[source];
        int pos = hashVertices.findData(temp);
        int posV = findVertex(temp,vertTemp);
        if (posV < 0) {
            vertTemp.push_back(temp);
            adjList[pos] = edge;
        } else {
            adjList[pos].push_back(edge[target]);
        }
    }
    if (vertTemp.size() < qtyVertices) {
        for (vector<T> edge : list) {
            T temp = edge[target];
            int pos = hashVertices.findData(temp);
            int posV = findVertex(temp,vertTemp);
            if (posV < 0) {
                vertTemp.push_back(temp);
                vector<T> tempVertex;
                tempVertex.push_back(temp);
                adjList[pos] = tempVertex;
            }
        }
    }
}

//Busca un dato en un vector, si lo encuentra regresa su posición, si no regresa -1
template<class T>
int Graph<T>::findVertex(T vertex, vector<T> verticesTemp){
    typename vector<T>::iterator it;
    it = find(verticesTemp.begin(), verticesTemp.end(), vertex);
    if (it != verticesTemp.end()){
        return it - verticesTemp.begin();
    } else {
        return -1;
    }
}

//Imprime la lista de adyacencias en un archivo de salida: printLista.txt
template<class T>
void Graph<T>::print(){
    ofstream salida("printLista.txt");
    for (vector<T> vertex : adjList) {
        bool firstV = true;
        for (T node : vertex) {
            if (firstV) {
                salida << node << " -> ";
                firstV = false;
            } else {
                salida << node << " ";
            }
        }
        salida << endl;
    }
    salida.close();
}

//Utiliza la funcion de findData de HashQ.h para encontrar la posición en la adjList de un ip solicitado
//Luego imprime ese ip y todas sus adyacencias
template<class T>
void Graph<T>::printVertice(T ip){
    int index = hashVertices.findData(ip);
    if (index >= 0) {
        bool firstV = true;
        for (auto node : adjList[index]) {
            if (firstV) {
                cout << node << " -> ";
                firstV = false;
            } else {
                cout << node << " ";
            }
        }
        cout << endl;
    } else {
        cout << "Ip No Encontrado" << endl;
    }
}

//Llama a la función de HashQ.h para imprimir a la Hash Table
template<class T>
void Graph<T>::printHash() {
    hashVertices.printHash();
}

template<class T>
void Graph<T>::bfs() {
    queue<int> q;
    vector<bool> status(vertices.size(),false);
    int vertex = 0;
    q.push(vertex);
    status[vertex] = true;
    while (!q.empty()) {
        vertex = q.front();
        cout << vertices[vertex] << " ";
        for (int adj=0; adj<adjList[vertex].size(); adj++) {
            int pos = findVertex(adjList[vertex][adj], vertices);
            if(!status[pos]) {
                q.push(pos);
                status[pos] = true;
            }
        }
        q.pop();
    }
    cout << endl;
}

template<class T>
void Graph<T>::dfs() {
    vector<bool> status(vertices.size(),false);
    dfsR(vertices[0],status);
}

template<class T>
void Graph<T>::dfsR(T vertex, vector<bool> &status) {
    int pos = findVertex(vertex, vertices);
    if (!status[pos]) {
        cout << vertex << " ";
        status[pos] = true;
    }
    for (auto adj : adjList[pos]) {
        int posAdj = findVertex(adj, vertices);
        if (!status[posAdj]) {
            dfsR(adj,status);
        }
    }
}

#endif