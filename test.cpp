#include <GL/glut.h>
#include <cstdio>
#include <cmath>
#include <ctime>
#include "View.h"
#include "Plane.h"
#include "Sphere.h"

float t = 1.1, curtime;
int width = 512, height = 512, curframes;
Color* pixels;
View* view;
Light l;

void PrepareView() {
	pixels = (Color*)malloc(width*height*sizeof(Color));

	view = new View(width, height, Ray(Vector3(-1, 5, 0), Vector3(1, -5, 0)));

	// Scene objects
	Sphere* esfera1 = new Sphere(Vector3(2, 0, -1), 1), *esfera2 = new Sphere(Vector3(3, 0, 0.25), 1);
	esfera1->SetDiffuseColor(Color(0,0.7,0.7)); esfera2->SetDiffuseColor(Color(0,0,0.7));

	Plane* chao = new Plane(Vector3(0,-1,0), Vector3(0,1,0)); chao->SetDiffuseColor(Color(1,0,0));
	view->AddSurface(esfera1); view->AddSurface(esfera2); view->AddSurface(chao);

	// Scene lights
	l = Light(Vector3(0,0,0), 0.5);
	view->AddLight(&l);
}

void DrawView () {

	time_t tempo;
	time(&tempo);
	t += 0.1;
	//l.position = Vector3(-2*cos(t), 2, -2*sin(t));

	view->DrawScene(pixels);
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

	glutSwapBuffers();

	curframes++;
	curtime += difftime(time(0), tempo);
	if(curtime >= 2) {
		printf("%f FPS\n", curframes/curtime);
		curtime = curframes = 0;
	}

	glutPostRedisplay();


}

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);  
  glutInitWindowPosition(200,200);
  glutInitWindowSize(width,height);
  glutCreateWindow("Part 1");

  PrepareView();
  glutDisplayFunc(DrawView);
  
  glutMainLoop();

  return 0;
}
