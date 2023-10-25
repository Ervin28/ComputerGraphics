// Open3D.cpp : Defines the entry point for the console application.
//


#include "glut.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

float xRot = 0.0f;
float yRot = 0.0f;
float yRot2 = 0.0f;
float r = 5.0f;
GLboolean bSwtich = 0;

void gluAlakzatok()
{
    // henger es korong
	float r = 0.9;
	float h = 6;
  	glColor3f(0, 1, 0);
	GLUquadricObj* henger;
  	henger = gluNewQuadric();
  	glPushMatrix();
  	glRotatef(180,0,1,0);
  	gluDisk(henger,0,r,20,20);
  	glPopMatrix();
  	glPushMatrix();
  	glTranslatef(0,0,h);
	gluDisk(henger,0,r,20,20);
  	glPopMatrix(); 
	gluCylinder(henger,r,r,h,20,20);
  	gluDeleteQuadric(henger);

	// gomb
	glColor3f(1, 0, 0);
	glPushMatrix();
    GLUquadricObj* gomb;
    gomb=gluNewQuadric();
	glTranslatef(-3,0,0);
    gluSphere(gomb, 2, 20, 20);
    gluDeleteQuadric(gomb);
	glPopMatrix();
	
	// korong szelet
  	glColor3f(0, 0, 1);
	GLUquadricObj* szelet;
  	szelet = gluNewQuadric();
  	glPushMatrix();
  	glRotatef(180,0,1,0);
	glTranslatef(-5, 0, 0);
  	gluPartialDisk(szelet,1,3,20,20, 60, 120);
    gluDeleteQuadric(szelet); 
  	glPopMatrix();
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
	glEnable(GL_LIGHTING);
	glRotatef(yRot,0,1,0); // y tengely koruli forgatas yRot fokkal 
	glRotatef(xRot,1,0,0); // x tengely koruli forgatas xRot fokkal 
	keringoFeny();
	gluAlakzatok();
	glPopMatrix();// visszatolti az aktualis transzformacios matrixot a matrix verembol
	glutSwapBuffers();// megcsereli a buffereket
}

void Timer(int value)
{
	yRot2+=3;
	if(yRot2 > 356.0f)
		yRot2 = 0.0f;

	if(yRot2 < -1.0f)
		yRot2 = 355.0f;
	
	if (bSwtich) glutTimerFunc(50,Timer,0);
	glutPostRedisplay();
}

/*
 *	billentyu leuteskor hivodik
 *  az xRot es yRot forgato valtozokat valtoztatja
 */
void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;
	if(key == GLUT_KEY_DOWN)
	{
		xRot += 5.0f;

	}
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
		bSwtich=!bSwtich;
		if (bSwtich)glutTimerFunc(50,Timer,0);
	}
	glutPostRedisplay(); // frissiti a glut ablakot
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
	glutCreateWindow("3D GLU alakzatok"); // letrehozza az ablakot a megadott nevvel
	glutReshapeFunc(ChangeSize);  // beallitja az atmeretezo fuggvenyt
	glutSpecialFunc(SpecialKeys); // beallitja az billentyuzet kezelo fuggvenyt 
	glutDisplayFunc(RenderScene); // beallitja a jelenet rajzolo fuggvenyt
	SetupRC();					  // inicializalja az openglt
	glutMainLoop(); // a glut elkezdi ismetelni a fo ciklusat
	return 0;
}

