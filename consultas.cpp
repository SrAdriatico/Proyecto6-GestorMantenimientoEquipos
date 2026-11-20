#include <iostream>
#include "gestor.h"

// Muestra solo los equipos que esten en el estado indicado
void mostrarPorEstado(vector<Equipo> &equipos, string estado) {
    int contador = 0;
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

void mostrarEnMantenimiento(vector<Equipo> &equipos) {
    mostrarPorEstado(equipos, "en mantenimiento");
}

void mostrarFueraServicio(vector<Equipo> &equipos) {
    mostrarPorEstado(equipos, "fuera de servicio");
}
