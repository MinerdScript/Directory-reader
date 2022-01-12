#include "XMLWriter.h"

XMLWriter::XMLWriter()
{
    //ctor
}

XMLWriter::~XMLWriter()
{
    //dtor
}

void XMLWriter::Espacos(int extra)
{
    F << string(N+extra, '\t');
}

bool XMLWriter::AbreDocumento(string documento)
{
    if(F.is_open())
    {
        cout << "Um documento XML ja esta aberto." << endl;
        return false;
    }
    F.open(documento);
    if(!F.is_open())
    {
        cout << "Erro ao abrir documento XML." << endl;
        return false;
    }
    N = 0;
    return true;
}

bool XMLWriter::FechaDocumento()
{
    if(!F.is_open())
    {
        cout << "Erro ao fechar documento: nenhum documento aberto." << endl;
        return false;
    }
    F.close();
    if(F.is_open())
    {
        cout << "Erro ao fechar documento." << endl;
        return false;
    }
    return true;
}

void XMLWriter::EscreveDiretoria(Directoria *directoria)
{
    Espacos();
    F << "<directoria>" << endl;

    EscreveAtributo("nome", directoria->Nome());



    list<Ficheiro*> filhosFich = directoria->FilhosFich();
    if(filhosFich.size())
    {
        Espacos(1);
        N += 2;
        F << "<ficheiros>" << endl;
        for(list<Ficheiro*>::iterator it = filhosFich.begin(); it != filhosFich.end(); it++)
        {
            EscreveFicheiro((*it));
        }
        N -= 2;
        Espacos(1);
        F << "</ficheiros>" << endl;
    }
    list<Directoria*> filhosDir = directoria->FilhosDir();
    if(filhosDir.size())
    {
        Espacos(1);
        F << "<directorias>" << endl;
        N += 2;
        for(list<Directoria*>::iterator it = filhosDir.begin(); it != filhosDir.end(); it++)
        {
            EscreveDiretoria((*it));
        }
        N -= 2;
        Espacos(1);
        F << "</directorias>" << endl;
    }

    Espacos();
    F << "</directoria>" << endl;
}

void XMLWriter::EscreveFicheiro(Ficheiro *ficheiro)
{
    Espacos();
    F << "<ficheiro>" << endl;

    EscreveAtributo("nome", ficheiro->Nome());
    EscreveAtributo("tamanho", to_string(ficheiro->Tamanho()));
    EscreveAtributo("dataM", *(ficheiro->DataM()));

    Espacos();
    F << "</ficheiro>" << endl;
}

void XMLWriter::EscreveAtributo(string atributo, string valor)
{
    Espacos(1);
    F << "<" << atributo << ">" << valor << "</" << atributo << ">" << endl;
}
