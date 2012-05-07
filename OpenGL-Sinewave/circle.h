#include "GL/gl.h"
#include "GL/freeglut.h"
#include <math.h>
#include <iostream>

class Circle {	 
	public: float freq, x, y, r;	
	public:
		Circle();
		void DrawInnerLines(float,float);
		void DrawCircle(float,float,int);
};

Circle::Circle (){	
	r = 1;	
}

void Circle :: DrawInnerLines(float t, float T)
{	
	freq = (2*3.1415926/T)*t;
  	x = r * cosf(freq);
  	y = r * sinf(freq);
 
  glBegin(GL_LINES);
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(x,y,0);

	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(x,0,0);

	glVertex3f(x,0,0);		
	glVertex3f(x,y,0);
	
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,y,0);

	glVertex3f(0,y,0);		
	glVertex3f(x,y,0);

	glColor3f(1,1,1);
  glEnd(); 
}

void Circle :: DrawCircle(float cx, float cy, int num_segments)
{
  float theta = 2*3.1415926 / float(num_segments);
  float tangential_factor = tanf(theta);//calculate the tangential factor
  float radial_factor = cosf(theta);//calculate the radial factor
  float x = r;//start at angle = 0;
  float y = 0;  

  glBegin(GL_LINE_LOOP);
  for(int i = 0; i< num_segments; i++)
  { 
	
    glVertex3f(x+cx,y+cy,0);//output vertex
    //calculate the tangential vector
    //the radial vector is (x,y)
    //to get the tangential vector you flip those coordinates and negate one

    float tx = -y;
    float ty = x;
	
    //add tangential vector

    x += tx * tangential_factor;
    y += ty * tangential_factor;

    //correct using radial factor

    x *= radial_factor;
    y *= radial_factor;
  }
  glEnd();
}
