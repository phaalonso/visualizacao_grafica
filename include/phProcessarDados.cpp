#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "phProcessarDados.hpp"
#include "desenhoBasico.hpp"

using namespace std;

/**
 * @brief Aloca um no da lista
 * 
 * @return listaDados* 
 */
listaDados *getNode()
{
    return (listaDados *)malloc(sizeof(listaDados));
}

/**
 * @brief Verifica se a lista esta vazia
 * 
 * @param lista 
 * @return int 
 */
int listaVazia(listaDados *lista)
{
    return lista == NULL;
}

/**
 * @brief Insere no final da lista
 * 
 * @param lista 
 * @param dados 
 * @return listaDados* 
 */
listaDados *insereFim(listaDados *lista, phPonto dados)
{
    listaDados *q, *aux;

    q = getNode();

    if (q != NULL)
    {
        q->ponto = dados;
        q->next = NULL;

        if (lista == NULL)
        {
            lista = q;
        }
        else
        {
            aux = lista;
            while (aux->next != NULL)
                aux = aux->next;

            aux->next = q;
        }

        return lista;
    }
    else
    {
        std::cout << "Erro na alocacao" << std::endl;
        return NULL;
    }
}

/**
 * @brief Função map, utiliza para mapear um numero que um range par outro, retirada do codigo fonte do Arduino
 * 
 * @param x 
 * @param in_min 
 * @param in_max 
 * @param out_min 
 * @param out_max 
 * @return float 
 */
float map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (float)(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * @brief Processa uma linha de dados
 * 
 * @param line 
 * @return arvore 
 */
phPonto processarDadosToponto(string line)
{
    string word;
    phPonto dado;

    stringstream s(line);

    getline(s, word, ','); // Nome

    getline(s, word, ','); // Time
    if (word == "BAL")
    {

        dado.r = 50;
        dado.g = 162;
        dado.b = 82;
    }
    else if (word == "CWS")
    {

        dado.r = 50;
        dado.g = 168;
        dado.b = 139;
    }
    else if (word == "ANA")
    {

        dado.r = 72;
        dado.g = 50;
        dado.b = 168;
    }
    else if (word == "BOS")
    {

        dado.r = 168;
        dado.g = 60;
        dado.b = 138;
    }
    else if (word == "CLE")
    {

        dado.r = 168;
        dado.g = 50;
        dado.b = 66;
    }
    else
    {

        dado.r = 255;
        dado.g = 255;
        dado.b = 255;
    }

    getline(s, word, ','); // Posição

    // Determina o formato do ponto de acordo com a posição no time
    if (word == "Catcher") {
        dado.tipo = PONTO;
    } else if (word == "Baseman") {
        dado.tipo = CIRCULO;
    } else if (word == "Shortstop") {
        dado.tipo = ESFERA;
    } else if (word == "Outfielder") {
        dado.tipo = CUBO;
    } else if (word == "Hitter") {
        dado.tipo = PIRAMIDE;
    } else if (word == "Pitcher") {
        dado.tipo = TRIANGULO;
    }

    getline(s, word, ',');
    dado.x = map(stof(word), 170, 210, -2.5, 2.5); // Altura

    getline(s, word, ',');
    dado.y = map(stof(word), 60, 135, -2.5, 2.5); // Peso

    getline(s, word, ',');
    dado.z = map(stof(word), 20, 50, 0, -5); // Idade

    dado.tamanho = 3;

    return dado;
}

/**
 * @brief Ler arquivo CSV presente com os dados
 * 
 * @param lista 
 * @return listaDados* 
 */
listaDados *lerDados(listaDados *lista)
{
    phPonto dados;

    std::fstream file;

    file.open("processed_mlb.csv", std::ios::in);

    if (!file)
    {
        std::cout << "Arquivo não encontrado" << std::endl;
        exit(1);
    }

    string line, word, temp;

    // Le o header do arquivo csv
    getline(file, line);

    do
    {
        getline(file, line);
        dados = processarDadosToponto(line);
        lista = insereFim(lista, dados);
    } while (file >> temp);

    return lista;
}

/**
 * @brief Imprime os dados da arvore
 * 
 * @param a 
 */
void imprimirPonto(phPonto p)
{
    std::cout << "( " << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
}

/**
 * @brief Imprime a lista
 * 
 * @param dados 
 */
void imprimirLista(listaDados *dados)
{
    listaDados *aux = dados;
    while (aux != NULL)
    {
        // std::cout << aux << std::endl;
        imprimirPonto(aux->ponto);
        aux = aux->next;
    }
}

/**
 * @Desenha dados
 * 
 * @param ponto 
 * @param tamanho 
 */
void phDesenharPontoArvore(phPonto *ponto)
{
    switch (ponto->tipo)
    {
    case PONTO:
        phDesenharPonto(ponto);
        break;
    case CIRCULO:
        phDesenhaCirculo(*ponto, 0.05);
        break;
    case ESFERA:
        phDesenharEsfera(*ponto, 0.05);
        break;
    case CUBO:
        phDesenharCuboPonto(*ponto, 0.05);
        break;
    case PIRAMIDE:
        phDesenharPiramide(*ponto, 0.1);
        break;
    case TRIANGULO:
        phDesenharTriangulo(*ponto, 0.1);
        break;
    }
}

/**
 * @brief desenha os dados da lista
 * 
 * @param lista 
 */
void phDesenharDados(listaDados *lista)
{
    if (listaVazia(lista))
        return;

    listaDados *aux = lista;

    while (aux != NULL)
    {
        phDesenharPontoArvore(&(aux->ponto));
        aux = aux->next;
    }
}