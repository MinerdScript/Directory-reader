#ifndef OBJETOGERAL_H
#define OBJETOGERAL_H

#include <string>
using namespace std;

class ObjetoGeral
{

    public:
        ObjetoGeral();
        virtual ~ObjetoGeral();
        void SetNome(string _novo);
        string &Nome();
    protected:
        string nome;

    private:
};

#endif // OBJETOGERAL_H
