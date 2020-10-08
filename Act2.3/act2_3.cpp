// Luis Cano Irigoyen  -  A00827178  -  7-Oct-2020  -  TC1031.10
// Act 2.3 - Actividad Integral estructura de datos lineales
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;

#include "DLL.h"

//Convierte a los meses en números
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
    return 0;
}

//Convierte a los números en meses
string stringMes (int m){
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

int main()
{
    //Variables iniciales
    ifstream bitacora ("bitacora.txt");
    string mesS, diaS, horaS, minS, segS, ip, razon;
    int mes, dia, hora, min, seg;
    DLL<datos> lisDatos;

    cout << endl << "Favor de esperar unos segundos mientras ordenamos los datos ..." << endl << endl;

    //Almacenamiento de datos en la Doubly Linked List
    int lineas = 0;
    if(bitacora.is_open()){
        while (!bitacora.eof()){
            getline(bitacora, mesS, ' ');
            mes = intMes(mesS);
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
            lisDatos.queue(datos(mes, dia, hora, min, seg, ip, razon));
        }
    }
    
    //Ordenamiento de los datos en lisDatos por su fecha y hora (con minutos/segundos)
    cout << "trabajando ..." << endl << endl;
    lisDatos.sort();
    
    //Almacenamiento de los datos ordenados en un archivo 
    ofstream resultados;
    resultados.open("bOrdenada.txt");
    for (int i = 1; i <= lisDatos.getSize(); i++){
        resultados << stringMes(lisDatos[i].mes) << " " << lisDatos[i].dia << " " << lisDatos[i].hora << ":" <<
        lisDatos[i].min << ":" << lisDatos[i].seg << " " << lisDatos[i].ip << " " << lisDatos[i].razon << endl;
    }

    //Variables iniciales
    string mesIS, mesFS;
    int mesI, diaI, horaI, mesF, diaF, horaF;
    int posI, posF;
    auto end = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
    string salir = "s";
    int completado = 0;

    //Interfaz para solicitud de datos
    while (salir == "S" || salir == "s"){
        while (completado == 0) {
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
            cin >>  mesIS;
            mesI = intMes(mesIS);
            cout << "Dia" << endl << ">> ";
            cin >> diaI;
            cout << "Hora" << endl << ">> ";
            cin >> horaI;
            cout << endl << "FIN:" << endl;
            cout << "Mes (formato: Xxx)" << endl << ">> ";
            cin >>  mesFS;
            mesF = intMes(mesFS);
            cout << "Dia" << endl << ">> ";
            cin >> diaF;
            cout << "Hora" << endl << ">> ";
            cin >> horaF;
            cout << endl;

            //Búsqueda binaria e impresión en pantalla de los datos correspondientes al rango seleccionado
            try {
                lisDatos.binarySearchRange(lisDatos, mesI, diaI, horaI, mesF, diaF, horaF, posI, posF);
                completado = 1;
            } catch(out_of_range& e) {
                cout << e.what() << endl;
                cout << "Fecha escrita incorrectamente o fuera del rango de la base de Datos..." << endl;
                cout << "Intenta nuevamente" << endl << endl;
            }
        }

        //imprimir datos de PosI a PosF
        cout << "Resultados de solicitud realizada en - " << ctime(&end_time) << endl;
        lisDatos.printRange(lisDatos, posI, posF);
        
        cout << endl <<  "Deseas realizar otra busqueda? (s/n) >> ";
        cin >> salir;
        completado = 0;
        cout << endl;
    }

    bitacora.close();

    cout << "... Cerrando programa ..." << endl << endl;

    return 0;
}
