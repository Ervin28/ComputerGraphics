// Open3D.cpp : Defines the entry point for the console application.
//


#include <stdlib.h>
#include "glut.h"
#include <math.h>
#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include <charconv>
using namespace std;

float xRot = 0.0f;
float yRot = 0.0f;
float yRot2 = 0.0f;
float r = 5.0f;
GLboolean bSwtich = 0;

void BitmapText(GLfloat x, GLfloat y, char *string)
{
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++){
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}

void StrokeText(string string)
{
  int len, i;
  len = string.length();
  for (i = 0; i < len; i++){
    glutStrokeCharacter (GLUT_STROKE_ROMAN, string[i]);
  }
}

bool animate = false, animate2 = false, animate3 = false;
float szog = 0.0, szog2 = 0.0, szog3 = 0.0,pont =0.0, pont2 = 0.0, pont3 = 0.0, pont4 = 0.0, elojel4 = 0.1f;
int elojel = 1, elojel2 = 1, elojel3 = 1 ;

void Timer(int value)
{
	szog += elojel * 0.5;
	if (szog > 30) elojel = -elojel;
	if (szog < -30) elojel = -elojel;
	if (animate) glutTimerFunc(30, Timer, value);
	glutPostRedisplay();
}
void Timer2(int value)
{
	szog2 += elojel2 * 0.5;
	pont +=elojel2 * -0.004;
	pont2 +=elojel2 * -0.01;
	if (szog2 > 45) {
		animate2 = !animate2;
		elojel2 = -elojel2;
	}

	if (szog2 < 0)
	{
		elojel2 = -elojel2;
	
	}
	if (animate2) glutTimerFunc(30, Timer2, value);
	glutPostRedisplay();
}
void Timer3(int value)
{
	szog3 += elojel3 * 0.5;
	pont3 += elojel4 * 0.1;
	pont4 += elojel4 * -0.000000000000000001;
	if (szog3 > 45) {
		elojel3 = -elojel3;
		elojel4 = -elojel4;
	}

	if (szog3 < 0)
	{
		elojel3 = -elojel3;
		elojel4 = -elojel4;
		/*animate2 = !animate2;
		animate3 = !animate3;*/

	}
	if (animate3) glutTimerFunc(30, Timer3, value);
	glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		animate = !animate;
		if (animate) glutTimerFunc(30, Timer, 0);
	}
	if (key == GLUT_KEY_F2)
	{
		animate2 = !animate2;
		if (animate2) glutTimerFunc(30, Timer2, 0);
	}
	if (key == GLUT_KEY_F3)
	{
		animate3 = !animate3;
		if (animate3) glutTimerFunc(30, Timer3, 0);
	}
	glutPostRedisplay();
}



void balkar()

{	
	
	float r = 0.1, g = 0.5, b = 1;
	glPushMatrix();
		
		//animacio
		glRotatef(szog2, 0, -1, -5);
		glTranslatef(pont, pont2, 0);
		
		glRotatef(-90, 0, 1, 0);
		glRotatef(45, 1, 0, 0);
		glTranslatef(0, 1, 0);
	
		GLUquadricObj* quadratic;
		quadratic = gluNewQuadric();

		//bal felkar
		glColor3f(r, g, b);
		gluCylinder(quadratic, 0.4f, 0.2f, 1.0f, 320, 32);

		//animacio2
		glRotatef(szog3, -0.1f, 0, 0);
		//glTranslatef(pont3, pont4,pont4);
	
		//bal alkar
		glTranslatef(0, 0, 1);
		glColor3f(b, r, g);
		gluCylinder(quadratic, 0.2f, 0.1f, 1.0f, 320, 32);

		//balkez
		glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
		glTranslatef(0, 0, 1);
		glutSolidSphere(0.2, 60, 60);

	glPopMatrix();

}
void jobbkar() {
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	float r = 0.1, g = 0.5, b = 1;
	
		glPushMatrix();

		glRotatef(szog, 5, 0, 1);

		glRotatef(90, 0, 1, 0);
		glRotatef(45, 1, 0, 0);
		glTranslatef(0, 1, 0);

		//jobb felkar
		glColor3f(r, g, b);
		gluCylinder(quadratic, 0.4f, 0.2f, 1.0f, 320, 32);
		/*glRotatef(szog, -1, -2, 0);*/
		//jobb alkar
		glTranslatef(0, 0, 1);
		glColor3f(b, r, g);
		gluCylinder(quadratic, 0.2f, 0.1f, 1.0f, 320, 32);

		//jobbkez
		glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
		glTranslatef(0, 0, 1);
		glutSolidSphere(0.2, 60, 60);
	glPopMatrix();
}

void ballab() {
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	float r = 0.1, g = 0.5, b = 1;
	
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		glTranslatef(0, -0.5f, 1);
		
		//animacio
		glRotatef(szog, 0, -2, 0);

		////bal comb
		glColor3f(r, g, b);
		gluCylinder(quadratic, 0.4f, 0.2f, 1.0f, 320, 32);

		//bal vadli
		glTranslatef(0, 0, 1);
		glColor3f(b, r, g);
		gluCylinder(quadratic, 0.2f, 0.1f, 1.0f, 320, 32);

		//bal talp
		glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
		glTranslatef(-0.25, 0, 1);
		//glutSolidSphere(0.2, 60, 60);
		glScalef(1, 0.4, 0.25);
		glutSolidCube(1);
	glPopMatrix();
}
void jobblab() {
	
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	float r = 0.1, g = 0.5, b = 1;
	glPushMatrix();
	
	//animacio
	glRotatef(szog, 2, 0, 0);

	glRotatef(90, 1, 0, 0);
	glRotatef(-90, 0, 0, 1);
	glTranslatef(0, 0.5f, 1);

	////jobb comb

	glColor3f(r, g, b);
	gluCylinder(quadratic, 0.4f, 0.2f, 1.0f, 320, 32);

	//jobb vadli
	glTranslatef(0, 0, 1);
	glColor3f(b, r, g);
	gluCylinder(quadratic, 0.2f, 0.1f, 1.0f, 320, 32);

	//jobb talp
	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	glTranslatef(-0.25, 0, 1);
	//glutSolidSphere(0.2, 60, 60);
	glScalef(1, 0.4, 0.25);
	glutSolidCube(1);

	glPopMatrix();

}
void karakter() {
	float r = 0.1, g = 0.5, b = 1;
	GLUquadricObj* quadratic,*quadratic1;
	quadratic = gluNewQuadric();
	quadratic1 = gluNewQuadric();

	glTranslatef(0, 5, 0);
	//fej
	glutSolidSphere(1, 60, 60);
	glTranslatef(0, -1.5f, 0);

	//nyak
	glRotatef(-90, 1, 0, 0);
	glColor3f(g, b, r);
	gluCylinder(quadratic, 0.5f, 0.3f, 1.0f, 320, 32);

	//torzs
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -2, 0);
	glScalef(1, 2, 0.5);
	glutSolidCube(2);
	
	//kezek
	balkar();
	jobbkar();
	//
	//glScalef(1.2f, 1, 1);
	//
	////labak
	ballab();
	jobblab();
	


	

	
	

	
}
void karakterSus()
{
	int V[8][3] = { {-2, -2, 2}, {2, -2, 2}, {2, 4, 2}, {-2, 4, 2}, {-2, -2, 0}, {2, -2, 0}, {2, 4, 0}, {-2, 4, 0} };
	
	int V2[8][3] = { {-2, -2, 2}, {-1, -2, 2}, {-1, -4, 2}, {-2, -4, 2}, {-2, -2, 0}, {-1, -2, 0}, {-1, -4, 0}, {-2, -4, 0} };
	
	int V3[8][3] = { {1, -2, 2}, {2, -2, 2}, {2, -4, 2}, {1, -4, 2}, {1, -2, 0}, {2, -2, 0}, {2, -4, 0}, {1, -4, 0} };

	int V4[8][3] = { {-1, -1, 1}, {1, -1, 1}, {1, 2, 1}, {-1, 2, 1}, {-1, -1, 0}, {1, -1, 0}, {1, 2, 0}, {-1, 2, 0} };

	float V5[8][3] = { {-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5}, {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5}, {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5}, {0.5, 0.5, -0.5}, {-0.5, 0.5, -0.5} };

	int F[6][4] = { {2, 3, 0, 1}, {2, 1, 5, 6}, {6, 5, 4, 7}, {7, 4, 0, 3}, {3, 2, 6, 7}, {0, 4, 5, 1} };

	float C[6][3] = { {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {0.5, 0.5, 0.5} };


	glNewList(1, GL_COMPILE);

	
	//fej
	
	glutSolidSphere(1, 60, 60);
	glTranslatef(0, -2, 0);
	
	//teste
	
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)
	{
		glColor3f(C[i][0], C[i][1], C[i][2]);
		glVertex3f(V[F[i][0]][0], V[F[i][0]][1], V[F[i][0]][2]);
		glVertex3f(V[F[i][1]][0], V[F[i][1]][1], V[F[i][1]][2]);
		glVertex3f(V[F[i][2]][0], V[F[i][2]][1], V[F[i][2]][2]);
		glVertex3f(V[F[i][3]][0], V[F[i][3]][1], V[F[i][3]][2]);
	}
	glEnd();

	//bal lab

	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)
	{
		glColor3f(C[i][0], C[i][1], C[i][2]);
		glVertex3f(V2[F[i][0]][0], V2[F[i][0]][1], V2[F[i][0]][2]);
		glVertex3f(V2[F[i][1]][0], V2[F[i][1]][1], V2[F[i][1]][2]);
		glVertex3f(V2[F[i][2]][0], V2[F[i][2]][1], V2[F[i][2]][2]);
		glVertex3f(V2[F[i][3]][0], V2[F[i][3]][1], V2[F[i][3]][2]);
	}
	glEnd();


	//jobb lab

	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)
	{
		glColor3f(C[i][0], C[i][1], C[i][2]);
		glVertex3f(V3[F[i][0]][0], V3[F[i][0]][1], V3[F[i][0]][2]);
		glVertex3f(V3[F[i][1]][0], V3[F[i][1]][1], V3[F[i][1]][2]);
		glVertex3f(V3[F[i][2]][0], V3[F[i][2]][1], V3[F[i][2]][2]);
		glVertex3f(V3[F[i][3]][0], V3[F[i][3]][1], V3[F[i][3]][2]);
	}
	glEnd();

	glTranslatef(0,0, 2);
	
	//taska
	
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)
	{
		glColor3f(C[i][0], C[i][1], C[i][2]);
		glVertex3f(V4[F[i][0]][0], V4[F[i][0]][1], V4[F[i][0]][2]);
		glVertex3f(V4[F[i][1]][0], V4[F[i][1]][1], V4[F[i][1]][2]);
		glVertex3f(V4[F[i][2]][0], V4[F[i][2]][1], V4[F[i][2]][2]);
		glVertex3f(V4[F[i][3]][0], V4[F[i][3]][1], V4[F[i][3]][2]);
	}
	glEnd();

	glTranslatef(0, 1, 0.7f);

	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)
	{
		glColor3f(C[i][1], C[i][0], C[i][2]);
		glVertex3f(V5[F[i][0]][0], V5[F[i][0]][1], V5[F[i][0]][2]);
		glVertex3f(V5[F[i][1]][0], V5[F[i][1]][1], V5[F[i][1]][2]);
		glVertex3f(V5[F[i][2]][0], V5[F[i][2]][1], V5[F[i][2]][2]);
		glVertex3f(V5[F[i][3]][0], V5[F[i][3]][1], V5[F[i][3]][2]);
	}
	glEnd();






	glEndList();

	glCallList(1);
}

void glutAlakzatok()
{		
    	glTranslatef(2,0,0);
		glPushMatrix();
			glColor3f(0,1,0);
			//glutSolidTeapot(2);
			glutSolidSphere(1.5,360,360);
			glTranslatef(-2,-3,0);
			glScalef(0.01,0.01,1);
			glDisable(GL_LIGHTING);
			StrokeText("Gomb");
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0,0,1);
			glTranslatef(4,-1.5,0);
			glPushMatrix();
				glRotatef(-90,1,0,0);
				glutSolidCone(1.5,3,20,20);
			glPopMatrix();
			glTranslatef(-1.2,-1.5,0);
			glScalef(0.01,0.01,1);
			glDisable(GL_LIGHTING);
			StrokeText("Kup");
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
			glColor3f(1,0,0);
			glTranslatef(-4,0,0);
			glutSolidCube(3);

			glTranslatef(-2,-3.0,0);
			glScalef(0.01,0.01,1);
			glDisable(GL_LIGHTING);
			StrokeText("Kocka");
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
			glColor3f(1,1,0);
			glTranslatef(-8,0,0);
				glutSolidTorus(0.5,1.5,20,20);

			glTranslatef(-1.5,-3.0,0);
			glScalef(0.01,0.01,1);
			glDisable(GL_LIGHTING);
			StrokeText("Torus");
			glEnable(GL_LIGHTING);
		glPopMatrix();
}

void glutAlakzatok2() {
int V[8][3] = { {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}, {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1} };


int F[6][4] = { {2, 3, 0, 1}, {2, 1, 5, 6}, {6, 5, 4, 7}, {7, 4, 0, 3}, {3, 2, 6, 7}, {0, 4, 5, 1} };

float C[6][3] = { {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {0.5, 0.5, 0.5} };


glNewList(1, GL_COMPILE);
glBegin(GL_QUADS);
for (int i = 0; i < 6; ++i)
{
	glColor3f(C[i][0], C[i][1], C[i][2]);
	glVertex3f(V[F[i][0]][0], V[F[i][0]][1], V[F[i][0]][2]);
	glVertex3f(V[F[i][1]][0], V[F[i][1]][1], V[F[i][1]][2]);
	glVertex3f(V[F[i][2]][0], V[F[i][2]][1], V[F[i][2]][2]);
	glVertex3f(V[F[i][3]][0], V[F[i][3]][1], V[F[i][3]][2]);
}
glEnd();
glEndList();

glCallList(1);
}

void keringoFeny()
{
	GLfloat	 lightPos[] = { -6.f, 0.0f, 0.0f, 1.0f };
	glPushMatrix();
		glRotatef(yRot2,0,1,0);
		glTranslatef(-6,0,0);
		glDisable(GL_LIGHTING);
		glColor3f(0.7,0.7,0.7);
		glutSolidSphere(0.2,10,10);
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glPopMatrix();
}

/*
 *	ablakfrissiteskor hivodik
 *  ujrarajzolja az ablakot
 */
void RenderScene(void)
{
	// torli a szin es melyseg buffert 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();// elmenti az aktualis transzformacios matrixot a matrix verembe
	glDisable(GL_LIGHTING);
	glColor3f(1,1,1);
	//BitmapText(-3,6,"Glut alakzatok");
	glEnable(GL_LIGHTING);
	glRotatef(yRot,0,1,0); // y tengely koruli forgatas yRot fokkal 
	glRotatef(xRot,1,0,0); // x tengely koruli forgatas xRot fokkal 
	keringoFeny();
	//glutAlakzatok();
	//glutAlakzatok2();
	karakter();
	//karakterSus();

	glPopMatrix();// visszatolti az aktualis transzformacios matrixot a matrix verembol
	glutSwapBuffers();// megcsereli a buffereket
}

void Timer9(int value)
{
	yRot2+=3;
	if(yRot2 > 356.0f)
		yRot2 = 0.0f;

	if(yRot2 < -1.0f)
		yRot2 = 355.0f;
	
	if (bSwtich) glutTimerFunc(50,Timer2,0);
	glutPostRedisplay();
}

/*
 *	billentyu leuteskor hivodik
 *  az xRot es yRot forgato valtozokat valtoztatja
 */
void SpecialKeys2(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;
	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	if(xRot > 356.0f)
		xRot = 0.0f;
	if(xRot < -1.0f)
		xRot = 355.0f;
	if(yRot > 356.0f)
		yRot = 0.0f;
	if(yRot < -1.0f)
		yRot = 355.0f;
	if (key==GLUT_KEY_F1)
	{
		bSwtich=~bSwtich;
		if (bSwtich)glutTimerFunc(50,Timer9,0);
	}
	glutPostRedisplay(); // frissiti a glut ablakot
}


void spinDisplay1(void)
{
    xRot += 5.0f;
	if(xRot > 356.0f)
		xRot = 0.0f;
	if(xRot < -1.0f)
		xRot = 355.0f;	
	glutPostRedisplay();
}

void spinDisplay2(void)
{
    yRot += 5.0f;
	if(yRot > 356.0f)
		yRot = 0.0f;
	if(yRot < -1.0f)
		yRot = 355.0f;	
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
            spinDisplay1();
			//glutIdleFunc(spinDisplay1);
		if (state == GLUT_UP)
			glutIdleFunc(NULL);
		break;
    case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay2);
		if (state == GLUT_UP)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

/*
 * ablakletrehozaskor es kepernyo atmeretezeskor hivodik	
 */

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat	 lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };

	// elkeruljuk a 0-val valo osztast
	if(h == 0)
		h = 1;

	// beallitja a Viewport-ot az ablak mereteire
    glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //atkapcsol projekcios matrix modba
	glLoadIdentity();// a transzformacios matrixot reseteli(ld. egyseg mtx)


	//beallitja az ortogonalis vetitest
	if (w <= h) 
    glOrtho (-9, 9, -9*h/w, 9*h/w, -10.0, 10.0);
    else 
    glOrtho (-9*w/h, 9*w/h, -9, 9, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW); // visszkapcsol model view modba
	glLoadIdentity(); // a transzformacios matrixot reseteli(ld. egyseg mtx)

	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
}

void SetupRC()
{
	GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST); // melyseg teszt vegzese (z-buffer)
	glShadeModel(GL_SMOOTH); // arnyekolasi mod 
	glDisable(GL_CULL_FACE);
	
	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	
	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// fekete (torlo) hattér szín
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv); //inicializalja a glut lib-et	
	glutInitWindowSize(300,300); //induló ablak méret
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //beallitja az ablakot dupla bufferelesre 
															  //rgb modba es melyseg buffer hasznalatara (z-buffer)
	glutCreateWindow("3D GLUT alakzatok"); // letrehozza az ablakot a megadott nevvel
	glutReshapeFunc(ChangeSize);  // beallitja az atmeretezo fuggvenyt
	glutSpecialFunc(SpecialKeys); // beallitja az billentyuzet kezelo fuggvenyt 
	//glutSpecialFunc(SpecialKeys2); // beallitja az billentyuzet kezelo fuggvenyt 
	glutDisplayFunc(RenderScene); // beallitja a jelenet rajzolo fuggvenyt
	glutMouseFunc(mouse);
	SetupRC();					  // inicializalja az openglt
	glutMainLoop(); // a glut elkezdi ismetelni a fo ciklusat
	return 0;
}

