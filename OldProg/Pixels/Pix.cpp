#include <GL/gl.h>
#include <GL/glfw.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "./ImageDef.h"
#include "../lib/Init.h"
#include "../lib/Save.h"
	



using namespace std;


void Draw(void)
{
	float image[WIDTH * HEIGHT * 3];
  	for(int i=0;i<WIDTH*HEIGHT;i++) {
		image[i*3] = 1;
		image[i*3+1] = 1;
		image[i*3+2] = 1;
		if(i%WIDTH == 200)
    			image[i*3]=((float)i)/((float)WIDTH*HEIGHT);
		else if(i > WIDTH*200 && i < WIDTH*201)
			image[i*3+1] = ((float)(i-WIDTH*200))/((float)WIDTH);
		else if (i%WIDTH == i/HEIGHT)
			image[i*3+2] = ((float)(i%WIDTH))/((float)WIDTH);
  	} 
	//GLfloat pos;
	//glGetFloatv(GL_CURRENT_RASTER_POSITION, &pos);
	//cout << pos << "\n";

//	glBitmap(WIDTH,HEIGHT,0,0,0,0,image);

//	glRasterPos4f(.2,.2,4.0,1.0);
	// clear the buffer

    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawPixels(WIDTH,HEIGHT,GL_RGB,GL_FLOAT,image);
	glfwSwapBuffers();
}

main(){
	int running = GL_TRUE;

	init();

	while(running){
	glClear(GL_COLOR_BUFFER_BIT);



	running = !glfwGetKey(GLFW_KEY_ESC) &&
		glfwGetWindowParam(GLFW_OPENED);



	//Draw a Square
	Draw();



	if(glfwGetKey('S')){
		while(glfwGetKey('S')){
			glfwPollEvents();
		}
		save("./Test.jpg");
		}
	}


	Shut_Down(0);
}


