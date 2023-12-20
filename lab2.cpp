#include <stdlib.h>
#include<ctime>
#include<SOIL/SOIL.h>
#include "particle.hpp"
#define MAXP 55000

Particle p[MAXP];
GLuint tex2d;

Ociste	ociste = { 1.0f, 0.0f, 4.5f };
int w, h;

void renderScene()
{
    for(int i = 0; i <MAXP; i++) {
        if(p[i].lifespan > p[i].age)
            p[i].draw(ociste);
        else
            p[i] = Particle();
    }
}

void animate(int value)
{
    for(int i = 0; i <MAXP; i++)
        p[i].process();
    glutPostRedisplay();
    glutTimerFunc(20, animate, 0);
}
void display()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    renderScene();
    glutSwapBuffers();
}
void reshape(int width, int height)
{
    w = width; h = height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 1, 5);
    //glFrustum(-1, 1, -1, 1, 1, 5);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(ociste.x, ociste.y, ociste.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	// ociste x,y,z; glediste x,y,z; up vektor x,y,z
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch (theKey)
    {
    case 'a': ociste.x = ociste.x+0.2f;
        break;
    case 'd': ociste.x = ociste.x-0.2f;
        break;
    case 'w': ociste.y = ociste.y + 0.2f;
        break;
    case 's': ociste.y = ociste.y - 0.2f;
        break;
    case 'r': ociste.x = 0.0; ociste.y = 0.0;
        break;
    case 27:  exit(0);
        break;
    }
    reshape(w, h);
    glutPostRedisplay();
}


int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(600, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(" Primjer animacije ");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(20, animate, 0);
    glutKeyboardFunc(myKeyboard);
    // tex2d = SOIL_load_OGL_texture
    // (
    //     "iskrica.tga",
    //     SOIL_LOAD_AUTO,
    //     SOIL_CREATE_NEW_ID,
    //     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    // );
    glutMainLoop();
}
