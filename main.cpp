#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>

//Inicializando Texturas
GLuint texturaPersonagem,texturaCenario,texturaObstaculo,texturaVida,texturaCenario1,texturaMenu,texturaPersonagem2;
GLuint texturaPause,texturaGameOver,texturaCenario2,texturaObstaculo2,texturaObstaculo3,texturaVida2;

//constantes responsaveis pela movimento inicial dos objetos
const float level_inicial_vida=0.38,level_inicial_obstaculo=0.78,inicial_pulo=0.071,Raio=7,sprites=0.125,sprite_obstaculo=0.25;
const float level_inicial_obstaculo2=1.2,sprite_cenario=0.5,variacao_cenario=0.00009,FPS_pause=1000/15;

//Constante gravidade e velocidade inicial personagem no eixo y, para equaçao cinematica
const float gravidade=17.6,velocidade_inicial_y=44.7,LIMITE=100,variacao_inicial=0;

//variaveis responsaveis por cada objeto do cenario
float cor_personagem1=1.0,cor_personagem2=1.0,cor_personagem3=1.0,cor_obstaculo1=1.0,cor_obstaculo2=1.0,cor_obstaculo3=1.0;
float cor_cenario1=1.0,cor_cenario2=1.0,cor_cenario3=1.0,cor_vida1=1.0,cor_vida2=1.0,cor_vida3=1.0;

//variaveis de controle do movimento dos objetos
float Velocidade_Obstaculos_X=variacao_inicial,Variacao_vida_X,Variacao_obstaculo_X,Variacao_personagem_Y,Velocidade_Personagem_Y=0;
float Velocidade_Vida_X=0,velocidade_vida,Velocidade_vida_Y=0,Velocidade_Obstaculo2_X=0,velocidade_obstaculo2,Variacao_obstaculo2;
float Variacao_personagem_2Y,Variacao_vida_2X,Variacao_obstaculo2_x;

//variaveis de niveis de dificuldade, variavel pause armazena o level anterior ao pressionamento da tecla p, para depois voltar o jogo no level que estava
float pause,level_inicial,Variavel_inicializacao_pulo=0.0,tempo=0.0,incremento_por_level=0.0037,angulo=0;
float angulo_inicial=0,FPS=1000/60,musica=17,musica_pause=17;

// variavel controle/comecar o jogo apenas uma vez
int controle_de_inicializacao=1,controle_menu=1,controle_de_inicializacao2=0,level_cenario=0,quantidade_vida=0,bonus_passaro,Aparecer_Vida=1;
//variavel responsavel por controlar o pause e o despause
int bottom=0,troca_arvore=0,troca_cenario=0,troca_vida=0,som_gameover=1,som_passaro=1,pontuacao_final=0,quantidade_passaro=0,vida=0,confirmacao=0;
int controle_passaro=1,passaro_final=0,botao_pause=0,confirmacao_reset=0;
//variaveis velocidades sprites

float sprite_personagem_x1=0.0,sprite_personagem_x2=0.0,sprite_obstaculo2_x1=1.0,sprite_obstaculo2_x2=1.0-sprite_obstaculo;
float sprite_cenario_x1=0.0,sprite_obstaculo2_y1=0.0,sprite_obstaculo2_y2=1,sprite_cenario_x2=sprite_cenario;
//variaveis seta
float seta=0;

//variaveis para casting
char c[20],p[20],b[20],a[20];
//Pontos 2d objeto Cartesiano
typedef struct pontos2d
{
    float x;
    float y;

}Pontos;

//Criando 4 pontos cartesianos para os obejetos
Pontos pontos_cenario_fundo[4],pontos_personagem[4],pontos_obstaculo1[4];
Pontos pontos_obstaculo2[4],pontos_cenario[4],pontos_vida[4],pontos_fronteiras[4];

void inicializa(void)
{
    glClearColor(1, 1, 1, 0);
    //habilita mesclagem de cores, para termos suporte a texturas (semi-)transparentes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    texturaPersonagem = SOIL_load_OGL_texture(
       "char1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
    texturaCenario = SOIL_load_OGL_texture(
        "Cenario1.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );
    texturaObstaculo = SOIL_load_OGL_texture(
        "tree-2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );
    texturaVida = SOIL_load_OGL_texture(
        "maca.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );
    texturaCenario1 = SOIL_load_OGL_texture(
        "base.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );
    texturaObstaculo3 = SOIL_load_OGL_texture(
        "Arvore2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );
    texturaCenario2 = SOIL_load_OGL_texture(
        "montanha.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );
    texturaObstaculo2 = SOIL_load_OGL_texture(
        "birds.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );
    texturaPause= SOIL_load_OGL_texture(
        "pause.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );
     texturaGameOver= SOIL_load_OGL_texture(
        "GameOver.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );
    texturaVida2= SOIL_load_OGL_texture(
        "fruit_banana.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
    );
    texturaMenu = SOIL_load_OGL_texture(
        "Menu.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
    texturaPersonagem2 = SOIL_load_OGL_texture(
        "char2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
    if (texturaPersonagem == 0 && texturaCenario==0 && texturaObstaculo==0&&texturaVida==0) {
        if(texturaCenario1==0&&texturaCenario2==0 && texturaObstaculo2==0 &&texturaObstaculo3==0)
            {
                if(texturaPause==0&&texturaGameOver==0&&texturaVida2==0&&texturaMenu==0&&texturaPersonagem2==0)

                   {
                     printf("Erro do SOIL: '%s'\n", SOIL_last_result());
                   }
            }
    }
}
//Imprime textos e variaveis
void texto(void* font, char* s, float x, float y) {
  unsigned int i;
  glRasterPos2f(x, y);

  for (i = 0; i<strlen (s); i++) {// menor que
     glutBitmapCharacter(font, s[i]);
  }
}

//Pontuaçao Final
void Pontuacao_Final()
{
    if(controle_de_inicializacao2)
    {
        //casting da variaveis inteiras
        itoa(pontuacao_final,p,10);
        itoa(passaro_final,a,10);
        glColor3f (1, 1, 1);
        texto(GLUT_BITMAP_HELVETICA_12,"PONTUACAO FINAL:", 35, 40);
        texto(GLUT_BITMAP_HELVETICA_12,"NIVEL:", 35, 35);
        texto(GLUT_BITMAP_HELVETICA_12, p, 42, 35);
        texto(GLUT_BITMAP_HELVETICA_12,"QUANTIDADE DE PASSAROS:", 35, 30);
        texto(GLUT_BITMAP_HELVETICA_12,a, 63, 30);
    }
}

//Imprime Variaveis na tela
void Quantidade_Vida()
 {
   if(!controle_de_inicializacao)
    {
        //casting da variaveis inteiras
        itoa(vida,c,10);
        itoa(level_cenario,p,10);
        itoa(quantidade_passaro,b,10);
        //Pontuações
        glColor3f (0, 0, 0);
        texto(GLUT_BITMAP_TIMES_ROMAN_10, "VIDAS:", 92, 97);
        texto(GLUT_BITMAP_TIMES_ROMAN_10, c, 94, 95);
        texto(GLUT_BITMAP_TIMES_ROMAN_10, "PASSARO:", 92, 89);
        texto(GLUT_BITMAP_TIMES_ROMAN_10, b, 94, 87);
        texto(GLUT_BITMAP_TIMES_ROMAN_10, "NIVEL:", 92, 93);
        texto(GLUT_BITMAP_TIMES_ROMAN_10, p, 94, 91);
    }
}
//Funções responsaveis pelo som
void Som_passaro()
{
    PlaySound(TEXT("Bird.wav"),NULL,SND_FILENAME |SND_ASYNC);
}
void Som_menu()
{
    PlaySound(TEXT("MusicaJogo.wav"),NULL,SND_FILENAME |SND_ASYNC);
}
void Som_Pulo()
{
    PlaySound(TEXT("pulo.wav"),NULL,SND_FILENAME |SND_ASYNC);
}
void Som_Game_Over()
{
    PlaySound(TEXT("gameover.wav"),NULL,SND_FILENAME |SND_ASYNC);
}
void Som_Vida()
{
    PlaySound(TEXT("pegandofruta.wav"),NULL,SND_FILENAME|SND_ASYNC);
}
void Musica_jogo()
{
    PlaySound(TEXT("pause.wav"),NULL,SND_FILENAME|SND_ASYNC);
}
void Perdendo_vida()
{
    PlaySound(TEXT("damage.wav"),NULL,SND_FILENAME|SND_ASYNC);
}
void Som_Reset()
{
    PlaySound(TEXT("Reset.wav"),NULL,SND_FILENAME|SND_ASYNC);
}

//surgiemnto da maçã
void AparecerVida()
{
    pontos_vida[0].x=95, pontos_vida[1].x=91, pontos_vida[2].x=91, pontos_vida[3].x=95;
    pontos_vida[0].y=72, pontos_vida[1].y=72, pontos_vida[2].y=76, pontos_vida[3].y=76;
}
//Pontos fixos para desenhar tela de pause/game over e etc
void Pontos_Extremos()
{
    pontos_fronteiras[0].x=0,pontos_fronteiras[1].x=0,pontos_fronteiras[2].x=100,pontos_fronteiras[3].x=100;
    pontos_fronteiras[0].y=0,pontos_fronteiras[1].y=100,pontos_fronteiras[2].y=100,pontos_fronteiras[3].y=0;
}
//Atribuindo valores no plano cartesiano para o passaro
void Surgimento_Obstaculo2()
{
    pontos_obstaculo2[0].x=93,pontos_obstaculo2[1].x=93,pontos_obstaculo2[2].x=96,pontos_obstaculo2[3].x=96;
    pontos_obstaculo2[0].y=72,pontos_obstaculo2[1].y=80,pontos_obstaculo2[2].y=80,pontos_obstaculo2[3].y=72;
}
//Remover as telas de pause/game over e etc
void Remove_Pontos()
{
    int i;
    for(i=0;i<4;i++)
    {
        pontos_fronteiras[i].x=0.0;
        pontos_fronteiras[i].y=0.0;
    }
}
//Remover a maçã
void  RemoverVida()
{
    int i;
    for(i=0;i<4;i++)
    {
         pontos_vida[i].x=0;
         pontos_vida[i].y=0;
    }
}
//remove o passaro
void Remover_Obstaculo2()
{
    int i;
    for(i=0;i<4;i++)
    {
        pontos_obstaculo2[i].x=0.0;
        pontos_obstaculo2[i].y=0.0;
    }
}
//Aparecer o passaro
int Level_Passaro()
{
    return 50+(rand()%20);
}
//Cenario Fundo
void Cenario_Fundo()
{
    //troca Cenario fundo
    if(troca_cenario%2==0)
    {
        glBindTexture(GL_TEXTURE_2D, texturaCenario);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, texturaCenario2);
    }
   //Pontos Cartesianos  iniciais  do CenarioFundo
    pontos_cenario_fundo[0].x=0.0,pontos_cenario_fundo[1].x=0.0,pontos_cenario_fundo[2].x=100,pontos_cenario_fundo[3].x=100;
    pontos_cenario_fundo[0].y=18.6,pontos_cenario_fundo[1].y=100,pontos_cenario_fundo[2].y=100,pontos_cenario_fundo[3].y=18.6;
    glColor3f(cor_cenario1,cor_cenario1,cor_cenario1);
    glBegin(GL_TRIANGLE_FAN);
       glTexCoord2f(sprite_cenario_x1, 0);glVertex3f(pontos_cenario_fundo[0].x,pontos_cenario_fundo[0].y, 0);
       glTexCoord2f(sprite_cenario_x1, 1);glVertex3f(pontos_cenario_fundo[1].x,pontos_cenario_fundo[1].y, 0);
       glTexCoord2f(sprite_cenario_x2, 1);glVertex3f(pontos_cenario_fundo[2].x,pontos_cenario_fundo[2].y, 0);
       glTexCoord2f(sprite_cenario_x2, 0);glVertex3f(pontos_cenario_fundo[3].x,pontos_cenario_fundo[3].y, 0);
    glEnd();
}
//opção confirmar resetar o jogo
void Confirma_Reset()
{
    if(confirmacao_reset)
	 {
		 glColor3f (0, 0, 0);
     	  texto(GLUT_BITMAP_9_BY_15,"Deseja Reiniciar o jogo?", 35, 40);
      	  texto(GLUT_BITMAP_8_BY_13,"Sim", 35, 35);
       	  texto(GLUT_BITMAP_8_BY_13,"Nao", 35, 30);
       	  glBegin(GL_POLYGON);
       	     glVertex3f(32,35.5+seta,0);
       	     glVertex3f(33,35.5+seta,0);
       	     glVertex3f(33,36.5+seta,0);
       	     glVertex3f(32,36.5+seta,0);
        glEnd();
        glBegin(GL_TRIANGLES);
             glVertex3f(33,35+seta,0);
       	     glVertex3f(35,36+seta,0);
       	     glVertex3f(33,37+seta,0);
       	glEnd();
      }
}
//opção confirmar saida do jogo
void Confirmacao()
{
	 if(confirmacao)
	 {
		 glColor3f (0, 0, 0);
     	  texto(GLUT_BITMAP_9_BY_15,"Deseja Sair do jogo?", 35, 40);
      	  texto(GLUT_BITMAP_8_BY_13,"Sim", 35, 35);
       	  texto(GLUT_BITMAP_8_BY_13,"Nao", 35, 30);
       	  glBegin(GL_POLYGON);
       	     glVertex3f(32,35.5+seta,0);
       	     glVertex3f(33,35.5+seta,0);
       	     glVertex3f(33,36.5+seta,0);
       	     glVertex3f(32,36.5+seta,0);
        glEnd();
        glBegin(GL_TRIANGLES);
             glVertex3f(33,35+seta,0);
       	     glVertex3f(35,36+seta,0);
       	     glVertex3f(33,37+seta,0);
       	glEnd();
      }
}
//Desenha o passaro
void Desenha_Obstaculo2()
{

    glBindTexture(GL_TEXTURE_2D, texturaObstaculo2);
    glColor3f(cor_cenario1,cor_cenario1,cor_cenario1);
    glBegin(GL_TRIANGLE_FAN);
       glTexCoord2f(sprite_obstaculo2_x2,sprite_obstaculo2_y1);glVertex3f(pontos_obstaculo2[0].x-Velocidade_Obstaculo2_X,pontos_obstaculo2[0].y, 0);
       glTexCoord2f(sprite_obstaculo2_x2,sprite_obstaculo2_y2);glVertex3f(pontos_obstaculo2[1].x-Velocidade_Obstaculo2_X,pontos_obstaculo2[1].y, 0);
       glTexCoord2f(sprite_obstaculo2_x1,sprite_obstaculo2_y2);glVertex3f(pontos_obstaculo2[2].x-Velocidade_Obstaculo2_X,pontos_obstaculo2[2].y, 0);
       glTexCoord2f(sprite_obstaculo2_x1,sprite_obstaculo2_y1);glVertex3f(pontos_obstaculo2[3].x-Velocidade_Obstaculo2_X,pontos_obstaculo2[3].y, 0);
    glEnd();
}
//desenha o cenario da base
void Desenha_Cenario()
{
    glBindTexture(GL_TEXTURE_2D, texturaCenario1);
    pontos_cenario[0].x=0,pontos_cenario[1].x=100,pontos_cenario[2].x=100,pontos_cenario[3].x=0;
    pontos_cenario[0].y=0,pontos_cenario[1].y=0,pontos_cenario[2].y=20,pontos_cenario[3].y=20;
    glColor3f(cor_cenario1,cor_cenario2,cor_cenario3);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);glVertex3f(pontos_cenario[0].x,pontos_cenario[0].y, 0);
        glTexCoord2f(1, 0);glVertex3f(pontos_cenario[1].x,pontos_cenario[1].y, 0);
        glTexCoord2f(1, 1);glVertex3f(pontos_cenario[2].x,pontos_cenario[2].y, 0);
        glTexCoord2f(0, 1);glVertex3f(pontos_cenario[3].x,pontos_cenario[3].y, 0);
    glEnd();
}
//desenha as arvores na tela
void Desenha_Obstaculo()
{
    pontos_obstaculo1[0].x=100,pontos_obstaculo1[1].x=100,pontos_obstaculo1[2].x=90,pontos_obstaculo1[3].x=90;
    pontos_obstaculo1[0].y=18.6,pontos_obstaculo1[1].y=54.8,pontos_obstaculo1[2].y=54.8, pontos_obstaculo1[3].y=18.6;
    //troca de arvore
    if(troca_arvore%2==0){
        glBindTexture(GL_TEXTURE_2D, texturaObstaculo);
    }
    else
    {
       glBindTexture(GL_TEXTURE_2D, texturaObstaculo3);
    }
    glColor3f(cor_obstaculo1,cor_obstaculo2,cor_obstaculo3);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(1, 0);glVertex3f(pontos_obstaculo1[0].x-Velocidade_Obstaculos_X,pontos_obstaculo1[0].y, 0);
        glTexCoord2f(1, 1);glVertex3f(pontos_obstaculo1[1].x-Velocidade_Obstaculos_X,pontos_obstaculo1[1].y, 0);
        glTexCoord2f(0, 1);glVertex3f(pontos_obstaculo1[2].x-Velocidade_Obstaculos_X,pontos_obstaculo1[2].y, 0);
        glTexCoord2f(0, 0);glVertex3f(pontos_obstaculo1[3].x-Velocidade_Obstaculos_X,pontos_obstaculo1[3].y, 0);
    glEnd();
}
//Desenha a maçã na tela
void Desenha_Vida()
{
    if(level_cenario>=level_inicial_vida)
    {
        //troca de fruta
        if(troca_vida%2==0)
        {
            glBindTexture(GL_TEXTURE_2D, texturaVida);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, texturaVida2);
        }
        glColor3f(cor_vida1,cor_vida2,cor_vida3);
        glBegin(GL_TRIANGLE_FAN);
           glTexCoord2f(1, 0);glVertex3f(pontos_vida[0].x-Velocidade_Vida_X,pontos_vida[0].y+Velocidade_vida_Y, 0);
           glTexCoord2f(0, 0);glVertex3f(pontos_vida[1].x-Velocidade_Vida_X,pontos_vida[1].y+Velocidade_vida_Y, 0);
           glTexCoord2f(0, 1);glVertex3f(pontos_vida[2].x-Velocidade_Vida_X,pontos_vida[2].y+Velocidade_vida_Y, 0);
           glTexCoord2f(1, 1);glVertex3f(pontos_vida[3].x-Velocidade_Vida_X,pontos_vida[3].y+Velocidade_vida_Y, 0);
        glEnd();
    }
}
//desenha personagem
void Desenha_Personagem()
{
    pontos_personagem[0].x=7,pontos_personagem[1].x=7,pontos_personagem[2].x=15,pontos_personagem[3].x=15;
    pontos_personagem[0].y=20,pontos_personagem[1].y=34.1,pontos_personagem[2].y=34.1,pontos_personagem[3].y=20;
    //troca personagem quando trocar o cenario
    if(troca_cenario%2==0)
    {
        glBindTexture(GL_TEXTURE_2D, texturaPersonagem);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, texturaPersonagem2);
    }
    glColor3f(cor_personagem1,cor_personagem2,cor_personagem3);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(sprite_personagem_x1, 0);glVertex3f(pontos_personagem[0].x,pontos_personagem[0].y+Velocidade_Personagem_Y, 0);
        glTexCoord2f(sprite_personagem_x1, 1);glVertex3f(pontos_personagem[1].x,pontos_personagem[1].y+Velocidade_Personagem_Y, 0);
        glTexCoord2f(sprite_personagem_x2, 1);glVertex3f(pontos_personagem[2].x,pontos_personagem[2].y+Velocidade_Personagem_Y, 0);
        glTexCoord2f(sprite_personagem_x2, 0);glVertex3f(pontos_personagem[3].x,pontos_personagem[3].y+Velocidade_Personagem_Y, 0);
    glEnd();
}

//Desenha a tela do pause
void Desenha_Pause()
{
    if(bottom%2!=0)
    {
        Pontos_Extremos();
        glBindTexture(GL_TEXTURE_2D, texturaPause);
        glColor3f(cor_personagem1,cor_personagem2,cor_personagem3);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0);glVertex3f(pontos_fronteiras[0].x,pontos_fronteiras[0].y, 0);
            glTexCoord2f(0, 1);glVertex3f(pontos_fronteiras[1].x,pontos_fronteiras[1].y, 0);
            glTexCoord2f(1, 1);glVertex3f(pontos_fronteiras[2].x,pontos_fronteiras[2].y, 0);
            glTexCoord2f(1, 0);glVertex3f(pontos_fronteiras[3].x,pontos_fronteiras[3].y, 0);
        glEnd();
    }

}
//Desenha tela game over
void Desenha_GameOver()
{
        Pontos_Extremos();
        if(controle_de_inicializacao2)
        {
            glBindTexture(GL_TEXTURE_2D, texturaGameOver);
            glColor3f(cor_personagem1,cor_personagem2,cor_personagem3);
            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(0, 0);glVertex3f(pontos_fronteiras[0].x,pontos_fronteiras[0].y, 0);
                glTexCoord2f(0, 1);glVertex3f(pontos_fronteiras[1].x,pontos_fronteiras[1].y, 0);
                glTexCoord2f(1, 1);glVertex3f(pontos_fronteiras[2].x,pontos_fronteiras[2].y, 0);
                glTexCoord2f(1, 0);glVertex3f(pontos_fronteiras[3].x,pontos_fronteiras[3].y, 0);
            glEnd();
            if(som_gameover)
            {
                 Som_Game_Over();
                 som_gameover=0;
            }
        }
        if(controle_menu)
        {

            glBindTexture(GL_TEXTURE_2D, texturaMenu);
            glColor3f(cor_personagem1,cor_personagem2,cor_personagem3);
            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(0, 0);glVertex3f(pontos_fronteiras[0].x,pontos_fronteiras[0].y, 0);
                glTexCoord2f(0, 1);glVertex3f(pontos_fronteiras[1].x,pontos_fronteiras[1].y, 0);
                glTexCoord2f(1, 1);glVertex3f(pontos_fronteiras[2].x,pontos_fronteiras[2].y, 0);
                glTexCoord2f(1, 0);glVertex3f(pontos_fronteiras[3].x,pontos_fronteiras[3].y, 0);
            glEnd();
        }

}

//Desenha CENA
void desenhaCena(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
    //Cenario Fundo
    Cenario_Fundo();
    //Cenario
    Desenha_Cenario();
    //Obstaculo
    Desenha_Obstaculo();
   //Personagem
    Desenha_Personagem();
    //Vida
    Desenha_Vida();
    //Obstaculo 2
    Desenha_Obstaculo2();
    //Pause
    Desenha_Pause();
    //Game Over
    Desenha_GameOver();
    glDisable(GL_TEXTURE_2D);
   //Pontuações
    Quantidade_Vida();
    Pontuacao_Final();
    //confirmar saida
    Confirmacao();
    //confirmacao reset
    Confirma_Reset();
    glutSwapBuffers();
}

//pulo
void Pulo_Personagem()
{
    Velocidade_Personagem_Y = velocidade_inicial_y*tempo - (0.5*gravidade*pow(tempo,2));
    tempo+=Variavel_inicializacao_pulo;
}
//Voltar o obstaculo ao lado direito
void Voltando_Inicio_Obstaculo()
{
     Velocidade_Obstaculos_X = variacao_inicial;
     level_inicial+=incremento_por_level;
     pause+=incremento_por_level;
     level_cenario++;
     troca_arvore++;
}
//Voltando o Obstaculo2 ao inicio
void Voltando_Obstaculo2()
{
    Remover_Obstaculo2();
    Velocidade_Obstaculo2_X=0.0;
    controle_passaro=0;
    som_passaro=1;
    bonus_passaro=level_cenario+Level_Passaro();
}
//ganha vida passaro
void Ganho_de_Vida2()
{
    //Ganha 5 vida a atingir o objeto 2
    Remover_Obstaculo2();
    quantidade_vida=quantidade_vida+10;
    vida=quantidade_vida/2;
    controle_passaro=0;
    Velocidade_Obstaculo2_X=0.0;
    Som_Vida();
    som_passaro=1;
    bonus_passaro=level_cenario+Level_Passaro();
    quantidade_passaro++;
}

void Ganho_de_Vida()
{
    //Ganho de vida
    velocidade_vida=level_inicial_vida;
    Velocidade_Vida_X=0.0;
    quantidade_vida++;
    vida=quantidade_vida/2;
    troca_vida++;
    Som_Vida();
}

void Reseta_fase()
{
    //Resetando a fase
    Perdendo_vida();
    quantidade_vida=quantidade_vida-2;
    vida=quantidade_vida/2;
    Velocidade_Obstaculos_X=variacao_inicial;
    Velocidade_Personagem_Y=0.0;
    Velocidade_Vida_X=0.0;
    Velocidade_Obstaculo2_X=0.0;
    Variavel_inicializacao_pulo=Variavel_inicializacao_pulo;
    Velocidade_Personagem_Y=0.0;
    if(level_cenario==bonus_passaro)
    {
        Remover_Obstaculo2();
    }
    som_passaro=1;
    //Pausando o jogo depois da colisao
    FPS=FPS_pause;
}

void Reseta()
{
    //Resetando o jogo
    //Resetando as variaveis
    FPS=FPS_pause;
    passaro_final=quantidade_passaro;
    quantidade_passaro=0;
    Velocidade_Obstaculos_X=variacao_inicial;
    Velocidade_Personagem_Y=0.0;
    tempo=0.0;
    Variavel_inicializacao_pulo=0.0;
    level_inicial=0.0;
    controle_de_inicializacao=1;
    pause=0.0;
    velocidade_vida=0.0;
    Velocidade_Vida_X=0.0;
    pontuacao_final=level_cenario;
    level_cenario=0;
    angulo_inicial=0;
    Velocidade_Obstaculo2_X=0.0;
    velocidade_obstaculo2=0.0;
    sprite_cenario_x2=sprite_cenario;
    sprite_cenario_x1=0.0;
    troca_cenario=0;
    vida=0;
    bonus_passaro=Level_Passaro();
    if(level_cenario==bonus_passaro)
    {
        Remover_Obstaculo2();
    }
    som_gameover=1;
    som_passaro=1;
}
//Mudar cor personagem depois colisao
void Mudando_Cor_Colisao()
{
    cor_personagem2=0.0;
}

void Personagem_Nao_Ultrapassar_LimiteCenario_Y()
{
    Velocidade_Personagem_Y=0.0;
    tempo=0.0;
    Variavel_inicializacao_pulo=0.0;
}

void redimensiona(int w, int h)
{
    glViewport(0, 0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 100, 0, 100, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//Pausa
void Pause()
{
    level_inicial=0.0;
    velocidade_vida=0.0;
    Variavel_inicializacao_pulo=0;
    angulo_inicial=0;
    velocidade_obstaculo2=0.0;
}
//Despausa
void Despausa()
{
    if(Velocidade_Personagem_Y!=0)
    {
        Variavel_inicializacao_pulo=inicial_pulo;
    }
    else
    {
         Variavel_inicializacao_pulo=0;
    }
    velocidade_vida=level_inicial_vida;
    level_inicial=pause;
    angulo_inicial=0.01;
    velocidade_obstaculo2=level_inicial_obstaculo2;
    Remove_Pontos();
    PlaySound(NULL,0,0);
}

//Inicializando as variaveis
void Inicializacao()
{
    PlaySound(NULL,0,0);
    velocidade_vida=level_inicial_vida;
    level_inicial=level_inicial_obstaculo;
    pause=level_inicial_obstaculo;
    Variavel_inicializacao_pulo = 0.0;
    controle_de_inicializacao--;
    quantidade_vida=0;
    level_cenario=0;
    angulo_inicial=0.01;
    velocidade_obstaculo2=level_inicial_obstaculo2;
    controle_de_inicializacao2=0;
    Remove_Pontos();
}


void SpecialInput(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
		{
            seta=0;
			break;
		}
		case GLUT_KEY_DOWN:
		{
            seta=-5;
            break;
		}
		default:
            break;
	}
}

void teclado(unsigned char key, int x, int y)
{
   switch(key)
   {

      case 27:
      	{
      		if(!controle_de_inicializacao&&!botao_pause&&!confirmacao_reset)
            {
                Pause();
                confirmacao=1;
                glutSpecialFunc(SpecialInput);
            }
            if(controle_de_inicializacao)
            {
                exit(0);
            }
            break;
      	}
      case 'p':
     {
           //pause o jogo

           if(!controle_de_inicializacao&&!confirmacao&&!confirmacao_reset)
            {
                botao_pause=1;
                if(bottom%2==0)
                {
                    Pause();
                    bottom++;
                    Musica_jogo();
                }
                //despausa o jogo
                else
                {
                    if(velocidade_vida==0)
                    {
                        Despausa();
                        bottom++;
                        Musica_jogo();
                        botao_pause=0;
                    }
                }
              }
            break;
      }
      //começar o jogo
      case 's':
      {
         controle_menu=0;
          //controle para que o usuario comece uma vez
          if(controle_de_inicializacao)
          {
              Inicializacao();
          }
          break;
      }
      //tecla espaço, responsavel pelo pulo do personagem
      case 32:
      {
            //condição para que a funcao pular so funcione quando o jogo estiver inicializado
            if(controle_de_inicializacao!=1&&!Variavel_inicializacao_pulo&&level_inicial!=0)
            {
                Variavel_inicializacao_pulo =inicial_pulo;
                Som_Pulo();
            }
            break;
      }
      case 'r':
        {
           if(!controle_de_inicializacao&&bottom%2==0&&!confirmacao&&!botao_pause)
            {
                Pause();
                confirmacao_reset=1;
                glutSpecialFunc(SpecialInput);

            }
            break;
        }
      case 13:
        {
            if(seta==0&&confirmacao==1)
            {
                exit(0);
            }
            if(seta==0&&confirmacao_reset==1)
            {
                Reseta();
                Inicializacao();
                Som_Reset();
                confirmacao_reset=0;
            }
            if(seta==-5&&confirmacao_reset==1)
            {
                Despausa();
                confirmacao_reset=0;
            }
            if(seta==-5&&confirmacao==1)
            {
                Despausa();
                confirmacao=0;
            }
            break;
        }
      default:
         break;
   }
}

void Movimento_Cenario(int num)
 {

     //Variaveis Variaçoes objetos
     Variacao_obstaculo_X=pontos_obstaculo1[0].x- Velocidade_Obstaculos_X;
     Variacao_personagem_Y = pontos_personagem[0].y + Velocidade_Personagem_Y;
     Variacao_vida_X = pontos_vida[1].x - Velocidade_Vida_X;
     Variacao_obstaculo2=pontos_obstaculo2[0].x-Velocidade_Obstaculo2_X;
     Variacao_personagem_2Y=pontos_personagem[1].y+ Velocidade_Personagem_Y;
     Variacao_obstaculo2_x=pontos_obstaculo2[2].x-Velocidade_Obstaculo2_X;
     Variacao_vida_2X=pontos_vida[0].x-Velocidade_Obstaculo2_X;
     cor_personagem2 = 1.0;
     //Definindo 60 fps
     FPS=1000/60;
     //equacao da trajetoria do personagem quando estiver pulando, pressionado a tecla barra de espaço
     if(Velocidade_Personagem_Y >= 0.0)
    {
        Pulo_Personagem();
    }
    //fazendo com que o personagem não ultrapasse a altura minima do Cenario, e reseta a variavel de inicializacao do pulo;
    if(Velocidade_Personagem_Y < 0.0)
    {
        Personagem_Nao_Ultrapassar_LimiteCenario_Y();
    }
    //Obstaculo ja chegou na extremidade esquerda do Cenario sem nenhuma colisao
    //aumenta a velocidade dos obstaculos
    if(Velocidade_Obstaculos_X >= LIMITE)
    {
        Voltando_Inicio_Obstaculo();
    }
    //nivel aparecer vida
    if(level_cenario>=Aparecer_Vida)
    {
    //Condicional de Verificaçao se o objeto  chegou no limite esquerdo da tela
        AparecerVida();
        if(Velocidade_Vida_X >= LIMITE)
        {
            Velocidade_Vida_X = 0.0;
            troca_vida++;
        }
        //Aquirindo vida ao personagem (Colisao entre o personagem e a vida)
        if((Variacao_vida_X <= pontos_personagem[3].x && Variacao_vida_X>=pontos_personagem[0].x)
           ||(Variacao_vida_2X <= pontos_personagem[3].x && Variacao_vida_2X>=pontos_personagem[0].x))
        {
            if((Variacao_personagem_Y>=pontos_vida[1].y+Velocidade_vida_Y && Variacao_personagem_Y<=pontos_vida[2].y+Velocidade_vida_Y)
               ||(Variacao_personagem_2Y>=pontos_vida[1].y+Velocidade_vida_Y && Variacao_personagem_2Y<=pontos_vida[2].y+Velocidade_vida_Y))
            {
                Ganho_de_Vida();
            }
        }
        //mudando o movimento da vida no eixo y
        Velocidade_vida_Y=Raio*sin(angulo);
        Velocidade_Vida_X+=velocidade_vida;
        angulo=angulo+angulo_inicial;;
    }
    if(level_cenario<Aparecer_Vida)
    {
        RemoverVida();
    }
    //sprite do personagem
    if(Variavel_inicializacao_pulo==0)
    {
        if(sprite_personagem_x2<=1&&controle_de_inicializacao==0 && level_inicial!=0)
        {
            sprite_personagem_x1=sprite_personagem_x2;
            sprite_personagem_x2+=sprites;
        }
        if(sprite_personagem_x2>1)
        {
            sprite_personagem_x1=0;
            sprite_personagem_x2=sprites;
        }
    }
    //fixando sprite quando o personagem pular
    if(Variavel_inicializacao_pulo!=0)
    {
        sprite_personagem_x1=sprites;
        sprite_personagem_x2=sprites+sprites;
    }
    if(level_cenario==bonus_passaro&&controle_passaro==0)
    {
        controle_passaro=1;
    }
    //aparecer o passaro
    if(level_cenario==bonus_passaro&&controle_passaro==1)
    {

        if(som_passaro)
        {
            Som_passaro();
            som_passaro=0;
        }
        Surgimento_Obstaculo2();
            //parte responsavel por sprite do obstaculo2
            if(sprite_obstaculo2_x2>0&&controle_de_inicializacao==0&&level_inicial!=0)
            {
                sprite_obstaculo2_x1=sprite_obstaculo2_x2;
                sprite_obstaculo2_x2-=sprite_obstaculo;
            }
            if(sprite_obstaculo2_x2<=0)
            {
                sprite_obstaculo2_x1=1;
                sprite_obstaculo2_x2=1-sprite_obstaculo;
            }
        //se o obstaculo chegou no limite do cenario
        if(Velocidade_Obstaculo2_X>=pontos_obstaculo2[0].x)
        {
            Voltando_Obstaculo2();
        }
        //Colisao entre personagem e o segundo obstaculo
        if((Variacao_obstaculo2<=pontos_personagem[3].x&&Variacao_obstaculo2>=pontos_personagem[0].x)
           ||(Variacao_obstaculo2_x<=pontos_personagem[3].x&&Variacao_obstaculo2_x>=pontos_personagem[0].x))
        {
            if((Variacao_personagem_Y>=pontos_obstaculo2[0].y&&Variacao_personagem_Y<=pontos_obstaculo2[2].y)
               ||(Variacao_personagem_2Y>=pontos_obstaculo2[0].y&&Variacao_personagem_2Y<=pontos_obstaculo2[2].y))
            {
                Ganho_de_Vida2();
            }
        }
        Velocidade_Obstaculo2_X+=velocidade_obstaculo2;
    }
    //Colisao Entre o personagem e o obstaculo
    //Resetando o jogo e aguardando o usuario a pressionar a tecla para reiniciar
    if(Variacao_obstaculo_X <= pontos_personagem[3].x+5 &&Variacao_obstaculo_X>=pontos_personagem[0].x)
    {
        //Colisao no eixo y
       if(Variacao_personagem_Y <= pontos_obstaculo1[1].y)
        {
          //Condicional de verificação de vida
          if(quantidade_vida < 2)
          {
                //variaveil responsavel por colocar a pontucao final, quando der game over
                passaro_final=0;
                pontuacao_final=0;
                Reseta();
                controle_de_inicializacao2=1;
          }
          else
          {
                Reseta_fase();
                controle_de_inicializacao2=0;
          }
          //mudando a cor do personagem quando ocorrido colisao
          Mudando_Cor_Colisao();
       }
    }
    //Aumenta velocidade dos obstaculos
    Velocidade_Obstaculos_X+=level_inicial;
    glutPostRedisplay();
    //chama a funcao Movimento_Cenario a cada 17 milissegundos ou 60 vezes por segundos
    glutTimerFunc(FPS,Movimento_Cenario, 0);
}

void Reproduzir_som_menu(int idx)
{
    if(controle_menu)
    {
        Som_menu();
        musica=80000;
    }

    glutTimerFunc(musica,Reproduzir_som_menu,0);
}
//Movimento Cenario Fundo
void Sprite_Cenario_Fundo(int idx)
{
    if(sprite_cenario_x2<=1&&controle_de_inicializacao==0 && level_inicial!=0)
    {
         if(sprite_cenario_x2>=variacao_cenario)
         {
            sprite_cenario_x1=sprite_cenario_x1+variacao_cenario;
            sprite_cenario_x2+=variacao_cenario;
         }
    }
    if(sprite_cenario_x2>1)
    {
        sprite_cenario_x2=sprite_cenario;
        troca_cenario++;
        sprite_cenario_x1=0.0;
    }
    glutPostRedisplay();
    glutTimerFunc(FPS,Sprite_Cenario_Fundo,0);

}
void atualiza()
{
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    srand(time(NULL));
    //a partir do level aleatorio que surge o passaro
    bonus_passaro=Level_Passaro();
    //Level Aparecer VIDA
    Aparecer_Vida=5+(rand()%15);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(250,80);
    glutCreateWindow("JUMP TREE");
    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenhaCena);
    glutKeyboardFunc(teclado);
    glutIdleFunc(atualiza);
    inicializa();
    glutTimerFunc(FPS,Movimento_Cenario, 0);
    glutTimerFunc(FPS,Sprite_Cenario_Fundo,0);
    glutTimerFunc(musica,Reproduzir_som_menu,0);
    glutMainLoop();
    return 0;
}
