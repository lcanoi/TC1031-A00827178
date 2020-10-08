#ifndef DLL_H
#define DLL_H

#include "datos.h"
#include "Node.h"

template<class T>
class DLL {
public:
    DLL();
    T& operator[](int index);
    int numFecha (int m, int d, int h, int min, int s);
    string stringMes (int m);
    void addFront(T newData);
    void addBack(T newData);
    void queue(T newData);
    T getData(int index);
    void updateAt(T newData, int index);
    void merge(int ini, int mid, int fin);
    void mergeSort(int ini, int fin);
    void sort();
    void binarySearchRange(DLL<T> list, int mesI, int diaI, int horaI, int mesF, int diaF, int horaF, int &posI, int &posF);
    int getSize();
    void printRange(DLL<T> list, int posI, int posF);
private:
    Node<T> *head, *tail;
    int size;
};

//Constructor
template<class T>
DLL<T>::DLL() {
    head = NULL;
    tail = NULL;
    size = 0;
}

//Sobrecarga de operador []
template<class T>
T& DLL<T>::operator[](int index){
    if (index >= 1 && index <= size){
        Node<T>* aux = head;
        int i = 1;
        while (aux != NULL){
            if (i == index){
                return aux->data;
            }
            aux = aux->next;
            i++;
        }
    }
    throw out_of_range("Position invalid");
}

//Convierte una fecha y hora a un solo valor numérico
template<class T>
int DLL<T>::numFecha (int m, int d, int h, int min, int s){
    min = 100 * min;
    h = 10000 * h;
    d = 1000000 * d;
    m = 100000000 * m;
    return (m + d + h + min + s);
}

//Convierte a los números en meses
template<class T>
string DLL<T>::stringMes (int m){
    if (m == 6){
        return "Jun";
    }else if (m == 7){
        return "Jul";
    }else if (m == 8){
        return "Aug";
    }else if (m == 9){
        return "Sep";
    }else if (m == 10){
        return "Oct";
    }
    return "";
}

//Agrega un elemento en la head de la lista
template<class T>
void DLL<T>::addFront(T newData){
    Node<T>* new_node = new Node<T>(newData);
    new_node->next = head; 
    new_node->prev = NULL; 
  
    if ((head) != NULL) 
        head->prev = new_node; 

    head = new_node; 
    size++;
}

//Agrega un elemento en el final de la lista
template<class T>
void DLL<T>::addBack(T newData){
    Node<T>* new_node = new Node<T>(newData); 
    Node<T>* last = head;
    new_node->next = NULL; 
  
    if (head == NULL) { 
        new_node->prev = NULL; 
        head = new_node; 
        size++;
        return; 
    } 
  
    while (last->next != NULL) 
        last = last->next; 
  
    last->next = new_node; 
    new_node->prev = last; 
    size++;
    return;  
}

//Agrega elementos al tail de la lista usando queue
template<class T>
void DLL<T>::queue(T newData){
    Node<T>* newNode = new Node<T>(newData); 
    if (tail == NULL) { 
        newNode->prev = NULL; 
        head = tail = newNode; 
        size++;
        return; 
    } else {
        newNode->prev = tail; 
        tail->next = newNode; 
        tail = newNode; 
        size++;
        return;
    }
}

//Regresa la data en la posición index de la lista
template<class T>
T DLL<T>::getData(int index){
    if (index >= 1 && index <= size){
        Node<T>* aux = head;
        int i = 1;
        while (aux != NULL){
            if (i== index){
                return aux->data;
            }
            aux = aux->next;
            i++;
        }
    }
    throw out_of_range("Position invalid");
}

//Actualiza la data a newData en la posición index de la lista
template<class T>
void DLL<T>::updateAt(T newData, int index){
    if (index >= 1 && index <= size){
        Node<T>* aux = head;
        int i = 1;
        while (aux != NULL){
            if (i== index){
                aux->data = newData;
                return;
            }
            aux = aux->next;
            i++;
        }
    }
    throw out_of_range("Position invalid updateat");
}

//Método utilizado para merge sort, combina las listas divididas de manera ordenada 
template<class T>
void DLL<T>::merge(int ini, int mid, int fin){
    DLL<T> listL;
    DLL<T> listR;
    int pos, f1, f2, i, j;
    pos = ini;
    f1 = mid - ini + 1;
    f2 = fin - mid;
    for (i=1; i <= f1; i++){
        listL.queue(getData(ini+i-1));
    }
    for (j=1; j <= f2; j++){
        listR.queue(getData(mid+1+j-1));
    }
    i = 1;
    j = 1;
    while(i <= f1 && j <= f2){
        if (numFecha(listL[i].mes, listL[i].dia, listL[i].hora, listL[i].min, listL[i].seg) <= 
            numFecha(listR[j].mes, listR[j].dia, listR[j].hora, listR[j].min, listR[j].seg)){
            updateAt(listL[i], pos);
            i++;
        }else {
            updateAt(listR[j], pos);
            j++;
        }
        pos++;
    }
    while (i <= f1) { 
        updateAt(listL[i], pos);
        i++; 
        pos++; 
    } 
    while (j <= f2) { 
        updateAt(listR[j], pos);
        j++; 
        pos++; 
    } 
}

//Método utilizado para merg sort, recursivamente divide la lista en mitades
template<class T>
void DLL<T>::mergeSort(int ini, int fin){
    if (ini < fin) {
        int mid = (ini + fin) / 2;
        mergeSort(ini, mid);
        mergeSort(mid+1, fin);

        merge(ini, mid, fin);
    }
}

//Inicializa el método de merge sort, organizando la lista desde la posición 1 hasta el final de la lista (size)
template<class T>
void DLL<T>::sort(){
    mergeSort(1,size);
}

//Realiza una búsqueda binaria para encontrar las fechas que se encuentren entre los rangos solicitados
//Resultado: posI y posF - Posición inicial y final en la lista de datos ordenados
//Estas posiciones delimitan el rango de fechas deseado
template<class T>
void DLL<T>::binarySearchRange(DLL<T> list, int mesI, int diaI, int horaI, int mesF, int diaF, int horaF, int &posI, int &posF){
    int mid, low, high;
    low = 0;
    high = size;
    int texto = 0;
    while (low <= high){
        mid = (low + high) / 2;
        if (numFecha(mesI, diaI, horaI, 0, 0) < numFecha(list[mid].mes, list[mid].dia, list[mid].hora, 0, 0)){
            high = mid - 1;
        } else if (numFecha(mesI, diaI, horaI, 0, 0) > numFecha(list[mid].mes, list[mid].dia, list[mid].hora, 0, 0)){
            low = mid + 1;
        } else {
            break;
        }
    }
    //Pueden haber varias entradas de la bitácota con el mismo mes/día/hora, por lo cual se 
    //revisan las entradas anteriores hasta que no sean iguales para determinar la posI
    while (numFecha(list[mid].mes, list[mid].dia, list[mid].hora, 0, 0) == 
        numFecha(list[mid-1].mes, list[mid-1].dia, list[mid-1].hora, 0, 0)){
        mid--;
    }
    low = mid;
    posI = low;
    high = size;
    while (low <= high){
        mid = (low + high) / 2;
        if (numFecha(mesF, diaF, horaF, 0, 0) < numFecha(list[mid].mes, list[mid].dia, list[mid].hora, 0, 0)){
            high = mid - 1;
        } else if (numFecha(mesF, diaF, horaF, 0, 0) > numFecha(list[mid].mes, list[mid].dia, list[mid].hora, 0, 0)){
            low = mid + 1;
        } else{
            break;
        }
    }
    while (numFecha(list[mid].mes, list[mid].dia, list[mid].hora, 0, 0) == 
        numFecha(list[mid+1].mes, list[mid+1].dia, list[mid+1].hora, 0, 0)){
        mid++;
    }
    posF = mid + 1;
}

//Regresa el tamaño de la lista
template<class T>
int DLL<T>::getSize(){
    return size;
}

//Imprime los datos de la lista entre los rangos posI y posF
template<class T>
void DLL<T>::printRange(DLL<T> list, int posI, int posF){
    for (int i = posI; i < posF; i++){
        cout << stringMes(list[i].mes) << " " << list[i].dia << " " << list[i].hora  << ":" << list[i].min 
        << ":" << list[i].seg << " " << list[i].ip << " " << list[i].razon << endl;
    }
}


#endif