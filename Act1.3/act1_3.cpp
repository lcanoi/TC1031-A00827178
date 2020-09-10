//Luis Cano Irigoyen  -  A00827178  -  10-Sep-2020  -  TC1031.10
//Act 1.3 - Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;

//Struct para almacenar todos los datos del archivo "bitacora.txt"
struct datos {
    string mes;
    int dia;
    int hora;
    int min;
    int seg;
    string ip;
    string razon;
    datos(string m, int d, int h, int mi, int s, string i, string r)
    : mes(m), dia(d), hora(h), min(mi), seg(s), ip(i), razon(r){}
};

//Convierte a los meses en números, para poder compararlos
int intMes (string m){
    if (m == "Jun" || m == "jun"){
        return 6;
    }else if (m == "Jul" || m == "jul"){
        return 7;
    }else if (m == "Aug" || m == "aug" || m == "Ago" || m == "ago"){
        return 8;
    }else if (m == "Sep" || m == "sep"){
        return 9;
    }else if (m == "Oct" || m == "oct"){
        return 10;
    }
}

//Función que ordena la bitacora comparando las fechas iterativamente
//Corre bien con listas cortas, pero con 16807 datos es bastante lenta
/*
void ordenaIterativoBitacora(vector<datos> &vec){
    int p = 0;
    for (int i=0; i<vec.size()-1; i++){
        for (int j=1+i; j<vec.size(); j++){
            if (intMes(vec[i].mes) > intMes(vec[j].mes)){
                struct datos temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
            else if (intMes(vec[i].mes) == intMes(vec[j].mes) && vec[i].dia > vec[j].dia){
                struct datos temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
            else if (intMes(vec[i].mes) == intMes(vec[j].mes) && vec[i].dia == vec[j].dia && vec[i].hora > vec[j].hora){
                struct datos temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
            else if (intMes(vec[i].mes) == intMes(vec[j].mes) && vec[i].dia == vec[j].dia && vec[i].hora == vec[j].hora && vec[i].min > vec[j].min){
                struct datos temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
            else if (intMes(vec[i].mes) == intMes(vec[j].mes) && vec[i].dia == vec[j].dia && vec[i].hora == vec[j].hora && vec[i].min == vec[j].min && vec[i].seg > vec[j].seg){
                struct datos temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
        }
    }
}
*/

//Función utilizada para ordenaMergeBitacora
//Ordena todos los datos de las listas separadas
void Merge(vector<datos> &lista, int inicio, int medio, int fin){
    int i, j, k;
    int f1 = medio - inicio + 1;
    int f2 = fin - medio;
    vector<datos> izq;
    vector<datos> der;
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
        if (intMes(izq[i].mes) < intMes(der[j].mes)){
            lista[k] = izq[i];
            i++;
        }
        else if (intMes(izq[i].mes) == intMes(der[j].mes) && izq[i].dia < der[j].dia){
            lista[k] = izq[i];
            i++;
        }
        else if (intMes(izq[i].mes) == intMes(der[j].mes) && izq[i].dia == der[j].dia && izq[i].hora < der[j].hora){
            lista[k] = izq[i];
            i++;
        }
        else if (intMes(izq[i].mes) == intMes(der[j].mes) && izq[i].dia == der[j].dia && izq[i].hora == der[j].hora && izq[i].min < der[j].min){
            lista[k] = izq[i];
            i++;
        }
        else if (intMes(izq[i].mes) == intMes(der[j].mes) && izq[i].dia == der[j].dia && izq[i].hora == der[j].hora == izq[i].min == der[j].min && izq[i].seg < der[j].seg){
            lista[k] = izq[i];
            i++;
        }
        else {
            lista[k] = der[j];
            j++;
        }
        k++;
    }
    while (i < f1) { 
        lista[k] = izq[i]; 
        i++; 
        k++; 
    } 
    while (j < f2) { 
        lista[k] = der[j]; 
        j++; 
        k++; 
    } 
}

//Función recursiva que divide el vector de datos en secciones pequeñas 
//Estas las vuelve a juntar ordenadas
void ordenaMergeBitacora(vector<datos> &lista, int inicio, int fin){
    if (inicio < fin) { 
        int medio = inicio + (fin - inicio) / 2; 
        ordenaMergeBitacora(lista, inicio, medio); 
        ordenaMergeBitacora(lista, medio + 1, fin); 
        Merge(lista, inicio, medio, fin); 
    } 
}

//Función que realiza búsqueda binaria para encontrar las fechas que se encuentren entre los rangos dados
//Resultado: posI y posF - Posición inicial y final en el vector de datos ordenado, entre las cuales
//los datos se encuentran dentro del rango de fechas deseado
void buscaBinariaBitacora(vector<datos> vec, string mesI, int diaI, int horaI, string mesF, int diaF, int horaF, int &posI, int &posF){
    int mid, low, high;
    low = 0;
    high = vec.size();
    int texto = 0;
    while (low <= high){
        mid = (low + high) / 2;
        if (intMes(mesI) < intMes(vec[mid].mes)){
            high = mid - 1;
        } else if (intMes(mesI) == intMes(vec[mid].mes) && diaI < vec[mid].dia){
            high = mid - 1;
        } else if (intMes(mesI) == intMes(vec[mid].mes) && diaI == vec[mid].dia && horaI < vec[mid].hora){
            high = mid - 1;
        } else if (intMes(mesI) > intMes(vec[mid].mes)){
            low = mid + 1;
        } else if (intMes(mesI) == intMes(vec[mid].mes) && diaI > vec[mid].dia){
            low = mid + 1;
        } else if (intMes(mesI) == intMes(vec[mid].mes) && diaI == vec[mid].dia && horaI > vec[mid].hora){
            low = mid + 1;
        } else{
            low = mid;
            break;
        }
    }
    posI = low;
    high = vec.size();
    while (low <= high){
        mid = (low + high) / 2;
        if (intMes(mesF) < intMes(vec[mid].mes)){
            high = mid - 1;
        } else if (intMes(mesF) == intMes(vec[mid].mes) && diaF < vec[mid].dia){
            high = mid - 1;
        } else if (intMes(mesF) == intMes(vec[mid].mes) && diaF == vec[mid].dia && horaF < vec[mid].hora){
            high = mid - 1;
        } else if (intMes(mesF) > intMes(vec[mid].mes)){
            low = mid + 1;
        } else if (intMes(mesF) == intMes(vec[mid].mes) && diaF > vec[mid].dia){
            low = mid + 1;
        } else if (intMes(mesF) == intMes(vec[mid].mes) && diaF == vec[mid].dia && horaF > vec[mid].hora){
            low = mid + 1;
        } else{
            low = mid + 1;
            break;
        }
    }
    posF = low;
}

//Imprime en la terminal las líneas de datos entre las posiciones del vector [inicio] - [fin]
void Muestra(vector<datos> vec, int inicio, int fin){
    for (int i = inicio; i < fin; i++){
        cout << vec[i].mes << " " << vec[i].dia << " " << vec[i].hora << " " <<
        vec[i].min << " " << vec[i].seg << " " << vec[i].ip << " " << vec[i].razon << endl;
    }
}

int main()
{
    //Variables iniciales
    ifstream bitacora ("bitacora.txt");
    string mes, diaS, horaS, minS, segS, ip, razon;
    int dia, hora, min, seg;
    vector<datos> vDatos;

    cout << endl << "Favor de esperar unos segundos mientras ordenamos los datos ..." << endl << endl;

    //Almacenamiento de datos en el vector
    int lineas = 0;
    if(bitacora.is_open()){
        while (!bitacora.eof()){
            getline(bitacora, mes, ' ');
            getline(bitacora, diaS, ' ');
            dia = stoi(diaS);
            getline(bitacora, horaS, ':');
            hora = stoi(horaS);
            getline(bitacora, minS, ':');
            min = stoi(minS);
            getline(bitacora, segS, ' ');
            seg = stoi(segS);
            getline(bitacora, ip, ' ');
            getline(bitacora, razon, '\n');
            vDatos.emplace_back((datos(mes, dia, hora, min, seg, ip, razon)));
            lineas += 1;
        }
    }

    //Ordenamiento de los datos en vDatos por su fecha y hora (con minutos/segundos)
    cout << "trabajando ..." << endl << endl;
    ordenaMergeBitacora(vDatos, 0, vDatos.size()-1);
    
    //Almacenamiento de los datos ordenados en un archivo 
    ofstream resultados;
    resultados.open("bOrdenada.txt");
    for (int i = 0; i < vDatos.size(); i++){
        resultados << vDatos[i].mes << " " << vDatos[i].dia << " " << vDatos[i].hora << ":" <<
        vDatos[i].min << ":" << vDatos[i].seg << " " << vDatos[i].ip << " " << vDatos[i].razon << endl;
    }

    //Variables iniciales
    string mesI, mesF;
    int diaI, horaI, diaF, horaF;
    
    //Interfaz para solicitud de datos
    cout << "   - Sistema de solicitud de registros fallidos -   " << endl;
    cout << "____________________________________________________" << endl << endl;
    cout << "Para realizar una solicitud ingresa la fecha y hora " << endl;
    cout << "de inicio y fin de tu busqueda." << endl;
    cout << "Puedes encontrar los datos ordenados en bOrdenada.txt" << endl << endl;
    cout << "Formato de los datos:" << endl;
    cout << "Mes     (Xxx) - Jun/Jul/Aug/Sep/Oct" << endl;
    cout << "Dia           - un numero" << endl;
    cout << "Hora  (24hrs) - un numero" << endl << endl;
    cout << "INICIO:" << endl;
    cout << "Mes (formato: Xxx)" << endl << ">> ";
    cin >>  mesI;
    cout << "Dia" << endl << ">> ";
    cin >> diaI;
    cout << "Hora" << endl << ">> ";
    cin >> horaI;
    cout << endl << "FIN:" << endl;
    cout << "Mes (formato: Xxx)" << endl << ">> ";
    cin >>  mesF;
    cout << "Dia" << endl << ">> ";
    cin >> diaF;
    cout << "Hora" << endl << ">> ";
    cin >> horaF;
    cout << endl;

    //Impresión en pantalla de los datos correspondientes al rango seleccionado
    int posI, posF;
    auto end = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
    buscaBinariaBitacora(vDatos, mesI, diaI, horaI, mesF, diaF, horaF, posI, posF);
    cout << "Resultados de solicitud realizada en - " << ctime(&end_time) << endl;
    Muestra(vDatos, posI, posF);
    bitacora.close();

    cout << endl << "... Cerrando programa ..." << endl << endl;

    return 0;
}
