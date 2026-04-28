#ifndef LZ78_H
#define LZ78_H

struct ParLZ78 {
    int indice;
    char c;
};

struct DatosComprimidos {
    ParLZ78* pares;
    int cantidad;
    int capacidad;
};

DatosComprimidos comprimirLZ78(const char* textoOriginal);
char* descomprimirLZ78(const DatosComprimidos& datos);
void liberarMemoria(DatosComprimidos& datos);

bool comparar(const char* texto1, const char* texto2);

#endif // LZ78_H
