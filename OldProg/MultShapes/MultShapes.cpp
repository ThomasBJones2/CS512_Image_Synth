#include <GL/gl.h>
#include <GL/glfw.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "./ImageDef.h"
#include "../lib/Init.h"
#include "../lib/Save.h"

#include "../lib/GeoShapes/ShapeDist.h"
	



using namespace std;

float Find_Max(vector2f Distance_Field[WIDTH][HEIGHT]){
	float max = Distance_Field[0][0][0];
	for(int i = 0; i < WIDTH; i ++)
		for(int j = 0; j < HEIGHT; j++){
			if(max < Distance_Field[i][j][0])
				max = Distance_Field[i][j][0];	
		}
	return max;
}

float Find_Min(vector2f Distance_Field[WIDTH][HEIGHT]){
	float min = Find_Max(Distance_Field);

	for(int i = 0; i < WIDTH; i ++)
		for(int j = 0; j < HEIGHT; j++){
			if(Distance_Field[i][j][0] > 0)
				if(min > Distance_Field[i][j][0])
					min = Distance_Field[i][j][0];	
		}
	return min;
}

void Draw(vector2f Distance_Field[WIDTH][HEIGHT],vector2f BackPlaneField[WIDTH][HEIGHT],
		vector2f FrontPlaneField[WIDTH][HEIGHT])
{
	float image[WIDTH * HEIGHT * 3];
	float val = 0;
	float max = Find_Max(Distance_Field);
	float min = Find_Min(Distance_Field);
  	for(int i=0;i<WIDTH*HEIGHT;i++) {
		if (Distance_Field[i%WIDTH][i/HEIGHT][0] > FrontPlaneField[i%WIDTH][i/HEIGHT][0]
			&&  Distance_Field[i%WIDTH][i/HEIGHT][0] < BackPlaneField[i%WIDTH][i/HEIGHT][0]){
			val = Distance_Field[i%WIDTH][i/HEIGHT][0]-min;
		}
		else
			val = 0;
		if(val != 0){	
			image[i*3] = 1.0 - val/(max-min);
			image[i*3+1] = 1.0 - val/(max-min);
			image[i*3+2] = 1.0 - val/(max-min);
		}
		else{
			image[i*3] = 0;
			image[i*3+1] = 0;
			image[i*3+2] = 0;		
		}

  	} 

    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawPixels(WIDTH,HEIGHT,GL_RGB,GL_FLOAT,image);
	glfwSwapBuffers();
}


main(){
	int running = GL_TRUE;

	init();

	float r;
	vector3f Direction, CenterPoint;

	cout << "What would you like to be the direction vector of your Cone?\n";
	cout << "X Vector: ";
	cin >> Direction[0];
	cout << "\n";

	cout << "Y Vector: ";
	cin >> Direction[1];
	cout << "\n";

	cout << "Z Vector: ";
	cin >> Direction[2];
	cout << "\n";

	cout << "Please Name a point in the center of the Cone:\n";
	cout << "X Vector: ";
	cin >> CenterPoint[0];
	cout << "\n";

	cout << "Y Vector: ";
	cin >> CenterPoint[1];
	cout << "\n";

	cout << "Z Vector: ";
	cin >> CenterPoint[2];
	cout << "\n";		

	cout << "What would you like the radius of the Cone to be?\n";
	cin >> r;

	while(running){
	glClear(GL_COLOR_BUFFER_BIT);



	running = !glfwGetKey(GLFW_KEY_ESC) &&
		glfwGetWindowParam(GLFW_OPENED);



	//Draw Distances for a Sphere
	vector2f DistField[WIDTH][HEIGHT];
	vector2f BackPlaneField[WIDTH][HEIGHT];
	vector2f FrontPlaneField[WIDTH][HEIGHT];
	Cone_Dist_Field(vector3f(0,0,0),Direction,CenterPoint,r,DistField);
	Plane_Dist_Field(vector3f(0,0,0), vector3f(0,0,5), vector3f(0,0,1), BackPlaneField);
	Plane_Dist_Field(vector3f(0,0,0), vector3f(0,0,1), vector3f(0,0,1), FrontPlaneField);
	Draw(DistField,BackPlaneField,FrontPlaneField);



	if(glfwGetKey('S')){
		while(glfwGetKey('S')){
			glfwPollEvents();
		}
		save("./Test.jpg");
		}
	}


	Shut_Down(0);
}

