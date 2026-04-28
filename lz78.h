#ifndef LZ78_H
#define LZ78_H

// Struct por par
struct ParLZ78 {
    int indice;
    char c;
};

// Struct dinamico
struct DatosComprimidos {
    ParLZ78* pares;
    int cantidad;
    int capacidad;
};

DatosComprimidos comprimirLZ78(const char* textoOriginal);
char* descomprimirLZ78(const DatosComprimidos& datos);
void liberarMemoria(DatosComprimidos& datos);

#endif // LZ78_H
