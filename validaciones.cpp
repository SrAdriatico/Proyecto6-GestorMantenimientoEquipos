#include <iostream>
#include "gestor.h"

// Pide un texto que no este vacio ni tenga ";" (el ";" separa los datos en los archivos)
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

// Pide un entero entre minimo y maximo. Se lee como texto y se revisa que sean
// solo digitos, asi el programa no se rompe si escriben letras o un negativo
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

// Busca un equipo por codigo: devuelve su posicion en el vector o -1 si no esta
int buscarPorCodigo(vector<Equipo> &equipos, int codigo) {
    for (int i = 0; i < equipos.size(); i++) {
        if (equipos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

// Pasa el texto a minusculas (solo A-Z) para poder comparar sin importar mayusculas
string aMinusculas(string texto) {
    for (int i = 0; i < texto.length(); i++) {
        if (texto[i] >= 'A' && texto[i] <= 'Z') {
            texto[i] = texto[i] + 32;   // en ASCII la 'a' esta 32 posiciones despues de la 'A'
        }
    }
    return texto;
}

// Dice si 'buscado' esta dentro de 'texto' sin importar mayusculas.
// Ej: contiene("Computador Dell", "dell") da true
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
