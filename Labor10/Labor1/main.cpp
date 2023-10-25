#include <time.h>
#include <cmath>
#include <windows.h>
#include "glut.h"
#include "RgbImage.h"

#ifndef _FILE_DEFINED
#define _FILE_DEFINED
typedef struct _iobuf
{
	void* _Placeholder;
} FILE;
#endif



static GLuint textureName[1];
float hatar = 80;
float X = 0, Y = 0;
const int MAX_RESZECSKEK = 10000;
const int MIN_RESZECSKEK = 10;
int AktReszecske = 8000;
float pozX[MAX_RESZECSKEK], pozY[MAX_RESZECSKEK], szinR[MAX_RESZECSKEK], szinG[MAX_RESZECSKEK], szinB[MAX_RESZECSKEK];

void ReszecskeMozgatas(int reszecskek)
{
	srand(time(NULL));
	float ujX;
	//Sleep(1);
	//glColor3d(2, .5, 0);
	for (int i = 0; i < reszecskek; ++i)
	{
		ujX = rand() % 2 + 1;
		szinR[i] = 1.0;
		szinG[i] = 1.0;
		szinB[i] = 1.0;
		if (ujX == 1 && pozX[i] <= hatar)
		{
			int temp1 = rand() % 100 + 3;
			int temp2 = rand() % 15 + 1.5;
			pozX[i] += temp2 * .0003;
			pozY[i] += temp1 * .00008;
		}

		if (ujX == 2 && pozX[i] >= -hatar)
		{
			int temp2 = rand() % 15 + 1.5;
			int temp1 = rand() % 100 + 3;
			pozX[i] -= temp2 * .0003;
			pozY[i] += temp1 * .00008;
		}
		if (pozY[i] > 0.5)
		{
			szinG[i] = 0.3;
			szinB[i] = 0;
		}
		if (pozY[i] > 0.8)
		{
			szinG[i] = 0.3;
			szinR[i] = 0.7;
		}
		if (pozY[i] > 1)
		{
			szinG[i] = 0.05;
			szinR[i] = 0.1;
		}
		if (pozY[i] >= 1.1)
		{
			szinG[i] = 0;
			szinR[i] = 0;
		}

		if ((pozX[i] >= 0.7 || pozX[i] <= -0.7))
		{
			szinG[i] = 0.005;
			szinR[i] = 0.005;
		}
	}
}

void Reshape(int height, int width)
{
	glViewport(0, 0, width, height);
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)height / (float)width, 1, 100);
	glMatrixMode(GL_MODELVIEW);

}

void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	float R, G, B;
	glPushMatrix();
	glTranslated(0, -0.2, 0);
	glBindTexture(GL_TEXTURE_2D, textureName[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);

	for (int i = 0; i < MAX_RESZECSKEK; ++i)
	{
		R = rand() % 100 + 1;
		G = rand() % 100 + 1;
		B = rand() % 100 + 1;
		glColor3f(szinR[i], szinG[i], szinB[i]);
		glTexCoord3f(0.0, 0.0, 0.1); glVertex3f(X - .009, Y - .009, -2);
		glTexCoord3f(1.0, 0.0, 0.1); glVertex3f(X + .009, Y - .009, -2);
		glTexCoord3f(1.0, 1.0, 0.1); glVertex3f(X + .009, Y + .009, -2);
		glTexCoord3f(0.0, 1.0, 0.1); glVertex3f(X - .009, Y + .009, -2);
		X = pozX[i];
		Y = -0.9 + pozY[i];
	}
	glEnd();
	glPopMatrix();
	//Sleep(.5);
	ReszecskeMozgatas(AktReszecske);

	if (AktReszecske != MAX_RESZECSKEK) ++AktReszecske;
	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
}


void SetupRC()
{
	GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_CULL_FACE);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	}
}


/*
 * Read a texture map from a BMP bitmap file.
 */
void loadTextureFromFile(const char* filename)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap(filename);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,
		theTexMap.GetNumCols(), theTexMap.GetNumRows(),
		GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());

}
void initFour(const char* filenames[2])
{
	glGenTextures(2, textureName);
	for (int i = 0; i < 2; i++) {
		glBindTexture(GL_TEXTURE_2D, textureName[i]);
		loadTextureFromFile(filenames[i]);
	}
}

const char* filenameArray[2] = {
		"explosion.bmp",
		"smoke.bmp"
};

void init()
{
	const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
	const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat high_shininess[] = { 100.0f };
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Reszecskek");
	init();
	initFour(filenameArray);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Keyboard);
	SetupRC();
	glutMainLoop();
	return 0;
}