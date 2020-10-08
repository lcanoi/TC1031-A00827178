#ifndef datos_H
#define datos_H

//Struct para almacenar todos los datos del archivo "bitacora.txt"
struct datos {
    int mes;
    int dia;
    int hora;
    int min;
    int seg;
    string ip;
    string razon;
    datos(int m, int d, int h, int mi, int s, string i, string r) : mes(m), dia(d), hora(h), min(mi), seg(s), ip(i), razon(r){}
    datos(void) : mes(0), dia(0), hora(0), min(0), seg(0), ip(""), razon(""){}
};

#endif
