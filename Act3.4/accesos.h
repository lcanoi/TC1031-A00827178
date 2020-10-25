#ifndef accesos_H
#define accesos_H

//Struct para almacenar los IPs diferentes y la cantidad de accesos a cada uno
struct accesos {
    string ip;
    int cant;
    accesos(string i, int c) : ip(i), cant(c){}
    accesos(void) : ip(""), cant(0){}
    bool operator<(accesos acceso);
    bool operator>(accesos acceso);
};

bool accesos::operator<(accesos acceso){
    if (cant < acceso.cant) {
        return true;
    } else {
        return false;
    }
}

bool accesos::operator>(accesos acceso){
    if (cant > acceso.cant) {
        return true;
    } else {
        return false;
    }
}

#endif