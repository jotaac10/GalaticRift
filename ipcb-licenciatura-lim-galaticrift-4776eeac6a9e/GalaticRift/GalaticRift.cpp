#include "systemLibraries.h"
#include "Ship.h"
#include "Enemy.h"
#include "balas.h"
#include "balasInimigos.h"
#include "EnemyLvl2.h"
#include "EnemyLvl3.h"

using namespace std;

// Funcoes
GLvoid drawGame(GLvoid);
GLvoid atualizarTempo(GLvoid);
GLvoid drawCollisionDomain(GLfloat, GLfloat, GLfloat, GLfloat);
GLvoid drawCollisionDomainQUADS(GLfloat, GLfloat, GLfloat, GLfloat);
GLvoid keyboardSplash(unsigned char, GLint, GLint);
GLvoid keyboardVitoriDerrota(unsigned char, GLint, GLint);
GLvoid keyboardComandos(unsigned char, GLint, GLint);
GLvoid menuComandos(GLvoid);
GLvoid drawSplash(GLvoid);
GLvoid drawHUD(GLvoid);
GLvoid idledSplash(GLvoid);
GLvoid startGame(GLvoid);
GLvoid gametimer(GLint);
GLvoid disparar(GLfloat* shipPosition);
GLvoid atualizarTirosInimigos(GLfloat* shipPosition);
GLvoid verificarColisoesNaveInimigos(GLfloat* shipPosition);
GLvoid atualizarTirosJogador(GLvoid);
GLvoid atualizarDominioColisaoInimigos(GLvoid);
GLvoid atualizarMovimentoInimigos(GLvoid);
GLvoid verificarGameOver(GLvoid);
GLvoid limparObjetos(GLvoid);
GLvoid drawDerrota(GLvoid);
GLvoid writeText(GLfloat posX, GLfloat posY, string text, GLint colorCode, GLvoid* typeface);
GLvoid drawPausa(GLvoid);
GLvoid startPausa(GLvoid);
GLvoid idleGame(GLvoid);
GLvoid inimigosDisparoTimer(GLint);
GLvoid carregarInimigosNivel(GLint nivel, GLint linha);
GLvoid resumeGame(GLvoid);

// Inicialização de objetos do jogo
GLfloat worldCoords[4] = { -20.0f, 20.0f, -20.0f, 20.0f };
Ship* player = new Ship(0.0f, -14.0f, 1.0f);
GLfloat shipHalfSize[2] = { 3.0f, 2.5f };
GLfloat* shipPosition = nullptr; // Ponteiro para posição da nave

//Balas
const GLfloat bulletHalfSize[2] = { 0.01f, 0.025f };
GLfloat balaposition = 0.0f;
vector<balas*> tirosJogador;
vector<balasInimigos*> tirosInimigos;

GLfloat enemiesCollisionDomain[4];
GLfloat enemyHalfSize[2] = { 5.0f, 1.0f };
GLfloat enemyHalfSize2[2] = { 4.0f, 2.0f };
GLfloat enemyHalfSize3[2] = { 3.0f, 1.25f };
GLfloat* enimyPosition = nullptr;
GLfloat enemiesSpeed = 0.1f;
GLint enimiesDirection = 0;
vector <Enemy*> enemies;
vector <EnemyLvl2*> enemiesNivel2;
vector<GLint> vidasInimigosNivel2;

//Variaveis jogo booleanos
GLboolean pause = false;
GLboolean gameOver = false;
GLboolean gameOn = false;

GLboolean redraw = false; // Controla se redesenhamos ou não a nave
GLboolean gameTick = true;
GLboolean canMove = true;
GLboolean disparoTimerAtivo = false;

//Boss
GLboolean spawnarBoss = false;
GLvoid createBoss(GLvoid);
GLint bossDirection = 0;
GLint vidaBoss = 5;
EnemyLvl3* boss = nullptr;

GLint pontuacao = 0;
GLint vidas = 5; // Vidas do jogador

// Niveis
GLint nivelAtual = 1;
GLint linhaAtualNivel1 = 1;
GLint linhaAtualNivel2 = 1;
GLint linhaAtualNivel3 = 1;
GLint numeroNiveis = 3;
GLboolean mudaNivel = false;

// Variáveis para o tempo de jogo
GLint tempoInicial = 0;
GLint tempoDecorrido = 0;
GLboolean contandoTempo = false;

// Callback de teclado
GLvoid keyboardGame(unsigned char key, GLint x, GLint y) {
    switch (key) {
    case 27: // ESC para sair
        exit(0);
        break;
    case 'A': case 'a': // Esquerda
        if (!gameOver && player->move(2)) redraw = true;
        break;
    case 'D': case 'd': // Direita
        if (!gameOver && player->move(0)) redraw = true;
        break;
    case 'W': case 'w': // Cima
        if (!gameOver && player->move(3)) redraw = true;
        break;
    case 'S': case 's': // Baixo
        if (!gameOver && player->move(1)) redraw = true;
        break;
    case ' ':  // Disparar
        if (!gameOver) {
            shipPosition = player->getPosition();
            disparar(shipPosition);
        }
        break;
    case 'P':
    case 'p':
        pause = !pause;
        if (!pause) {
            resumeGame(); // retoma o jogo
        }
        else {
            startPausa(); 
        }
        break;
    }
}
GLvoid resumeGame(GLvoid) {
    glutKeyboardFunc(keyboardGame);
    glutDisplayFunc(drawGame);
    glutIdleFunc(idleGame);
    glutPostRedisplay();
}

GLvoid disparar(GLfloat* shipPosition) {
    // Criar bala acima do centro da nave (shipHalfSize[1] é a metade da altura da nave)
    balas* novaBala = new balas(shipPosition[0], shipPosition[1] + shipHalfSize[1], 1.0f);
    tirosJogador.push_back(novaBala);
}

GLvoid startPausa(GLvoid) {
    //Set keyboard callbacks
    glutKeyboardFunc(keyboardGame);
    //Set display callbacks
    glutDisplayFunc(drawPausa);
}

GLvoid keyboardVitoriDerrota(unsigned char key, GLint x, GLint y) {
    switch (key) {
    case 27: // ESC para sair
        exit(0);
        break;
    case 'r': case 'R':
        startGame();
        break;

    case 'm': case 'M':
        drawSplash();
        break;

    }

}
GLvoid keyboardSplash(unsigned char key, GLint x, GLint y) {
    switch (key) {
    case 27: // ESC para sair
        exit(0);
        break;
    case 'c': case 'C':
        menuComandos();
        break;

    case 'n': case 'N':
        startGame();
        break;

    }

}
GLvoid keyboardComandos(unsigned char key, GLint x, GLint y) {
    switch (key) {
    case 27: // ESC para sair
        exit(0);
        break;
    case 'S': case 's': // Start game
        startGame();
        break;
    case 'C': case 'c': // Voltar ao splash
        glutKeyboardFunc(keyboardSplash);
        glutDisplayFunc(drawSplash);
        glutPostRedisplay();
        break;
    }
}

GLvoid idleSplash(GLvoid) {

}

// Callback idle
GLvoid idleGame(GLvoid) {

    if (gameOver) return;
    atualizarTempo();
    if (gameTick && !gameOver && !pause) {
        gameTick = false;

        shipPosition = player->getPosition();
        if (!shipPosition) return;

        atualizarTirosInimigos(shipPosition);
        verificarColisoesNaveInimigos(shipPosition);
        atualizarTirosJogador();
        atualizarDominioColisaoInimigos();
        atualizarMovimentoInimigos();
        verificarGameOver();

        if (redraw) {
            redraw = false;
            glutPostRedisplay();
        }
    }

    glutPostRedisplay();
}
GLvoid iniciarContagemTempo() {
    tempoInicial = glutGet(GLUT_ELAPSED_TIME) / 1000;
    contandoTempo = true;
}

GLvoid atualizarTempo() {
    if (contandoTempo && !gameOver && !pause) {
        tempoDecorrido = (glutGet(GLUT_ELAPSED_TIME) / 1000) - tempoInicial;
    }
}

GLvoid verificarGameOver(GLvoid) {
    if (vidas <= 0) {
        gameOver = true;
        limparObjetos();
        drawDerrota();
        pause = true;
    }
}

GLvoid limparObjetos() {
    // Apaga inimigos do nível 1
    for (Enemy* e : enemies) {
        delete e;
    }
    enemies.clear();

    // Apaga inimigos do nível 2
    for (EnemyLvl2* e : enemiesNivel2) {
        delete e;
    }
    enemiesNivel2.clear();
    vidasInimigosNivel2.clear();

    // Apaga tiros inimigos
    for (balasInimigos* b : tirosInimigos) {
        delete b;
    }
    tirosInimigos.clear();

    // Apaga tiros do jogador
    for (balas* b : tirosJogador) {
        delete b;
    }
    tirosJogador.clear();

    // Apaga boss se existir
    if (boss) {
        delete boss;
        boss = nullptr;
    }
}

string formatarTempo(GLint segundos) {
    GLint minutos = segundos / 60;
    GLint segs = segundos % 60;
    return to_string(minutos) + " min, " + to_string(segs) + " seg";
}
GLvoid drawVitoria() {
    glutDisplayFunc(drawVitoria);
    glutKeyboardFunc(keyboardVitoriDerrota);

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Título "Vitória"
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 40, glutGet(GLUT_WINDOW_HEIGHT) / 2 + 60);
    string titulo = "Vitoria";
    for (char c : titulo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Pontuação
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 70, glutGet(GLUT_WINDOW_HEIGHT) / 2 + 20);
    string pontos = "Pontuacao: " + to_string(pontuacao);
    for (char c : pontos) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Tempo
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 70, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 10);
    string tempo = "Tempo: " + formatarTempo(tempoDecorrido);
    for (char c : tempo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Instruções
    glColor3f(0.7f, 0.7f, 0.7f);
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 90, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 50);
    string instrucao1 = "Pressione R para reiniciar";
    for (char c : instrucao1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    // Instruções
    glColor3f(0.7f, 0.7f, 0.7f);
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 90, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 70);
    string instrucao3 = "Pressione M para voltar Menu";
    for (char c : instrucao3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 90, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 90);
    string instrucao2 = "Pressione ESC para sair";
    for (char c : instrucao2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    pause = true;

    glutSwapBuffers();
}
GLvoid drawDerrota() {
    glutDisplayFunc(drawDerrota);
    glutKeyboardFunc(keyboardVitoriDerrota);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Título "Derrota"
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 40, glutGet(GLUT_WINDOW_HEIGHT) / 2 + 60);
    string titulo = "Derrota";
    for (char c : titulo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Pontuação
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 70, glutGet(GLUT_WINDOW_HEIGHT) / 2 + 20);
    string pontos = "Pontuacao: " + to_string(pontuacao);
    for (char c : pontos) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Tempo
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 70, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 10);
    string tempo = "Tempo: " + formatarTempo(tempoDecorrido);
    for (char c : tempo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Instruções
    glColor3f(0.7f, 0.7f, 0.7f);
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 90, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 50);
    string instrucao1 = "Pressione R para reiniciar";
    for (char c : instrucao1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    // Instruções
    glColor3f(0.7f, 0.7f, 0.7f);
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 90, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 70);
    string instrucao3 = "Pressione M para voltar Menu";
    for (char c : instrucao3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 90, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 90);
    string instrucao2 = "Pressione ESC para sair";
    for (char c : instrucao2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glutSwapBuffers();
}
GLvoid drawComandos() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Título
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50, glutGet(GLUT_WINDOW_HEIGHT) - 50);
    string titulo = "Comandos";
    for (char c : titulo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Comandos
    glColor3f(1.0f, 1.0f, 1.0f);
    GLint y = glutGet(GLUT_WINDOW_HEIGHT) - 100;

    glRasterPos2i(50, y); y -= 30;
    string esc = "ESC - Sair do Jogo";
    for (char c : esc) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2i(50, y); y -= 30;
    string cima = "W - Cima";
    for (char c : cima) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2i(50, y); y -= 30;
    string baixo = "S - Baixo";
    for (char c : baixo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2i(50, y); y -= 30;
    string esquerda = "A - Esquerda";
    for (char c : esquerda) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2i(50, y); y -= 30;
    string direita = "D - Direita";
    for (char c : direita) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2i(50, y); y -= 30;
    string disparar = "SPACO - Disparar";
    for (char c : disparar) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2i(50, y); y -= 30;
    string pausa = "P - Pausa";
    for (char c : pausa) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glutSwapBuffers();
}
GLvoid drawPausa(GLvoid) {

    writeText(1.85f, 2.5f, "JOGO EM PAUSA", 2, GLUT_BITMAP_HELVETICA_18);

    glutSwapBuffers();
}
GLvoid startGame(GLvoid) {
    glutKeyboardFunc(keyboardGame);
    glutDisplayFunc(drawGame);
    glutIdleFunc(idleGame);
    glutTimerFunc(17, gametimer, 0);
    glutTimerFunc(5000, inimigosDisparoTimer, 0);
    nivelAtual = 1;

    linhaAtualNivel1 = 1;
    linhaAtualNivel2 = 1;
    linhaAtualNivel3 = 1;
    pontuacao = 0;
    vidas = 5;
    gameOver = false;
    pause = false;
    iniciarContagemTempo();

    if (!disparoTimerAtivo) {
        glutTimerFunc(5000, inimigosDisparoTimer, 0);
        disparoTimerAtivo = true;
    }
    enemiesSpeed = 0.1f;
    disparoTimerAtivo = false;
}
GLvoid menuComandos(GLvoid) {
    glutKeyboardFunc(keyboardComandos);
    glutDisplayFunc(drawComandos);
    glutIdleFunc(idleSplash);
    glutPostRedisplay();
}
GLvoid drawHUD(GLvoid) {
    // Configura a projeção ortogonal para o HUD (coordenadas de janela)
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);

    // Título do jogo
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    glRasterPos2i(windowWidth / 2 - 70, glutGet(GLUT_WINDOW_HEIGHT) - 30);
    string title = "Galatic Rift";
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Nível atual - alinhado à esquerda, abaixo do título
    glRasterPos2i(20, glutGet(GLUT_WINDOW_HEIGHT) - 70);
    string nivel = "Nivel " + to_string(nivelAtual);
    for (char c : nivel) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Pontuação (chamada de "Pontos" conforme a imagem)
    glRasterPos2i(20, glutGet(GLUT_WINDOW_HEIGHT) - 100);
    string pontos = "Pontos: " + to_string(pontuacao);
    for (char c : pontos) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Vidas
    glRasterPos2i(20, glutGet(GLUT_WINDOW_HEIGHT) - 130);
    string vida = "Vidas: " + to_string(vidas);
    for (char c : vida) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Linha divisória abaixo do título
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    glVertex2i(0, glutGet(GLUT_WINDOW_HEIGHT) - 50);
    glVertex2i(windowWidth, glutGet(GLUT_WINDOW_HEIGHT) - 50);
    glEnd();

    // Restaura as matrizes de projeção e modelo
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
GLvoid drawSplash(void) {
    disparoTimerAtivo = false;

    glutKeyboardFunc(keyboardSplash);
    glClearColor(0, 0, 0, 0);// definição da cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);// limpar o buffer de cor

    glMatrixMode(GL_PROJECTION); //seleção da matriz de projeção
    glLoadIdentity(); //carregar a matriz identidade na matriz de projeção

    gluOrtho2D(0.0f, 4.0f, 0.0f, 4.0f); //definir as coordenadas da tela de desenho

    glMatrixMode(GL_MODELVIEW); //seleção da matriz de modelação e visualização
    glLoadIdentity(); //carregar a matriz identidade na matriz de modelação e visualização

    writeText(1.90f, 3.5f, "GALATIC RIFT", 1, GLUT_BITMAP_HELVETICA_18);

    writeText(1.85f, 2.5f, "N - NOVO JOGO", 3, GLUT_BITMAP_HELVETICA_12);
    writeText(1.85f, 2.3f, "C - COMANDOS", 2, GLUT_BITMAP_HELVETICA_12);
    writeText(1.75f, 2.1f, "ESCAPE - SAIR JOGO", 0, GLUT_BITMAP_HELVETICA_12);

    glutSwapBuffers();
}
GLvoid writeText(GLfloat posX, GLfloat posY, string text, GLint colorCode, GLvoid* typeface) {

    static stringstream buffer;
    char c;

    buffer.str(""); 
    buffer.clear();
    buffer << text << endl;
    switch (colorCode) {
    case 1: //red
        glColor3f(1.0f, 0.0f, 0.0f);
        break;
    case 2: //blue
        glColor3f(0.0f, 0.0f, 1.0f);
        break;
    case 3: //green
        glColor3f(0.0f, 1.0f, 0.0f);
        break;
    default: //branco
        glColor3f(1.0f, 1.0f, 1.0f);
        break;

    }
    glRasterPos2f(posX, posY);
    while (buffer.get(c)) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}
// Função de desenho
GLvoid drawGame(void) {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(worldCoords[0], worldCoords[1], worldCoords[2], worldCoords[3]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    shipPosition = player->getPosition();
    //drawCollisionDomain(shipPosition[0], shipPosition[1], shipHalfSize[0], shipHalfSize[1]);
    player->draw();

    for (GLint i = 0; i < enemies.size(); i++) {
        enemies.at(i)->drawEnemyNivel1();
        enimyPosition = enemies.at(i)->getPosition();
    }

    for (GLint i = 0; i < enemiesNivel2.size(); i++) {
        enemiesNivel2.at(i)->drawEnemyNivel2();
    }

    for (int i = 0; i < tirosInimigos.size(); i++) {
        tirosInimigos[i]->draw();
    }

    for (int i = 0; i < tirosJogador.size(); i++) {
        tirosJogador[i]->draw();
    }

    if (boss) {
        boss->drawEnemyNivel3();
        enimyPosition = boss->getPosition();
        //drawCollisionDomain(enimyPosition[0], enimyPosition[1], enemyHalfSize[0], enemyHalfSize[1]);
    }

    // Desenha o HUD (informações na tela)
    drawHUD();
    glutSwapBuffers();
}

GLvoid atualizarTirosInimigos(GLfloat* shipPosition) {
    // Verifica colisão dos tiros inimigos com a nave
    for (GLint i = 0; i < tirosInimigos.size(); ) {
        GLfloat* bulletPos = tirosInimigos[i]->getPosition();
        if (!bulletPos) {
            i++;
            continue;
        }

        // Verifica colisão com a nave
        if (!(bulletPos[0] + bulletHalfSize[0] < shipPosition[0] - shipHalfSize[0] ||
            bulletPos[0] - bulletHalfSize[0] > shipPosition[0] + shipHalfSize[0] ||
            bulletPos[1] + bulletHalfSize[1] < shipPosition[1] - shipHalfSize[1] ||
            bulletPos[1] - bulletHalfSize[1] > shipPosition[1] + shipHalfSize[1])) {

            vidas--;
            if (vidas <= 0) {
                gameOver = true;
                cout << "Fim de jogo! Vidas esgotadas.\n";
            }
            else {
                cout << "Vida perdida! Vidas restantes: " << vidas << endl;
            }
            delete tirosInimigos[i];
            tirosInimigos.erase(tirosInimigos.begin() + i);
            continue;
        }

        // Atualiza posição do tiro
        tirosInimigos[i]->update();

        // Remove tiros que saíram da tela
        if (bulletPos[1] < worldCoords[2]) {
            delete tirosInimigos[i];
            tirosInimigos.erase(tirosInimigos.begin() + i);
        }
        else {
            i++;
        }
    }
}
GLvoid verificarColisoesNaveInimigos(GLfloat* shipPosition) {
    if (nivelAtual == 1) {
        if (enemies.empty()) {
            linhaAtualNivel1++;
            if (linhaAtualNivel1 <= 3) {
                carregarInimigosNivel(1, linhaAtualNivel1);
            }
            else {
                nivelAtual = 2;
                linhaAtualNivel1 = 1;
                carregarInimigosNivel(2, 1);
            }
        }
    }
    else if (nivelAtual == 2) {
        if (enemiesNivel2.empty()) {
            linhaAtualNivel2++;
            if (linhaAtualNivel2 <= 3) {
                carregarInimigosNivel(2, linhaAtualNivel2);
            }
            else {
                nivelAtual = 3;
                spawnarBoss = true;
                linhaAtualNivel2 = 1;
            }
        }
    }
    else if (nivelAtual == 3) {
        if (!boss) {
            carregarInimigosNivel(3, 1);
        }
        // Verifica se o boss foi derrotado
        if (boss && vidaBoss <= 0) {
            drawVitoria();
        }
    }
}

GLvoid atualizarTirosJogador() {
    for (GLint i = 0; i < tirosJogador.size(); ) {
        tirosJogador[i]->update();
        GLfloat* bulletPos = tirosJogador[i]->getPosition();
        if (!bulletPos) {
            delete tirosJogador[i];
            tirosJogador.erase(tirosJogador.begin() + i);
            continue;
        }

        bool bulletRemoved = false;

        // Colisão com inimigos nível 1
        for (GLint j = 0; j < enemies.size(); j++) {
            GLfloat* enemyPos = enemies[j]->getPosition();
            if (!enemyPos) continue;

            if (!(bulletPos[0] + bulletHalfSize[0] < enemyPos[0] - enemyHalfSize[0] ||
                bulletPos[0] - bulletHalfSize[0] > enemyPos[0] + enemyHalfSize[0] ||
                bulletPos[1] + bulletHalfSize[1] < enemyPos[1] - enemyHalfSize[1] ||
                bulletPos[1] - bulletHalfSize[1] > enemyPos[1] + enemyHalfSize[1])) {

                pontuacao += 5;
                delete enemies[j];
                enemies.erase(enemies.begin() + j);
                delete tirosJogador[i];
                tirosJogador.erase(tirosJogador.begin() + i);
                bulletRemoved = true;
                break;
            }
        }

        // Colisão com inimigos nível 2
        if (!bulletRemoved && nivelAtual >= 2) {
            for (GLint j = 0; j < enemiesNivel2.size(); j++) {
                GLfloat* enemyPos = enemiesNivel2[j]->getPosition();
                if (!enemyPos) continue;

                if (!(bulletPos[0] + bulletHalfSize[0] < enemyPos[0] - enemyHalfSize2[0] ||
                    bulletPos[0] - bulletHalfSize[0] > enemyPos[0] + enemyHalfSize2[0] ||
                    bulletPos[1] + bulletHalfSize[1] < enemyPos[1] - enemyHalfSize2[1] ||
                    bulletPos[1] - bulletHalfSize[1] > enemyPos[1] + enemyHalfSize2[1])) {

                    vidasInimigosNivel2[j]--;

                    if (vidasInimigosNivel2[j] <= 0) {
                        pontuacao += 10;
                        delete enemiesNivel2[j];
                        enemiesNivel2.erase(enemiesNivel2.begin() + j);
                        vidasInimigosNivel2.erase(vidasInimigosNivel2.begin() + j);
                    }

                    delete tirosJogador[i];
                    tirosJogador.erase(tirosJogador.begin() + i);
                    bulletRemoved = true;
                    break;
                }
            }
        }

        // Colisão com o boss (nível 3)
        if (!bulletRemoved && nivelAtual == 3 && boss) {
            GLfloat* bossPos = boss->getPosition();
            if (bossPos) {
                if (!(bulletPos[0] + bulletHalfSize[0] < bossPos[0] - enemyHalfSize3[0] ||
                    bulletPos[0] - bulletHalfSize[0] > bossPos[0] + enemyHalfSize3[0] ||
                    bulletPos[1] + bulletHalfSize[1] < bossPos[1] - enemyHalfSize3[1] ||
                    bulletPos[1] - bulletHalfSize[1] > bossPos[1] + enemyHalfSize3[1])) {

                    pontuacao += 2;
                    vidaBoss--;
                    std::cout << "Vida do Boss: " << vidaBoss << std::endl;

                    if (vidaBoss <= 0) {
                        delete boss;
                        boss = nullptr;
                        drawVitoria();
                    }

                    delete tirosJogador[i];
                    tirosJogador.erase(tirosJogador.begin() + i);
                    bulletRemoved = true;
                    continue;
                }
            }
        }

        // Se o tiro saiu da tela
        if (!bulletRemoved && bulletPos[1] > worldCoords[3]) {
            delete tirosJogador[i];
            tirosJogador.erase(tirosJogador.begin() + i);
        }
        else if (!bulletRemoved) {
            i++;
        }
    }
}

GLvoid atualizarDominioColisaoInimigos() {
    // Inicializa o domínio de colisão com valores extremos
    enemiesCollisionDomain[0] = worldCoords[1]; // minX
    enemiesCollisionDomain[1] = worldCoords[0]; // maxX
    enemiesCollisionDomain[2] = worldCoords[3]; // minY
    enemiesCollisionDomain[3] = worldCoords[2]; // maxY

    // Atualiza domínio para inimigos do nível 1
    for (GLint i = 0; i < enemies.size(); i++) {
        GLfloat* pos = enemies[i]->getPosition();
        if (!pos) continue;

        enemiesCollisionDomain[0] = min(enemiesCollisionDomain[0], pos[0] - enemyHalfSize[0]);
        enemiesCollisionDomain[1] = max(enemiesCollisionDomain[1], pos[0] + enemyHalfSize[0]);
        enemiesCollisionDomain[2] = min(enemiesCollisionDomain[2], pos[1] - enemyHalfSize[1]);
        enemiesCollisionDomain[3] = max(enemiesCollisionDomain[3], pos[1] + enemyHalfSize[1]);
    }

    // Atualiza domínio para inimigos do nível 2
    if (nivelAtual == 2) {
        for (GLint i = 0; i < enemiesNivel2.size(); i++) {
            GLfloat* pos = enemiesNivel2[i]->getPosition();
            if (!pos) continue;

            enemiesCollisionDomain[0] = min(enemiesCollisionDomain[0], pos[0] - enemyHalfSize2[0]);
            enemiesCollisionDomain[1] = max(enemiesCollisionDomain[1], pos[0] + enemyHalfSize2[0]);
            enemiesCollisionDomain[2] = min(enemiesCollisionDomain[2], pos[1] - enemyHalfSize2[1]);
            enemiesCollisionDomain[3] = max(enemiesCollisionDomain[3], pos[1] + enemyHalfSize2[1]);
        }
    }

    // Atualiza domínio para inimigo do nível 3 (boss)
    if (nivelAtual == 3 && boss) {
        GLfloat* pos = boss->getPosition();
        if (pos) {
            enemiesCollisionDomain[0] = min(enemiesCollisionDomain[0], pos[0] - enemyHalfSize3[0]);
            enemiesCollisionDomain[1] = max(enemiesCollisionDomain[1], pos[0] + enemyHalfSize3[0]);
            enemiesCollisionDomain[2] = min(enemiesCollisionDomain[2], pos[1] - enemyHalfSize3[1]);
            enemiesCollisionDomain[3] = max(enemiesCollisionDomain[3], pos[1] + enemyHalfSize3[1]);
        }
    }
}
GLvoid atualizarMovimentoInimigos() {
    static GLboolean wentDown = false;
    static GLint enemiesDirectionAnterior = 0;
    static GLint rightWallHits = 0;

    // Atualiza direção dos inimigos
    switch (enimiesDirection) {
    case 0: { // Direita
        if (enemiesCollisionDomain[1] + enemiesSpeed > worldCoords[1]) {
            rightWallHits++;
            if (rightWallHits >= 3) {
                enimiesDirection = 1; 
                rightWallHits = 0;    
            }
        }
        break;
    }
    case 1: // Baixo
        if (!wentDown) {
            wentDown = true;
            enimiesDirection = (enemiesDirectionAnterior == 0) ? 2 : 0;
        }
        else {
            wentDown = false;
        }
        break;
    case 2: // Esquerda
        if (enemiesCollisionDomain[0] - enemiesSpeed < worldCoords[0]) {
            enimiesDirection = 1; // Descer
        }
        break;
    }

    // Salva direção anterior antes de descer
    if (enimiesDirection == 0 || enimiesDirection == 2) {
        enemiesDirectionAnterior = enimiesDirection;
    }

    // Aplica movimento aos inimigos do nível 1
    for (GLint i = 0; i < enemies.size(); i++) {
        GLfloat* pos = enemies[i]->getPosition();
        if (!pos) continue;

        switch (enimiesDirection) {
        case 0: pos[0] += enemiesSpeed; break;
        case 1: pos[1] -= enemiesSpeed; break;
        case 2: pos[0] -= enemiesSpeed; break;
        }
    }

    // Aplica movimento aos inimigos do nível 2 (mais rápidos)
    if (nivelAtual == 2) {
        for (GLint i = 0; i < enemiesNivel2.size(); i++) {
            GLfloat* pos = enemiesNivel2[i]->getPosition();
            if (!pos) continue;

            switch (enimiesDirection) {
            case 0: pos[0] += enemiesSpeed * 1.2f; break;
            case 1: pos[1] -= enemiesSpeed * 1.2f; break;
            case 2: pos[0] -= enemiesSpeed * 1.2f; break;
            }
        }
    }

    if (nivelAtual == 3 && boss) {
        GLfloat* pos = boss->getPosition();
        if (pos) {
            switch (enimiesDirection) {
            case 0: pos[0] += enemiesSpeed * 1.2f; break;
            case 1: pos[1] -= enemiesSpeed * 1.2f; break;
            case 2: pos[0] -= enemiesSpeed * 1.2f; break;
            }
        }
    }
}


GLvoid gametimer(GLint param) {
    gameTick = true;
    glutTimerFunc(17, gametimer, 0);
}

GLvoid dispararInimigos() {
    // Disparo dos inimigos do nível 1
    for (GLint i = 0; i < enemies.size(); i++) {
        GLfloat* pos = enemies[i]->getPosition();
        balasInimigos* novaBala = new balasInimigos(pos[0], pos[1] - enemyHalfSize[1], 0.2f);
        tirosInimigos.push_back(novaBala);
    }

    // Disparo dos inimigos do nível 2
    for (GLint i = 0; i < enemiesNivel2.size(); i++) {
        GLfloat* pos = enemiesNivel2[i]->getPosition();
        balasInimigos* novaBala = new balasInimigos(pos[0], pos[1] - enemyHalfSize2[1], 0.5f);
        tirosInimigos.push_back(novaBala);
    }
    if (boss && nivelAtual == 3) {
        GLfloat* bossPos = boss->getPosition();
        if (bossPos) {
            balasInimigos* tiro1 = new balasInimigos(bossPos[0], bossPos[1] - enemyHalfSize3[1], 0.8f);
            tirosInimigos.push_back(tiro1);
        }
    }
}
GLvoid inimigosDisparoTimer(GLint value) {
    dispararInimigos(); // Chama a função de disparo
    glutTimerFunc(10000, inimigosDisparoTimer, 0);
}
// Função para desenhar a área de colisão (retângulo)
GLvoid drawCollisionDomain(GLfloat posX, GLfloat posY, GLfloat halfSizeX, GLfloat halfSizeY) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(posX - halfSizeX, posY - halfSizeY);
    glVertex2f(posX + halfSizeX, posY - halfSizeY);

    glVertex2f(posX + halfSizeX, posY - halfSizeY);
    glVertex2f(posX + halfSizeX, posY + halfSizeY);

    glVertex2f(posX + halfSizeX, posY + halfSizeY);
    glVertex2f(posX - halfSizeX, posY + halfSizeY);

    glVertex2f(posX - halfSizeX, posY + halfSizeY);
    glVertex2f(posX - halfSizeX, posY - halfSizeY);
    glEnd();
}
GLvoid carregarInimigosNivel(GLint nivel, GLint linha = 1) {
    if (nivel == 1) {
        enemies.clear();

        if (linha == 1) {
            // Primeira linha - 4 inimigos
            for (int i = 0; i < 4; i++) {
                Enemy* oneEnemy = new Enemy(i * 8.0f - 15.0f, 10.0f, 0.5f);
                enemies.push_back(oneEnemy);
            }
        }
        else if (linha == 2) {
            // Segunda linha - 4 inimigos
            for (int i = 0; i < 4; i++) {
                Enemy* oneEnemy = new Enemy(i * 7.0f - 15.0f, 10.0f, 0.5f);
                enemies.push_back(oneEnemy);
            }
        }
        else if (linha == 3) {
            // Terceira linha -4 inimigos
            for (int i = 0; i < 4; i++) {
                Enemy* oneEnemy = new Enemy(i * 6.0f - 15.0f, 14.0f, 0.5f);
                enemies.push_back(oneEnemy);
            }
        }
    }
    else if (nivel == 2) {
        enemiesNivel2.clear();
        vidasInimigosNivel2.clear();

        if (linha == 1) {
            // Primeira linha - 3 inimigos (2 vidas)
            for (int i = 0; i < 3; i++) {
                EnemyLvl2* oneEnemy = new EnemyLvl2(i * 10.0f - 15.0f, 10.0f, 0.75f);
                enemiesNivel2.push_back(oneEnemy);
                vidasInimigosNivel2.push_back(2);
            }
        }
        else if (linha == 2) {
            // Segunda linha - 3 inimigos (2 vidas)
            for (int i = 0; i < 3; i++) {
                EnemyLvl2* oneEnemy = new EnemyLvl2(i * 8.0f - 15.0f, 12.0f, 0.75f);
                enemiesNivel2.push_back(oneEnemy);
                vidasInimigosNivel2.push_back(2);
            }
        }
    }
    else if (nivel == 3) {
        // Nível 3 - Cria o boss apenas se não existir
        if (!boss) {
            boss = new EnemyLvl3(0.0f, 10.0f, 2.0f);
        }
        else {
            // Se já existe, apenas reposiciona
            GLfloat* pos = boss->getPosition();
            pos[0] = 0.0f;
            pos[1] = 10.0f;
        }
        vidaBoss = 5;
    }
}

GLvoid drawCollisionDomainQUADS(GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(xMin, yMin);
    glVertex2f(xMax, yMin);

    glVertex2f(xMax, yMin);
    glVertex2f(xMax, yMax);



    glVertex2f(xMin, yMax);
    glVertex2f(xMax, yMax);



    glEnd();
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("GalaticRift");

    // Regista callbacks
    glutKeyboardFunc(keyboardSplash);
    glutDisplayFunc(drawSplash);
    glutIdleFunc(idleSplash);
    //glutTimerFunc(2000, inimigosDisparoTimer, 0);
    glutMainLoop();

    return 0;
}