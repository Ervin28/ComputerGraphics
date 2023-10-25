#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "RgbImage.h"

#ifdef __APPLE__
#  include "GLUT/glut.h"
#else
#  include "glut.h"
#endif

#define PI 3.14159265

using namespace std;

//*************************************************PROJECT NR.1: ANIMATED CHARACTER*************************************************

/*

// Globals.
static float highlightColor[3] = { 0.0, 0.0, 0.0 }; // Emphasize color.
static float lowlightColor[3] = { 0.7, 0.7, 0.7 }; // De-emphasize color.
static float partSelectColor[3] = { 1.0, 0.0, 0.0 }; // Selection indicate color.
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.
static int animateMode = 0; // In animation mode?
static int animationPeriod = 33.33; // Time interval between frames.
static ofstream outFile; // File to write configurations data.
static ifstream inFile; // File to read configurations data.

// Camera class.
class Camera
{
public:
	Camera();
	void incrementViewDirection();
	void decrementViewDirection();
	void incrementZoomDistance() { zoomDistance += 1.0; }
	void decrementZoomDistance() { zoomDistance -= 1.0; }

	float getViewDirection() const { return viewDirection; }
	float getZoomDistance() const { return zoomDistance; }

private:
	float viewDirection;
	float zoomDistance;
};

// Global camera.
Camera camera;

// Camera constructor.
Camera::Camera()
{
	viewDirection = 0.0;
	zoomDistance = 30.0;
}

// Function to increment camera viewing angle.
void Camera::incrementViewDirection()
{
	viewDirection += 5.0;
	if (viewDirection > 360.0) viewDirection -= 360.0;
}

// Function to decrement camera viewing angle.
void Camera::decrementViewDirection()
{
	viewDirection -= 5.0;
	if (viewDirection < 0.0) viewDirection += 360.0;
}

// Man class.
class Man
{
public:
	Man();
	void incrementSelectedPart();

	void incrementPartAngle();
	void decrementPartAngle();
	void setPartAngle(float angle) { partAngles[selectedPart] = angle; }

	void incrementUpMove() { upMove += 0.1; }
	void decrementUpMove() { upMove -= 0.1; }
	void setUpMove(float move) { upMove = move; }

	void incrementForwardMove() { forwardMove += 0.1; }
	void decrementForwardMove() { forwardMove -= 0.1; }
	void setForwardMove(float move) { forwardMove = move; }

	void setHighlight(int inputHighlight) { highlight = inputHighlight; }

	void draw();
	void outputData();
	void writeData();

private:
	// Man configuration values. 
	float partAngles[9]; // Angles from 0 to 360 of 9 body parts - torso, left and right
	// upper arms, left and right lower arms, left and right upper
	// legs, left and right lower legs. 
	// All parts move parallel to the same plane.

	float upMove, forwardMove; // Up and forward translation components - both lie
	// on the plane parallel to which parts rotate -
	// therefore all translations and part rotations
	// are along one fixed plane.

	int selectedPart; // Selected part number - this part can be interactively rotated
	// in the develop mode.

	int highlight; // If man is currently selected.
};

// Global vector of man configurations.
vector<Man> manVector;

// Global iterators to traverse manVector.
vector<Man>::iterator manVectorIterator;
vector<Man>::iterator manVectorAnimationIterator;

// Man constructor.
Man::Man()
{
	for (int i = 0; i < 9; i++) partAngles[i] = 0.0;
	upMove = 0.0;
	forwardMove = 0.0;
	selectedPart = 0;
	highlight = 1;
}

// Function to incremented selected part..
void Man::incrementSelectedPart()
{
	if (selectedPart < 8) selectedPart++;
	else selectedPart = 0;
}

// Function to draw man.
void Man::draw()
{
	if (highlight || animateMode) glColor3fv(highlightColor);
	else glColor3fv(lowlightColor);

	glPushMatrix();

	// Up and forward translations.
	glTranslatef(0.0, upMove, forwardMove);

	// Torso begin.
	if (highlight && !animateMode) if (selectedPart == 0) glColor3fv(partSelectColor);

	glRotatef(partAngles[0], 1.0, 0.0, 0.0);

	glPushMatrix();
	glScalef(4.0, 16.0, 4.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Torso end.

	// Head begin.
	glPushMatrix();

	glTranslatef(0.0, 11.5, 0.0);
	glPushMatrix();
	glScalef(2.0, 3.0, 2.0);
	glutWireSphere(1.0, 10, 8);
	glPopMatrix();

	glPopMatrix();
	// Head end.

	// Left upper and lower arm begin.
	glPushMatrix();

	// Left upper arm begin.
	if (highlight && !animateMode) if (selectedPart == 1) glColor3fv(partSelectColor);
	glTranslatef(3.0, 8.0, 0.0);
	glRotatef(180.0 + partAngles[1], 1.0, 0.0, 0.0);
	glTranslatef(0.0, 4.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Left upper arm end.

	// Left lower arm begin.
	if (highlight && !animateMode) if (selectedPart == 2) glColor3fv(partSelectColor);
	glTranslatef(0.0, 4.0, 0.0);
	glRotatef(partAngles[2], 1.0, 0.0, 0.0);
	glTranslatef(0.0, 4.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Left lower arm end.

	glPopMatrix();
	// Left upper and lower arm end.

	// Right upper and lower arm begin.
	glPushMatrix();

	// Right upper arm begin.
	if (highlight && !animateMode) if (selectedPart == 3) glColor3fv(partSelectColor);
	glTranslatef(-3.0, 8.0, 0.0);
	glRotatef(180.0 + partAngles[3], 1.0, 0.0, 0.0);
	glTranslatef(0.0, 4.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Right upper arm end. 

	// Right lower arm begin.
	if (highlight && !animateMode) if (selectedPart == 4) glColor3fv(partSelectColor);
	glTranslatef(0.0, 4.0, 0.0);
	glRotatef(partAngles[4], 1.0, 0.0, 0.0);
	glTranslatef(0.0, 4.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Right lower arm end.

	glPopMatrix();
	// Right upper and lower arm end.

	// Left upper and lower leg with foot begin.
	glPushMatrix();

	// Left upper leg begin.
	if (highlight && !animateMode) if (selectedPart == 5) glColor3fv(partSelectColor);
	glTranslatef(1.5, -8.0, 0.0);
	glRotatef(partAngles[5], 1.0, 0.0, 0.0);
	glTranslatef(0.0, -4.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Left upper leg end.

	// Left lower leg with foot begin.
	if (highlight && !animateMode) if (selectedPart == 6) glColor3fv(partSelectColor);
	glTranslatef(0.0, -4.0, 0.0);
	glRotatef(partAngles[6], 1.0, 0.0, 0.0);
	glTranslatef(0.0, -4.0, 0.0);

	// Lower leg.
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();

	// Foot.
	glTranslatef(0.0, -5.0, 0.5);
	glPushMatrix();
	glScalef(2.0, 1.0, 3.0);
	glutWireCube(1.0);
	glPopMatrix();

	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Left lower leg with foot end.

	glPopMatrix();
	// Left upper and lower leg with foot end.

	// Right upper and lower leg with foot begin.
	glPushMatrix();

	// Right upper leg begin.
	if (highlight && !animateMode) if (selectedPart == 7) glColor3fv(partSelectColor);
	glTranslatef(-1.5, -8.0, 0.0);
	glRotatef(partAngles[7], 1.0, 0.0, 0.0);
	glTranslatef(0.0, -4.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();
	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Right upper leg end.

	// Right lower leg with foot begin.
	if (highlight && !animateMode) if (selectedPart == 8) glColor3fv(partSelectColor);
	glTranslatef(0.0, -4.0, 0.0);
	glRotatef(partAngles[8], 1.0, 0.0, 0.0);
	glTranslatef(0.0, -4.0, 0.0);

	// Lower leg.
	glPushMatrix();
	glScalef(2.0, 8.0, 2.0);
	glutWireCube(1.0);
	glPopMatrix();

	// Foot.
	glTranslatef(0.0, -5.0, 0.5);
	glPushMatrix();
	glScalef(2.0, 1.0, 3.0);
	glutWireCube(1.0);
	glPopMatrix();

	if (highlight && !animateMode) glColor3fv(highlightColor);
	// Right lower leg with foot end.

	glPopMatrix();
	// Right upper and lower leg with foot end.

	glPopMatrix();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	// Place camera.
	gluLookAt(camera.getZoomDistance() * sin(camera.getViewDirection() * PI / 180.0), 0.0,
		camera.getZoomDistance() * cos(camera.getViewDirection() * PI / 180.0), 0.0,
		0.0, 0.0, 0.0, 1.0, 0.0);

	// Move man right 10 units because of data text on left of screen.
	glTranslatef(10.0, 0.0, 0.0);
	manVectorAnimationIterator->draw();

	// Other (fixed) objects in scene are drawn below starting here.

	// Black floor.
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (float z = -25.0; z < 100.0; z += 5.0)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (float x = -50.0; x < 50.0; x += 5.0)
		{
			glVertex3f(x, -25.0, z);
			glVertex3f(x, -25.0, z + 5.0);
		}
		glEnd();
	}

	// Green sphere.
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0.0, -20.0, 10.0);
	glPushMatrix();
	glScalef(5.0, 5.0, 5.0);
	glutWireSphere(1.0, 10, 8);
	glPopMatrix();

	glutSwapBuffers();
}

// Timer function.
void animate(int value)
{
	if (animateMode)
	{
		manVectorAnimationIterator++;
		if (manVectorAnimationIterator == manVector.end())
			manVectorAnimationIterator = manVector.begin();
	}
	glutTimerFunc(animationPeriod, animate, 1);
	glutPostRedisplay();
}

// Function to read configurations from file.
void inputConfigurations(void)
{
	float readValue;
	int i;
	Man newMan;

	inFile.open("animateManDataIn.txt");

	while (!inFile.eof())
	{
		newMan = Man();
		for (i = 0; i < 9; i++)
		{
			inFile >> readValue;
			newMan.setPartAngle(readValue);
			newMan.incrementSelectedPart();
		}
		inFile >> readValue;
		newMan.setUpMove(readValue);
		inFile >> readValue;
		newMan.setForwardMove(readValue);
		manVector.push_back(Man(newMan));
	}
	manVector.pop_back(); // Remove configuration at the back because the routine
	// read eol after the last configuration and before eof and
	// creates a fake configuration.
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	inputConfigurations(); // Read configurations from file.

	// Initialize global iterators for manVector.
	manVectorIterator = manVector.begin();
	manVectorAnimationIterator = manVector.begin();

	// Initialize camera.
	camera = Camera();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'a': // Toggle between animate mode on and off..
		if (animateMode == 0)
		{
			manVectorAnimationIterator = manVector.begin();
			animateMode = 1;
		}
		else animateMode = 0;
		glutPostRedisplay();
		break;
	case 'r': // Rotate camera.
		camera.incrementViewDirection();
		glutPostRedisplay();
		break;
	case 'R': // Rotate camera.
		camera.decrementViewDirection();
		glutPostRedisplay();
		break;
	case 'z': // Zoom in.
		camera.decrementZoomDistance();
		glutPostRedisplay();
		break;
	case 'Z': // Zoom out.
		camera.incrementZoomDistance();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_DOWN) animationPeriod += 10;
	if (key == GLUT_KEY_UP) if (animationPeriod > 10) animationPeriod -= 10;
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	cout << "Interaction:" << endl;
	cout << "Press a to toggle between animation on/off." << endl
		<< "Press the up/down arrow keys to speed up/slow down animation." << endl
		<< "Press r/R to rotate the viewpoint." << endl
		<< "Press z/Z to zoom in/out." << endl;
}

// Main routine.
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("animateMan2.cpp");
	setup();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
	glutTimerFunc(5, animate, 1);
	glutMainLoop();

	return 0;
}

*/



//*************************************************PROJECT NR.2: FIRE SIMULATION USING PARTICLE SYSTEMS*************************************************
//3 q w e q w

/*

#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <conio.h>

#include "Particles.h"

using namespace std;

GLfloat zoom;
GLfloat zoomSize = -80;

System particleSystem;

GLfloat particleSize = 0.5;

GLint shapeChoise = 0;  // 0 is quad, 1 is triangle. and 2 is sphere and ...

void DrawParticles(void)
{
	int i;

	for (i = 1; i < particleSystem.getNumOfParticles(); i++)
	{
		glPushMatrix();

		// set color and fade value (alpha) of current particle
		glColor4f(particleSystem.getR(i), particleSystem.getG(i), particleSystem.getB(i), particleSystem.getAlpha(i));

		// move the current particle to its new position
		glTranslatef(particleSystem.getXPos(i), particleSystem.getYPos(i), particleSystem.getZPos(i) + zoom);

		// rotate the particle (this is proof of concept for when proper smoke texture is added)
		glRotatef(particleSystem.getDirection(i) - 90, 0, 0, 1);

		// scale the wurrent particle (only used for smoke)
		glScalef(particleSystem.getScale(i), particleSystem.getScale(i), particleSystem.getScale(i));

		if (shapeChoise == 0)  // Q key
		{
			glBegin(GL_QUADS);

			glVertex3f(-particleSize, -particleSize, 0);
			glVertex3f(particleSize, -particleSize, 0);
			glVertex3f(particleSize, particleSize, 0);
			glVertex3f(-particleSize, particleSize, 0);

			glEnd();
		}

		else if (shapeChoise == 1)  // T key
		{
			glBegin(GL_TRIANGLES);
			glVertex3f(-particleSize, -particleSize, 0);
			glVertex3f(particleSize, -particleSize, 0);
			glVertex3f(particleSize, particleSize, 0);
		}

		else if (shapeChoise == 2) // S key
		{
			glutWireSphere(particleSize, 50, 50);
		}

		else if (shapeChoise == 3)   //W key
		{
			glutWireTorus(4, particleSize, 14, 9); // inner r 4, //outer r particleSize, //slices 14, // rings  9)
		}

		else if (shapeChoise == 4)  // E key
		{
			glutWireTetrahedron();
		}

		else if (shapeChoise == 5) // C key
		{
			glutWireCube(particleSize);
		}

		else if (shapeChoise == 6)  // R key
		{
			glutWireTeapot(particleSize);
		}


		glEnd();
		glEnable(GL_DEPTH_TEST);
		glPopMatrix();
	}
}

void display(void)
{
	glClearDepth(1);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, -10);
	particleSystem.updateParticles();
	DrawParticles();
	glutSwapBuffers();
}

void init(void)
{
	glEnable(GL_DEPTH_TEST);
	zoom = -80.0; // we use zoom out to see the particles movements
	particleSystem.setSystemType(1);
	particleSystem.createParticles();
}

void opacityInit()   // opacity changing rendering
{
	glEnable(GL_BLEND);
	zoom = -80.0; // we use zoom out to see the particles movements
	particleSystem.setSystemType(1);
	particleSystem.createParticles();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutSwapBuffers();
	glLoadIdentity();
}

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 51: //3 key: fire
		cout << "Starting the Fire particles program!!" << endl << endl;
		zoom = -40.0;
		particleSystem.setSystemType(3);
		particleSystem.createParticles();
		break;

	case 52: //4 key: fireWithSmoke
		cout << "Starting the Fire particles program!!" << endl << endl;
		zoom = -40.0;
		particleSystem.setSystemType(4);
		particleSystem.createParticles();
		break;

	case 61: //+ key: change x pull for more wind to right
		cout << "Increasing the wind to the right sides of the particles.." << endl << endl;
		particleSystem.modifySystemPull(0.0005, 0.0, 0.0);
		break;

	case 45: //- key: change x pull for wind wind to left
		cout << "Increasing the wind to the left sides of the particles.." << endl << endl;
		particleSystem.modifySystemPull(-0.0005, 0.0, 0.0);
		break;

	case 104: 
		cout << "Increasing the particle sizes.." << endl << endl;
		particleSize += 0.08;
		break;

	case 72: 
		cout << "Increasing the particle sizes.." << endl << endl;
		particleSize += 0.08;
		break;

	case 108: 
		cout << "Decreasing the particle sizes.." << endl << endl;
		particleSize -= 0.08;
		break;

	case 76: 
		cout << "Decreasing the particle sizes.." << endl << endl;
		particleSize -= 0.08;
		break;

	case 113: 
		cout << "Choosing the Quad particles.." << endl << endl;
		shapeChoise = 0;
		break;

	case 81: 
		cout << "Choosing the Quad particles.." << endl << endl;
		shapeChoise = 0;
		break;


	case 84: 
		cout << "Choosing the Triangle particles.." << endl << endl;
		shapeChoise = 1;
		break;

	case 116: 
		cout << "Choosing the Triangle particles.." << endl << endl;
		shapeChoise = 1;
		break;

	case 115: 
		cout << "Choosing the Sphere particles.." << endl << endl;
		shapeChoise = 2;
		break;

	case 83: 
		cout << "Choosing the Sphere particles.." << endl << endl;
		shapeChoise = 2;
		break;

	case 119: 
		cout << "Choosing the Torus particles.." << endl << endl;
		shapeChoise = 3;
		break;

	case 101:  
		cout << "Choosing the Tetrahedran particles.." << endl << endl;
		shapeChoise = 4;
		break;


	case 99: 
		cout << "Choosing the Cube particles.." << endl << endl;
		shapeChoise = 5;
		break;

	case 27: //Escape key
		cout << "Exiting.." << endl << endl;
		exit(0);
		delete particles;  // For releasing the Memory that used by particles.

	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);   
	zoom = zoomSize;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Particle System");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	opacityInit();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	// Keyboard Functions
	glutKeyboardFunc(handleKeypress);
	glutMouseFunc(OnMouseClick);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}

*/

//*************************************************PROJECT NR.3: USE TEXTURES*************************************************



static GLuint textureName[16];
float xRot = 0.0f;
float yRot = 0.0f;
float yRot2 = 0.0f;
float r = 5.0f;


//  Read a texture map from a BMP bitmap file.
 
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


//  Load the four textures, by repeatedly called loadTextureFromFile().
 
void initFour(const char* filenames[])
{
	glGenTextures(16, textureName);
	for (int i = 0; i <= 15; i++) {
		glBindTexture(GL_TEXTURE_2D, textureName[i]);
		loadTextureFromFile(filenames[i]);
	}
}


// Display the i-th texture.
 
void drawTextureQuad(int i) {
	glBindTexture(GL_TEXTURE_2D, textureName[i]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
	glEnd();
}


 // Draw the four textures in the OpenGL graphics window

void drawScene2(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();
	glTranslatef(-1.1f, 1.1f, 0.0f);
	drawTextureQuad(0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.1f, 1.1f, 0.0f);
	drawTextureQuad(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.1f, -1.1f, 0.0f);
	drawTextureQuad(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.1f, -1.1f, 0.0f);
	drawTextureQuad(3);
	glPopMatrix();

	glFlush();
	glDisable(GL_TEXTURE_2D);
}
void kocka() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glRotatef(yRot, 0, 1, 0);
	glRotatef(xRot, 1, 0, 0);

	glBindTexture(GL_TEXTURE_2D, textureName[0]);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);       // P1
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);       // P2
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, -0.5);       // P3
	glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, -0.5);       // P4

	glEnd();

	// White side - BACK
	glBindTexture(GL_TEXTURE_2D, textureName[1]);
	glBegin(GL_POLYGON);
	//glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// Purple side - RIGHT
	glBindTexture(GL_TEXTURE_2D, textureName[2]);
	glBegin(GL_POLYGON);
	//glColor3f(1.0, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// Green side - LEFT
	glBindTexture(GL_TEXTURE_2D, textureName[3]);
	glBegin(GL_POLYGON);
	//glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// Blue side - TOP
	glBindTexture(GL_TEXTURE_2D, textureName[4]);
	glBegin(GL_POLYGON);
	//glColor3f(0.0, 0.0, 1.0);

	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// Red side - BOTTOM
	glBindTexture(GL_TEXTURE_2D, textureName[5]);
	glBegin(GL_POLYGON);
	//glColor3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glFlush();
	glutSwapBuffers();
}



void foundation() {
	float width = 10.0f;
	float height = 0.2f;
	float depth = 5.0f;
	float V[8][3] = { {-width, -height, depth}, {width, -height, depth}, {width, height, depth}, {-width, height, depth}, {-width, -height, -depth}, {width, -height, -depth}, {width, height, -depth}, {-width, height, -depth} };
	int F[6][4] = { {1, 2, 3, 0}, {5, 6, 2, 1}, {4, 7, 6, 5}, {0, 3, 7, 4}, {6, 7, 3, 2}, {5, 1, 0, 4} };
	glNewList(1, GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D, textureName[1]);
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)
	{
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(V[F[i][0]][0], V[F[i][0]][1], V[F[i][0]][2]);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(V[F[i][1]][0], V[F[i][1]][1], V[F[i][1]][2]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(V[F[i][2]][0], V[F[i][2]][1], V[F[i][2]][2]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(V[F[i][3]][0], V[F[i][3]][1], V[F[i][3]][2]);
	}
	glEnd();
	glEndList();
	glCallList(1);

}

void house()
{
	glPushMatrix();

	glTranslatef(6, 1.5f, 2.5f);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureName[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glBegin(GL_QUADS);  // Wall
	glTexCoord3f(0.0, 2.0, 0.1);  glVertex3f(-2, 0, 1);
	glTexCoord3f(4.0, 2.0, 0.1);  glVertex3f(2, 0, 1);
	glTexCoord3f(4.0, 0.0, 0.1);  glVertex3f(2, -1.5, 1);
	glTexCoord3f(0.0, 0.0, 0.1);  glVertex3f(-2, -1.5, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureName[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);  // Roof
	glTexCoord3f(0.0, 2.0, 0); glVertex3f(-2.2, 0.5, 0);
	glTexCoord3f(4.0, 2.0, 0); glVertex3f(2.2, 0.5, 0);
	glTexCoord3f(4.0, 0.0, 1.25); glVertex3f(2.2, -0.1, 1.25);
	glTexCoord3f(0.0, 0.0, 1.25); glVertex3f(-2.2, -0.1, 1.25);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureName[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);  // Door
	glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(-0.3, -0.4, 1.0001);
	glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(0.3, -0.4, 1.0001);
	glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(0.3, -1.5, 1.0001);
	glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(-0.3, -1.5, 1.0001);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureName[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);  // Window Left
	glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(-1.5, -0.3, 1.0001);
	glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(-0.75, -0.3, 1.0001);
	glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(-0.75, -0.8, 1.0001);
	glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(-1.5, -0.8, 1.0001);
	glEnd();

	glBegin(GL_QUADS);  // Window Right
	glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(1.5, -0.3, 1.0001);
	glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(0.75, -0.3, 1.0001);
	glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(0.75, -0.8, 1.0001);
	glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(1.5, -0.8, 1.0001);
	glEnd();
	glPopMatrix();

	// Back side
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureName[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glBegin(GL_QUADS);  // Wall
	glTexCoord3f(0.0, 2.0, -1);  glVertex3f(-2, 0, -1);
	glTexCoord3f(4.0, 2.0, -1);  glVertex3f(2, 0, -1);
	glTexCoord3f(4.0, 0.0, -1);  glVertex3f(2, -1.5, -1);
	glTexCoord3f(0.0, 0.0, -1);  glVertex3f(-2, -1.5, -1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureName[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);  // Roof
	glTexCoord3f(0.0, 2.0, 0); glVertex3f(-2.2, 0.5, 0);
	glTexCoord3f(4.0, 2.0, 0); glVertex3f(2.2, 0.5, 0);
	glTexCoord3f(4.0, 0.0, -1.25); glVertex3f(2.2, -0.1, -1.25);
	glTexCoord3f(0.0, 0.0, -1.25); glVertex3f(-2.2, -0.1, -1.25);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureName[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);  // Window Left
	glTexCoord3f(0.0, 1.0, -1.0001); glVertex3f(-1.5, -0.3, -1.0001);
	glTexCoord3f(1.0, 1.0, -1.0001); glVertex3f(-0.75, -0.3, -1.0001);
	glTexCoord3f(1.0, 0.0, -1.0001); glVertex3f(-0.75, -0.8, -1.0001);
	glTexCoord3f(0.0, 0.0, -1.0001); glVertex3f(-1.5, -0.8, -1.0001);
	glEnd();

	glBegin(GL_QUADS);  // Window Right
	glTexCoord3f(0.0, 1.0, 1.0001); glVertex3f(1.5, -0.3, -1.0001);
	glTexCoord3f(1.0, 1.0, 1.0001); glVertex3f(0.75, -0.3, -1.0001);
	glTexCoord3f(1.0, 0.0, 1.0001); glVertex3f(0.75, -0.8, -1.0001);
	glTexCoord3f(0.0, 0.0, 1.0001); glVertex3f(1.5, -0.8, -1.0001);
	glEnd();
	glPopMatrix();

	// Right side
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureName[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glBegin(GL_QUADS);  // Wall
	glTexCoord3f(0.0, 2.0, 1); glVertex3f(2, 0, 1);
	glTexCoord3f(2.0, 2.0, -1); glVertex3f(2, 0, -1);
	glTexCoord3f(2.0, 0.0, -1); glVertex3f(2, -1.5, -1);
	glTexCoord3f(0.0, 0.0, 1); glVertex3f(2, -1.5, 1);
	glEnd();

	glBegin(GL_TRIANGLES);  // Wall Upper
	glTexCoord3f(0.0, 1.0, 0); glVertex3f(2, 0.5, 0);
	glTexCoord3f(1.0, 0.0, 1); glVertex3f(2, 0, 1);
	glTexCoord3f(-1.0, 0.0, -1); glVertex3f(2, 0, -1);
	glEnd();
	glPopMatrix();

	// Left side
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureName[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glBegin(GL_QUADS);  // Wall
	glTexCoord3f(0.0, 2.0, 1);    glVertex3f(-2, 0, 1);
	glTexCoord3f(2.0, 2.0, -1);    glVertex3f(-2, 0, -1);
	glTexCoord3f(2.0, 0.0, -1);    glVertex3f(-2, -1.5, -1);
	glTexCoord3f(0.0, 0.0, 1);    glVertex3f(-2, -1.5, 1);
	glEnd();

	glBegin(GL_TRIANGLES);  // Wall Upper
	glTexCoord3f(0.0, 1.0, 0);    glVertex3f(-2, 0.5, 0);
	glTexCoord3f(1.0, 0.0, 1);    glVertex3f(-2, 0, 1);
	glTexCoord3f(-1.0, 0.0, -1);    glVertex3f(-2, 0, -1);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void sun() {
	glPushMatrix();

	glTranslatef(-9, 7, 0);

	GLUquadricObj* sphere;
	sphere = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, textureName[6]);
	gluQuadricOrientation(sphere, GLU_OUTSIDE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricTexture(sphere, GL_TRUE);
	gluSphere(sphere, 1, 20, 20);
	gluDeleteQuadric(sphere);

	glPopMatrix();
}

void sky() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureName[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(0, 4, -5);

	glBegin(GL_QUADS);
	glTexCoord3f(0.1, 1.0, 0.1);  glVertex3f(-10, 4, 0);
	glTexCoord3f(1.0, 1.0, 0.1);  glVertex3f(10, 4, 0);
	glTexCoord3f(1.0, 0.0, 0.1);  glVertex3f(10, -4, 0);
	glTexCoord3f(0.1, 0.0, 0.1);  glVertex3f(-10, -4, 0);
	glEnd();
	glPopMatrix();
}

void lake() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureName[8]);
	//const double PI = 3.14159;


	double i, resolution = 0.1;
	double height = 1;
	double radius = 2.5;

	glPushMatrix();
	glTranslatef(-7, -0.75f, -1.5f);

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(0, height, 0);
	for (i = 2 * PI; i >= 0; i -= resolution)

	{
		glTexCoord2f(0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f);
		glVertex3f(radius * cos(i), height, radius * sin(i));
	}

	glTexCoord2f(0.5, 0.5);
	glVertex3f(radius, height, 0);
	glEnd();

	glPopMatrix();
}

void bamboo() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureName[9]);
	//const double PI = 3.14159;


	double i, resolution = 0.1;
	double height = 1.5f;
	double radius = 0.1;

	glPushMatrix();
	glTranslatef(-9.6f, 0, -1.5f);

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(0, height, 0);
	for (i = 2 * PI; i >= 0; i -= resolution)

	{
		glTexCoord2f(0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f);
		glVertex3f(radius * cos(i), height, radius * sin(i));
	}

	glTexCoord2f(0.5, 0.5);
	glVertex3f(radius, height, 0);
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(0, 0, 0);
	for (i = 0; i <= 2 * PI; i += resolution)
	{
		glTexCoord2f(0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f);
		glVertex3f(radius * cos(i), 0, radius * sin(i));
	}
	glEnd();


	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= 2 * PI; i += resolution)
	{
		const float tc = (i / (float)(2 * PI));
		glTexCoord2f(tc, 0.0);
		glVertex3f(radius * cos(i), 0, radius * sin(i));
		glTexCoord2f(tc, 1.0);
		glVertex3f(radius * cos(i), height, radius * sin(i));
	}

	glTexCoord2f(0.0, 0.0);
	glVertex3f(radius, 0, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(radius, height, 0);
	glEnd();

	glPopMatrix();
}

void path() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textureName[10]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(6, 0.21f, 0.5f);
	glRotatef(90, 1, 0, 0);

	glBegin(GL_QUADS);
	glTexCoord3f(0.1, 1.0, 0.1);  glVertex3f(-0.5f, 4.6f, 0);
	glTexCoord3f(1.0, 1.0, 0.1);  glVertex3f(0.5f, 4.6f, 0);
	glTexCoord3f(1.0, 0.0, 0.1);  glVertex3f(0.5f, -4.6f, 0);
	glTexCoord3f(0.1, 0.0, 0.1);  glVertex3f(-0.5f, -4.6f, 0);
	glEnd();
	glPopMatrix();
}

void bench() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureName[0]);
	//const double PI = 3.14159;


	double i, resolution = 0.1;
	double height = 0.5f;
	double radius = 0.1;
	glPushMatrix();
	glTranslatef(-6, 0, -4.25f);
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= 2 * PI; i += resolution)
	{
		const float tc = (i / (float)(2 * PI));
		glTexCoord2f(tc, 0.0);
		glVertex3f(radius * cos(i), 0, radius * sin(i));
		glTexCoord2f(tc, 1.0);
		glVertex3f(radius * cos(i), height, radius * sin(i));
	}

	glTexCoord2f(0.0, 0.0);
	glVertex3f(radius, 0, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(radius, height, 0);
	glEnd();



	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= 2 * PI; i += resolution)
	{
		const float tc = (i / (float)(2 * PI));
		glTexCoord2f(tc, 0.0);
		glVertex3f(radius * cos(i), 0, radius * sin(i));
		glTexCoord2f(tc, 1.0);
		glVertex3f(radius * cos(i), height, radius * sin(i));
	}

	glTexCoord2f(0.0, 0.0);
	glVertex3f(radius, 0, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(radius, height, 0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= 2 * PI; i += resolution)
	{
		const float tc = (i / (float)(2 * PI));
		glTexCoord2f(tc, 0.0);
		glVertex3f(radius * cos(i), 0, radius * sin(i));
		glTexCoord2f(tc, 1.0);
		glVertex3f(radius * cos(i), height, radius * sin(i));
	}

	glTexCoord2f(0.0, 0.0);
	glVertex3f(radius, 0, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(radius, height, 0);
	glEnd();

	glTranslatef(-1, 0, 0);

	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= 2 * PI; i += resolution)
	{
		const float tc = (i / (float)(2 * PI));
		glTexCoord2f(tc, 0.0);
		glVertex3f(radius * cos(i), 0, radius * sin(i));
		glTexCoord2f(tc, 1.0);
		glVertex3f(radius * cos(i), height, radius * sin(i));
	}

	glTexCoord2f(0.0, 0.0);
	glVertex3f(radius, 0, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(radius, height, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureName[11]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(0.5f, 0.5f, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);

	glBegin(GL_QUADS);
	glTexCoord3f(0.1, 1.0, 0.1);  glVertex3f(-0.2f, 0.7f, 0);
	glTexCoord3f(1.0, 1.0, 0.1);  glVertex3f(0.2f, 0.7f, 0);
	glTexCoord3f(1.0, 0.0, 0.1);  glVertex3f(0.2f, -0.7f, 0);
	glTexCoord3f(0.1, 0.0, 0.1);  glVertex3f(-0.2f, -0.7f, 0);
	glEnd();
	glPopMatrix();
}

void treeBottom() {
	float width = 0.2f;
	float height = 1.5f;
	float depth = 0.2f;
	float V[8][3] = { {-width, -height, depth}, {width, -height, depth}, {width, height, depth}, {-width, height, depth}, {-width, -height, -depth}, {width, -height, -depth}, {width, height, -depth}, {-width, height, -depth} };
	int F[6][4] = { {1, 2, 3, 0}, {5, 6, 2, 1}, {4, 7, 6, 5}, {0, 3, 7, 4}, {6, 7, 3, 2}, {5, 1, 0, 4} };
	float C[6][3] = { {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f} };


	glNewList(1, GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D, textureName[13]);
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)
	{
		//glColor3f(C[i][0], C[i][1], C[i][2]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(V[F[i][0]][0], V[F[i][0]][1], V[F[i][0]][2]);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(V[F[i][1]][0], V[F[i][1]][1], V[F[i][1]][2]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(V[F[i][2]][0], V[F[i][2]][1], V[F[i][2]][2]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(V[F[i][3]][0], V[F[i][3]][1], V[F[i][3]][2]);
	}
	glEnd();
	glEndList();
	glCallList(1);
}

void treeTop() {
	float width = 1.5f;
	float height = 0.2f;
	float depth = 0.5f;
	float V[8][3] = { {-width, -height, depth}, {width, -height, depth}, {width, height, depth}, {-width, height, depth}, {-width, -height, -depth}, {width, -height, -depth}, {width, height, -depth}, {-width, height, -depth} };
	int F[6][4] = { {1, 2, 3, 0}, {5, 6, 2, 1}, {4, 7, 6, 5}, {0, 3, 7, 4}, {6, 7, 3, 2}, {5, 1, 0, 4} };
	float C[6][3] = { {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f} };


	glNewList(1, GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D, textureName[12]);
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)
	{
		//glColor3f(C[i][0], C[i][1], C[i][2]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(V[F[i][0]][0], V[F[i][0]][1], V[F[i][0]][2]);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(V[F[i][1]][0], V[F[i][1]][1], V[F[i][1]][2]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(V[F[i][2]][0], V[F[i][2]][1], V[F[i][2]][2]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(V[F[i][3]][0], V[F[i][3]][1], V[F[i][3]][2]);
	}
	glEnd();
	glEndList();
	glCallList(1);

}
void treeTop2() {
	float width = 1.0f;
	float height = 0.2f;
	float depth = 0.5f;
	float V[8][3] = { {-width, -height, depth}, {width, -height, depth}, {width, height, depth}, {-width, height, depth}, {-width, -height, -depth}, {width, -height, -depth}, {width, height, -depth}, {-width, height, -depth} };
	int F[6][4] = { {1, 2, 3, 0}, {5, 6, 2, 1}, {4, 7, 6, 5}, {0, 3, 7, 4}, {6, 7, 3, 2}, {5, 1, 0, 4} };
	float C[6][3] = { {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f} };


	glNewList(1, GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D, textureName[12]);
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)
	{
		//glColor3f(C[i][0], C[i][1], C[i][2]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(V[F[i][0]][0], V[F[i][0]][1], V[F[i][0]][2]);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(V[F[i][1]][0], V[F[i][1]][1], V[F[i][1]][2]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(V[F[i][2]][0], V[F[i][2]][1], V[F[i][2]][2]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(V[F[i][3]][0], V[F[i][3]][1], V[F[i][3]][2]);
	}
	glEnd();
	glEndList();
	glCallList(1);

}
void treeTop3() {
	float width = 0.5f;
	float height = 0.2f;
	float depth = 0.5f;
	float V[8][3] = { {-width, -height, depth}, {width, -height, depth}, {width, height, depth}, {-width, height, depth}, {-width, -height, -depth}, {width, -height, -depth}, {width, height, -depth}, {-width, height, -depth} };
	int F[6][4] = { {1, 2, 3, 0}, {5, 6, 2, 1}, {4, 7, 6, 5}, {0, 3, 7, 4}, {6, 7, 3, 2}, {5, 1, 0, 4} };
	float C[6][3] = { {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f} };


	glNewList(1, GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D, textureName[12]);
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)
	{
		//glColor3f(C[i][0], C[i][1], C[i][2]);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(V[F[i][0]][0], V[F[i][0]][1], V[F[i][0]][2]);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(V[F[i][1]][0], V[F[i][1]][1], V[F[i][1]][2]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(V[F[i][2]][0], V[F[i][2]][1], V[F[i][2]][2]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(V[F[i][3]][0], V[F[i][3]][1], V[F[i][3]][2]);
	}
	glEnd();
	glEndList();
	glCallList(1);

}
void swing() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureName[14]);
	//const double PI = 3.14159;


	double i, resolution = 0.1;
	double height = 2.0f;
	double radius = 0.05;
	glPushMatrix();

	glTranslatef(1.2f, -1, 0);

	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= 2 * PI; i += resolution)
	{
		const float tc = (i / (float)(2 * PI));
		glTexCoord2f(tc, 0.0);
		glVertex3f(radius * cos(i), 0, radius * sin(i));
		glTexCoord2f(tc, 1.0);
		glVertex3f(radius * cos(i), height, radius * sin(i));
	}

	glTexCoord2f(0.0, 0.0);
	glVertex3f(radius, 0, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(radius, height, 0);
	glEnd();



	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= 2 * PI; i += resolution)
	{
		const float tc = (i / (float)(2 * PI));
		glTexCoord2f(tc, 0.0);
		glVertex3f(radius * cos(i), 0, radius * sin(i));
		glTexCoord2f(tc, 1.0);
		glVertex3f(radius * cos(i), height, radius * sin(i));
	}

	glTexCoord2f(0.0, 0.0);
	glVertex3f(radius, 0, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(radius, height, 0);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= 2 * PI; i += resolution)
	{
		const float tc = (i / (float)(2 * PI));
		glTexCoord2f(tc, 0.0);
		glVertex3f(radius * cos(i), 0, radius * sin(i));
		glTexCoord2f(tc, 1.0);
		glVertex3f(radius * cos(i), height, radius * sin(i));
	}

	glTexCoord2f(0.0, 0.0);
	glVertex3f(radius, 0, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(radius, height, 0);
	glEnd();

	glTranslatef(-0.75f, 0, 0);

	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= 2 * PI; i += resolution)
	{
		const float tc = (i / (float)(2 * PI));
		glTexCoord2f(tc, 0.0);
		glVertex3f(radius * cos(i), 0, radius * sin(i));
		glTexCoord2f(tc, 1.0);
		glVertex3f(radius * cos(i), height, radius * sin(i));
	}

	glTexCoord2f(0.0, 0.0);
	glVertex3f(radius, 0, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(radius, height, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureName[15]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(0.35f, 0.0, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);

	glBegin(GL_QUADS);
	glTexCoord3f(0.1, 1.0, 0.1);  glVertex3f(-0.2f, 0.5f, 0);
	glTexCoord3f(1.0, 1.0, 0.1);  glVertex3f(0.2f, 0.5f, 0);
	glTexCoord3f(1.0, 0.0, 0.1);  glVertex3f(0.2f, -0.5f, 0);
	glTexCoord3f(0.1, 0.0, 0.1);  glVertex3f(-0.2f, -0.5f, 0);
	glEnd();
	glPopMatrix();


}

void tree() {
	glPushMatrix();

	glTranslatef(-4, 1.5f, -4);

	treeBottom();
	swing();

	glTranslatef(0, 1.25f, 0);
	treeTop();
	glTranslatef(0, 0.25f, 0);
	treeTop2();
	glTranslatef(0, 0.25f, 0);
	treeTop3();


	glPopMatrix();
}

void texture() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glRotatef(12, 1, 0, 0);
	foundation();
	//glTranslatef(6, 1.5f, 2.5f);
	house();
	//glTranslatef(-15, 6, 0);
	sun();
	sky();
	lake();
	path();
	bench();
	tree();
	bamboo();
	glTranslatef(0.21f, 0, -0.9f);
	bamboo();
	glTranslatef(0.22f, 0, -0.9f);
	bamboo();

	glFlush();
	glutSwapBuffers();
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(yRot, 0, 1, 0);
	glRotatef(xRot, 1, 0, 0); // x tengely koruli forgatas xRot fokkal
	//kocka();
	texture();

	glPopMatrix();
	glutSwapBuffers();
}



void resizeWindow(int w, int h)
{
	float viewWidth = 2.2;
	float viewHeight = 2.2;
	glViewport(0, 0, w, h);
	h = (h == 0) ? 1 : h;
	w = (w == 0) ? 1 : w;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h < w) {
		viewWidth *= (float)w / (float)h;
	}
	else {
		viewHeight *= (float)h / (float)w;
	}
	glOrtho(-viewWidth, viewWidth, -viewHeight, viewHeight, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat	 lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	if (w <= h)
		glOrtho(-9, 9, -9 * h / w, 9 * h / w, -10.0, 10.0);
	else
		glOrtho(-9 * w / h, 9 * w / h, -9, 9, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

const char* filenameArray[16] = {
		"fa.bmp",
		"grass.bmp",
		"brick.bmp",
		"window.bmp",
		"roof.bmp",
		"door.bmp",
		"sun.bmp",
		"sky2.bmp",
		"water.bmp",
		"bamboo.bmp",
		"path.bmp",
		"bench.bmp",
		"Oak-Leaves.bmp",
		"tree.bmp",
		"rope.bmp",
		"swing.bmp"
};

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 1.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 1.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 1.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 1.0f;
	if (xRot > 360.0f)
		xRot = 0.0f;
	if (xRot < -1.0f)
		xRot = 360.0f;
	if (yRot > 360.0f)
		yRot = 0.0f;
	if (yRot < -1.0f)
		yRot = 360.0f;
	glutPostRedisplay();
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initFour(filenameArray);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeys);
	SetupRC();
	glutMainLoop();
	return 0;
}

