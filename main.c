
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdint.h>
#include <stdlib.h>

#include <sys/time.h>


struct timeval start_time;

float time;
int32_t level;
int32_t score;

void timer_reset() {
    time=0;
    gettimeofday(&start_time, NULL);
}

void timer_update() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    time = ( (current_time.tv_sec-start_time.tv_sec) + (current_time.tv_usec-start_time.tv_usec)/1000000.0f);
}


void quad() {
    glBegin(GL_QUADS);
    glVertex2f(-1,-1);
    glVertex2f( 1,-1); 
    glVertex2f( 1, 1); 
    glVertex2f(-1, 1);
    glEnd();
}



void display() {
    timer_update();
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,0,-1);
    glColor3f(1,1,1);
    float s=time;
    glScalef(s,s,s);
    glOrtho(-2,2,-2,2,-1,1);
    quad();
    
}



void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
        exit(0);
        break;
    }
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutCreateWindow("GLUT Test");
    glutKeyboardFunc(&keyboard);    
    glutDisplayFunc(&display);
    glutIdleFunc(&idle);
    timer_reset();
    level=0;
    score=0;
    
    glutMainLoop();
}

