#ifndef HORA_FECHA_H
#define HORA_FECHA_H

#include <iostream>
#include <ctime>

using namespace std;

void mostrarFechaHora() {
    time_t ahora = time(0);
    tm* tiempoLocal = localtime(&ahora);

    cout << "\nFecha y hora actual: ";
    cout << tiempoLocal->tm_mday << "/"
         << tiempoLocal->tm_mon + 1 << "/"
         << tiempoLocal->tm_year + 1900 << " ";

    if (tiempoLocal->tm_hour < 10) cout << "0";
    cout << tiempoLocal->tm_hour << ":";

    if (tiempoLocal->tm_min < 10) cout << "0";
    cout << tiempoLocal->tm_min << ":";

    if (tiempoLocal->tm_sec < 10) cout << "0";
    cout << tiempoLocal->tm_sec << endl;
}

#endif // HORA_FECHA_H
