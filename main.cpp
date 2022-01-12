#include <locale>
#include <iostream>
using namespace std;
#include "SistemaFicheiros.h"

int menu1(){
    int opt;
    cout <<"Escolha a opcao!"<<endl;
    cout <<"1-> Carregar a directoria \"C:/Diretoria Teste\";"<<endl;
    cout <<"2-> Ler um ficheiro XML;"<<endl;
    cout <<"0-> Prima 0 para sair do programa."<<endl;
    cin >> opt;
    if(opt >= 0 && opt <=2){
        cout <<endl <<endl;
        return opt;
    }
    cout << endl << "Essa opcao nao e valida!"<<endl<<endl;
    return menu1();
}

int menu2(){
    int opt;
    cout <<endl <<endl;
    cout <<"Escolha a opcao!"<<endl;
    cout <<"1-> Numero de ficheiros;"<<endl;
    cout <<"2-> Numero de directorias;"<<endl;
    cout <<"3-> Mostrar a memoria usada;"<<endl;
    cout <<"4-> Mostrar a directoria com mais elementos;"<<endl;
    cout <<"5-> Mostrar a directoria com menos elementos;"<<endl;
    cout <<"6-> Mostrar ficheiro que ocupa mais espaco em disco;"<<endl;
    cout <<"7-> Mostrar directoria que ocupa mais espaco em disco;"<<endl;
    cout <<"8-> Procurar uma determinada directoria ou ficheiro;"<<endl;
    cout <<"9-> Remover todos os ficheiros ou directorias com o nome especificado;"<<endl;
    cout <<"10-> Escrever em um arquivo no formato XML;"<<endl;
    cout <<"11-> Mover um ficheiro para outra directoria;"<<endl;
    cout <<"12-> Mover uma directoria para outra directoria mãe;"<<endl;
    cout <<"13-> Mostrar a data de modificação de um ficheiro;"<<endl;
    cout <<"14-> Observar a diretoria em formato tree;"<<endl;
    cout <<"15-> Pesquisar e mostrar uma lista de todas as diretorias com um certo nome;"<<endl;
    cout <<"16-> Pesquisar e mostrar uma lista de todos os ficheiros com um certo nome;"<<endl;
    cout <<"17-> Renomear ficheiro;"<<endl;
    cout <<"18-> Verificar se existem ficheiros repetidos;"<<endl;
    cout <<"19-> Copiar ficheiros para outra directoria mãe."<<endl;
    cout <<"0-> Prima 0 para sair do sub-menu."<<endl;
    cin >> opt;
    if(opt >= 0 && opt <=19){
        cout <<endl <<endl;
        return opt;
    }
    cout << endl << "Essa opcao nao e valida!"<<endl<<endl;
    return menu2();
}

int main()
{
    bool LoadFuncionou;
    setlocale(LC_ALL,"Portuguese");
    SistemaFicheiros *sistema = new SistemaFicheiros();
    int opt1=3, opt2=1;
    while(opt1>0){
        opt1 = menu1();
        opt2=1;
        if(opt1 == 0) return 0;
        if(opt1 == 1){
            LoadFuncionou = sistema->Load("C:/DirectoriaTeste");
            if(!LoadFuncionou){
                cout << "O programa nao teve sucesso ao abrir a diretoria, verifique se existe a diretoria com o seguinte caminho: \"C:/DirectoriaTeste\""<<endl<<endl<<endl;
                continue;
            }
        }
        if(opt1 == 2){
            LoadFuncionou= sistema->Ler_XML("dados.xml", sistema);
            if(!LoadFuncionou){
                cout << "O XML esta mal escrito! Verifique se o XML que pretender ler chama-se \"dados.xml\" e se encontra na pasta do programa."<<endl<<endl<<endl;
                continue;
            }
        }
        while(opt2>0){
            opt2 = menu2();
            switch(opt2){
                case 1:
                    cout << "Numero de ficheiros: " << sistema->ContarFicheiros() << endl;
                    break;
                case 2:
                    cout << "Numero de directorias: " << sistema->ContarDirectorias() << endl;
                    break;
                case 3:
                    cout << "Memoria: " << sistema->Memoria() << endl;
                    break;
                case 4:{
                    string *dirMaisElementos = sistema->DirectoriaMaisElementos();
                    cout << (*dirMaisElementos) << endl;
                    delete dirMaisElementos;
                    break;
                }
                case 5:{
                    string *dirMenosElementos = sistema->DirectoriaMenosElementos();
                    cout << (*dirMenosElementos) << endl;
                    delete dirMenosElementos;
                    break;
                }
                case 6:{
                    string *fichMaior = sistema->FicheiroMaior();
                    cout << (*fichMaior) << endl;
                    delete fichMaior;
                    break;
                }
                case 7:{
                    string *dirMaior = sistema->DirectoriaMaisEspaco();
                    cout << (*dirMaior) << endl;
                    delete dirMaior;
                    break;
                }
                case 8:{
                    //Search
                    string nome;
                    int opc;

                    cout<<"O que pretende pesquisar? Digite:"<<endl<<"0 - Ficheiro"<<endl<<"1 - Directoria"<<endl;
                    cin >> opc;

                    string *result;
                    if (opc == 0)
                    {
                        cout<<"Escreva o nome do ficheiro a encontrar."<<endl;
                        cin >> nome;
                        result = sistema->Search(nome, SistemaFicheiros::Tipo::ficheiro);
                        if (result)
                        {
                            cout << (*result) << endl;
                            delete result;
                        }
                        else
                            cout << "Ficheiro nao encontrado." << endl;
                    }
                    else if (opc == 1)
                    {
                        cout<<"Escreva o nome da directoria a encontrar."<<endl;
                        cin >> nome;
                        result = sistema->Search(nome, SistemaFicheiros::Tipo::directoria);
                        if (result)
                        {
                            cout << (*result) << endl;
                            delete result;
                        }
                        else
                            cout << "Directoria nao encontrada." << endl;
                    }
                    else
                    {
                        cout << "Opcao invalida." << endl;
                        break;
                    }
                    break;
                }
                case 9:{
                    //RemoverAll
                    string opc;
                    string nome;
                    cout<<"O que pretende remove? Digite:"<<endl<<"FICH - Ficheiro"<<endl<<"DIR - Directoria"<<endl;
                    cin >> opc;
                    if (opc != "FICH" && opc != "DIR")
                    {
                        cout << "Opcao invalida." << endl;
                        break;
                    }
                    else if (opc == "FICH")
                    {
                        cout<<"Escreva o nome de ficheiros a remover."<<endl;
                        cin >> nome;
                        if (sistema->RemoverAll(nome, opc))
                        {
                            cout<<"Ficheiros com o nome '"<<nome<<"' foram removidos com sucesso!";
                        }else {
                            cout<<"Ficheiros com o nome '"<<nome<<"' não foram removidos.";
                        }
                    }
                    else if (opc == "DIR")
                    {
                        cout<<"Escreva o nome de directorias a remover."<<endl;
                        cin >> nome;
                        if (sistema->RemoverAll(nome, opc))
                        {
                            cout<<"Directorias com o nome '"<<nome<<"' foram removidas com sucesso!";
                        }else {
                            cout<<"Directorias com o nome '"<<nome<<"' não foram removidas.";
                        }
                    }
                    break;
                }
                case 10:{
                    string nome;
                    cout<<"Escreva o nome do arquivo."<<endl;
                    cin >> nome;
                    sistema->Escrever_XML(nome);//"dados.xml"
                    break;
                }
                case 11:{
                    //MoverFicheiro
                    string nomeFich;
                    string nomeDir;
                    cout<<"Escreva o nome do ficheiro que deseja mover."<<endl;
                    cin >> nomeFich;
                    cout<<"Escreva o nome da directoria destino."<<endl;
                    cin >> nomeDir;
                    if (sistema->MoveFicheiro(nomeFich, nomeDir))
                    {
                        cout<<"Ficheiro movido para a directoria destino com sucesso!"<<endl;
                    }else
                    {
                        cout<<"Nao foi possivel mover o ficheiro. Verifique se fez erros de escrita."<<endl;
                    }
                    break;
                }
                case 12:{
                    //MoverDirectoria
                    string nomeOrigem;
                    string nomeDestino;
                    cout<<"Escreva o nome da directoria origem."<<endl;
                    cin >> nomeOrigem;
                    cout<<"Escreva o nome da directoria destino."<<endl;
                    cin >> nomeDestino;
                    if (sistema->MoverDirectoria(nomeOrigem, nomeDestino))
                    {
                        cout<<"Directoria movida para a directoria destino com sucesso!"<<endl;
                    }else
                    {
                        cout<<"Nao foi possivel mover a directoria. Verifique se fez erros de escrita."<<endl;
                    }
                    break;
                }
                case 13:{
                    //DataFicheiro
                    string nomeFich;
                    cout<<"Escreva o nome do ficheiro."<<endl;
                    cin >> nomeFich;
                    string *resultado = sistema->DataFicheiro(nomeFich);
                    if (resultado)
                        cout<<(*resultado)<<endl;
                    else
                        cout<<"Ficheiro nao encontrado. Verifique se fez erros de escrita."<<endl;
                    break;
                }
                case 14:{
                    string *nomeFich = new string("tree.txt");
                    sistema->Tree(nomeFich);
                    delete nomeFich;
                    break;
                }
                //
                case 15:{
                    string nomeDir;
                    list<string> lres;
                    cout<<"Escreva o nome de diretoria que deseja guardar em uma lista e mostrar." <<endl;
                    cin >> nomeDir;
                    sistema->PesquisarAllDirectorias(lres, nomeDir);
                    int index = 1;
                    cout<<"Esta e a lista das diretorias:"<<endl<<endl;
                    for(list<string>::iterator i = lres.begin(); i!=lres.end(); i++){
                        cout << index <<"-> "<< *i;
                        index++;
                    }
                    break;
                }
                //
                case 16:{
                    string nomeFich;
                    list<string> lres;
                    cout<<"Escreva o nome do ficheiro que deseja guardar em uma lista e mostrar." <<endl;
                    cin >> nomeFich;
                    sistema->PesquisarAllFicheiros(lres, nomeFich);
                    cout<<"Esta e a lista dos ficheiros:"<<endl<<endl;
                    int index=1;
                    for(list<string>::iterator i = lres.begin(); i!=lres.end(); i++){
                        cout << index <<"-> "<< *i;
                        index++;
                    }
                    break;
                }
                case 17:{
                    string fich_old, fich_new;
                    cout<<"Digite o nome antigo."<<endl;
                    cin>>fich_old;
                    cout<<"Digite o novo nome do ficheiro."<<endl;
                    cin>>fich_new;
                    sistema->RenomearFicheiros(fich_old, fich_new);
                    break;
                }
                case 18:{
                    if(sistema->FicheiroDuplicados()){
                        cout<<"Existem ficheiros duplicados."<<endl;
                    }else{
                        cout<<"Nao existe nenhum ficheiro duplicado."<<endl;
                    }
                    break;
                }
                case 19:{
                    //CopyBatch
                    string padrao;
                    string nomeOrigem;
                    string nomeDestino;

                    cout<<"Digite o padrao a encontrar."<<endl;
                    cin >> padrao;

                    cout<<"Escreva o nome da directoria origem."<<endl;
                    cin >> nomeOrigem;

                    cout<<"Escreva o nome da directoria destino."<<endl;
                    cin >> nomeDestino;

                    if (sistema->CopyBatch(padrao, nomeOrigem, nomeDestino))
                    {
                        cout<<"Ficheiros movido para a directoria destino com sucesso!"<<endl;
                    }else{
                        cout<<"Operacao nao foi concluida com sucesso. Verifique se fez erros de escrita."<<endl;
                    }
                    break;
                }

                case 0:
                    break;
                default:{
                    cout<<"Ocorreu algum erro na escolha da opcao no menu."<<endl;
                    break;
                }
            }
        }
    }
    return 0;
}
