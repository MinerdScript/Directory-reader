#include "SistemaFicheiros.h"

SistemaFicheiros::SistemaFicheiros()
{
    //ctor
}

SistemaFicheiros::~SistemaFicheiros()
{
    //dtor
    if(raiz)
        delete raiz;
}

string Espacos(int N)
{
    string s = "";
    for (int i = 0; i < N; i++)
        s.append("\t");
    return s;
}

char* FormatarData(time_t valor)
{
    char *data = (char*)malloc(36 * sizeof(char));
    strftime(data, 36, "%d.%m.%Y %H:%M:%S", localtime(&valor));
    return data;
}

bool SistemaFicheiros::ProcessaDir(const string &path, int N, Directoria *pai, Directoria *estaDir)
{
    bool RET = true;
    DIR *dir;
    struct dirent *abrir;
    struct stat status;

    if ((dir = opendir(path.c_str())) != NULL)
    {
        if(!pai)
        {
            estaDir = new Directoria();
            estaDir->SetNome(path);
            raiz = estaDir;
        }

        //cout << Espacos(N) << estaDir->Nome() << endl;
        while ((abrir = readdir(dir)) != NULL) {
            if ((strcmp(abrir->d_name, ".") != 0) && (strcmp(abrir->d_name, "..") != 0))
			{
			    string p = path;
                p.append("/");
                p.append(abrir->d_name);
                stat(p.c_str(), &status);

			    //cout << Espacos(N) << abrir->d_name << ";" << endl;
                if (S_ISDIR(status.st_mode))
                {
                    //Directoria
                    Directoria *filho = new Directoria();
                    filho->SetNome(abrir->d_name);
                    //Adicionar filho ao pai e indicar pai ao filho
                    filho->SetDirPai(estaDir);

                    RET = ProcessaDir(p, N+1, estaDir, filho);
                    if(!RET)
                        return RET;
                }else if(S_ISREG(status.st_mode))
                {
                    //Ficheiro
                    //cout << Espacos(N) << abrir->d_name << ";" << endl;
                    Ficheiro *filhoFich = new Ficheiro(status.st_size);

                    char *data = FormatarData(status.st_mtime);
                    filhoFich->SetDataM(new string(data));
                    //cout << Espacos(N) << *filhoFich->DataM() << endl;
                    delete data;

                    filhoFich->SetNome(abrir->d_name);
                    //Adicionar filho ao pai e indicar pai ao filho
                    filhoFich->SetDirPai(estaDir);
                }
			}
        }
        closedir(dir);
    }else{
        RET = false;
    }
    dir = NULL;
    return RET;
}

bool SistemaFicheiros::Load(const string &path)
{
    if (raiz)
        delete raiz;
    raiz = NULL;
    return ProcessaDir(path, 0, NULL, NULL);
}

int SistemaFicheiros::ContarFicheiros()
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    if(raiz)
        return raiz->ContarFicheiros(true);

    return -1;
}

int SistemaFicheiros::ContarDirectorias()
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    if(raiz)
        return raiz->ContarDirectorias(true);
    return -1;
}

int SistemaFicheiros::Memoria()
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    if(raiz)
        return raiz->Memoria(true);
    return -1;
}

string *SistemaFicheiros::DirectoriaMaisElementos()
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    unsigned int N = 0;
    Directoria *maior = raiz->DirectoriaMaisElementos(NULL, N);

    if(maior)
        return maior->Caminho();
    else{
        cout << "Error: [" <<__FUNCTION__ << "] Directoria maior foi NULL" << endl;
    }
    return new string;
}

string *SistemaFicheiros::DirectoriaMenosElementos()
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    unsigned int N = 999999999;
    Directoria *menor = raiz->DirectoriaMenosElementos(NULL, N);

    if(menor)
        return menor->Caminho();
    else{
        cout << "Error: [" <<__FUNCTION__ << "] Directoria menor foi NULL" << endl;
    }
    return new string;
}

string *SistemaFicheiros::FicheiroMaior()
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    off_t N = 0;
    Ficheiro *maior = raiz->FicheiroMaior(NULL, N);
    if(maior)
    {
        string *caminho = maior->DirPai()->Caminho();
        caminho->append("/");
        caminho->append(maior->Nome());
        return caminho;
    }else{
        cout << "Error: [" <<__FUNCTION__ << "] Ficheiro maior foi NULL" << endl;
    }
    return new string;
}

string *SistemaFicheiros::DirectoriaMaisEspaco()
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    unsigned int N = 0;
    Directoria *maior = raiz->DirectoriaMaisEspaco(NULL, N);

    if(maior)
        return maior->Caminho();
    else{
        cout << "Error: [" <<__FUNCTION__ << "] Directoria maior foi NULL" << endl;
    }
    return NULL;
}

string *SistemaFicheiros::Search(const string &s, int Tipo)
{
    cout << "[" <<__FUNCTION__ << "]" << endl;

    if(!Tipo)
    {
        //Ficheiro
        Ficheiro *encontrado = raiz->SearchFich(s);
        if(encontrado)
        {
            string *Caminho = NULL;
            Caminho = encontrado->DirPai()->Caminho();
            Caminho->append("/");
            Caminho->append(encontrado->Nome());
            //delete encontrado;
            return Caminho;
        }
    }else
    {
        Directoria *encontrado = raiz->SearchDir(s);
        if(encontrado)
        {
            return encontrado->Caminho();
            //delete encontrado;
        }
    }

    return NULL;
}

bool SistemaFicheiros::RemoverAll(const string &s, const string &tipo)
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    return raiz->RemoverAll(s, tipo);
}

void SistemaFicheiros::Escrever_XML(const string &s)
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    XMLWriter *xml = new XMLWriter();

    xml->AbreDocumento(s);
    xml->EscreveDiretoria(raiz);
    xml->FechaDocumento();

    delete xml;
}

bool SistemaFicheiros::Ler_XML(const string &s, SistemaFicheiros *sistema)
{
    bool valorParaRetorno;
    if(raiz){
        delete raiz;
        raiz = NULL;
    }

    XMLReader *xml = new XMLReader(sistema);
    valorParaRetorno = xml->AbreDocumento(s);
    xml->FechaDocumento();
    delete xml;
    return valorParaRetorno;
}

bool SistemaFicheiros::MoveFicheiro(const string &NomeFich, const string &DirNova)
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    Ficheiro *fich = raiz->SearchFich(NomeFich);
    Directoria *dirNova = raiz->SearchDir(DirNova);

    if(fich && dirNova)
    {
        fich->DirPai()->RemoveFich(fich);
        fich->SetDirPai(dirNova);
        return true;
    }
    return false;
}

bool SistemaFicheiros::MoverDirectoria(const string &DirOld, const string &DirNew)
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    Directoria *dirOld = raiz->SearchDir(DirOld);
    if(!dirOld) return false;



    Directoria *dirNew = raiz->SearchDir(DirNew);

    Directoria *dir = dirNew->DirPai();
    bool descendente = false;

    while(dir && !descendente)
    {
        if(dir->Nome() == dirOld->Nome())
        {
            descendente = true;
        }
        dir = dir->DirPai();
    }

    if(dirNew && !descendente)
    {
        dirOld->DirPai()->RemoveDir(dirOld);
        dirOld->SetDirPai(dirNew);
        return true;
    }
    return false;
}

string *SistemaFicheiros::DataFicheiro(const string &ficheiro)
{
    cout << "[" <<__FUNCTION__ << "]" << "< const string &ficheiro = " << ficheiro << ">" << endl;
    Ficheiro *fich = raiz->SearchFich(ficheiro);

    if (fich) {
        return fich->DataM();
    }
    return NULL;
}

void SistemaFicheiros::Tree(const string *fich)
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    ofstream F;
    if (fich)
        F.open(*fich);

    vector<bool> niveis;
    niveis.push_back(false); //começar com o nivel 0 em falso
    raiz->Tree(F, 0, niveis);

    if (F.is_open())
        F.close();
}

void SistemaFicheiros::PesquisarAllDirectorias(list<string> &lres, const string &dir)
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    raiz->SearchAllDir(lres, dir);
}

void SistemaFicheiros::PesquisarAllFicheiros(list<string> &lres, const string &file)
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    raiz->SearchAllFich(lres, file);
}

void SistemaFicheiros::RenomearFicheiros(const string &fich_old,const string &fich_new)
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    raiz->RenomearFicheiros(fich_old, fich_new);
}

bool SistemaFicheiros::FicheiroDuplicados()
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    map<string,unsigned int> encontrados;
    raiz->FicheirosDuplicados(encontrados);
    map<string,unsigned int>::iterator it;
    bool repetidos = false;
    for (auto const& par : encontrados)
    {
        //cout << par.first << "; " << par.second << endl;
        if (par.second > 0)
        {
            if (par.second == 1)
                cout << "O ficheiro '" << par.first << "' esta repetido " << par.second << " vez." << endl;
            else
                cout << "O ficheiro '" << par.first << "' esta repetido " << par.second << " vezes." << endl;
            repetidos = true;
        }
    }
    return repetidos;
}

bool SistemaFicheiros::CopyBatch(const string &padrao, const string &nomeDirOrigem, const string &nomeDirDestino)
{
    cout << "[" <<__FUNCTION__ << "]" << endl;
    Directoria *dirOrigem = raiz->SearchDir(nomeDirOrigem);
    if(!dirOrigem) return false;

    Directoria *dirDestino = raiz->SearchDir(nomeDirDestino);
    if(!dirDestino) return false;
    map<string, unsigned int> encontrados;

    list<Ficheiro*> fichEncontrados;
    dirOrigem->PluralSearchFich(fichEncontrados, padrao);

    string nomeFich;
    for(list<Ficheiro*>::iterator itFich = fichEncontrados.begin(); itFich != fichEncontrados.end(); itFich++)
    {
        nomeFich = (*itFich)->Nome();
        map<string, unsigned int>::iterator it = encontrados.find(nomeFich);
        if (it != encontrados.end())//.count 0 ou 1, false ou true
        {
            //elemento encontrado no mapa
            it->second++;
        }
        else
            encontrados.insert({nomeFich, 0});
    }

    for(list<Ficheiro*>::iterator itFich = fichEncontrados.begin(); itFich != fichEncontrados.end(); itFich++)
    {
        nomeFich = (*itFich)->Nome();//referência&
        map<string, unsigned int>::iterator it = encontrados.find(nomeFich);
        if (it != encontrados.end())
        {
            if (it->second > 0)
            {
                nomeFich.append(to_string(it->second));
                it->second--;
            }
            //remove ficheiro do pai
            (*itFich)->DirPai()->RemoveFich((*itFich));
            //adiciona ficheiro ao novo pai
            (*itFich)->SetDirPai(dirDestino);
        }
    }

    return true;
}

Directoria *SistemaFicheiros::Raiz(){
    return raiz;
}

void SistemaFicheiros::SetRaiz(Directoria *ptrRaiz){
    raiz = ptrRaiz;
}
