#include <iostream>
#include "gestor.h"

// Recorre los equipos y muestra solo los que tienen el estado que le pasamos.
// Las opciones 6 y 7 del menu usan esta misma funcion
void mostrarPorEstado(vector<Equipo> &equipos, string estado) {
    int contador = 0;   // cuantos equipos coinciden, para el total del final
    cout << "\n--- EQUIPOS: " << estado << " ---\n";
    for (int i = 0; i < equipos.size(); i++) {
        if (equipos[i].estado == estado) {
            mostrarUnEquipo(equipos[i]);
            contador++;
        }
    }
    if (contador == 0) {
        cout << "No hay equipos en este estado.\n";
    } else {
        cout << "Total: " << contador << "\n";
    }
}

// Opcion 6: reutiliza mostrarPorEstado para no repetir codigo
void mostrarEnMantenimiento(vector<Equipo> &equipos) {
    mostrarPorEstado(equipos, "en mantenimiento");
}

// Opcion 7: igual que la anterior pero con otro estado
void mostrarFueraServicio(vector<Equipo> &equipos) {
    mostrarPorEstado(equipos, "fuera de servicio");
}
