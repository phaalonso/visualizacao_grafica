#ifndef PHDESENHOBASICO_INCLUDE
#define PHDESENHOBASICO_INCLUDE

#include <GLFW/glfw3.h>

enum formatos {
    PONTO = 0,
    CIRCULO = 1,
    ESFERA = 2,
    CUBO = 3,
    PIRAMIDE = 4,
    TRIANGULO = 6
};

typedef struct phPonto {
    GLfloat x, y, z;
    GLubyte r, g, b;
    GLfloat tamanho;
    formatos tipo;
} phPonto;

typedef struct pontosData {
    GLfloat x, y, z;
    GLubyte r, g, b;
    GLfloat tamanho;
    struct pontosData *next;
} pontosData;

void phDesenharRetangulo(float minX, float minY, float maxX, float maxY);
void phDesenhaCirculo(phPonto centro, float raio);
void phDesenharPontosElementos();
void phDesenharPonto(phPonto *ponto);
void phDesenharEsfera(phPonto ponto, double raio);
void phDesenharCuboFixo();
void phDesenharPiramide(phPonto ponto, float a);
void phDesenharEixosOrigem(float inicioEixo, float fimEixo);
void phDesenharGrid(float initWidth, float endWidth, int passo);
void phInserirData(pontosData *pontos);
void phCubo(float pontox, float pontoy, float posZ, float width);
void phDesenharCuboPonto(phPonto ponto, float width);
void phDesenharTriangulo(phPonto ponto, float a);

#endif