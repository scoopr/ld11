
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


void display() {
    glClearColor(rand()%256/255.0f, 0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    
}



void idle() {
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutCreateWindow("GLUT Test");
    //glutKeyboardFunc(&keyboard);    
    glutDisplayFunc(&display);
    glutIdleFunc(&idle);
    
    glutMainLoop();
}

