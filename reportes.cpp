#include <iostream>
#include <fstream>
#include "gestor.h"

// Rangos de frecuencia de mantenimiento (definidos por el equipo):
//   Baja:  0 a 2 mantenimientos
//   Media: 3 a 5 mantenimientos
//   Alta:  6 o mas mantenimientos
const int LIMITE_BAJA = 2;
const int LIMITE_MEDIA = 5;

// Guarda un reporte en un archivo de texto
void guardarReporte(string nombreArchivo, string contenido) {
    ofstream archivo(nombreArchivo.c_str());
    archivo << contenido;
    archivo.close();
    cout << "(Reporte guardado en " << nombreArchivo << ")\n";
}

void generarRanking(vector<Equipo> &equipos) {
    int n = equipos.size();
    if (n == 0) {
        cout << "No hay equipos registrados.\n";
        return;
    }

    // Copia para no desordenar la lista original
    vector<Equipo> copia = equipos;

    // Ordenamiento burbuja de mayor a menor numero de mantenimientos
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (copia[j].mantenimientos < copia[j + 1].mantenimientos) {
                Equipo temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }

    int totalMants = 0;   // acumulador
    for (int i = 0; i < n; i++) {
        totalMants += copia[i].mantenimientos;
    }

    int limite = 10;      // mostramos el top 10
    if (n < 10) {
        limite = n;
    }

    string r = "\n===== RANKING: EQUIPOS CON MAS MANTENIMIENTOS =====\n";
    for (int i = 0; i < limite; i++) {
        r += to_string(i + 1) + ". [" + to_string(copia[i].codigo) + "] "
           + copia[i].nombre + " (" + copia[i].tipo + ") - "
           + to_string(copia[i].mantenimientos) + " mantenimientos\n";
    }
    r += "Total de mantenimientos de todos los equipos: " + to_string(totalMants) + "\n";

    cout << r;
    guardarReporte("reporte_ranking.txt", r);
}

void generarInforme(vector<Equipo> &equipos) {
    int n = equipos.size();
    int operativos = 0, enMant = 0, fuera = 0;   // contadores por estado
    int baja = 0, media = 0, alta = 0;           // contadores por frecuencia
    vector<string> tipos;                        // tipos encontrados
    vector<int> cantPorTipo;                     // cuantos hay de cada tipo

    for (int i = 0; i < n; i++) {
        // Clasificacion por estado
        if (equipos[i].estado == "operativo") {
            operativos++;
        } else if (equipos[i].estado == "en mantenimiento") {
            enMant++;
        } else if (equipos[i].estado == "fuera de servicio") {
            fuera++;
        }

        // Clasificacion por frecuencia
        int m = equipos[i].mantenimientos;
        if (m <= LIMITE_BAJA) {
            baja++;
        } else if (m <= LIMITE_MEDIA) {
            media++;
        } else {
            alta++;
        }

        // Clasificacion por tipo: buscamos si el tipo ya esta en la lista
        int pos = -1;
        for (int j = 0; j < tipos.size(); j++) {
            if (tipos[j] == equipos[i].tipo) {
                pos = j;
            }
        }
        if (pos == -1) {
            tipos.push_back(equipos[i].tipo);
            cantPorTipo.push_back(1);
        } else {
            cantPorTipo[pos]++;
        }
    }

    string r = "\n========== INFORME DE CLASIFICACION ==========\n";
    r += "Total de equipos registrados: " + to_string(n) + "\n";

    r += "\n-- Clasificacion por tipo --\n";
    for (int j = 0; j < tipos.size(); j++) {
        r += "  " + tipos[j] + ": " + to_string(cantPorTipo[j]) + "\n";
    }

    r += "\n-- Clasificacion por estado --\n";
    r += "  Operativos: " + to_string(operativos) + "\n";
    r += "  En mantenimiento: " + to_string(enMant) + "\n";
    r += "  Fuera de servicio: " + to_string(fuera) + "\n";

    r += "\n-- Clasificacion por frecuencia de mantenimiento --\n";
    r += "  Baja (0-" + to_string(LIMITE_BAJA) + "): " + to_string(baja) + "\n";
    r += "  Media (" + to_string(LIMITE_BAJA + 1) + "-" + to_string(LIMITE_MEDIA) + "): " + to_string(media) + "\n";
    r += "  Alta (" + to_string(LIMITE_MEDIA + 1) + " o mas): " + to_string(alta) + "\n";

    cout << r;
    guardarReporte("informe_clasificacion.txt", r);
}
