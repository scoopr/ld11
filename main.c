
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

float goal;

void timer_reset() {
    time=0;
    gettimeofday(&start_time, NULL);
}

void init_level() {
    level+=1;
    goal=(3+rand()%6)/10.0f;
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
    glClear(GL_COLOR_BUFFER_BIT);

    float speed = 0.15f + level * 0.01f;
    float pos = time * speed;
    
    glLoadIdentity();
    glTranslatef(0,0,-1);
    glScalef(goal,goal,goal);
    glColor3f(1,0,0);
    quad();
    
    
    glLoadIdentity();
    glTranslatef(0,0,-1);
    glColor3f(1,1,1);
    glScalef(pos,pos,pos);
    quad();
    
    glutSwapBuffers();
    
}



void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
        exit(0);
        break;
        case ' ':
        init_level();
        timer_reset();
        break;
    }
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInit(&argc, argv);
    glutCreateWindow("GLUT Test");
    glutKeyboardFunc(&keyboard);    
    glutDisplayFunc(&display);
    glutIdleFunc(&idle);
    timer_reset();
    init_level();
    level=0;
    score=0;
    
    glutMainLoop();
}

