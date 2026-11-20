// Gestor de Mantenimiento de Equipos - Proyecto 6 (Programacion, grupo 1718)
// Aqui solo esta el menu principal. Lo que hace cada opcion esta en los otros .cpp
#include <iostream>
#include "gestor.h"

int main() {
    // aqui se guardan todos los datos mientras el programa esta abierto
    vector<Equipo> equipos;
    vector<Mantenimiento> mants;

    // al abrir, leemos los archivos para recuperar lo que se guardo antes
    cargarDatos(equipos, mants);

    int opcion;
    // el menu se repite hasta que el usuario elija 0
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
        // leerEntero no deja pasar letras ni numeros fuera de 0-9
        opcion = leerEntero("Seleccione una opcion: ", 0, 9);

        switch (opcion) {
            case 1:
                registrarEquipo(equipos);
                // guardamos enseguida para no perder nada si cierran la ventana
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
            // las opciones 2, 3, 6, 7, 8 y 9 solo consultan, por eso no guardan
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
                // ultimo guardado antes de salir
                guardarDatos(equipos, mants);
                cout << "Datos guardados. Hasta luego!\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}
