#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <fstream>
using namespace std;
#include "Directoria.h"
#include "Ficheiro.h"

class XMLWriter
{
    ofstream F;
    unsigned int N;
    public:
        XMLWriter();
        virtual ~XMLWriter();
        bool AbreDocumento(string documento);
        bool FechaDocumento();
        void EscreveDiretoria(Directoria *directoria);
        void EscreveFicheiro(Ficheiro *ficheiro);
        void Espacos(int extra = 0);
        void EscreveAtributo(string atributo, string value);

    protected:

    private:
};

#endif // XMLWRITER_H
