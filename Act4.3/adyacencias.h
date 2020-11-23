#ifndef adyacencias_H
#define adyacencias_H

//Struct para almacenar los IPs diferentes y la cantidad de accesos a cada uno
struct adyacencias {
    string ipO;
    int cant;
    adyacencias(string iO, int c) : ipO(iO), cant(c){}
    adyacencias(void) : ipO(""), cant(0){}
    bool operator<(adyacencias vertice);
    bool operator>(adyacencias vertice);
};

bool adyacencias::operator<(adyacencias vertice){
    return cant < vertice.cant;
}

bool adyacencias::operator>(adyacencias vertice){
    return cant > vertice.cant;
}

#endif
