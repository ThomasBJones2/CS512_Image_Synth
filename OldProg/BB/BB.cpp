#include <GL/gl.h>
#include <GL/glfw.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "./ImageDef.h"
#include "../lib/Init.h"
#include "../lib/Save.h"
#include <cml/cml.h>
#include "../lib/GeoShapes/ShapeDist.h"	



using namespace std;
using namespace cml;

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

void Draw(vector2f Distance_Field[WIDTH][HEIGHT])
{
	float image[WIDTH * HEIGHT * 3];
	float val = 0;
	float max = Find_Max(Distance_Field);
	float min = Find_Min(Distance_Field);
  	for(int i=0;i<WIDTH*HEIGHT;i++) {
		if (Distance_Field[i%WIDTH][i/HEIGHT][0] > 0 ){
			val = Distance_Field[i%WIDTH][i/HEIGHT][0]-min;
//			cout << "Val: " << val << " Min: " << min << " Max: " << max << "\n";
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

/*This function finds a field of distances from the eye to a BB, if the distance does not exist, a field point
holds the value -1*/
void BB_Dist_Field(vector3f EyePosition, vector3f Corner1, vector3f Corner2, 
	vector2f DistField[WIDTH][HEIGHT]){
	vector3f Pixel_Ray;

	for (int w = 0; w < WIDTH; w ++){
		for(int h = 0; h < HEIGHT; h ++){
			Pixel_Ray = FindPR(vector3f(0,0,0),vector3f(0,0,1),w,h,WIDTH,HEIGHT,WIDTH_DIST);
			DistField[w][h] = BB_Intersect_Distance (vector3f(0,0,0),Pixel_Ray, Corner1, Corner2);
		}
	}
}

main(){
	int running = GL_TRUE;

	init();

	float r;
	vector3f Corner1, Corner2;

	cout << "What is corner 1?\n";
	cin >> Corner1[0] >> Corner1[1] >> Corner1[2];

	cout << "What is corner 2?\n";
	cin >> Corner2[0] >> Corner2[1] >> Corner2[2];

	while(running){
	glClear(GL_COLOR_BUFFER_BIT);



	running = !glfwGetKey(GLFW_KEY_ESC) &&
		glfwGetWindowParam(GLFW_OPENED);



	//Draw Distances for a Sphere
	vector2f DistField[WIDTH][HEIGHT];
	BB_Dist_Field(vector3f(0,0,0),Corner1,Corner2,DistField);
	Draw(DistField);



	if(glfwGetKey('S')){
		while(glfwGetKey('S')){
			glfwPollEvents();
		}
		save("./Test.jpg");
		}
	}


	Shut_Down(0);
}

