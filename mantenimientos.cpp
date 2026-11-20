#include <iostream>
#include "gestor.h"

// Busca el mantenimiento ACTIVO (no finalizado) de un equipo.
// Devuelve su posicion en el vector, o -1 si no tiene ninguno activo
int buscarMantActivo(vector<Mantenimiento> &mants, int codigoEquipo) {
    for (int i = 0; i < mants.size(); i++) {
        if (mants[i].codigoEquipo == codigoEquipo && !mants[i].finalizado) {
            return i;
        }
    }
    return -1;
}

void registrarMantenimiento(vector<Equipo> &equipos, vector<Mantenimiento> &mants) {
    cout << "\n--- REGISTRAR MANTENIMIENTO ---\n";
    int codigo = leerEntero("Codigo del equipo: ", 1, 99999);

    // Validacion: el equipo debe existir
    int pos = buscarPorCodigo(equipos, codigo);
    if (pos == -1) {
        cout << "Error: no existe un equipo con ese codigo.\n";
        return;
    }

    // Validacion: no puede tener otro mantenimiento activo
    if (buscarMantActivo(mants, codigo) != -1) {
        cout << "Error: este equipo ya tiene un mantenimiento activo.\n";
        return;
    }

    Mantenimiento m;
    m.codigoEquipo = codigo;
    cout << "Tipo: 1. Preventivo  2. Correctivo\n";
    if (leerEntero("Opcion: ", 1, 2) == 1) {
        m.tipo = "preventivo";
    } else {
        m.tipo = "correctivo";
    }
    m.descripcion = leerTexto("Descripcion: ");
    // Validacion: dias no negativos (leerEntero no acepta negativos)
    m.diasFueraServicio = leerEntero("Dias fuera de servicio estimados (0-365): ", 0, 365);
    m.finalizado = false;

    mants.push_back(m);

    // Control de estado: el equipo pasa a "en mantenimiento"
    equipos[pos].estado = "en mantenimiento";
    equipos[pos].mantenimientos++;

    cout << "Mantenimiento registrado. El equipo " << equipos[pos].nombre
         << " ahora esta en mantenimiento.\n";
}

void finalizarMantenimiento(vector<Equipo> &equipos, vector<Mantenimiento> &mants) {
    cout << "\n--- FINALIZAR MANTENIMIENTO ---\n";
    int codigo = leerEntero("Codigo del equipo: ", 1, 99999);

    int pos = buscarPorCodigo(equipos, codigo);
    if (pos == -1) {
        cout << "Error: no existe un equipo con ese codigo.\n";
        return;
    }

    // Validacion: debe existir un mantenimiento activo (ni inexistente ni ya finalizado)
    int idx = buscarMantActivo(mants, codigo);
    if (idx == -1) {
        cout << "Error: este equipo no tiene un mantenimiento activo para finalizar.\n";
        return;
    }

    cout << "Mantenimiento activo: " << mants[idx].tipo << " - "
         << mants[idx].descripcion << "\n";
    mants[idx].diasFueraServicio = leerEntero("Dias reales fuera de servicio (0-365): ", 0, 365);
    mants[idx].finalizado = true;

    // Control de estado: se elige el nuevo estado del equipo
    cout << "Nuevo estado del equipo: 1. Operativo  2. Fuera de servicio\n";
    if (leerEntero("Opcion: ", 1, 2) == 1) {
        equipos[pos].estado = "operativo";
    } else {
        equipos[pos].estado = "fuera de servicio";
    }

    cout << "Mantenimiento finalizado. Estado actual: " << equipos[pos].estado << "\n";
}
