#include <GL/gl.h>
#include <GL/glfw.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "./ImageDef.h"
#include "../lib/Init.h"
#include "../lib/Save.h"
#include <cml/cml.h>
	



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
		if (Distance_Field[i%WIDTH][i/HEIGHT][0] > 0){
			val = Distance_Field[i%WIDTH][i/HEIGHT][0]-min;
//			cout << "Val: " << val << " Min: " << min << " Max: " << max << "\n";
		}
		else
			val = 0;
		if(val != 0){	
			image[i*3] = 1.0 - val/max;
			image[i*3+1] = 1.0 - val/max;
			image[i*3+2] = 1.0 - val/max;
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

/*This function finds the line of length 1 from the eye to a particular pixel in the 
fustrum*/

vector3f FindPL(int w, int h, int width, int height,float width_dist){
	float aspect_ratio = ((float)height)/((float)width);
	vector3f line(((float)(w- width/2.0))/((float)width)*width_dist,
			((float)(h- height/2.0))/((float)height)*width_dist*aspect_ratio,1);
	line = line*1.0/((float)(line.length()));
	return line;
}


/*Find the distance from the eye at (0,0,0) to the sphere)*/
/*Equation found at: http://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection*/
vector2f Sphere_Intersect_Distance(vector3f Pixel_Line, vector3f Center, float Radius){
	vector2f dist;
	float line_center = dot(Pixel_Line, Center);	
	float Sqrt_Val = line_center*line_center - 
			dot(Center,Center) + Radius*Radius;
	if(Sqrt_Val > 0){
		dist[0] = (line_center - sqrt(Sqrt_Val)); 
		dist[1] = (line_center + sqrt(Sqrt_Val));
	}
	else{
		dist[0] = -100.0;
		dist[1] = -100.0;
	}
	return dist;
}

/*This function finds a field of distances from the eye to a sphere, if the distance does not exist, a field point
holds the value -1*/
void Sphere_Dist_Field(vector3f EyePosition, vector3f Center, float Radius, vector2f DistField[WIDTH][HEIGHT]){

	vector3f Pixel_Line;
	vector2f Dist;
	for (int w = 0; w < WIDTH; w ++){
		for(int h = 0; h < HEIGHT; h ++){
			Pixel_Line = FindPL(w,h,WIDTH,HEIGHT,WIDTH_DIST);
			DistField[w][h] = Sphere_Intersect_Distance (Pixel_Line,Center, Radius);
		}
	}
}

main(){
	int running = GL_TRUE;

	init();

	float a,b,c,r;

	cout << "Where would you like the center of the sphere?\n";
	cout << "X Vector: ";
	cin >> a;
	cout << "\n";

	cout << "Y Vector: ";
	cin >> b;
	cout << "\n";

	cout << "Z Vector: ";
	cin >> c;
	cout << "\n";

	cout << "What would you like the radius of the sphere to be?\n";
	cin >> r;

	while(running){
	glClear(GL_COLOR_BUFFER_BIT);



	running = !glfwGetKey(GLFW_KEY_ESC) &&
		glfwGetWindowParam(GLFW_OPENED);



	//Draw Distances for a Sphere
	vector2f DistField[WIDTH][HEIGHT];
	Sphere_Dist_Field(vector3f(0,0,0),vector3f(a,b,c),r,DistField);
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

