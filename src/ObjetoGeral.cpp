#include "ObjetoGeral.h"


ObjetoGeral::ObjetoGeral()
{
    //ctor
}

ObjetoGeral::~ObjetoGeral()
{
    //dtor
}

void ObjetoGeral::SetNome(string _novo)
{
    nome = _novo;
}

string &ObjetoGeral::Nome()
{
    return nome;
}

