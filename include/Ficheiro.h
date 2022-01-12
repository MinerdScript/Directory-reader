#ifndef FICHEIRO_H
#define FICHEIRO_H


#include <string>
using namespace std;

#include "ObjetoGeral.h"
class Directoria;

class Ficheiro : public ObjetoGeral
{
    off_t tamanho;
    Directoria *dirPai = NULL;
    public:
        Ficheiro();
        Ficheiro(off_t &tam);
        virtual ~Ficheiro();
        unsigned int Memoria();
        off_t &Tamanho();
        void SetDirPai(Directoria *pai);
        Directoria *DirPai();
        void SetTamanho(off_t tam);
        void SetDataM(string *_dataM);
        string *DataM();
    protected:

    private:
        string *dataM;
};

#endif // FICHEIRO_H
