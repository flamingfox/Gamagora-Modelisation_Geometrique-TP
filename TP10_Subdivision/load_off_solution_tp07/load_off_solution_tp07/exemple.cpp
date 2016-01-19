 
/********************************************************/
/* Chargement fichier off                               */
/********************************************************/

/* inclusion des fichiers d'en-tete Glut */


#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <GL/glut.h>

#include "int_vector.h"
#include "mid_edge.h"

std::vector <double> vertex;
std::vector <double> normal;
std::vector <double> color;
std::vector <int> connectivity;

std::vector <std::vector<int> > face_ring;

int drawing_number=-1;

char presse,presse_d=0;
int anglex,angley,x,y,xold,yold;
double zoom=-5.0;

/* Prototype des fonctions */
void affichage();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);

void load_off_file(const char* filename);
void build_normal();
void scale();
void colorize();
void create_drawing_list();
void subdivide();

int main(int argc,char **argv)
{
  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(550,550);
  glutCreateWindow("Test");

  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);

  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);


  //light
  float light_ambient[4]={0.4,0.4,0.4,1.0};
  float light_diffuse[4]={0.4,0.4,0.4,1.0};
  float light_specular[4]={0.3,0.3,0.3,1.0};
  float light_position [4] = {2.0,100.0,100.0,1.0};

  float material_ambient [4] = {1.0,1.0,1.0,1.0};
  float material_diffuse [4] = {1.0,1.0,1.0,1.0};
  float material_specular [4] = {1.0,1.0,1.0,1.0};
  float material_exponent [1] = {60.0};


  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);  
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);  
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_exponent);
  glEnable(GL_DEPTH_TEST);




  /* Charge fichier off */
  load_off_file("david_2.off");

  /* Subdivision du maillage*/
  subdivide();
  subdivide();
  
  /* Calcule les normales */
  build_normal();

  /* center and scale size */
  scale();

  /* colorize */
  colorize();

  /* drawing list */
  create_drawing_list();

  /* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}

void subdivide()
{

  /* tailles */
  int N_vertex=vertex.size()/3;
  int N_triangle=connectivity.size()/3;

  /* la nouvelle connectivite */
  std::vector <int> new_connectivity;

  /* Conteneur pour les indices des sommets milieux */
  mid_edge mid;
  mid.init(N_vertex);
  
  int index_0=0,index_1=0,index_2;
  int current_index=N_vertex;//the index of the current mid_point in the vertex vector
  for(int k_triangle=0;k_triangle<N_triangle;k_triangle++)
    {
      for(int k_edge=0;k_edge<3;k_edge++) //on parcours toute les aretes
	{
	  // indices des sommets de l'arete courante
	  index_0 = connectivity[3*k_triangle+k_edge];
	  index_1 = connectivity[3*k_triangle+(k_edge+1)%3];

	  if(mid.existing_mid_point(index_0,index_1)==0) //si==0, sommet non répertorié: on l'ajoute
	    {
	      // ajoute le sommet dans la liste
	      mid.add_mid_point(index_0,index_1,current_index++);
	      // On place les nouvelles coordonnees
	      for(int k_dim=0;k_dim<3;k_dim++)
		vertex.push_back(0.5*(vertex[3*index_0+k_dim]+vertex[3*index_1+k_dim]));
	    }
	}
    }


  int index_mid_0=0,index_mid_1=0,index_mid_2=0;
  // MAJ de la nouvelle connectivite
  for(int k_triangle=0;k_triangle<N_triangle;k_triangle++)
    {
      //indice des sommets de bases
      index_0 = connectivity[3*k_triangle+0];
      index_1 = connectivity[3*k_triangle+1];
      index_2 = connectivity[3*k_triangle+2];
      
      //indice des sommets milieux des 3 aretes
      index_mid_0 = mid.index_mid_point(index_0,index_1);
      index_mid_1 = mid.index_mid_point(index_1,index_2);
      index_mid_2 = mid.index_mid_point(index_2,index_0);
      
      //ajout des 3 triangles lateraux
      new_connectivity.push_back(index_0);new_connectivity.push_back(index_mid_0);new_connectivity.push_back(index_mid_2);
      new_connectivity.push_back(index_1);new_connectivity.push_back(index_mid_1);new_connectivity.push_back(index_mid_0);
      new_connectivity.push_back(index_2);new_connectivity.push_back(index_mid_2);new_connectivity.push_back(index_mid_1);
      
      //ajout du triangle centrale reliant les points milieux.
      new_connectivity.push_back(index_mid_0);new_connectivity.push_back(index_mid_1);new_connectivity.push_back(index_mid_2);
      
    }
  
  connectivity=new_connectivity;


  //** ALGO **/
  //
  // index_mid_edge <- nombre de sommets
  // Pour chaque face
  //   Pour chaque arete [v0,v1]
  //   ajouter index_mid_edge pour arete [v0,v1]
  //   ajouter (v0+v1)/2 dans liste de sommets
  //   incremente index_mid_edge

  // Pour chaque face d'arete [v0,v1,v2]
  //   ajouter face [v0,index_mid_edge(v0,v1),index_mid_edge(v2,v0)] dans connectivity
  //   ajouter face [v1,index_mid_edge(v1,v2),index_mid_edge(v0,v1)] dans connectivity      
  //   ajouter face [v2,index_mid_edge(v2,v0),index_mid_edge(v1,v2)] dans connectivity
  //   ajouter face [index_mid_edge(v0,v1),index_mid_edge(v1,v2),index_mid_edge(v2,v0)] dans connectivity
  //
  //**      **/


}

void create_drawing_list()
{
	if(glIsList(drawing_number))
		glDeleteLists(drawing_number,1);
	drawing_number=glGenLists(1);
	glNewList(drawing_number,GL_COMPILE);

	int N_triangle=connectivity.size();
	glEnableClientState(GL_NORMAL_ARRAY);	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glNormalPointer(GL_DOUBLE,0,&normal[0]);
	glVertexPointer(3,GL_DOUBLE,0,&vertex[0]);
	glColorPointer(3,GL_DOUBLE,0,&color[0]);

	glDrawElements(GL_TRIANGLES,N_triangle,GL_UNSIGNED_INT,&connectivity[0]);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);


	glEndList();
}

void colorize()
{
	int N_vertex=vertex.size()/3;
	double minimum[3]={99,99,99},maximum[3]={-1,-1,-1};
	for(int k=0;k<N_vertex;k++)
		for(int k_dim=0;k_dim<3;k_dim++)
		{
			if(vertex[3*k+k_dim]>maximum[k_dim])
				maximum[k_dim]=vertex[3*k+k_dim];
			if(vertex[3*k+k_dim]<minimum[k_dim])
				minimum[k_dim]=vertex[3*k+k_dim];
		}

	color.resize(3*N_vertex);
	for(int k=0;k<N_vertex;k++)
		for(int k_dim=0;k_dim<3;k_dim++)
			color[3*k+k_dim]=(vertex[3*k+k_dim]-minimum[k_dim])/(maximum[k_dim]-minimum[k_dim]);	
}

void scale()
{
	int N_vertex=vertex.size()/3;
	double minimum[3]={99,99,99},maximum[3]={-1,-1,-1};
	for(int k=0;k<N_vertex;k++)
		for(int k_dim=0;k_dim<3;k_dim++)
		{
			if(vertex[3*k+k_dim]>maximum[k_dim])
				maximum[k_dim]=vertex[3*k+k_dim];
			if(vertex[3*k+k_dim]<minimum[k_dim])
				minimum[k_dim]=vertex[3*k+k_dim];
		}
	double maxmax=fmax(fmax(maximum[0],maximum[1]),maximum[2]);
	double minmin=fmax(fmin(minimum[0],minimum[1]),minimum[2]);

	for(int k=0;k<N_vertex;k++)
		for(int k_dim=0;k_dim<3;k_dim++)
			vertex[3*k+k_dim]=(vertex[3*k+k_dim]-0.5*(maximum[k_dim]+minimum[k_dim]))/(maxmax-minmin);
}

void load_off_file(const char* filename)
{

#define SIZE_BUFFER 2048
	char buffer[SIZE_BUFFER]={'\0'};


	FILE *fid=NULL;
	fid=fopen(filename,"r");
	if(fid==NULL)
	{printf("ERROR loading %s in load_off_file\n",filename);exit(-1);}


	while(strcmp(buffer,"OFF")!=0)
	{
		if(fscanf(fid,"%s",buffer)==EOF)
		{printf("ERROR file %s is not off file\n",filename);exit(-1);}
		if(buffer[0]=='#')//comments
			fgets(buffer,sizeof(buffer),fid);
	}


	//pass comments
	fscanf(fid,"%s",buffer);
	while(buffer[0]=='#')//comments
	{
		fgets(buffer,sizeof(buffer),fid);
		fscanf(fid,"%s",buffer);
	}


	//read Number of vertices
	int N_vertex=0,N_polygon=0;
	int k_vertex=0;
	N_vertex=atoi(buffer);//N_vertex
	fscanf(fid,"%d",&N_polygon);//N_polygon
	fgets(buffer,sizeof(buffer),fid);//read line


	//read vertices
	float X[3];
	while(k_vertex<N_vertex)
	{
		if(fscanf(fid,"%f %f %f",X,X+1,X+2)!=3)
		{
			fscanf(fid,"%s",buffer);
			if(buffer[0]!='#')
			{printf("ERROR loading %s\n",filename);exit(-1);}
			else//read line
				fgets(buffer,sizeof(buffer),fid);
		}
		else
		{
			for(int k=0;k<3;k++)
				vertex.push_back(X[k]);
			k_vertex++;
		}
	}

	//read connectivity
	int size_poly=0;
	int k_polygon=0;
	int k_current_polygon=0;
	int temp=0;
	std::vector <int> v_poly;
	for(k_polygon=0;k_polygon<N_polygon;k_polygon++)
	{
		if(fscanf(fid,"%d",&size_poly)!=1)
		{
			fscanf(fid,"%s",buffer);
			if(buffer[0]!='#')
			{printf("ERROR loading triangles in load_off_file %s\n",filename);exit(-1);}
			else//read line
			{
				fgets(buffer,sizeof(buffer),fid);
				k_polygon--;
			}
		}
		else
		{
			v_poly.resize(0);
			for(k_current_polygon=0;k_current_polygon<size_poly;k_current_polygon++)
			{
				fscanf(fid,"%d",&temp);
				v_poly.push_back(temp);
			}

			for(unsigned int k=0;k<v_poly.size()-2;k++)
			{
				connectivity.push_back(v_poly[0]);
				connectivity.push_back(v_poly[k+1]);
				connectivity.push_back(v_poly[k+2]);
			}


		}
	}

	printf("[Chargement fichier %s OK]\n",filename);

}

void build_normal()
{


	int N_triangle=connectivity.size()/3;
	int N_vertex=vertex.size()/3;
	face_ring.resize(N_vertex);

	//fill face ring
	for(int k=0;k<N_triangle;k++)
		for(int k_tri=0;k_tri<3;k_tri++)
			face_ring[connectivity[3*k+k_tri]].push_back(k);

	//normal per face
	std::vector <double> face_normal;
	face_normal.resize(3*N_triangle);
	double *X0=NULL,*X1=NULL,*X2=NULL;
	double u[3],v[3];
	double _normal[3],n;
	for(int k=0;k<N_triangle;k++)
	{
		X0=&vertex[3*connectivity[3*k+0]];
		X1=&vertex[3*connectivity[3*k+1]];
		X2=&vertex[3*connectivity[3*k+2]];

		for(int k_dim=0;k_dim<3;u[k_dim]=X1[k_dim]-X0[k_dim],v[k_dim]=X2[k_dim]-X0[k_dim],k_dim++);
		_normal[0]=u[1]*v[2]-u[2]*v[1];
		_normal[1]=u[2]*v[0]-u[0]*v[2];
		_normal[2]=u[0]*v[1]-u[1]*v[0];
		n = powf(_normal[0]*_normal[0]+_normal[1]*_normal[1]+_normal[2]*_normal[2],0.5);
		if(n>0.0001)
			for(int k_dim=0;k_dim<3;k_dim++)
				_normal[k_dim]/=n;
		for(int k_dim=0;k_dim<3;k_dim++)
			face_normal[3*k+k_dim]=_normal[k_dim];
	}
	int N_ring=0;
	normal.resize(3*N_vertex);
	for(int k=0;k<N_vertex;k++)
	{
		//init to 0
		for(int k_dim=0;k_dim<3;k_dim++)
			normal[3*k+k_dim]=0.0;

		//sum up over the faces
		N_ring=face_ring[k].size();
		for(int k_ring=0;k_ring<N_ring;k_ring++)
			for(int k_dim=0;k_dim<3;k_dim++)
				normal[3*k+k_dim]+=face_normal[3*face_ring[k][k_ring]+k_dim];

		//normalize
		n = powf(normal[3*k+0]*normal[3*k+0]+normal[3*k+1]*normal[3*k+1]+normal[3*k+2]*normal[3*k+2],0.5);
		if(n>0.0001)
			for(int k_dim=0;k_dim<3;k_dim++)
				normal[3*k+k_dim]/=n;
	}

}

void affichage()
{

	/* effacement de l'image avec la couleur de fond */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (45, 1.0, 0.1,100.0);


	//Modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0,0.0,zoom);
	glRotatef(-angley,1.0,0.0,0.0);
	glRotatef(-anglex,0.0,1.0,0.0);


	glCallList(drawing_number);

	/*
	   glBegin(GL_TRIANGLES);

	   int N=connectivity.size()/3;
	   for(int i=0;i<N;i++)
	   {
	   for(int k=0;k<3;k++)
	   {
	   glColor3f(
	   color[3*connectivity[3*i+k]+0],
	   color[3*connectivity[3*i+k]+1],
	   color[3*connectivity[3*i+k]+2]
	   );


	   glNormal3f(
	   normal[3*connectivity[3*i+k]+0],
	   normal[3*connectivity[3*i+k]+1],
	   normal[3*connectivity[3*i+k]+2]
	   );
	   glVertex3f(
	   vertex[3*connectivity[3*i+k]+0],
	   vertex[3*connectivity[3*i+k]+1],
	   vertex[3*connectivity[3*i+k]+2]
	   );
	   }
	   }

	   glEnd();
	   */

	/* On echange les buffers */
	glutSwapBuffers();
}

void clavier(unsigned char touche,int x,int y)
{
	x=0;y=0;
	switch (touche)
	{
		case 'p': /* affichage du carre plein */
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			glutPostRedisplay();
			break;
		case 'f': /* affichage en mode fil de fer */
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			glutPostRedisplay();
			break;
		case 's' : /* Affichage en mode sommets seuls */
			glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
			glutPostRedisplay();
			break;
		case 'd':
			glEnable(GL_DEPTH_TEST);
			glutPostRedisplay();
			break;
		case 'D':
			glDisable(GL_DEPTH_TEST);
			glutPostRedisplay();
			break;
        case 'q' : /*la touche 'q' permet de quitter le programme */
			exit(0);
	}
}

void reshape(int x,int y)
{
	if (x<y)
		glViewport(0,(y-x)/2,x,x);
	else 
		glViewport((x-y)/2,0,y,y);
}

void mouse(int button, int state,int x,int y)
{
	/* si on appuie sur le bouton gauche */
	if(state == GLUT_DOWN) 
	{
		xold = x; /* on sauvegarde la position de la souris */
		yold=y;
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		presse=1;
	if(button == GLUT_LEFT_BUTTON && state==GLUT_UP)
		presse=0;

	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		presse_d=1;
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		presse_d=0;

}

void mousemotion(int x,int y)
{
	if (presse) /* si le bouton gauche est presse */
	{
		/* on modifie les angles de rotation de l'objet
		   en fonction de la position actuelle de la souris et de la derniere
		   position sauvegardee */
		anglex=anglex+(x-xold); 
		angley=angley+(y-yold);
		glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
	}
	if(presse_d)
	{
		zoom = zoom + (y-yold)/50.0;
		glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
	}


	xold=x; /* sauvegarde des valeurs courante de le position de la souris */
	yold=y;
}






