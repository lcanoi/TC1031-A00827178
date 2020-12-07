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
    int findVertex(T vertex);
    void dfsR(T vertex, vector<bool> &status);
public:
    Graph(vector<vector<T>> list, vector<T> vert, int qtyVertices, int qtyEdges);
    void print();
    void printVertice(T ip);
    void bfs();
    void dfs();
    void test();
};

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
    int pos;
    bool inTemp = false;
    for (vector<T> edge : list){
        T temp = edge[source];
        pos = hashVertices.findData(temp);
        for (auto vert : vertTemp) {
            if (vert == temp) {
                inTemp = true;
            }
        }
        if (!inTemp) {
            vertTemp.push_back(temp);
            adjList[pos] = edge;
        } else {
            adjList[pos].push_back(edge[target]);
            inTemp = false;
        }
    }
    if (vertTemp.size() < qtyVertices) {
        for (vector<T> edge : list) {
            T temp = edge[target];
            pos = hashVertices.findData(temp);
            for (auto vert : vertTemp) {
                if (vert == temp) {
                    inTemp = true;
                }
            }
            if (!inTemp) {
                vertTemp.push_back(temp);
                vector<T> tempVertex;
                tempVertex.push_back(temp);
                adjList[pos] = tempVertex;
            }
        }
    }
}

template<class T>
int Graph<T>::findVertex(T vertex){
    typename vector<T>::iterator it;
    it = find(vertices.begin(), vertices.end(), vertex);
    if (it != vertices.end()){
        return it - vertices.begin();
    } else {
        return -1;
    }
}

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

template<class T>
void Graph<T>::printVertice(T ip){
    for (vector<T> vertex : adjList) {
        bool firstV = true;
        T temp = vertex[0];
        if (ip == temp) {
            for (T node : vertex) {
                if (firstV) {
                    cout << node << " -> ";
                    firstV = false;
                } else {
                    cout << node << " ";
                }
            }
        }
    }
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
            int pos = findVertex(adjList[vertex][adj]);
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
    int pos = findVertex(vertex);
    if (!status[pos]) {
        cout << vertex << " ";
        status[pos] = true;
    }
    for (auto adj : adjList[pos]) {
        int posAdj = findVertex(adj);
        if (!status[posAdj]) {
            dfsR(adj,status);
        }
    }
}

template<class T>
void Graph<T>::test() {
    hashVertices.printHash();
}

#endif