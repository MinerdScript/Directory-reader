#ifndef SISTEMAFICHEIROS_H
#define SISTEMAFICHEIROS_H
#include <iostream>

#include <string>
using namespace std;
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <vector>
#include "Directoria.h"
#include "Ficheiro.h"
#include "XMLWriter.h"
#include "XMLReader.h"

class SistemaFicheiros
{
    Directoria *raiz = NULL;
    public:
        enum Tipo
        {
            ficheiro,
            directoria
        };
        SistemaFicheiros();
        virtual ~SistemaFicheiros();
        bool ProcessaDir(const string &path, int N = 0, Directoria *pai = NULL, Directoria *estaDir = NULL);
        bool Load(const string &path);
        int ContarFicheiros();
        int ContarDirectorias();
        int Memoria();
        string *DirectoriaMaisElementos();
        string *DirectoriaMenosElementos();
        string *FicheiroMaior();
        string *DirectoriaMaisEspaco();
        string *Search(const string &s, int Tipo);
        bool RemoverAll(const string &s, const string &tipo);
        void Escrever_XML(const string &s);
        bool Ler_XML(const string &s, SistemaFicheiros *sistema);
        bool MoveFicheiro(const string &Fich, const string &DirNova);
        bool MoverDirectoria(const string &DirOld, const string &DirNew);
        string *DataFicheiro(const string &ficheiro);
        void Tree(const string *fich);
        void PesquisarAllDirectorias(list<string> &lres, const string &dir);
        void PesquisarAllFicheiros(list<string> &lres, const string &file);
        void RenomearFicheiros(const string &fich_old,const string &fich_new);
        bool FicheiroDuplicados();
        bool CopyBatch(const string &padrao, const string &DirOrigem, const string &DirDestino);
        Directoria *Raiz();
        void SetRaiz(Directoria *ptrRaiz);
    protected:

    private:
};

#endif // SISTEMAFICHEIROS_H
