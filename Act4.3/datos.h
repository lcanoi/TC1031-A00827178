#ifndef datos_H
#define datos_H

//Struct para almacenar todos los datos del archivo "bitacoraACT4_3.txt"
struct datos {
    string mes;
    int dia;
    string hora;
    string ipO;
    string puertoO;
    string ipD;
    string puertoD;
    string razon;
    datos(string m, int d, string h, string iO, string pO, string iD, string pD, string r) : mes(m), dia(d), hora(h), ipO(iO), puertoO(pO), ipD(iD), puertoD(pD), razon(r){}
    datos(void) : mes(""), dia(0), hora(""), ipO(""), puertoO(""), ipD(""), puertoD(""), razon(""){}
    bool operator<(datos dato);
    bool operator>(datos dato);
};

bool datos::operator<(datos dato){
    return ipO < dato.ipO;
}

bool datos::operator>(datos dato){
    return ipO > dato.ipO;
}

#endif
