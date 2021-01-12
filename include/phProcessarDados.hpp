#ifndef PROCESSARDADOS_INCLUDE
#define PROCESSARDADOS_INCLUDE

#include <GLFW/glfw3.h>
#include "desenhoBasico.hpp"

extern float escalaPonto;
typedef struct listaDados {
    phPonto ponto;
    struct listaDados *next;
}listaDados;

listaDados* lerDados(listaDados *dados);
void imprimirLista(listaDados *dados);
void phDesenharDados(listaDados *lista);

#endif