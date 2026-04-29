#include "encript.h"

using namespace std;

unsigned char encriptarByte(unsigned char byte, int n, unsigned char clave) {
    // rot izq
    unsigned char rotado = (byte << n) | (byte >> (8 - n));

    // XOR
    return rotado ^ clave;
}

unsigned char desencriptarByte(unsigned char byte, int n, unsigned char clave) {

    // Quitar XOR
    unsigned char sinXor = byte ^ clave;

    // Rot der
    return (sinXor >> n) | (sinXor << (8 - n));
}

string encriptarString(const string& texto, int n, unsigned char clave) {

    string resultado = "";
    for (size_t i = 0; i < texto.length(); ++i) {
        resultado += encriptarByte(static_cast<unsigned char>(texto[i]), n, clave);
    }
    return resultado;
}

string desencriptarString(const string& texto, int n, unsigned char clave) {

    string resultado = "";
    for (size_t i = 0; i < texto.length(); ++i) {
        resultado += desencriptarByte(static_cast<unsigned char>(texto[i]), n, clave);
    }
    return resultado;
}

void encriptarBuffer(unsigned char* buffer, int tamano, int n, unsigned char clave) {
    // Encript byte a byte por bloque de mem
    for (int i = 0; i < tamano; ++i) {
        buffer[i] = encriptarByte(buffer[i], n, clave);
    }
}

void desencriptarBuffer(unsigned char* buffer, int tamano, int n, unsigned char clave) {
    // lo mismo pero des uwu
    for (int i = 0; i < tamano; ++i) {
        buffer[i] = desencriptarByte(buffer[i], n, clave);
    }
}
