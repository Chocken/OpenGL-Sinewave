#include "GL/gl.h"
#include "GL/freeglut.h"
#include "circle.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "vertex.h"
using namespace std;

//angle of rotation
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0, t = 0, T = 5,yPrev = 0;
vector<Vertex> points;

void reshape(int width, int height)
{
    glViewport(0,0, (GLsizei)width, (GLsizei)height);//Set our viewport to the size of our window
    glMatrixMode(GL_PROJECTION);//switch to the projection matrix so that we can manipulate how our scene is viewed
    glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artefacts (cleaning up)
    gluPerspective(60,(GLfloat)width/(GLfloat)height, 1.0, 100.0); // Set the field of view angle (degrees), the aspect ratio of our window, & the new and far planes
    glMatrixMode(GL_MODELVIEW);//Switch back to modelview matrix, so that we can draw shapes correctly  
}

void DrawAxes()
{
	glBegin(GL_LINES);
	
	glVertex3f(-2,0,0);
	glVertex3f(2,0,0);

	glVertex3f(0,-2,0);
	glVertex3f(0,2,0);

	glVertex3f(0,0,-T);
	glVertex3f(0,0,T);
	
  	glEnd();
}	

void keyboard (unsigned char key, int x, int y) {
    if (key=='q')
    {
    xrot += 1;
    if (xrot >360) xrot -= 360;
    }

    if (key=='z')
    {
    xrot -= 1;
    if (xrot < -360) xrot += 360;
    }

    if (key=='w')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos += float(sin(yrotrad)) ;
    zpos -= float(cos(yrotrad)) ;
    ypos -= float(sin(xrotrad)) ;
    }

    if (key=='s')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos -= float(sin(yrotrad));
    zpos += float(cos(yrotrad)) ;
    ypos += float(sin(xrotrad));
    }

    if (key=='d')
    {
    yrot += 1;
    if (yrot >360) yrot -= 360;
    }

    if (key=='a')
    {
    yrot -= 1;
    if (yrot < -360)yrot += 360;
    }
    if (key==27)
    {
    exit(0);
    }
}

void enable(void){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_SMOOTH);
}

void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
}

void display(void)
{
    Circle myCircle;	  
    glClearColor(0.f,0.f,0.f,0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer)
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-5.0f);//Push everything back 5 units into the scene, otherwise we won't see the primitive 
    camera();    
    yPrev = myCircle.y;
    glPushMatrix();        	
    glTranslatef(0.0f,0.0f,t);
    myCircle.DrawInnerLines(t,T);
    myCircle.DrawCircle(0, 0, 100);
    
    glPopMatrix();
    glBegin(GL_POINTS);
    for(int i=0;i<points.size();i++)
    {
	glVertex3f(points[i].x,points[i].y,points[i].z);
    }
    glEnd();       	    
    DrawAxes();    
    glutSwapBuffers(); //swap the buffers	
    glFlush();//Flush the OpenGL buffers to the window
    
    points.push_back(Vertex(0.0f,myCircle.y,t)); //fill the vector of sinewave points	
    t-=0.002;//
    if (t < -T)
    { 
	t = 0;
        points.clear();
    }
    
    

}

/* Main method - main entry point of application
the freeglut library does the window creation work for us, 
regardless of the platform. */
int main(int argc, char** argv)
{    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - First window demo");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);      
    glutKeyboardFunc(keyboard); //check the keyboard
    glutMainLoop();    
    return 0;
}
