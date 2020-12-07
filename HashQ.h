#ifndef HashQ_H
#define HashQ_H

class HashQ {
private:
    vector<string> table;
    vector<int> status; // 0-Vacía 1-Ocupada 2-Borrada
    int size;
    int qty;
    int hashing(string data);
    bool isFull();
    int quadTest(int index);
    int quadProbe(int index, int cont);
public:
    HashQ();
    HashQ(int size);
    HashQ(vector<string> list);
    int findData(string data);
    void addData(string data);
    void deleteData(string data);
    string dataInIndex(int index);
    void printHash();
};

HashQ::HashQ() {
    size = 0;
}

HashQ::HashQ(int size) {
    this->size = size;
    qty = 0;
    // Crea la tabla con datos por default del tamaño de la lista
    vector<string> tmpTable(size);
    table = tmpTable;
    // Crea la tabla de status con valor de 0 (vacío) con tamaño de la lista
    vector<int> tmpStatus(size, 0);
    status = tmpStatus;
}

HashQ::HashQ(vector<string> list) {
    size = list.size();
    qty = 0;
    // Crea la tabla con datos por default del tamaño de la lista
    vector<string> tmpTable(size);
    table = tmpTable;
    // Crea la tabla de status con valor de 0 (vacío) con tamaño de la lista
    vector<int> tmpStatus(size, 0);
    status = tmpStatus;
    for (auto data : list) {
        addData(data);
    }
}

int HashQ::quadTest(int index) {
    if (status[index] == 0 || status[index] == 2) {
        return index;
    }
    int cont = 1;
    int newIndex = index;
    while (status[newIndex] == 1) {
        newIndex = (index + cont * cont) % size;
        cont ++;
    }
    return newIndex;
}

int HashQ::quadProbe(int index, int cont) {
    return fmod(index + int(pow(-1,cont-1)) * int(pow((cont+1)/2,2)),size);
}

int HashQ::hashing(string data) {
    int len = data.length();
    int key;
    if (len == 1) {
        key = int(data[0]);
    } else {
        if (len == 2) {
            key = int(data[0]) + int(data[1]);
        } else {
            if (len >= 3) {
                key = int(data[1]) + int(data[2]);
            }
        }
    }
    return key%size;
}

void HashQ::addData(string data) {
    if (!isFull()) {
        int index = hashing(data);
        if (status[index] == 0 || status[index] == 2) {
            table[index] = data;
            status[index] = 1;
            qty++;
        } else {
            int cont = 1;
            int newIndex = quadProbe(index, cont);
            while (status[newIndex] == 1) {
                if (data == table[newIndex]) {
                    throw runtime_error("El valor ya exite en la tabla");
                }
                cont++;
                newIndex = quadProbe(index, cont);
            }
            table[newIndex] = data;
            status[newIndex] = 1;
            qty++;
        }       
    } else {
        throw out_of_range("La tabla ya esta llena");
    }
}

int HashQ::findData(string data) {
    int cont = 1;
    int index = hashing(data);
    while (status[index] != 0 && cont < size) {
        if (status[index] == 1 && table[index] == data) {
            return index;
        }
        index = quadProbe(index,cont);
        cont++;
    }
    return -1;
}

string HashQ::dataInIndex(int index) {
    return table[index];
}

bool HashQ::isFull() {
    return size == qty;
}

void HashQ::printHash() {
    cout << "Hash Table" << endl;
    for (auto str : table){
        cout << str << endl;
    }
}

#endif