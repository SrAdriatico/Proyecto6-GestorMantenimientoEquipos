#ifndef GESTOR_H   // guarda de inclusion: evita que se incluya dos veces
#define GESTOR_H

#include <string>
#include <vector>
using namespace std;

// ---------- ESTRUCTURAS ----------
struct Equipo {
    int codigo;
    string nombre;
    string tipo;
    string ubicacion;
    string estado;        // "operativo", "en mantenimiento" o "fuera de servicio"
    int mantenimientos;   // cuantos mantenimientos ha tenido en total
};

struct Mantenimiento {
    int codigoEquipo;
    string tipo;          // "preventivo" o "correctivo"
    string descripcion;
    int diasFueraServicio;
    bool finalizado;
};

// ---------- validaciones.cpp ----------
string leerTexto(string mensaje);
int leerEntero(string mensaje, int minimo, int maximo);
int buscarPorCodigo(vector<Equipo> &equipos, int codigo);
string aMinusculas(string texto);
bool contiene(string texto, string buscado);

// ---------- archivos.cpp ----------
void cargarDatos(vector<Equipo> &equipos, vector<Mantenimiento> &mants);
void guardarDatos(vector<Equipo> &equipos, vector<Mantenimiento> &mants);

// ---------- equipos.cpp ----------
void mostrarUnEquipo(Equipo e);
string elegirTipo();
void registrarEquipo(vector<Equipo> &equipos);
void mostrarEquipos(vector<Equipo> &equipos);
void buscarEquipo(vector<Equipo> &equipos);

// ---------- mantenimientos.cpp ----------
int buscarMantActivo(vector<Mantenimiento> &mants, int codigoEquipo);
void registrarMantenimiento(vector<Equipo> &equipos, vector<Mantenimiento> &mants);
void finalizarMantenimiento(vector<Equipo> &equipos, vector<Mantenimiento> &mants);

// ---------- consultas.cpp ----------
void mostrarPorEstado(vector<Equipo> &equipos, string estado);
void mostrarEnMantenimiento(vector<Equipo> &equipos);
void mostrarFueraServicio(vector<Equipo> &equipos);

// ---------- reportes.cpp ----------
void generarRanking(vector<Equipo> &equipos);
void generarInforme(vector<Equipo> &equipos);

#endif
