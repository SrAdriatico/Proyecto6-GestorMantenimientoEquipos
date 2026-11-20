#include <iostream>
#include "gestor.h"

// Muestra un solo equipo (se reutiliza en busquedas y consultas)
void mostrarUnEquipo(Equipo e) {
    cout << "[" << e.codigo << "] " << e.nombre
         << " | Tipo: " << e.tipo
         << " | Ubicacion: " << e.ubicacion
         << " | Estado: " << e.estado
         << " | Mantenimientos: " << e.mantenimientos << "\n";
}

void mostrarEquipos(vector<Equipo> &equipos) {
    if (equipos.size() == 0) {
        cout << "No hay equipos registrados.\n";
        return;
    }
    cout << "\n--- EQUIPOS REGISTRADOS (" << equipos.size() << ") ---\n";
    for (int i = 0; i < equipos.size(); i++) {
        mostrarUnEquipo(equipos[i]);
    }
}

// Muestra los tipos permitidos y devuelve el elegido.
// Usar una lista fija evita que un mismo tipo quede escrito de varias formas
string elegirTipo() {
    cout << "Tipos: 1. Computador  2. Impresora  3. Instrumento de medicion\n";
    cout << "       4. Proyector   5. Equipo de red  6. Otro\n";
    int op = leerEntero("Tipo: ", 1, 6);
    switch (op) {
        case 1: return "Computador";
        case 2: return "Impresora";
        case 3: return "Instrumento de medicion";
        case 4: return "Proyector";
        case 5: return "Equipo de red";
        default: return "Otro";
    }
}

void registrarEquipo(vector<Equipo> &equipos) {
    cout << "\n--- REGISTRAR EQUIPO ---\n";
    Equipo e;
    e.codigo = leerEntero("Codigo (1-99999): ", 1, 99999);

    // Validacion: no permitir codigos repetidos
    if (buscarPorCodigo(equipos, e.codigo) != -1) {
        cout << "Error: ya existe un equipo con el codigo " << e.codigo << ".\n";
        return;
    }

    e.nombre = leerTexto("Nombre: ");
    e.tipo = elegirTipo();
    e.ubicacion = leerTexto("Ubicacion: ");
    e.estado = "operativo";     // todo equipo nuevo empieza operativo
    e.mantenimientos = 0;

    equipos.push_back(e);
    cout << "Equipo registrado correctamente.\n";
}

void buscarEquipo(vector<Equipo> &equipos) {
    cout << "\nBuscar por: 1. Codigo  2. Nombre  3. Tipo\n";
    int criterio = leerEntero("Opcion: ", 1, 3);
    int encontrados = 0;   // contador

    if (criterio == 1) {
        int codigo = leerEntero("Codigo: ", 1, 99999);
        int pos = buscarPorCodigo(equipos, codigo);
        if (pos != -1) {
            mostrarUnEquipo(equipos[pos]);
            encontrados = 1;
        }
    } else {
        string buscado = leerTexto("Texto a buscar: ");
        for (int i = 0; i < equipos.size(); i++) {
            string campo;
            if (criterio == 2) {
                campo = equipos[i].nombre;
            } else {
                campo = equipos[i].tipo;
            }
            if (contiene(campo, buscado)) {
                mostrarUnEquipo(equipos[i]);
                encontrados++;
            }
        }
    }

    if (encontrados == 0) {
        cout << "No se encontro ningun equipo.\n";
    } else {
        cout << "Resultados encontrados: " << encontrados << "\n";
    }
}
