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
