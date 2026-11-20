#include <iostream>
#include <fstream>
#include "gestor.h"

// Parte una linea tipo "101;Dell;Computador;..." en sus campos
vector<string> separar(string linea) {
    vector<string> campos;
    string actual = "";
    for (int i = 0; i < linea.length(); i++) {
        if (linea[i] == ';') {
            campos.push_back(actual);
            actual = "";
        } else {
            actual += linea[i];
        }
    }
    campos.push_back(actual);   // el ultimo campo no termina en ';'
    return campos;
}

// Lee equipos.txt y mantenimientos.txt al iniciar el programa
void cargarDatos(vector<Equipo> &equipos, vector<Mantenimiento> &mants) {
    string linea;
    int invalidas = 0;   // contador de lineas con formato malo

    ifstream archEquipos("equipos.txt");
    if (!archEquipos) {
        cout << "Aviso: no se encontro equipos.txt, se empieza sin equipos.\n";
    } else {
        while (getline(archEquipos, linea)) {
            if (linea != "") {
                vector<string> c = separar(linea);
                if (c.size() == 6) {
                    Equipo e;
                    e.codigo = stoi(c[0]);
                    e.nombre = c[1];
                    e.tipo = c[2];
                    e.ubicacion = c[3];
                    e.estado = c[4];
                    e.mantenimientos = stoi(c[5]);
                    equipos.push_back(e);
                } else {
                    invalidas++;
                }
            }
        }
        archEquipos.close();
    }

    ifstream archMants("mantenimientos.txt");
    if (!archMants) {
        cout << "Aviso: no se encontro mantenimientos.txt.\n";
    } else {
        while (getline(archMants, linea)) {
            if (linea != "") {
                vector<string> c = separar(linea);
                if (c.size() == 5) {
                    Mantenimiento m;
                    m.codigoEquipo = stoi(c[0]);
                    m.tipo = c[1];
                    m.descripcion = c[2];
                    m.diasFueraServicio = stoi(c[3]);
                    m.finalizado = (c[4] == "1");
                    mants.push_back(m);
                } else {
                    invalidas++;
                }
            }
        }
        archMants.close();
    }

    cout << "Se cargaron " << equipos.size() << " equipos y "
         << mants.size() << " mantenimientos.\n";
    if (invalidas > 0) {
        cout << "Aviso: se ignoraron " << invalidas << " lineas con formato invalido.\n";
    }
}

// Reescribe los dos archivos con lo que hay en los vectores
void guardarDatos(vector<Equipo> &equipos, vector<Mantenimiento> &mants) {
    ofstream archEquipos("equipos.txt");
    for (int i = 0; i < equipos.size(); i++) {
        archEquipos << equipos[i].codigo << ";" << equipos[i].nombre << ";"
                    << equipos[i].tipo << ";" << equipos[i].ubicacion << ";"
                    << equipos[i].estado << ";" << equipos[i].mantenimientos << "\n";
    }
    archEquipos.close();

    ofstream archMants("mantenimientos.txt");
    for (int i = 0; i < mants.size(); i++) {
        archMants << mants[i].codigoEquipo << ";" << mants[i].tipo << ";"
                  << mants[i].descripcion << ";" << mants[i].diasFueraServicio << ";"
                  << mants[i].finalizado << "\n";   // el bool se guarda como 1 o 0
    }
    archMants.close();
}
