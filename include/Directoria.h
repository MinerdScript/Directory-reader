#ifndef DIRECTORIA_H
#define DIRECTORIA_H
#include <list>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "ObjetoGeral.h"
#include "Ficheiro.h"

class Directoria : public ObjetoGeral
{
    list<Directoria*> filhosDir;
    list<Ficheiro*> filhosFich;
    Directoria * dirPai = NULL;
    public:
        Directoria();
        virtual ~Directoria();
        bool AddDir(Directoria *dir);
        bool AddFich(Ficheiro *fich);
        void RemoveDir(Directoria *dir);
        void RemoveDir(const string &nomeDir);
        void RemoveFich(Ficheiro *fich);
        void RemoveFich(const string &nomeFich);
        unsigned int ContarFicheiros(bool recursivo = true);
        unsigned int ContarDirectorias(bool recursivo = true);
        unsigned int Memoria(bool recursivo = true);
        Directoria *DirectoriaMaisElementos(Directoria *maior, unsigned int &maiorN);
        Ficheiro *FicheiroMaior(Ficheiro *maior, off_t &maiorN);
        Directoria *DirectoriaMaisEspaco(Directoria *maior, unsigned int &maiorN);
        Directoria *DirectoriaMenosElementos(Directoria *menor, unsigned int &menorN);
        void Tree(ofstream &F, int nivel, vector<bool> &niveis);
        string *Search(const string &s, int &Tipo);
        Ficheiro *SearchFich(const string &s);
        void PluralSearchFich(list<Ficheiro*> &encontrados, const string &padrao);
        Directoria *SearchDir(const string &s);
        void SearchAllFich(list<string> &lres, const string &file );
        void SearchAllDir(list<string> &lres, const string &dir );
        void RenomearFicheiros(const string &fich_old,const string &fich_new);
        bool RemoverAll(const string &s, const string &tipo);
        void FicheirosDuplicados(map<string,unsigned int> &encontrados);
        string *Caminho();
        void SetDirPai(Directoria *pai);
        Directoria *DirPai();
        list<Directoria*> &FilhosDir();
        list<Ficheiro*> &FilhosFich();
    protected:

    private:
};

#endif // DIRECTORIA_H
