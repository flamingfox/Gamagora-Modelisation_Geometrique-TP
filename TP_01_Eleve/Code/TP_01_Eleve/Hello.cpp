/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 * hello.c
 * This is a simple, introductory OpenGL program.
 */
#include <GL/glut.h>
#include <math.h>

void drawCircle(float centerX, float centerY, float r);
void drawMultipleCircle(float firstCenterX, float firstCenterY, float firstR, float Growth, float nbCircle);
void drawMultipleCircleLine(float firstCenterX, float firstCenterY, float firstR, float Growth, float nbCircle);
void drawFractalSegment(const float& startX, const float& startY, const float& endX, const float& endY, int nbIteration = 1);

void display(void)
{
/* clear all pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

/* draw white polygon (rectangle) with corners at
 * (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0) 
 */
  
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


   glBegin(GL_TRIANGLES);
   glColor3f (1.0, 1.0, 1.0);
      glVertex3f (0.10, 0.10, 0.0);
      glVertex3f (0.10, 0.80, 0.0);
      glVertex3f (0.25, 0.10, 0.0);
   glEnd();

   drawMultipleCircle(0.5, 0.15, 0.05, 1.25, 5);
   drawMultipleCircleLine(0.5, 0.9, 0.05, 0.8, 10);

   drawFractalSegment(0.5, 0.65, 0.8, 0.65, 5);
   drawFractalSegment(0.8, 0.65, 0.65, 0.35, 3);
   drawFractalSegment(0.65, 0.35, 0.5, 0.65, 1);



/* Swap the buffers to show the one
 * on which we writed
 */
   glutSwapBuffers();
}

void init (void)
{
/* select clearing color     */
   glClearColor (0.0, 0.0, 0.0, 0.0);

/* initialize viewing values  */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

/*
 * Declare initial window size, position, and display mode
 * (double buffer and RGB).  Open window with "hello"
 * in its title bar.  Call initialization routines.
 * Register callback function to display graphics.
 * Enter main loop and process events.
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello");
   //glOrtho(0.0, 500.0, 0.0, 500.0, 0.0, 1.0);
   init ();
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}

void drawCircle(float centerX, float centerY, float r){

	int nbIterationMax = 32;

	glBegin(GL_LINE_LOOP);
	glColor3f (1.0, 1.0, 1.0);

		for(int i=0; i<nbIterationMax; i++){
			glVertex3f( centerX + cos(i*2*3.14/nbIterationMax)*r, centerY + sin(i*2*3.14/nbIterationMax)*r, 0 );
		}
	glEnd();
}

void drawMultipleCircle(float firstCenterX, float firstCenterY, float firstR, float Growth, float nbCircle){

	float r=firstR;
	float beginX = firstCenterX - r;
	
	for(int i=0; i<nbCircle; i++){
		drawCircle(beginX+r, firstCenterY, r);
		r *= Growth;
	}
}

void drawMultipleCircleLine(float firstCenterX, float firstCenterY, float firstR, float Growth, float nbCircle){

	float r = firstR;
	float x = firstCenterX;
	
	for(int i=0; i<nbCircle; i++){
		drawCircle(x, firstCenterY, r);
		x = x + r + r*Growth;
		r *= Growth;
	}
}

void drawFractalSegment(const float& startX, const float& startY, const float& endX, const float& endY, int nbIteration){

	/**
					 (O)
	                  X
	                 / \
	                /   \
	(A)         (M)/     \(N)        (B)
	 X-----------X----X---X----------X
					 (I)

	 !!! A = Start(x,y) , B = End(x,y)

	**/

	float startEndX = endX-startX;
	float startEndY = endY-startY;

	float d = sqrt( ( startEndX * startEndX ) + ( startEndY * startEndY ) );

	float mX = startX+startEndX/3.0, mY = startY+startEndY/3.0;
	float nX = startX+2*startEndX/3.0, nY = startY+2*startEndY/3.0;

	float iX = startX+startEndX/2.0, iY = startY+startEndY/2.0;

	float oX = (mX+nX)*cosf(3.14/3) - (nY-mY)*sinf(3.14/3), oY = (mY+nY)*cosf(3.14/3)+(nX-mX)*sinf(3.14/3);

	if(nbIteration <= 1){
		glBegin(GL_LINE_STRIP);
		glColor3f (1.0, 1.0, 1.0);
		
		glVertex3f( startX, startY, 0 );

		glVertex3f( mX , mY, 0);

		glVertex3f( oX, oY, 0 );

		glVertex3f( nX, nY, 0 );

		glVertex3f( endX, endY, 0 );
		glEnd();
	}
	else{

		drawFractalSegment(startX, startY, mX, mY, nbIteration-1);
		
		drawFractalSegment(mX, mY, oX, oY, nbIteration-1);
		
		drawFractalSegment(oX, oY, nX, nY, nbIteration-1);

		drawFractalSegment(nX, nY, endX, endY, nbIteration-1);

	}

}