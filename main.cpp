#include <iostream>
#include "gestor.h"

int main() {
    vector<Equipo> equipos;
    vector<Mantenimiento> mants;

    cargarDatos(equipos, mants);   // carga automatica al iniciar

    int opcion;
    do {
        cout << "\n====== GESTOR DE MANTENIMIENTO DE EQUIPOS ======\n";
        cout << "1. Registrar equipo\n";
        cout << "2. Mostrar equipos\n";
        cout << "3. Buscar equipo (codigo, nombre o tipo)\n";
        cout << "4. Registrar mantenimiento\n";
        cout << "5. Finalizar mantenimiento\n";
        cout << "6. Ver equipos en mantenimiento\n";
        cout << "7. Ver equipos fuera de servicio\n";
        cout << "8. Ranking de equipos con mas mantenimientos\n";
        cout << "9. Informe de clasificacion\n";
        cout << "0. Salir\n";
        opcion = leerEntero("Seleccione una opcion: ", 0, 9);

        switch (opcion) {
            case 1:
                registrarEquipo(equipos);
                guardarDatos(equipos, mants);
                break;
            case 2:
                mostrarEquipos(equipos);
                break;
            case 3:
                buscarEquipo(equipos);
                break;
            case 4:
                registrarMantenimiento(equipos, mants);
                guardarDatos(equipos, mants);
                break;
            case 5:
                finalizarMantenimiento(equipos, mants);
                guardarDatos(equipos, mants);
                break;
            case 6:
                mostrarEnMantenimiento(equipos);
                break;
            case 7:
                mostrarFueraServicio(equipos);
                break;
            case 8:
                generarRanking(equipos);
                break;
            case 9:
                generarInforme(equipos);
                break;
            case 0:
                guardarDatos(equipos, mants);
                cout << "Datos guardados. Hasta luego!\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}
