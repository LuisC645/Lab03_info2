#include "lz78.h"

int obtenerLongitud(const char* texto) {
    int len = 0;
    while (texto[len] != '\0') len++;
    return len;
}

void agregarPar(DatosComprimidos& arreglo, int indice, char c) {

    if (arreglo.cantidad == arreglo.capacidad) {
        int nuevaCapacidad = (arreglo.capacidad == 0) ? 10 : arreglo.capacidad * 2;
        ParLZ78* nuevoArreglo = new ParLZ78[nuevaCapacidad];

        for (int i = 0; i < arreglo.cantidad; ++i) {
            nuevoArreglo[i] = arreglo.pares[i];
        }

        if (arreglo.pares != nullptr) {
            delete[] arreglo.pares;
        }
        arreglo.pares = nuevoArreglo;
        arreglo.capacidad = nuevaCapacidad;
    }

    arreglo.pares[arreglo.cantidad].indice = indice;
    arreglo.pares[arreglo.cantidad].c = c;
    arreglo.cantidad++;
}

DatosComprimidos comprimirLZ78(const char* textoOriginal) {

    DatosComprimidos salida = {nullptr, 0, 0};
    DatosComprimidos diccionario = {nullptr, 0, 0};

    int longitud = obtenerLongitud(textoOriginal);
    int prefijoActual = 0;

    for (int i = 0; i < longitud; ++i) {
        char caracterActual = textoOriginal[i];
        int indiceEncontrado = 0;

        for (int j = 0; j < diccionario.cantidad; ++j) {
            if (diccionario.pares[j].indice == prefijoActual && diccionario.pares[j].c == caracterActual) {
                indiceEncontrado = j + 1;
                break;
            }
        }

        if (indiceEncontrado != 0) {
            prefijoActual = indiceEncontrado;
        } else {
            agregarPar(salida, prefijoActual, caracterActual);
            agregarPar(diccionario, prefijoActual, caracterActual);
            prefijoActual = 0;
        }
    }

    if (prefijoActual != 0) {
        agregarPar(salida, prefijoActual, '\0');
    }

    liberarMemoria(diccionario);
    return salida;
}

char* descomprimirLZ78(const DatosComprimidos& datos) {

    int* longitudes = new int[datos.cantidad + 1];
    longitudes[0] = 0;
    int totalCaracteres = 0;

    for (int i = 0; i < datos.cantidad; ++i) {
        int prefijo = datos.pares[i].indice;
        longitudes[i + 1] = longitudes[prefijo] + 1;
        totalCaracteres += longitudes[i + 1];
        if (i == datos.cantidad - 1 && datos.pares[i].c == '\0') totalCaracteres--;
    }

    char* textoReconstruido = new char[totalCaracteres + 1];
    int posicionEscritura = 0;

    for (int i = 0; i < datos.cantidad; ++i) {
        int prefijo = datos.pares[i].indice;
        char c = datos.pares[i].c;

        int tamanoFrase = longitudes[prefijo];
        int indiceEscritura = posicionEscritura + tamanoFrase - 1;

        int actual = prefijo;
        while (actual != 0) {
            textoReconstruido[indiceEscritura--] = datos.pares[actual - 1].c;
            actual = datos.pares[actual - 1].indice;
        }

        posicionEscritura += tamanoFrase;

        if (!(i == datos.cantidad - 1 && c == '\0')) {
            textoReconstruido[posicionEscritura++] = c;
        }
    }

    textoReconstruido[totalCaracteres] = '\0';
    delete[] longitudes;
    return textoReconstruido;
}

void liberarMemoria(DatosComprimidos& datos) {

    if (datos.pares != nullptr) {
        delete[] datos.pares;
        datos.pares = nullptr;
    }
    datos.cantidad = 0;
    datos.capacidad = 0;
}

bool comparar(const char* texto1, const char* texto2) {
    int i = 0;

    while (texto1[i] != '\0' || texto2[i] != '\0') {
        if (texto1[i] != texto2[i]) {
            return false;
        }
        i++;
    }
    return true;
}
