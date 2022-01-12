#include "Directoria.h"

Directoria::Directoria()
{
    //ctor
}

Directoria::~Directoria()
{
    for(list<Ficheiro*>::iterator it = filhosFich.begin(); it != filhosFich.end(); it++)
    {
        delete (*it);
    }
    filhosFich.clear();

    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
    {
        delete (*it);
    }
    filhosDir.clear();
}

bool Directoria::AddDir(Directoria *dir)
{
    filhosDir.push_back(dir);
    return true;
}

bool Directoria::AddFich(Ficheiro *fich)
{
    filhosFich.push_back(fich);
    return true;
}

void Directoria::RemoveDir(Directoria *dir)
{
    filhosDir.remove(dir);
}

void Directoria::RemoveDir(const string &nomeDir)
{

}

void Directoria::RemoveFich(Ficheiro *fich)
{
    filhosFich.remove(fich);
}

void Directoria::RemoveFich(const string &nomeFich)
{

}

list<Directoria*> &Directoria::FilhosDir()
{
    return filhosDir;
}

list<Ficheiro*> &Directoria::FilhosFich()
{
    return filhosFich;
}

unsigned int Directoria::ContarFicheiros(bool recursivo)
{
    unsigned int conta = filhosFich.size();
    if(recursivo)
    {
        for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
        {
            conta += (*it)->ContarFicheiros(true);
        }
    }
    return conta;
}

unsigned int Directoria::ContarDirectorias(bool recursivo)
{
    unsigned int conta = filhosDir.size();
    if(recursivo && conta)//Não vale a pena entrar no for() com conta == 0
    {
        for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
        {
            conta += (*it)->ContarDirectorias(true);
        }
    }
    return conta;
}

unsigned int Directoria::Memoria(bool recursivo)
{
    unsigned int conta = sizeof(Directoria);
    conta += sizeof(list<Directoria*>);
    conta += sizeof(list<Ficheiro*>);
    conta += sizeof(Ficheiro)*filhosFich.size();
    conta += sizeof(string) + sizeof(char)*Nome().length();//nome
    if(recursivo)
        for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
            conta += (*it)->Memoria(true);
    return conta;
}

Directoria *Directoria::DirectoriaMaisElementos(Directoria *maior, unsigned int &maiorN)
{
    unsigned int N = ContarFicheiros(false) + ContarDirectorias(false);//recursivo = false
    if(N > maiorN)
    {
        maiorN = N;
        maior = this;
    }
    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
    {
        maior = (*it)->DirectoriaMaisElementos(maior, maiorN);
    }
    return maior;
}

Ficheiro *Directoria::FicheiroMaior(Ficheiro *maior, off_t &maiorN)
{
    for(list<Ficheiro*>::iterator it = filhosFich.begin(); it != filhosFich.end(); it++)
    {
        if((*it)->Tamanho() > maiorN)
        {
            maiorN = (*it)->Tamanho();
            maior = (*it);
        }
    }
    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
    {
        maior = (*it)->FicheiroMaior(maior, maiorN);
    }
    return maior;
}

Directoria *Directoria::DirectoriaMenosElementos(Directoria *menor, unsigned int &menorN)
{
    unsigned int N = ContarFicheiros(false) + ContarDirectorias(false);//recursivo = false
    if(N < menorN)
    {
        menorN = N;
        menor = this;
    }
    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
    {
        menor = (*it)->DirectoriaMenosElementos(menor, menorN);
    }
    return menor;
}

Directoria *Directoria::DirectoriaMaisEspaco(Directoria *maior, unsigned int &maiorN)
{
    unsigned int N = 0;//Memoria(false);//recursivo = false
    //cout << this->Nome() << " : " << N << endl;
    for(list<Ficheiro*>::iterator it = filhosFich.begin(); it != filhosFich.end(); it++)
    {
        N += (unsigned int)(*it)->Tamanho();
    }
    if(N > maiorN)
    {
        maiorN = N;
        maior = this;

    }
    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
    {
        maior = (*it)->DirectoriaMaisEspaco(maior, maiorN);
    }
    return maior;
}

Ficheiro *Directoria::SearchFich(const string &s)
{
    for(list<Ficheiro*>::iterator it = filhosFich.begin(); it != filhosFich.end(); it++)
    {
        if((*it)->Nome() == s)
        {
            return (*it);
        }
    }
    Ficheiro *RET = NULL;
    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
    {
        RET = (*it)->SearchFich(s);
        if(RET)
            return RET;
    }
    return RET;
}

void Directoria::PluralSearchFich(list<Ficheiro*> &encontrados, const string &padrao)
{
    for(list<Ficheiro*>::iterator it = filhosFich.begin(); it != filhosFich.end(); it++)
    {
        if((*it)->Nome().find(padrao) != string::npos)
        {
            encontrados.push_back((*it));
        }
    }
    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
    {
        (*it)->PluralSearchFich(encontrados, padrao);
    }
}

Directoria *Directoria::SearchDir(const string &s)
{
    if(nome == s)
        return this;
    Directoria *RET = NULL;
    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
    {
        RET = (*it)->SearchDir(s);
        if(RET)
            break;
    }
    return RET;
}

string *Directoria::Search(const string &s, int &Tipo)
{

    if(Tipo == 0)
    {
        string *caminho;
        //Search ficheiro
        for(list<Ficheiro*>::iterator it = filhosFich.begin(); it != filhosFich.end(); it++)
        {
            if((*it)->Nome() == s)
            {
                caminho = Caminho();
                caminho->append("/"+(*it)->Nome());
                return caminho;
            }
        }
    }else{
        //Search directoria
        if(nome == s)
            return Caminho();
    }
    string *RET = NULL;

    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
    {
        RET = (*it)->Search(s, Tipo);
        if(RET)
            break;
    }
    return RET;
}

void Directoria::SearchAllFich(list<string> &lres, const string &file){
    string *caminho;
    for(list<Ficheiro*>::iterator it = filhosFich.begin(); it != filhosFich.end(); it++){
        if((*it)->Nome() == file)
        {
            caminho = Caminho();
            caminho->append("/"+(*it)->Nome());
            lres.push_back(*caminho);
        }
    }
    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++){
        (*it)->SearchAllFich(lres, file);
    }
}

void Directoria::SearchAllDir(list<string> &lres, const string &dir){
    string *caminho;
    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++){
        if((*it)->Nome() == dir)
        {
            caminho = Caminho();
            caminho->append("/"+(*it)->Nome());
            lres.push_back(*caminho);
        }
        (*it)->SearchAllDir(lres, dir);
    }
}

void Directoria::RenomearFicheiros(const string &fich_old,const string &fich_new){
    bool existeFichNew = false;
    Ficheiro *aux = NULL;
    for(list<Ficheiro*>::iterator it = filhosFich.begin(); it != filhosFich.end(); it++){
        if((*it)->Nome() == fich_old)
            aux = (*it);
        if((*it)->Nome() == fich_new)
           existeFichNew = true;
    }
    if(existeFichNew){
        cout << "Ja existe um ficheiro com o nome " << fich_new << " na diretoria " << Nome() << "."<<endl;
    }else if(aux!= NULL){
        aux->SetNome(fich_new);
    }
    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++){
        (*it)->RenomearFicheiros(fich_old, fich_new);
    }
}

void Directoria::FicheirosDuplicados(map<string, unsigned int> &encontrados){
    string nomeFich;
    for(list<Ficheiro*>::iterator fichIt = filhosFich.begin(); fichIt != filhosFich.end(); fichIt++)
    {
        nomeFich = (*fichIt)->Nome();
        map<string, unsigned int>::iterator it = encontrados.find(nomeFich);
        if (it != encontrados.end())//.count 0 ou 1, false ou true
        {
            //elemento encontrado no mapa
            it->second++;
            cout << it->second << endl;
        }
        else
            encontrados.insert({nomeFich, 0});

    }
    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
    {
        (*it)->FicheirosDuplicados(encontrados);
    }
}

bool Directoria::RemoverAll(const string &s, const string &tipo)
{
    bool RET = false;
    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
    {
        RET = (*it)->RemoverAll(s, tipo);
    }

    if(tipo=="DIR")
    {
        if(Nome() == s)
        {
            RET = true;
            delete this;
        }
    }else{
        for(list<Ficheiro*>::iterator it = filhosFich.begin(); it != filhosFich.end(); it++)
        {
            if((*it)->Nome() == s)
            {
                RET = true;
                filhosFich.remove((*it));
                delete (*it);
            }
        }
    }

    return RET;
}

void Directoria::Tree(ofstream &F, int nivel, vector<bool> &niveis)
{
    if(F.is_open())
    {
        F << nome << endl;
    }
    cout << nome << endl;

    nivel += 1;
    if(niveis.size() < nivel+1)
        niveis.push_back(true);
    niveis[nivel] = true;

    string s;

    for (int i = 1; i <= nivel; i++)
    {
        s+="\t";
        if (niveis[i]){
            s += "|";
            if (i == nivel)
                s += ">";
        }else
            s += " ";
    }

    for(list<Ficheiro*>::iterator it = filhosFich.begin(); it != filhosFich.end(); it++)
    {
        if((*it) == filhosFich.back() && !filhosDir.size())
            s.replace(2*nivel-1, 1, "-");
        if(F.is_open())
            F << s << (*it)->Nome() << endl;
        cout << s << (*it)->Nome() << endl;
    }

    s.replace(2*nivel, 1, "}");

    for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
    {
        if((*it) == filhosDir.back())
        {
            s.replace(2*nivel-1 , 1, "-");
            niveis[nivel] = false;
        }

        if(F.is_open())
            F << s;
        cout << s;

        (*it)->Tree(F, nivel, niveis);
    }

    niveis[nivel] = false;
}

string *Directoria::Caminho()
{
    string path;
    string barra = "/";
    Directoria *atual = this;
    while(atual)
    {
        path.insert(0, atual->Nome());
        atual = atual->DirPai();
        if(atual)
            path.insert(0, barra);
    }
    return new string(path);
}

void Directoria::SetDirPai(Directoria *pai)
{
    pai->AddDir(this);
    dirPai = pai;
}

Directoria *Directoria::DirPai()
{
    return dirPai;
}

