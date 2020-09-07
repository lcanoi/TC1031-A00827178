#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct datos {
    string mes;
    string dia;
    string hora;
    string ip;
    string razon;
};

int main()
{
    ifstream bitacora ("bitacora.txt");
    string mes, dia, hora, ip, razon;
    vector<string> vMes;
    vector<string> vDia;
    vector<string> vHora;
    vector<string> vIp;
    vector<string> vRazon;
    int i = 0;
    if(bitacora.is_open()){
        while (!bitacora.eof()){
            getline(bitacora, mes, ' ');
            vMes.push_back(mes);
            getline(bitacora, dia, ' ');
            vDia.push_back(dia);
            getline(bitacora, hora, ' ');
            vHora.push_back(hora);
            getline(bitacora, ip, ' ');
            vIp.push_back(ip);
            getline(bitacora, razon, '\n');
            vRazon.push_back(razon);
            i += 1;
        }
    }
    cout << "Test: " << vMes[5] << " " << vDia[5] << " " << vHora[5] << " " << vIp[5] << " " << vRazon[5] << endl;
    bitacora.close();
    return 0;
}
