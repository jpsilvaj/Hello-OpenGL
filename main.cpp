
#include <windows.h>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
#   include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#define QUADRADO 0
#define TRIANGULO 1
#define POLIGONO 2

#define ABSCICSSAS 0
#define ORDENADAS 1

char texto[30];
GLint primitiva = QUADRADO;

GLfloat redObjeto;
GLfloat greenObjeto;
GLfloat blueObjeto;

GLfloat redFundo;
GLfloat blueFundo;
GLfloat greenFundo;
GLfloat alfaFundo;

GLfloat scale;
GLfloat rotate;

GLfloat widthJanela;
GLfloat heightJanela;

void DesenhaPoligono();
void DesenhaQuadrado();
void DesenhaTriangulo();
void DesenhaBotoes();
void DesenhaTexto(char string[]);
void objeto();
static void resize(GLsizei width, GLsizei height);
static void key(unsigned char key, int x, int y);
static void teclasEspeciais(GLint key, GLint x, GLint y);
static void display(void);
static void idle(void);
static void init(void);

static void init(){

    redFundo = 1;
    greenFundo = 1;
    blueFundo = 1;
    alfaFundo = 0;

    redObjeto = 0;
    greenObjeto = 0;
    blueObjeto = 0;

    rotate = 0;
    scale = 1;

    widthJanela = 640;
    heightJanela = 480;

    //glutInitWindowSize(widthJanela,heightJanela);

    glViewport(0, 0, widthJanela, heightJanela);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-widthJanela/2, widthJanela/2, -heightJanela/2, heightJanela/2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


static void resize(GLsizei width, GLsizei height){

    if(height == 0)
        height = 1;

    widthJanela = width;
    heightJanela = height;

    glViewport(0, 0, widthJanela, heightJanela);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-widthJanela/2, widthJanela/2, -heightJanela/2, heightJanela/2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

/* GLUT callback Handlers */
void objeto(){

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(redObjeto,greenObjeto,blueObjeto);

    switch(primitiva){

        case QUADRADO:
            DesenhaQuadrado();
            break;

        case TRIANGULO:
            DesenhaTriangulo();
            break;

        case POLIGONO:
            DesenhaPoligono();
            break;

    }

    DesenhaBotoes();

}

void DesenhaQuadrado(){

    glPushMatrix();
        glRotatef(rotate,0, 0, 1);
        glScalef(scale, scale, 1);
        glBegin(GL_QUADS);
            glColor3f(0,0,1);
            glVertex2i(0,0);
            glColor3f(redObjeto,greenObjeto,blueObjeto);
            glVertex2i(0,heightJanela/6);
            glVertex2i(widthJanela/6,heightJanela/6);
            glVertex2i(widthJanela/6,0);
        glEnd();
    glPopMatrix();

}

void DesenhaTriangulo(){

    glPushMatrix();
        glRotatef(rotate,0, 0, 1);
        glScalef(scale, scale, 1);
        glBegin(GL_TRIANGLES);
            glColor3f(0,0,1);
            glVertex2i(0,0);
            glColor3f(redObjeto,greenObjeto,blueObjeto);
            glVertex2i(50,0);
            glVertex2i(25,30);
        glEnd();
    glPopMatrix();

}

void DesenhaPoligono(){

    glPushMatrix();
        glRotatef(rotate,0, 0, 1);
        glScalef(scale, scale, 1);
        glBegin(GL_POLYGON);
            glColor3f(0,0,1);
            glVertex2i(0,0);
            glColor3f(redObjeto,greenObjeto,blueObjeto);
            glVertex2i(50,50);
            glVertex2i(30,20);
        glEnd();
    glPopMatrix();
}

void DesenhaTexto(GLint i){

    int offset = 0;

    glColor3f(1.0,1.0,1.0);

    strcpy(texto, " ");

    switch(i){
        case 0: sprintf(texto,"Escalamento +"); break;
        case 1: sprintf(texto,"Escalamento -"); break;
        case 2: sprintf(texto,"Rotacionamento H"); break;
        case 3: sprintf(texto,"Rotacionamento AH"); break;
    }

    glPushMatrix();
        glRasterPos2i(widthJanela/2-100,heightJanela/2-18);
        while(*(texto+offset)){
                 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*(texto+offset));
                 offset++;
        }
    glPopMatrix();

}

void DesenhaBotoes(){

    int i;

    for( i = 0; i < 4;i++){

        glPushMatrix();
            glTranslatef(0,(i*-30),0);
            glColor3f(0.0,0.0,0.0);
            glBegin(GL_QUADS);
                glVertex2i( (widthJanela/2-10) , (heightJanela/2-5) );
                glVertex2i( (widthJanela/2-10) , (heightJanela/2-25) );
                glVertex2i( (widthJanela/2-105) , (heightJanela/2-25) );
                glVertex2i( (widthJanela/2-105) , (heightJanela/2-5) );
            glEnd();
            DesenhaTexto(i);
        glPopMatrix();

    }

}

static void display(void){

    glClearColor(redFundo,greenFundo,blueFundo,alfaFundo);
    glClear(GL_COLOR_BUFFER_BIT);
    DesenhaBotoes();
    objeto(); // desenhaobjeto
    glutSwapBuffers();

}

static void key(unsigned char key, int x, int y){

    switch (key){

        case 27:
            exit(0);
            break;

        case 32:
            init();
            break;

        case 'T':
        case 't':
            primitiva = TRIANGULO;
            break;

        case 'Q':
        case 'q':
            primitiva = QUADRADO;
            break;

        case 'P':
            primitiva = POLIGONO;
            break;

        case 'C':
        case 'c':

            if ( redObjeto > 0.9 || blueObjeto > 0.9 || greenObjeto > 0.9){
                redObjeto = 0;
                blueObjeto = 0;
                greenObjeto = 0;
            }
            redObjeto = redObjeto + 0.18;
            greenObjeto = greenObjeto + 0.15;
            blueObjeto = blueObjeto + 0.10;
            break;

        case 'b':
        case 'B':

            if (redFundo < 0.2 || blueFundo < 0.2 || redFundo < 0.2){
                redFundo = 1;
                blueFundo = 1;
                greenFundo = 1;
            }
            redFundo = redFundo - 0.18;
            blueFundo = blueFundo - 0.15;
            greenFundo = greenFundo - 0.10;

            break;

        default:
            printf("tecla digitada foi %c\n",key);

    }

    glutPostRedisplay();
}

static void teclasEspeciais(GLint key, GLint x, GLint y){

    switch(key){




    }


}

static void idle(void){
    glutPostRedisplay();
}

static void gerenciaMouse(GLint button, GLint state, GLint x, GLint y){

    if(button == GLUT_LEFT_BUTTON)
        if(state == GLUT_DOWN){

            if ( ((x>(widthJanela-105)) && (x<(widthJanela-10)))){

                if((y<25) && (y>5))
                    scale +=0.8;          //Botão de escalamento "positivo" apertado
                if((y<55) && (y>35))
                    scale -=0.8;         //Botão de escalamento "negativo" apertado
                if((y<85) && (y>65))
                    rotate +=15;        //Botão de rotacionamento sentido horário apertado
                if((y<115) && (y>95))
                    rotate -=15;       //Botão de rotacionamento sentido anti-horário apertado

            }

        }

    glutPostRedisplay();

}

/* Program entry point */

int main(int argc, char *argv[]){

    init();

    glutInit(&argc, argv);
    glutInitWindowSize(widthJanela,heightJanela);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Trabalho Computação Gráfica");

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(key);
    glutSpecialFunc(teclasEspeciais);
    glutMouseFunc(gerenciaMouse);

    glutMainLoop();

    return EXIT_SUCCESS;

}
