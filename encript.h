#ifndef ENCRIPT_H
#define ENCRIPT_H

#include <string>

using namespace std;

unsigned char encriptarByte(unsigned char byte, int n, unsigned char clave);
unsigned char desencriptarByte(unsigned char byte, int n, unsigned char clave);

string encriptarString(const string& texto, int n, unsigned char clave);
string desencriptarString(const string& texto, int n, unsigned char clave);

void encriptarBuffer(unsigned char* buffer, int tamano, int n, unsigned char clave);
void desencriptarBuffer(unsigned char* buffer, int tamano, int n, unsigned char clave);

#endif // ENCRIPT_H
