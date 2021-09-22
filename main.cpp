#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#define DISPLAYSIZE 12

using namespace std;

                        /* Instru��es do exercicio*/

/*
    Desenvolver um programa C para gerenciar uma fila de espera para um escrit�rio.
    O programa deve a cada novo cliente, solicitar seu nome e informar um n�mero de senha aleat�rio.
    O nome junto com o n�mero de senha devem ser inseridos em uma fila circular com aloca��o sequencial,
    com no m�ximo 20 posi��es de mem�ria.
    Cada posi��o armazena os dados (n�mero e nome) de um cliente.
    As inser��es s�o sempre realizadas no final da fila.
    O programa deve tamb�m oferecer a op��o de indicar o pr�ximo cliente a ser atendido.
    Neste caso deve retirar o primeiro elemento da fila circular, e informa o n�mero e nome do cliente.
    O programa deve tamb�m oferecer uma op��o de finaliza��o.
*/

class Fila
{
public:

    // Initialize front and rear
    int fim, inicio;

    // Circular Queue
    int tamanhoDaFila;
    int *intArr;
    string *stringArr;

    Fila(int s)
    {
       inicio = fim = -1;
       tamanhoDaFila = s;
       intArr = new int[s];
       stringArr = new string[s];
    }

    void enfileirar(int value, string name);
    int desenfileirar();
    void displayFila();
};

void Fila::enfileirar(int value, string name)
{
    if ((inicio == 0 && fim == tamanhoDaFila-1) ||
            (fim == (inicio-1)%(tamanhoDaFila-1)))
    {
        cout << "\nA fila esta cheia." << endl;
        return;
    }

    else if (inicio == -1) /* inserindo primeiro elemento */
    {
        inicio = fim = 0;
        intArr[fim] = value;
        stringArr[fim] = name;
    }

    else if (fim == tamanhoDaFila-1 && inicio != 0)
    {
        fim = 0;
        intArr[fim] = value;
        stringArr[fim] = name;
    }

    else
    {
        fim++;
        intArr[fim] = value;
        stringArr[fim] = name;
    }
}

// Funcao para chamar o proximo paciente
int Fila::desenfileirar()
{
    if (inicio == -1)
    {
        cout << "\nA fila esta vazia" << endl;
        return INT_MIN;
    }

    int senha = intArr[inicio];
    string data = stringArr[inicio];
    intArr[inicio] = -1;
    stringArr[inicio] = "";
    if (inicio == fim)
    {
        inicio = -1;
        fim = -1;
    }
    else if (inicio == tamanhoDaFila-1)
        inicio = 0;
    else
        inicio++;

    cout << "\nPaciente: " << data << "\nSenha: " << senha << endl;
}

// Displays para organizar a visualiza��o da fila.
void getStringDisplay(string str)
{
    string displayAux[DISPLAYSIZE] = {"|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|"};
    int k = 0;
    for(int i=((DISPLAYSIZE-str.size())/2); i<DISPLAYSIZE;i++)
    {
        if(k<str.size())
        {
            displayAux[i]=str[k];
            k++;
        }
    }
    for(int i=0; i<DISPLAYSIZE;i++)
    {
        cout << displayAux[i];
    }
}

void getIntDisplay(int intToConvert)
{
    auto str = to_string(intToConvert);
    string displayAux[DISPLAYSIZE] = {"|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|"};
    int k = 0;
    for(int i=((DISPLAYSIZE-str.size())/2); i<DISPLAYSIZE;i++)
    {
        if(k<str.size())
        {
            displayAux[i]=str[k];
            k++;
        }
    }
    for(int i=0; i<DISPLAYSIZE;i++)
    {
        cout << displayAux[i];
    }
}

void Fila::displayFila()
{
    if (inicio == -1)
    {
        cout << "\nA fila esta vazia" << endl;
        return;
    }

    printf("\nLista de pacientes aguardando atendimento: \n");
    string auxs = "Senha";
    string auxn = "Nome";
    getStringDisplay(auxs);
    getStringDisplay(auxn);
    cout << endl;
    if (fim >= inicio)
    {
        for (int i = inicio; i <= fim; i++)
        {
            int intAux = intArr[i];
            string stringAux = stringArr[i];
            getIntDisplay(intAux);
            getStringDisplay(stringAux);
            cout << endl;
        }
    }
    else
    {
        for (int i = inicio; i < tamanhoDaFila; i++)
        {
            int intAux = intArr[i];
            string stringAux = stringArr[i];
            getIntDisplay(intAux);
            getStringDisplay(stringAux);
            cout << endl;
        }
        for (int i = 0; i <= fim; i++)
        {
            int intAux = intArr[i];
            string stringAux = stringArr[i];
            getIntDisplay(intAux);
            getStringDisplay(stringAux);
            cout << endl;
        }
    }
}

void programStart(Fila f)
{
    int escolha = 0;
    cout << "\nBem vindo ao consultorio do Nivaldinho!"
         << "\nDigite o numero correspondente a acao que deseja tomar."
         << "\n1- Chamar o proximo paciente para ser atendido | 2- Adicionar novo paciente a fila \n3- Mostrar lista de atendimento | 0- ENCERRAR PROGRAMA\nSua escolha: ";
    cin >> escolha;

    switch (escolha)
    {
        case 1:
        {
            f.desenfileirar();
            programStart(f);
            break;
        }
        case 2:
        {
            cout << "\nDigite o nome do paciente: ";
            string stringAux;
            cin >> stringAux;
            // Gerando a senha de 1 at� 1000 para o paciente
            int intAux = rand() % 1000 + 1;
            f.enfileirar(intAux, stringAux);
            programStart(f);
        }
        case 3:
        {
            f.displayFila();
            programStart(f);
            break;
        }
        case 0:
        {
            abort();
            break;
        }
        default:
        {
            programStart(f);
            break;
        }
    }
    return;
}

int main()
{
    Fila f(20);
    programStart(f);

    return 0;
}
