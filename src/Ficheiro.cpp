#include "Ficheiro.h"
#include "Directoria.h"

Ficheiro::Ficheiro(){}

Ficheiro::Ficheiro(off_t &tam)
{

    //ctor
    tamanho = tam;
}



Ficheiro::~Ficheiro()
{
    //dtor
    dirPai = NULL;
    if(dataM)
        delete dataM;
}

unsigned int Ficheiro::Memoria()
{
    unsigned int conta = sizeof(Ficheiro);
    conta += sizeof(string) + sizeof(char)*Nome().length();
    conta += sizeof(off_t);//tamanho
    return conta;
}

off_t &Ficheiro::Tamanho()
{
    return tamanho;
}

void Ficheiro::SetDirPai(Directoria *pai)
{
    dirPai = pai;
    pai->AddFich(this);
}

Directoria *Ficheiro::DirPai()
{
    return dirPai;
}

void Ficheiro::SetTamanho(off_t tam){
    tamanho = tam;
}

string *Ficheiro::DataM()
{
    return dataM;
}

void Ficheiro::SetDataM(string *_dataM)
{
    dataM = _dataM;
}
