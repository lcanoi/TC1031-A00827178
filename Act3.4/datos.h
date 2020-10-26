#ifndef datos_H
#define datos_H

//Struct para almacenar todos los datos del archivo "bitacora2.txt"
struct datos {
    string mes;
    int dia;
    string hora;
    string ip;
    string razon;
    datos(string m, int d, string h, string i, string r) : mes(m), dia(d), hora(h), ip(i), razon(r){}
    datos(void) : mes(""), dia(0), hora(""), ip(""), razon(""){}
    bool operator<(datos dato);
    bool operator>(datos dato);
};

bool datos::operator<(datos dato){
    return ip < dato.ip;
}

bool datos::operator>(datos dato){
    return ip > dato.ip;
}

#endif
