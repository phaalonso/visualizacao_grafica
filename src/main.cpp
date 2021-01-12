#include <GLFW/glfw3.h>
#include <iostream>
#include "desenhoBasico.hpp"
#include "phProcessarDados.hpp"

// def: variaveis globais de controle da visualizacao
static float passoRotacao = 1;
static float passoZoom = 1;

float zoom_level = 0.0, zoom_min = 5.0f, zoom_max = 100.0f, rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;

float inicioExito = -2.5, fimEixo = 2.5;

double xPosAntes, yPosAntes;

listaDados *dados = NULL;

pontosData data = {.x = 2.0f, .y = 2.0f, .z = 0.0f, .r = 255, .g = 255, .b = 255};

/**
 * Função para definições premiliares do projeto
 */
void aplicarConfigInicial(GLFWwindow *window);
void processarTeclado(GLFWwindow *window, int key, int scancode, int action, int mode);
/**
 * Função para redimensionamento de janela
 */
void ajustarJanela(GLFWwindow *window, int w, int h);
void processarScroll(GLFWwindow *window, double xoffset, double yoffset);
void processarClick(GLFWwindow *window, double xpos, double ypos);

void desenharCena()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // phDesenharPontosElementos();

    // phPonto p1 = {0.0, 0.0, -100.0, 128, 128, 243}; // x, y, z, r, g, b
    // phDesenharPonto(&p1, 10);

    glMatrixMode(GL_MODELVIEW); // Habilitando modo de edição do modelo-visão
    glLineWidth(1.0f);
    glLoadIdentity(); // Carrega a matriz identidade

    glTranslatef(0.0f, 0.0f, -(zoom_min + zoom_level)); //tx, ty, tz

    glRotatef(rot_x, 1.0f, 0.0f, 0.0f);
    glRotatef(rot_y, 0.0f, 1.0f, 0.0f);
    glRotatef(rot_z, 0.0f, 0.0f, 1.0f);

    // phDesenharCubo();
    // phDesenharPiramide();
    phDesenharEixosOrigem(inicioExito, fimEixo);
    phDesenharGrid(inicioExito, fimEixo, 10);
    // phInserirData(&data);
    phDesenharDados(dados);
}

int main(void)
{
    dados = lerDados(dados);
    // imprimirLista(dados);

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    else
        std::cout << "Funcionou glfw" << std::endl;

    std::cout << "Os movimentos de tela podem ser feitos atraves do teclado, da mesma maneira que apresentado em aula" << std::endl;
    std::cout << "Ou também através do scroll do mouse para zoom" << std::endl;
    std::cout << "Ou pressionando o botão esquerdo do mouse" << std::endl;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(600, 600, "View e projecao ortogonal", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Aplicando configuração inicia*/
    aplicarConfigInicial(window);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        desenharCena();
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void aplicarConfigInicial(GLFWwindow *window)
{
    std::cout << "Aplicando configuração inicial" << std::endl;

    glClearColor(0.50f, 0.50f, 0.50f, 1.0f); // Especifica cor de fundo
    glEnable(GL_DEPTH_BUFFER_BIT);           // Habilitando profundidade

    //Configuração do registro de callbacks do glfw
    glfwSetKeyCallback(window, processarTeclado);
    glfwSetScrollCallback(window, processarScroll);
    glfwSetCursorPosCallback(window, processarClick);

    ajustarJanela(window, 200, 200);
}

/**
 * Função para redimensionamento de janela
 */
void ajustarJanela(GLFWwindow *window, int w, int h)
{
    std::cout << "Redimensionamento da janela. Width: " << w << " Height: " << h << std::endl;

    // Indicação da nova área útil da janela redimensionada (em pixel)
    // glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); // Uma alteração que envolve a projeção é necessária

    glFrustum(-5.0, 5.0, -5.0, 5.0, 5, 100); // Exemplo slide
}

/**
 * Função para entrada de teclado
 */
void processarTeclado(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    std::cout << "Uma tecla foi pressionada " << key << std::endl;

    // Esc foi pressionado
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        std::cout << "A tecla esc foi pressionada " << key << std::endl;

        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // rotacoes ao longo do eixo y - movimento de virar a cabeca para os lados
    else if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        rot_y += passoRotacao;
        std::cout << "Left pressionado..rotacao anti-horaria ao longo do eixo y! Valor do rot_y: "
                  << rot_y << std::endl;
    }
    else if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        rot_y -= passoRotacao;
        std::cout << "Left pressionado..rotacao anti-horaria ao longo do eixo y! Valor do rot_y: "
                  << rot_y << std::endl;
    }
    // rotacoes ao longo do eixo x - movimento de levantar/abaixar a cabeca
    else if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        rot_x += passoRotacao;
        std::cout << "Up pressionado..rotacao anti-horaria ao longo do eixo x! Valor do rot_x: "
                  << rot_x << std::endl;
    }
    else if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
    {
        rot_x -= passoRotacao;
        std::cout << "Down pressionado..rotacao anti-horaria ao longo do eixo x! Valor do rot_x: "
                  << rot_x << std::endl;
    }
    // rotacoes ao longo do eixo z - movimento de inclinar a cabeca
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        rot_z += passoRotacao;
        std::cout << "Q pressionado..rotacao anti-horaria ao longo do eixo z! Valor do rot_z: "
                  << rot_z << std::endl;
    }
    else if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        rot_z -= passoRotacao;
        std::cout << "W pressionado..rotacao anti-horaria ao longo do eixo z! Valor do rot_z: "
                  << rot_z << std::endl;
    }
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        std::cout << "(R)eset pressionado." << std::endl;
        rot_x = rot_y = rot_z = 0.0f;
        zoom_level = zoom_min;
    }
    // zoom - teclado +-
    else if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
    {
        escalaPonto += 0.1;
        std::cout << "Aumentando escala" << escalaPonto << std::endl;
    }
    else if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS)
    {
        if (escalaPonto > 0.1)
        {
            escalaPonto -= 0.1;
            std::cout << "Diminuindo escala" << escalaPonto << std::endl;
        } else {
            std::cout << "Não é possivel reduzir a escala abaixo de 0.1" << std::endl;
        }
    }
}

/**
 * @brief Realiza o zoom da tela utilizando o scroll do mouse
 * 
 * @param window 
 * @param xoffset 
 * @param yoffset 
 */
void processarScroll(GLFWwindow *window, double xoffset, double yoffset)
{
    // std::cout << xoffset << " " << yoffset << std::endl;

    if (yoffset == 1)
        zoom_level -= passoZoom / 3.0;
    else if (yoffset == -1)
        zoom_level += passoZoom;
}

void processarClick(GLFWwindow *window, double xpos, double ypos)
{
    double deslocamentoX, deslocamentoY;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        xPosAntes = xpos;
        yPosAntes = ypos;
        return;
    }

    deslocamentoX = (xPosAntes - xpos) / 5.0;
    deslocamentoY = (yPosAntes - ypos) / 5.0;

    // std::cout << deslocamentoX << " " << deslocamentoY << std::endl;

    rot_x += deslocamentoY;
    rot_y += deslocamentoX;

    glfwGetCursorPos(window, &xpos, &ypos);
    xPosAntes = xpos;
    yPosAntes = ypos;
}