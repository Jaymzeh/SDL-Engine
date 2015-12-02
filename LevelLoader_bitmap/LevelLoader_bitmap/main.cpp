#include "freeglut\glut.h"

#include "map.h"

#define windowWidth 640
#define windowHeight 640

float i = 0;

Map *map = NULL;


void init(){
	map = new Map("SampleMap4.txt", 0, windowHeight);
	map->setBitmap("BlockSpriteBitmap2.bmp");
	map->loadMapTiles();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	map->render();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0, 0);
	glVertex2f(0, windowHeight);
	glVertex2f(windowWidth, windowHeight);
	glVertex2f(windowWidth, 0);
	glEnd();

	glutPostRedisplay();
}

void update(){

}

void keys(unsigned char k, int x, int y){
	switch (k){

	case VK_ESCAPE:
		exit(0);
		break;

	case 'w' | 'W':
		glTranslated(0, -32, 0);
		break;

	case 's' | 'S':
		glTranslated(0, 32, 0);
		break;

	case 'a' | 'A':
		glTranslated(32, 0, 0);
		break;

	case 'd' | 'D':
		glTranslated(-32, 0, 0);
		break;

	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Level Loader Prototype - Bitmap");
	glClearColor(0, 0, 0, 0);
	gluOrtho2D(0, windowWidth, 0, windowHeight);
	init();
	glutKeyboardFunc(keys);
	glutDisplayFunc(display);
	glutIdleFunc(update);
	glutMainLoop();
	delete map;
	return 0;
}
