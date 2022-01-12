#include "XMLReader.h"

#include "SistemaFicheiros.h"
#include "Directoria.h"
#include "Ficheiro.h"

XMLReader::XMLReader(SistemaFicheiros *sis)
{
    sistema = sis;
}

XMLReader::~XMLReader()
{
    //dtor
}

bool XMLReader::AbreDocumento(string documento)
{
    if(F.is_open())
    {
        cout << "Erro ao abrir " << documento << " para leitura: XMLReader já tem um documento aberto." << endl;
        return false;
    }
    F.open(documento);
    if(!F.is_open())
    {
        cout << "Erro ao abrir " << documento << " para leitura." << endl;
        return false;
    }
    LerDocumento();
    if(XMLMalEscrito)
            return false;
    return true;
}

bool XMLReader::FechaDocumento()
{
    if(!F.is_open())
    {
        cout << "Erro ao fechar o documento: XMLReader não tem nenhum documento aberto." << endl;
        return false;
    }
    F.close();
    if(F.is_open())
    {
        cout << "Erro ao fechar o documento." << endl;
        return false;
    }
    return true;
}

bool XMLReader::LerDocumento(){
    Directoria *dirPai = NULL;
    string line;
    while (getline(F, line)){
        Trim(line);
        dirPai = LerElemento(line, dirPai);
        if(XMLMalEscrito)
            return false;
    }
    return true;
}

Directoria* XMLReader::LerElemento(string &s, Directoria *dirPai)
{
    int j = 0;
    bool op = false, sfinal = false, iguais = false;
    string::iterator i;
    string tag_inicial, tag_final, conteudo;
    if(s[0]!='<'){
        cout << "Este XML esta mal escrito."<<endl;
        XMLMalEscrito = true;
        return dirPai;
    }
    for (i = s.begin(); i != s.end(); i++){
        tag_inicial+=*i;
        if(*i == '>'){
            i++;
            break;
        }

    }
    if(i!=s.end())
        sfinal = true;
    while(i!=s.end()){
        if(op == true)
            tag_final+=*i;
        if(*i=='<'){
            op = true;
            tag_final += *i;
        }
        if(!op) conteudo +=*i;
        i++;
    }
    if(sfinal == true){
        for (int n = 0; n<tag_inicial.length(); n++){
            if(tag_inicial[n]!=tag_final[j]){
                XMLMalEscrito = true;
                return dirPai;
            }
            j++;
            if(j==1)
                j++;
        }
    }
    if(tag_inicial.compare("<directoria>")==0){
        Directoria *dir = new Directoria();
        if(!dir){
            cout << "Ocorreu um erro ao criar a diretoria"<<endl;
            return dirPai;
        }
        if(!dirPai){
            sistema->SetRaiz(dir);
            return dir;
        }
        dir->SetDirPai(dirPai);
        return dir;
    }else if(tag_inicial.compare("</directoria>")==0){
        dirPai = dirPai->DirPai();
        return dirPai;
    }else if(tag_inicial.compare("<directorias>")==0){
        tagFicheiros = false;
        return dirPai;
    }else if(tag_inicial.compare("</directorias>")==0){
        return dirPai;
    }else if(tag_inicial.compare("<ficheiro>")==0){
        Ficheiro *fich = new Ficheiro();
        ficheiroTemp = fich;
        fich->SetDirPai(dirPai);
        return dirPai;
    }else if(tag_inicial.compare("</ficheiro>")==0){
        return dirPai;
    }else if(tag_inicial.compare("<ficheiros>")==0){
        tagFicheiros = true;
        return dirPai;
    }else if(tag_inicial.compare("</ficheiros>")==0){
        return dirPai;
    }else if(tag_inicial.compare("<nome>")==0){
        if(tagFicheiros==true){
            ficheiroTemp->SetNome(conteudo);
            return dirPai;
        }else{
            dirPai->SetNome(conteudo);
            return dirPai;
        }
    }else if(tag_inicial.compare("<tamanho>")==0){
        ficheiroTemp->SetTamanho(stoi(conteudo));
        return dirPai;
    }else if(tag_inicial.compare("<dataM>")==0){
        ficheiroTemp->SetDataM(&conteudo);
        return dirPai;
    }
    XMLMalEscrito = true;
    return dirPai;
}

void XMLReader::Trim(string &s){
    s.erase(remove(s.begin(), s.end(), '\t'), s.end());
}
