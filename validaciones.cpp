#include <iostream>
#include "gestor.h"

// Pide un texto que no este vacio y que no tenga ';'
// (el ';' lo usamos para separar los datos en los archivos)
string leerTexto(string mensaje) {
    string texto;
    bool valido = false;
    while (!valido) {
        cout << mensaje;
        getline(cin, texto);
        valido = texto.length() > 0;
        for (int i = 0; i < texto.length(); i++) {
            if (texto[i] == ';') {
                valido = false;
            }
        }
        if (!valido) {
            cout << "  Error: no puede quedar vacio ni tener ';'.\n";
        }
    }
    return texto;
}

// Pide un numero entero entre minimo y maximo.
// Lo lee como texto y revisa que solo tenga digitos,
// asi el programa no se rompe si el usuario escribe letras.
int leerEntero(string mensaje, int minimo, int maximo) {
    string texto;
    int numero = 0;
    bool valido = false;
    while (!valido) {
        cout << mensaje;
        getline(cin, texto);
        valido = texto.length() > 0 && texto.length() <= 9;
        for (int i = 0; i < texto.length(); i++) {
            if (texto[i] < '0' || texto[i] > '9') {
                valido = false;
            }
        }
        if (valido) {
            numero = stoi(texto);
            if (numero < minimo || numero > maximo) {
                valido = false;
            }
        }
        if (!valido) {
            cout << "  Error: escribe un numero entre " << minimo << " y " << maximo << ".\n";
        }
    }
    return numero;
}

// Busca un equipo por codigo. Devuelve su posicion en el vector, o -1 si no existe
int buscarPorCodigo(vector<Equipo> &equipos, int codigo) {
    for (int i = 0; i < equipos.size(); i++) {
        if (equipos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

// Convierte un texto a minusculas (solo letras A-Z)
string aMinusculas(string texto) {
    for (int i = 0; i < texto.length(); i++) {
        if (texto[i] >= 'A' && texto[i] <= 'Z') {
            texto[i] = texto[i] + 32;   // en ASCII, 'a' esta 32 posiciones despues de 'A'
        }
    }
    return texto;
}

// Dice si 'buscado' aparece dentro de 'texto', sin importar mayusculas
// Ej: contiene("Computador Dell", "dell") -> true
bool contiene(string texto, string buscado) {
    texto = aMinusculas(texto);
    buscado = aMinusculas(buscado);
    for (int i = 0; i + buscado.length() <= texto.length(); i++) {
        bool coincide = true;
        for (int j = 0; j < buscado.length(); j++) {
            if (texto[i + j] != buscado[j]) {
                coincide = false;
            }
        }
        if (coincide) {
            return true;
        }
    }
    return false;
}
