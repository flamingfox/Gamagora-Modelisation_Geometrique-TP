#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>

#include "GL/glut.h"

#define WIDTH  480
#define HEIGHT 480

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1
#define PI 3.14159

#define KEY_ESC 27

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
GLvoid window_idle(); 

const int posLight[4] = {0, 25, 25, 0};

int main(int argc, char **argv) 
{  
	// initialisation  des paramètres de GLUT en fonction
	// des arguments sur la ligne de commande
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// définition et création de la fenêtre graphique
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Primitives graphiques");

	// initialisation de OpenGL et de la scène
	initGL();  
	init_scene();

	// choix des procédures de callback pour 
	// le tracé graphique
	glutDisplayFunc(&window_display);
	// le redimensionnement de la fenêtre
	glutReshapeFunc(&window_reshape);
	// la gestion des événements clavier
	glutKeyboardFunc(&window_key);
	glutIdleFunc(&window_idle);
	// la boucle prinicipale de gestion des événements utilisateur
	glutMainLoop();  

	return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque

GLvoid initGL() 
{
	glShadeModel(GL_SMOOTH);
	glClearColor(RED, GREEN, BLUE, ALPHA);
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
}

void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	render_scene();

	// trace la scène grapnique qui vient juste d'être définie
	glFlush();
	glutSwapBuffers();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);

	// toutes les transformations suivantes s´appliquent au modèle de vue 
	glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
	switch (key) {    
	case KEY_ESC:  
		exit(1);
		break;

	default:
		printf ("La touche %d n´est pas active.\n", key);
		break;
	}     
}

GLvoid window_idle() 
{  
	glutPostRedisplay();
}


void render_scene()
{
	//c'est ici qu'on dessine
	glLoadIdentity();

	//glLightiv(GL_LIGHT0, GL_POSITION, posLight);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	const float rotation = fmod(glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 20, 360.0 );

	glRotated(rotation, 0,0,1);

	glColor3f(0.0,0.0,1.0); //Z bleu
		glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0,20,0);
	glEnd();

	glColor3f(0.7,0.7,0.7); //Blanc

	for(int i=1; i<=4; i++){

		glRotated(rotation, 0,1,0);
		glTranslated(5.0,0.0,0.0);

		glPushMatrix();
		
		glRotated(rotation*i, 0,1,0);
		glutWireTeapot(3.0);

		glPushMatrix();

		glRotated(rotation*i*-3.0, 0,1,0);
		glTranslated(7,0,0);
		glutSolidSphere(1.0, 16, 16);

		glPopMatrix();
		glPopMatrix();

		glTranslated(-5,5,0);
		glScaled(0.65,0.65,0.65);		
	}
}