#include "mesh.h";
#include "OFFManager.h";
#include <GL\glut.h>;

#include "Aretes.h";

#define WIDTH  800
#define HEIGHT 800

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1

#define KEY_ESC 27

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
GLvoid window_idle();

const int posLight1[4] = {0, 0, -5, 0};

Mesh m;

int main(int argc, char **argv) 
{
	
	m = OFFManager::meshLoader("bunny.off");

	std::cout << "nb vertex : " << m.nbvertex() << std::endl;
	std::cout << "nb face : " << m.nbface()/3 << std::endl;

	Aretes aretes = Aretes(m);

	std::cout << "nb aretes : " << aretes.getNbAretes() << std::endl;
	std::cout << "nb aretes par faces : 3" << std::endl;

	float nbMin, nbMax;

	aretes.getNbAretesBySommet(nbMin, nbMax);

	std::cout << "nb aretes par sommet : min = " << nbMin << "; max = " << nbMax << std::endl;

	std::cout << "nb aretes partage par 0 ou 1 sommet : " << aretes.getNbAretesBy0Et1Face(m) << std::endl;

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

    return 0;

	//OFFManager::meshWriter("test.off", m);
}

// initialisation du fond de la fenêtre graphique : noir opaque

GLvoid initGL() 
{
	glShadeModel(GL_SMOOTH);
	glClearColor(RED, GREEN, BLUE, ALPHA);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
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
	glOrtho(-1, 1, -1, 1, -1, 1);

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

	const float rotation = fmod(glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 20, 360.0 );

	glLightiv(GL_LIGHT0, GL_POSITION, posLight1);

	glRotated(rotation, 0,1,0);

	m.affichage();

}