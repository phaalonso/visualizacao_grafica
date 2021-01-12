#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
#include "desenhoBasico.hpp"

void phDesenharRetangulo(float minX, float minY, float maxX, float maxY)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_LINE, GL_POINT, GL_FILL
    glColor3f(0.0, 0.0, 0.5);
    glLineWidth(1.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(minX, minY, 0.0f);
    glVertex3f(minX, maxY, 0.0f);
    glVertex3f(maxX, minY, 0.0f);
    glVertex3f(maxX, maxY, 0.0f);
    glEnd();
}

void phDesenhaCirculo(phPonto centro, float raio)
{
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(0.01);

    glColor3ub(centro.r, centro.g, centro.b);
    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(centro.x, centro.y, centro.z);

    float x1 = 0.0f;
    float y1 = 0.0f;

    for (int i = 0; i < 360; i++)
    {
        x1 = centro.x + cosf(i) * raio;
        y1 = centro.y + sinf(i) * raio;

        // std::cout << "X1:" << x1 << std::endl;
        // std::cout << "Y1:" << y1 << std::endl;

        glVertex3f(x1, y1, centro.z);
    }

    glEnd();
}

/**
 * @brief Função auxiliar para desenhar uma parte da esfera
 * 
 * @param u 
 * @param v 
 * @param ponto 
 * @param raio 
 */
void _pontoEsfera(double u, double v, phPonto ponto, double raio)
{
    double x, y, z;
    x = (cos(u) * sin(v) * raio) + ponto.x;
    y = (cos(v) * raio) + ponto.y;
    z = (sin(u) * sin(v) * raio) - ponto.z;

    // std::cout << x << " " << y << " " << z << std::endl;
    glVertex3f(x, y, -z);
}

/**
 * @brief Desenha a esfera a partir de um determinado centro, considerando um raio x
 * 
 * @param ponto 
 * @param raio 
 */
void phDesenharEsfera(phPonto ponto, double raio)
{
    double u, v, passo;

    passo = 0.1;
    glLineWidth(passo);
    glColor3ub(ponto.r, ponto.g, ponto.b);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);

    for (u = 0; u <= 2 * M_PI; u += passo)
    {
        for (v = 0; v <= M_PI; v += passo)
        {
            ///primeiro triangulo
            _pontoEsfera(u, v, ponto, raio);

            u += passo;
            _pontoEsfera(u, v, ponto, raio);

            u -= passo;
            v += passo;
            _pontoEsfera(u, v, ponto, raio);

            ///segundo triangulo
            v -= passo;
            u += passo;
            _pontoEsfera(u, v, ponto, raio);

            v += passo;
            _pontoEsfera(u, v, ponto, raio);

            u -= passo;
            _pontoEsfera(u, v, ponto, raio);
            v -= passo;
        }
    }

    glEnd();
}

void phDesenharPontosElementos()
{
    glPointSize(5.0f); // Tamanho do ponto
    glLineWidth(5.0f); // Tamanho do ponto

    // Experimento para o uso de glDrawElements
    float pontosCoords[4][3] = {
        //x, y, z
        {-5.0, 5.0, -100.0},
        {5.0, 5.0, -100.0},
        {5.0, -5.0, -5.0},
        {-5.0, -5.0, -5.0},
    };

    float pontosCor[4][3] = {
        //r, g, b
        {1.0, 0.0, 0.0},
        {0.0, 1.0, -100.0},
        {0.0, 0.0, -5.0},
        {0.0, 1.0, -5.0},
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pontosCoords); // Size, tipo deslocamento inicial, ponteiro
    glColorPointer(3, GL_FLOAT, 0, pontosCor);

    //Desenha
    glDrawArrays(GL_LINES, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

/**
 * @Desenha ponto
 * 
 * @param ponto 
 * @param tamanho 
 */
void phDesenharPonto(phPonto *ponto)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &ponto->x); // Tamanho, tipo, deslocamento inicial
    // glColorPointer(3, GL_FLOAT, 0, &ponto->r);
    glColorPointer(3, GL_UNSIGNED_BYTE, 0, &ponto->r);

    glPointSize(ponto->tamanho);   // Tamanho do ponto
    glDrawArrays(GL_POINTS, 0, 1); // Desenha um ponto

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

/**
 * @brief Desenha um cubo em uma posição fixa
 * 
 */
void phDesenharCuboFixo()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLfloat verticesCubo[] = {
        -1, -1, -1, -1, -1, 1, -1, 1, 1, -1, 1, -1,
        1, -1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1,
        -1, -1, -1, -1, -1, 1, 1, -1, 1, 1, -1, -1,
        -1, 1, -1, -1, 1, 1, 1, 1, 1, 1, 1, -1,
        -1, -1, -1, -1, 1, -1, 1, 1, -1, 1, -1, -1,
        -1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1, 1};

    GLfloat coresCubo[] = {
        0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
        1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0,
        0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0,
        0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1};

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, verticesCubo);
    glColorPointer(3, GL_FLOAT, 0, coresCubo);

    // Send data: 24 vertices
    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

/**
Figura geometrica - piramide
*/
void phDesenharPiramide(phPonto ponto, float a)
{
    // Aplica uma escala para alterar o objeto ao longo dos eixos coordenados
    GLfloat halfA = a / 2.0f;
    std::cout << halfA << std::endl;
    // glScalef(2.0, 2.0, 2.0);
    GLfloat verticesPiramide[] = {
        // Triangulo lateral esquerdo
        ponto.x - halfA,
        ponto.y - halfA,
        ponto.z + halfA,
        ponto.x,
        ponto.y + halfA,
        ponto.z,
        ponto.x - halfA,
        ponto.y - halfA,
        ponto.z - halfA,

        // Triangulo lateral direito
        ponto.x + halfA,
        ponto.y - halfA,
        ponto.z + halfA,
        ponto.x,
        ponto.y + halfA,
        ponto.z,
        ponto.x + halfA,
        ponto.y - halfA,
        ponto.z - halfA,

        // Triangulo frontal
        ponto.x - halfA,
        ponto.y - halfA,
        ponto.z + halfA,
        ponto.x,
        ponto.y + halfA,
        ponto.z,
        ponto.x + halfA,
        ponto.y - halfA,
        ponto.z + halfA,

        // Triangulo traseiro
        ponto.x - halfA,
        ponto.y - halfA,
        ponto.z - halfA,
        ponto.x,
        ponto.y + halfA,
        ponto.z,
        ponto.x + halfA,
        ponto.y - halfA,
        ponto.z - halfA,

        // Bases da piramide
        ponto.x - halfA,
        ponto.y - halfA,
        ponto.z + halfA,
        ponto.x + halfA,
        ponto.y - halfA,
        ponto.z + halfA,
        ponto.x + halfA,
        ponto.y - halfA,
        ponto.z - halfA,

        ponto.x - halfA,
        ponto.y - halfA,
        ponto.z + halfA,
        ponto.x - halfA,
        ponto.y - halfA,
        ponto.z - halfA,
        ponto.x + halfA,
        ponto.y - halfA,
        ponto.z - halfA,
    };

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3ub(ponto.r, ponto.g, ponto.b);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, verticesPiramide); // size, tipo, deslocamento inicial, ponteiro

    glDrawArrays(GL_TRIANGLES, 0, 6 * 3); // desenha os pontos da piramide

    // limpa estados
    glDisableClientState(GL_VERTEX_ARRAY);
}

void phDesenharEixosOrigem(float inicioEixo, float fimEixo)
{
    float tomCinza = 0;

    glLineWidth(2.0);
    glColor3f(tomCinza, tomCinza, tomCinza);

    // Eixo X
    glBegin(GL_LINES);
    glVertex3f(inicioEixo, inicioEixo, 0.0);
    glVertex3f(fimEixo, inicioEixo, 0.0);
    glEnd();

    // Eixto Y
    glColor3f(tomCinza, tomCinza, tomCinza);
    glBegin(GL_LINES);
    glVertex3f(inicioEixo, inicioEixo, 0.0);
    glVertex3f(inicioEixo, fimEixo, 0.0);
    glEnd();

    // Eixo Z
    glColor3f(tomCinza, tomCinza, tomCinza);
    glBegin(GL_LINES);
    glVertex3f(inicioEixo, inicioEixo, 0);
    glVertex3f(inicioEixo, inicioEixo, -(fimEixo * 2));
    glEnd();

    // origem (0,0,0)
    glPointSize(2.0f);
    glColor3ub(91, 235, 52);
    glBegin(GL_POINTS);
    glVertex3f(inicioEixo, inicioEixo, 0.0f);
    glEnd();

    // restore
    glLineWidth(1.0);
    glPointSize(1.0f);
}

/**
 * @brief Desenha um triangulo equilatero, levando em consideração o tamanho a
 * 
 * @param ponto 
 * @param a 
 */
void phDesenharTriangulo(phPonto ponto, float a)
{
    GLfloat verticesTriangulo[] = {
        ponto.x, ponto.y + a / 2.0f, ponto.z,
        ponto.x + a / 2.0f, ponto.y - a / 2.0f, ponto.z,
        ponto.x - a / 2.0f, ponto.y - a / 2.0f, ponto.z,
    };

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3ub(ponto.r, ponto.g, ponto.b);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, verticesTriangulo); // size, tipo, deslocamento inicial, ponteiro

    glDrawArrays(GL_TRIANGLES, 0, 3); // desenha os pontos da piramide

    // limpa estados
    glDisableClientState(GL_VERTEX_ARRAY);
}

/**
 * @brief Função utilizada para o desenho da grid
 * 
 * @param pontox 
 * @param pontoy 
 * @param posZ 
 * @param width 
 */
void phCubo(float pontox, float pontoy, float posZ, float width)
{
    float maxX, maxY, maxZ;

    maxX = pontox + width;
    maxY = pontoy + width;
    maxZ = posZ - width;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLfloat verticesCubo[] = {
        pontox, pontoy, posZ, pontox, pontoy, maxZ, pontox, maxY, maxZ, pontox, maxY, posZ,
        maxX, pontoy, posZ, maxX, pontoy, maxZ, maxX, maxY, maxZ, maxX, maxY, posZ,
        pontox, pontoy, posZ, pontox, pontoy, maxZ, maxX, pontoy, maxZ, maxX, pontoy, posZ,
        pontox, maxY, posZ, pontox, maxY, maxZ, maxX, maxY, maxZ, maxX, maxY, posZ,
        pontox, pontoy, posZ, pontox, maxY, posZ, maxX, maxY, posZ, maxX, pontoy, posZ,
        pontox, pontoy, maxZ, pontox, maxY, maxZ, maxX, maxY, maxZ, maxX, pontoy, maxZ};

    glEnableClientState(GL_VERTEX_ARRAY);

    glColor3ub(69, 69, 69);
    glVertexPointer(3, GL_FLOAT, 0, verticesCubo);

    // Send data: 24 vertices
    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
}

/**
 * @brief Desenha um cupo apartir de um ponto
 * 
 * @param ponto 
 * @param width 
 */
void phDesenharCuboPonto(phPonto ponto, float width)
{
    float maxX, maxY, maxZ;

    maxX = ponto.x + width;
    maxY = ponto.y + width;
    maxZ = ponto.z - width;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    GLfloat verticesCubo[] = {
        ponto.x, ponto.y, ponto.z, ponto.x, ponto.y, maxZ, ponto.x, maxY, maxZ, ponto.x, maxY, ponto.z,
        maxX, ponto.y, ponto.z, maxX, ponto.y, maxZ, maxX, maxY, maxZ, maxX, maxY, ponto.z,
        ponto.x, ponto.y, ponto.z, ponto.x, ponto.y, maxZ, maxX, ponto.y, maxZ, maxX, ponto.y, ponto.z,
        ponto.x, maxY, ponto.z, ponto.x, maxY, maxZ, maxX, maxY, maxZ, maxX, maxY, ponto.z,
        ponto.x, ponto.y, ponto.z, ponto.x, maxY, ponto.z, maxX, maxY, ponto.z, maxX, ponto.y, ponto.z,
        ponto.x, ponto.y, maxZ, ponto.x, maxY, maxZ, maxX, maxY, maxZ, maxX, ponto.y, maxZ};

    glEnableClientState(GL_VERTEX_ARRAY);

    glColor3ub(ponto.x, ponto.y, ponto.z);
    glVertexPointer(3, GL_FLOAT, 0, verticesCubo);

    // Send data: 24 vertices
    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
}

/**
 * @brief Desenha a grid do grafico assim como o ponto de origem
 * 
 * @param initWidth 
 * @param endWidth 
 * @param reparticoes 
 */
void phDesenharGrid(float initWidth, float endWidth, int reparticoes)
{
    // initWidth <=> endWidth
    float posX, posY, posZ, pas, nextX, nextY, nextZ;

    posX = posY = initWidth;
    posZ = 0.0f;

    pas = (float)(fabs(initWidth) + fabs(endWidth)) / reparticoes;

    for (int z = 0; z < reparticoes; z++)
    {
        nextZ = posZ - pas;
        for (int y = 0; y < reparticoes; y++)
        {
            nextY = posY + pas;
            for (int x = 0; x < reparticoes; x++)
            {
                nextX = posX + pas;
                phCubo(posX, posY, posZ, pas);
                posX = nextX;
            }
            posX = initWidth;
            posY = nextY;
        }
        posY = initWidth;
        posZ = nextZ;
    }
}