#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

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

int intMes (string m){
    if (m == "Jun"){
        return 6;
    }else if (m == "Jul"){
        return 7;
    }else if (m == "Aug" || m == "Ago"){
        return 8;
    }else if (m == "Sep"){
        return 9;
    }else if (m == "Oct"){
        return 10;
    }
}

vector<datos> cambio(vector<datos> &lista, int a, int b){
    struct datos temp = lista[a];
    lista[a] = lista[b];
    lista[b] = temp;
}

void ordenaBitacora(vector<datos> &vec){
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

void buscaBitacora(vector<datos> vec, string mesI, int diaI, int horaI, string mesF, int diaF, int horaF, int &posI, int &posF){
    int mid, low, high;
    low = 0;
    high = vec.size();
    while (low <= high){
        mid = (low + high) / 2;
        if (intMes(mesI) < intMes(vec[mid].mes)){
            high = mid - 1;
        } else if (intMes(mesI) == intMes(vec[mid].mes) && diaI < vec[mid].dia){
            high = mid - 1;
        } else if (intMes(mesI) == intMes(vec[mid].mes) && diaI == vec[mid].dia && horaI <= vec[mid].hora){
            high = mid - 1;
        } else if (intMes(mesI) > intMes(vec[mid].mes)){
            low = mid + 1;
        } else if (intMes(mesI) == intMes(vec[mid].mes) && diaI > vec[mid].dia){
            low = mid + 1;
        } else if (intMes(mesI) == intMes(vec[mid].mes) && diaI == vec[mid].dia && horaI >= vec[mid].hora){
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
        cout << "Medio es: " << mid << endl;
        if (intMes(mesF) < intMes(vec[mid].mes)){
            high = mid - 1;
            cout << "b1" << endl;
        } else if (intMes(mesF) == intMes(vec[mid].mes) && diaF < vec[mid].dia){
            high = mid - 1;
            cout << "b2" << endl;
        } else if (intMes(mesF) == intMes(vec[mid].mes) && diaF == vec[mid].dia && horaF <= vec[mid].hora){
            high = mid - 1;
            cout << "b3" << endl;
        } else if (intMes(mesF) > intMes(vec[mid].mes)){
            low = mid + 1;
            cout << "s1" << endl;
        } else if (intMes(mesF) == intMes(vec[mid].mes) && diaF > vec[mid].dia){
            low = mid + 1;
            cout << "s2" << endl;
        } else if (intMes(mesF) == intMes(vec[mid].mes) && diaF == vec[mid].dia && horaF >= vec[mid].hora){
            low = mid + 1;
            cout << "s3" << endl;
        } else{
            cout << "listo" << endl;
            break;
        }
    }
    posF = mid;
}

void Muestra(vector<datos> vec, int inicio, int fin){
    for (int i = inicio; i <= fin; i++){
        cout << "Test: " << i << ". " << vec[i].mes << " " << vec[i].dia << " " << vec[i].hora << " " <<
        vec[i].min << " " << vec[i].seg << " " << vec[i].ip << " " << vec[i].razon << endl;
    }
}

int main()
{
    ifstream bitacora ("bitacora_test.txt");
    string mes, diaS, horaS, minS, segS, ip, razon;
    int dia, hora, min, seg;
    vector<datos> vDatos;

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

    ordenaBitacora(vDatos);
    vector<datos> vec = vDatos;
    for (int i = 0; i < vDatos.size(); i++){
        cout << "Test: " << i << ". " << vec[i].mes << " " << vec[i].dia << " " << vec[i].hora << " " <<
        vec[i].min << " " << vec[i].seg << " " << vec[i].ip << " " << vec[i].razon << endl;
    }

    string mesI, mesF;
    int diaI, horaI, diaF, horaF;
    cout << "   - Sistema de solicitud de registros fallidos -   " << endl;
    cout << "____________________________________________________" << endl << endl;
    cout << "Para realizar una solicitud ingresa la fecha y hora " << endl;
    cout << "de inicio y fin de tu busqueda." << endl << endl;
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
    int posI, posF;
    buscaBitacora(vDatos, mesI, diaI, horaI, mesF, diaF, horaF, posI, posF);
    cout << "Desde " << posI << " hasta " << posF << endl;
    Muestra(vDatos, posI, posF);
    bitacora.close();
    return 0;
}
