#ifndef XMLREADER_H
#define XMLREADER_H

#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
#include "Directoria.h"
#include "Ficheiro.h"
class Directoria;
class SistemaFicheiros;
class Ficheiro;

class XMLReader
{
    Ficheiro *ficheiroTemp = NULL;
    bool tagFicheiros = false;
    bool XMLMalEscrito=false;
    ifstream F;
    SistemaFicheiros *sistema = NULL;
    public:
        XMLReader(SistemaFicheiros *sis);
        virtual ~XMLReader();
        bool AbreDocumento(string documento);
        bool FechaDocumento();
        bool LerDocumento();
        Directoria* LerElemento(string &s, Directoria *dirPai = NULL);
        void Trim(string &s);
    protected:

    private:
};

#endif // XMLREADER_H
