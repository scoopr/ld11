
#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>

#include <sys/time.h>
#include <math.h>

struct timeval start_time;

float the_time;
int level;
int score;
int failed;

float goal;

void timer_reset() {
    the_time=0;
    gettimeofday(&start_time, NULL);
}

float position() {
    float speed = 0.15f + level * 0.05f;
    return the_time * speed;            
}


void init_level() {
    timer_reset();
    level+=1;
    goal=(3+rand()%6)/10.0f;
    printf("score %d\n", score);
}


void finish_level() {
    float accuracy = fabs( position() - goal );
    if(accuracy < 0) {
        failed=1;
    } else {
        score+=(int)(accuracy*10.0f);
    }
}

void timer_update() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    the_time = ( (current_time.tv_sec-start_time.tv_sec) + (current_time.tv_usec-start_time.tv_usec)/1000000.0f);
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

    if(failed) {
        return;
    }
    
    float pos = position();
    
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
        if(!failed) finish_level();
        init_level();
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
    init_level();
    level=0;
    score=0;
    failed=0;
    
    glutMainLoop();
}

