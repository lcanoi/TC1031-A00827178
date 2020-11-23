#ifndef Graph_H
#define Graph_H

template<class T>
class Graph {
private:
    vector<vector<T>> adjList;
    vector<T> vertices;
    int qtyVertices;
    int qtyEdges;
    int findVertex(T vertex);
    void dfsR(T vertex, vector<bool> &status);
public:
    Graph(vector<vector<T>> list, int qtyVertices, int qtyEdges);
    void print();
    void printVertice(T ip);
    void bfs();
    void dfs();
};

template<class T>
Graph<T>::Graph(vector<vector<T>> list, int qtyVertices, int qtyEdges){
    this->qtyVertices = qtyVertices;
    this->qtyEdges = qtyEdges;
    int source = 0;
    int target = 1;
    for (vector<T> edge : list){
        T temp = edge[source];
        int pos = findVertex(temp);
        if (pos >= 0) {
            adjList[pos].push_back(edge[target]);
        } else {
            vertices.push_back(temp);
            adjList.push_back(edge);
        }
    }
    if (vertices.size() < qtyVertices) {
        for (vector<T> edge : list) {
            T temp = edge[target];
            int pos = findVertex(temp);
            if (pos<0) { // not found
                vertices.push_back(temp);
                vector<T> tempVertex;
                tempVertex.push_back(temp);
                adjList.push_back(tempVertex);
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

#endif