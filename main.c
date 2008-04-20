
#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>

// TODO: apple ifdef

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>

#include <sys/time.h>
#include <math.h>

#include <stdarg.h>

struct timeval start_time;

float the_time;
int level;
int score;
int failed;

float goal;

#define LEEWAY 0.05f



void timer_reset() {
    the_time=0;
    gettimeofday(&start_time, NULL);
}



float position() {
    float speed = 0.2f + logf(level * 0.05f + 1);
    return the_time * speed;            
}



void init_level() {
    timer_reset();
    level+=1;
    failed=0;
    goal=(40+rand()%50)/100.0f;
}



void finish_level() {
	float pos=position();
    if( fabs(goal-pos) < LEEWAY && pos < 1 ) {
        score += 1;
    } else {
        failed=1;
    }
}



void timer_update() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    the_time = ( (current_time.tv_sec-start_time.tv_sec) + (current_time.tv_usec-start_time.tv_usec)/1000000.0f);
}



void quad(float scale) {
	glLoadIdentity();
	glTranslatef(0,0,-1);
	glScalef(scale, scale, scale);
    glBegin(GL_QUADS);
    glVertex2f(-1,-1);
    glVertex2f( 1,-1); 
    glVertex2f( 1, 1); 
    glVertex2f(-1, 1);
    glEnd();
}



void print(char *str, ...) {
	va_list args;
	int i, len;
	char temp[1024];
	int width;
	va_start(args, str);
	len=vsnprintf(temp, 1024, str, args);
	glLoadIdentity();

	width=0;
	for(i=0; i < len; i++) {
		width+=glutBitmapWidth( GLUT_BITMAP_HELVETICA_18 , temp[i]);
	}

	glRasterPos2f( -width/(float)glutGet(GLUT_WINDOW_WIDTH)  , 0.8f);
	for(i=0; i < len; i++) {
		glutBitmapCharacter( GLUT_BITMAP_9_BY_15 , temp[i]);
	}
	va_end(args);
}



void display() {
    timer_update();
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1,1,1);

    float pos = position();

	if( pos > 1) failed=1;

    if(failed) {
		print("%d", score);
    	glutSwapBuffers();
        return;
    }
    
    glColor3f(1,0,0);
    quad(goal+LEEWAY);
    glColor3f(0,0,0);
    quad(goal-LEEWAY);
    
    glColor3f(1,1,1);
    quad(pos);
    
	print("%d", score);
    glutSwapBuffers();
    
}



void keyboard(unsigned char key, int x, int y) {
    switch(key) {
    case 27:
        exit(0);
        break;
    case ' ':
    	if(failed) {
	    	failed=0;
    		level=0;
    		score=0;
    		init_level();
    	} else {
	        finish_level();
	        if(!failed) init_level();    		
    	}
        break;
    }
}



void idle() {
    glutPostRedisplay();
}



int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInit(&argc, argv);
    glutCreateWindow("redgate");
    glutKeyboardFunc(&keyboard);    
    glutDisplayFunc(&display);
    glutIdleFunc(&idle);
    init_level();
    level=0;
    score=0;
    failed=0;
    
    glutMainLoop();
}

