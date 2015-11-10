
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "struct.h"

/* au cas ou M_PI ne soit defini */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

#define WIDTH  600
#define HEIGHT 600

#define KEY_ESC 27

float angleX=0.0f; //angle de rotation en Y de la scene
float angleY=0.0f; //angle de rotation en X de la scene

float pasDeplacement=1.25;


//position lumiere
float xLitePos=0;
float yLitePos=10;
float zLitePos=-100;

float tx=0.0;
float ty=0.0;
float tz=0.0;

void createCylindre(const point3& centre, const float& hauteur, const float& rayon, const int& nbMedi = 10);
void createSphere(const point3& centre, const float& rayon, const int& nbMedi, const int& nbAlti);
void createCone(const float& rayon, const float& longueur, const float& ratioTronque, const int& nbMedi);
void createSphereTronquer(const point3& centre, const float& rayon, const int& nbMedi, const int& nbAlti, const float& angleOuverture);

/* initialisation d'OpenGL*/
static void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// Si vous avez des choses à initialiser, c est ici.	
}


/* Dessin */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //effacement du buffer

	//Description de la scene
	glLoadIdentity();
	//rotation de la scene suivant les mouvements de la souris
	glRotatef(-angleY,0.0f,0.0f,1.0f);
	glRotatef(angleX,0.0f,1.0f,0.0f);
	glTranslatef(tx,ty,tz);

	glRotatef(-angleY,0.0f,0.0f,1.0f);
	glRotatef(angleX,0.0f,1.0f,0.0f);

	// Voir plus tard les push et Pop
	glPushMatrix();			

	//glRotatef(-90,1.0f,0.0f,0.0f);
	// C'est ici que l'on dessine notre cylindre
	// Il n'y a pour l'instant qu'un triangle gris ...

	// Exemple d'appel à Point3
	point3 p1 = point3(-1.0,1.0,0.0);
	point3 p2 = point3(1,1,0);
	point3 p3 = point3(1,2,0);
	//tableau de points
	point3 tab[2];

	tab[0]=p1;
	tab[1]=p2;

	// 0 = cylindre; 1 = sphère, 2 = cone
#define sequence 3

#if(sequence == 0)
	createCylindre(point3(0,0,0), 10, 5);
#elif(sequence == 1)
	createSphere(point3(0,0,0), 5, 16, 16);
#elif(sequence == 2)
	createCone(5.0, 10.0, 0.5, 6);
#elif(sequence == 3)
	createSphereTronquer(point3(0,0,0), 10, 16, 16, 45);
#endif
	glPopMatrix();			



	//affiche les axes du repere
	glColor3f(0.0,1.0,0.0); //Y vert
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(0,20,0);
	glEnd();

	glColor3f(0.0,0.0,1.0); //Z bleu
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(0,0,20);
	glEnd();

	glColor3f(1.0,0.0,0.0); //X rouge
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(20,0,0);
	glEnd();

	glutSwapBuffers();// echange des buffers
}

/* Au cas ou la fenetre est modifiee ou deplacee */
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLvoid gestionSouris(int x, int y)
{
	angleX=x*720/WIDTH; //gere l'axe Oy
	angleY=-(y*180/HEIGHT-90)*4; //gere l'axe Ox

	glutPostRedisplay();
}

GLvoid gestionFleche(int key, int x, int y) 
{
	switch (key) {
	case GLUT_KEY_UP :
		tz+=int(pasDeplacement);glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN :
		tz-=int(pasDeplacement);glutPostRedisplay();
		break;
		glutPostRedisplay();
	}

}

GLvoid window_key_down(unsigned char key, int x, int y)  //appuie des touches
{  
	switch (key) 
	{

		//deplacement de la camera
	case 'z':
		ty+=int(pasDeplacement);glutPostRedisplay();
		break;

	case 's':
		ty-=int(pasDeplacement);glutPostRedisplay();
		break;

	case 'q':
		tx-=int(pasDeplacement);glutPostRedisplay();
		break;

	case 'd':
		tx+=int(pasDeplacement);glutPostRedisplay();
		break;

		//sortie
	case KEY_ESC:
		exit(0);
		break;

	default:
		printf ("La touche %d non active.\n", key);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInitWindowSize(400, 400);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Mon cylindre");
	init();
	glEnable(GL_DEPTH_TEST);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(&window_key_down);
	glutDisplayFunc(display);
	glutPassiveMotionFunc(gestionSouris);
	glutSpecialFunc(&gestionFleche);
	glutMainLoop();
	return 0;
}

void createCylindre(const point3& centre, const float& hauteur, const float& rayon, const int& nbMedi){
	point3 pCentreBas(centre.x, centre.y, centre.z - hauteur/2);
	point3 pCentreHaut(centre.x, centre.y, centre.z + hauteur/2);

	glColor3f(0.8,0.3,0.3);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(pCentreBas.x, pCentreBas.y, pCentreBas.z);
	for(int i = 0; i <= nbMedi; i++){
		glVertex3f(pCentreBas.x + rayon*cos( i*2*M_PI/nbMedi ),
			pCentreBas.y+ rayon*sin(i*2*M_PI/nbMedi ),
			pCentreBas.z);
	}
	glEnd();


	glColor3f(0.3,0.3,0.8);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(pCentreHaut.x, pCentreHaut.y, pCentreHaut.z);
	for(int i = 0; i <= nbMedi; i++){
		glVertex3f(pCentreHaut.x+ rayon*cos( i*2*M_PI/nbMedi ),
			pCentreHaut.y+ rayon*sin(i*2*M_PI/nbMedi ),
			pCentreHaut.z);
	}
	glEnd();

	glColor3f(0.7,0.7,0.7);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < nbMedi; i++){

		glVertex3f(pCentreBas.x + rayon*cos( i*2*M_PI/nbMedi ),
			pCentreBas.y+ rayon*sin( i*2*M_PI/nbMedi ),
			pCentreBas.z);

		glVertex3f(pCentreBas.x + rayon*cos( ((i+1)%nbMedi) *2*M_PI/nbMedi ),
			pCentreBas.y+ rayon*sin( ((i+1)%nbMedi) *2*M_PI/nbMedi ),
			pCentreBas.z);

		glVertex3f(pCentreHaut.x+ rayon*cos( i*2*M_PI/nbMedi ),
			pCentreHaut.y+ rayon*sin( i *2*M_PI/nbMedi ),
			pCentreHaut.z);

		glVertex3f(pCentreHaut.x+ rayon*cos( i*2*M_PI/nbMedi ),
			pCentreHaut.y+ rayon*sin( i *2*M_PI/nbMedi ),
			pCentreHaut.z);

		glVertex3f(pCentreBas.x + rayon*cos( ((i+1)%nbMedi) *2*M_PI/nbMedi ),
			pCentreBas.y+ rayon*sin( ((i+1)%nbMedi) *2*M_PI/nbMedi ),
			pCentreBas.z);

		glVertex3f(pCentreHaut.x+ rayon*cos( ( (i+1)%nbMedi )*2*M_PI/nbMedi ),
			pCentreHaut.y+ rayon*sin( ( (i+1)%nbMedi ) *2*M_PI/nbMedi ),
			pCentreHaut.z);

	}
	glEnd();

}

void createSphere(const point3& centre, const float& rayon, const int& nbMedi, const int& nbAlti){

	/*
	x = r*sin(phi)*cos(gama);
	y = r*sin(phi)*sin(gama);
	z = r*cos(phi);

	*/

	float divSphereAlti = nbAlti+1;

#define deltaPhi (float)(M_PI/divSphereAlti)
#define deltaGama (float)(2*M_PI/nbMedi)

	glColor3f(0.8,0.3,0.3);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(centre.x, centre.y, centre.z + rayon);
	for(int i = 0; i < nbMedi; i++){

		glVertex3f(centre.x + rayon*cos( i*deltaGama )*sin(deltaPhi),
			centre.y+ rayon*sin(i*deltaGama)*sin(deltaPhi),
			centre.z + rayon*cos(deltaPhi));
	}

	glVertex3f(centre.x + rayon*sin(deltaPhi),
		centre.y,
		centre.z + rayon*cos(deltaPhi));
	glEnd();


	glColor3f(0.3,0.3,0.8);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(centre.x, centre.y, centre.z - rayon);
	for(int i = 0; i < nbMedi; i++){

		glVertex3f(centre.x + rayon*cos( i*deltaGama )*sin( (divSphereAlti-1) * deltaPhi),
			centre.y+ rayon*sin(i*deltaGama)*sin( (divSphereAlti-1) * deltaPhi),
			centre.z + rayon*cos( (divSphereAlti-1) * deltaPhi));
	}

	glVertex3f(centre.x + rayon*sin(deltaPhi),
		centre.y,
		centre.z + rayon*cos( (divSphereAlti-1) * deltaPhi));
	glEnd();

	glColor3f(0.7,0.7,0.7);
	glBegin(GL_TRIANGLES);
	for(int j = 1; j < divSphereAlti-1; j++){
		for(int i = 0; i < nbMedi; i++){

			glVertex3f(centre.x + rayon*sin( j* deltaPhi) * cos( i*deltaGama ),
				centre.y+ rayon*sin( j * deltaPhi) * sin(i*deltaGama),
				centre.z + rayon*cos( j * deltaPhi));

			glVertex3f(centre.x + rayon*sin( j * deltaPhi) * cos( ((i+1)%nbMedi) *deltaGama ),
				centre.y+ rayon*sin( j * deltaPhi) * sin( ((i+1)%nbMedi) *deltaGama),
				centre.z + rayon*cos( j * deltaPhi));

			glVertex3f(centre.x + rayon*sin( (j+1) * deltaPhi) * cos( i*deltaGama ),
				centre.y+ rayon*sin( (j+1) * deltaPhi) * sin(i*deltaGama),
				centre.z + rayon*cos( (j+1) * deltaPhi));

			glVertex3f(centre.x + rayon*sin( (j+1) * deltaPhi) * cos( i*deltaGama ),
				centre.y+ rayon*sin( (j+1) * deltaPhi) * sin(i*deltaGama),
				centre.z + rayon*cos( (j+1) * deltaPhi));

			glVertex3f(centre.x + rayon*sin( j * deltaPhi) * cos( ((i+1)%nbMedi) *deltaGama ),
				centre.y+ rayon*sin( j * deltaPhi) * sin( ((i+1)%nbMedi) *deltaGama),
				centre.z + rayon*cos( j * deltaPhi));

			glVertex3f(centre.x + rayon*sin( (j+1) * deltaPhi) * cos( ((i+1)%nbMedi) *deltaGama ),
				centre.y+ rayon*sin( (j+1) * deltaPhi) * sin( ((i+1)%nbMedi) *deltaGama),
				centre.z + rayon*cos( (j+1) * deltaPhi));

		}
	}
	glEnd();

}

void createCone(const float& rayon, const float& longueur, const float& ratioTronque, const int& nbMedi){

#define deltaGama (float)(2*M_PI/nbMedi)

	glColor3f(0.8,0.3,0.3);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, longueur,	0);
	for(int i = 0; i <= nbMedi; i++){
		glVertex3f(rayon*cos( (i%nbMedi)*deltaGama ),
			longueur,
			rayon*sin((i%nbMedi)*deltaGama));
	}
	glEnd();

	if(ratioTronque >= 1.0){

		glColor3f(0.8,0.8,0.8);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0, 0, 0);
		for(int i = 0; i <= nbMedi; i++){
			glVertex3f(rayon*cos( (i%nbMedi)*deltaGama ),
				longueur,
				rayon*sin((i%nbMedi)*deltaGama));
		}
		glEnd();

	}
	else if(ratioTronque > 0.0){

		glColor3f(0.8,0.8,0.8);
		glBegin(GL_TRIANGLES);
		for(int i = 0; i < nbMedi; i++){

			glVertex3f( (1-ratioTronque)*rayon *cos( i*deltaGama ),
				(1-ratioTronque)*longueur,
				(1-ratioTronque)*rayon *sin( i*deltaGama) );

			glVertex3f( (1-ratioTronque)*rayon *cos( ((i+1)%nbMedi)*deltaGama ),
				(1-ratioTronque)*longueur,
				(1-ratioTronque)*rayon *sin(((i+1)%nbMedi)*deltaGama));

			glVertex3f( rayon *cos( i*deltaGama ),
				longueur,
				rayon *sin( i*deltaGama) );

			glVertex3f( rayon *cos( i*deltaGama ),
				longueur,
				rayon *sin( i*deltaGama) );

			glVertex3f( (1-ratioTronque)*rayon *cos( ((i+1)%nbMedi)*deltaGama ),
				(1-ratioTronque)*longueur,
				(1-ratioTronque)*rayon *sin(((i+1)%nbMedi)*deltaGama));

			glVertex3f( rayon *cos( ((i+1)%nbMedi)*deltaGama ),
				longueur,
				rayon *sin( ((i+1)%nbMedi)*deltaGama));
		}
		glEnd();

		glColor3f(0.3,0.3,0.8);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0, (1-ratioTronque)*longueur, 0);
		for(int i = 0; i <= nbMedi; i++){
			glVertex3f( (1-ratioTronque)*rayon *cos( (i%nbMedi)*deltaGama ),
				(1-ratioTronque)*longueur,
				(1-ratioTronque)*rayon *sin((i%nbMedi)*deltaGama ));
		}
		glEnd();

	}
}

void createSphereTronquer(const point3& centre, const float& rayon, const int& nbMedi, const int& nbAlti, const float& angleOuverture){

	/*
	x = r*sin(phi)*cos(gama);
	y = r*sin(phi)*sin(gama);
	z = r*cos(phi);

	*/

	float divSphereAlti = nbAlti+1;
	float angleInterdit = angleOuverture;

	while(angleInterdit > 360)
		angleInterdit -= 360;

	angleInterdit *= (2*M_PI/360);

#define deltaPhi (float)(M_PI/divSphereAlti)
#define deltaGama (float)(2*M_PI/nbMedi)

	glColor3f(0.8,0.3,0.3);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(centre.x, centre.y, centre.z + rayon);
	for(int i = 0; i < nbMedi; i++){

		if( i*deltaGama >= angleInterdit ){
			glVertex3f(centre.x + rayon*cos( i*deltaGama )*sin(deltaPhi),
				centre.y+ rayon*sin(i*deltaGama)*sin(deltaPhi),
				centre.z + rayon*cos(deltaPhi));
		}
	}

	glVertex3f(centre.x + rayon*sin(deltaPhi),
		centre.y,
		centre.z + rayon*cos(deltaPhi));
	glEnd();


	glColor3f(0.3,0.3,0.8);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(centre.x, centre.y, centre.z - rayon);
	for(int i = 0; i < nbMedi; i++){

		if( i*deltaGama >= angleInterdit ){
			glVertex3f(centre.x + rayon*cos( i*deltaGama )*sin( (divSphereAlti-1) * deltaPhi),
				centre.y+ rayon*sin(i*deltaGama)*sin( (divSphereAlti-1) * deltaPhi),
				centre.z + rayon*cos( (divSphereAlti-1) * deltaPhi));
		}
	}

	glVertex3f(centre.x + rayon*sin(deltaPhi),
		centre.y,
		centre.z + rayon*cos( (divSphereAlti-1) * deltaPhi));
	glEnd();

	glColor3f(0.7,0.7,0.7);
	glBegin(GL_TRIANGLES);

	int iMaxInterdit = -1;
	for(int j = 1; j < divSphereAlti-1; j++){
		for(int i = 0; i < nbMedi; i++){

			//if(i*deltaGama < -angleInterdit || i*deltaGama > +angleInterdit ){
			if( i*deltaGama >= angleInterdit ){

				glVertex3f(centre.x + rayon*sin( j* deltaPhi) * cos( i*deltaGama ),
					centre.y+ rayon*sin( j * deltaPhi) * sin(i*deltaGama),
					centre.z + rayon*cos( j * deltaPhi));

				glVertex3f(centre.x + rayon*sin( j * deltaPhi) * cos( ((i+1)%nbMedi) *deltaGama ),
					centre.y+ rayon*sin( j * deltaPhi) * sin( ((i+1)%nbMedi) *deltaGama),
					centre.z + rayon*cos( j * deltaPhi));

				glVertex3f(centre.x + rayon*sin( (j+1) * deltaPhi) * cos( i*deltaGama ),
					centre.y+ rayon*sin( (j+1) * deltaPhi) * sin(i*deltaGama),
					centre.z + rayon*cos( (j+1) * deltaPhi));

				glVertex3f(centre.x + rayon*sin( (j+1) * deltaPhi) * cos( i*deltaGama ),
					centre.y+ rayon*sin( (j+1) * deltaPhi) * sin(i*deltaGama),
					centre.z + rayon*cos( (j+1) * deltaPhi));

				glVertex3f(centre.x + rayon*sin( j * deltaPhi) * cos( ((i+1)%nbMedi) *deltaGama ),
					centre.y+ rayon*sin( j * deltaPhi) * sin( ((i+1)%nbMedi) *deltaGama),
					centre.z + rayon*cos( j * deltaPhi));

				glVertex3f(centre.x + rayon*sin( (j+1) * deltaPhi) * cos( ((i+1)%nbMedi) *deltaGama ),
					centre.y+ rayon*sin( (j+1) * deltaPhi) * sin( ((i+1)%nbMedi) *deltaGama),
					centre.z + rayon*cos( (j+1) * deltaPhi));

			}
			else{
				iMaxInterdit = i+1;
			}
		}
	}
	glEnd();

	glColor3f(0.0,0.7,0.7);
	glBegin(GL_TRIANGLES);
	for(int j = 0; j < divSphereAlti; j++){

		//i = 0;
		glVertex3f(centre.x, centre.y, centre.z);
		glVertex3f(centre.x + rayon*sin( j* deltaPhi ),
			centre.y,
			centre.z + rayon*cos( j * deltaPhi ));

		glVertex3f(centre.x + rayon*sin( (j+1) * deltaPhi),
			centre.y,
			centre.z + rayon*cos( (j+1) * deltaPhi));

		
		glVertex3f(centre.x, centre.y, centre.z);
		glVertex3f(centre.x + rayon*sin( j* deltaPhi ) * cos( iMaxInterdit*deltaGama ),
			centre.y+ rayon*sin( j * deltaPhi) * sin( iMaxInterdit*deltaGama ),
			centre.z + rayon*cos( j * deltaPhi ));

		glVertex3f(centre.x + rayon*sin( (j+1) * deltaPhi) * cos( iMaxInterdit*deltaGama ),
			centre.y+ rayon*sin( (j+1) * deltaPhi) * sin( iMaxInterdit*deltaGama),
			centre.z + rayon*cos( (j+1) * deltaPhi));
			
	}
	glEnd();

}