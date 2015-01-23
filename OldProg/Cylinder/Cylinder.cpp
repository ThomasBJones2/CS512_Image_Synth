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

/*This function finds the ray of length 1 from the eye to a particular pixel in the 
fustrum asuming that the center of the fustrum is length 1 away from the eye and the eye
is centered in the fustrum*/

vector3f FindPR(int w, int h, int width, int height,float width_dist){
	float aspect_ratio = ((float)height)/((float)width);
	vector3f ray(((float)(w- width/2.0))/((float)width)*width_dist,
			((float)(h- height/2.0))/((float)height)*width_dist*aspect_ratio,1);
	ray = ray*1.0/((float)(ray.length()));
	return ray;
}


/*Find the distance from the eye at (0,0,0) to the cylindar)*/
/*Equation formulated on scratch paper*/
vector2f Cylindar_Intersect_Distance(vector3f Pixel_Ray, vector3f Direction, vector3f CenterPoint,  float Radius){
	vector2f dist;
	vector3f Eye(0,0,0);
	float Sqrt_Val;
	float a,b,c;
	vector3f EyetoPoint = Eye - CenterPoint;

	a = dot(Pixel_Ray,Pixel_Ray)-dot(Pixel_Ray,Direction)*dot(Pixel_Ray,Direction);
	b = 2*(dot(Pixel_Ray,EyetoPoint) - dot(Pixel_Ray,Direction)*dot(EyetoPoint,Direction));	
	c = dot(EyetoPoint,EyetoPoint)-
		dot(EyetoPoint,Direction)*dot(EyetoPoint,Direction)- Radius*Radius; 
	
	Sqrt_Val = b*b - 4.0*a*c;	

	if(Sqrt_Val > 0){
		dist[0] = (-b - sqrt(Sqrt_Val))/(2.0*a); 
		dist[1] = (-b + sqrt(Sqrt_Val))/(2.0*a);
	}
	else{
		dist[0] = -100.0;
		dist[1] = -100.0;
	}


	return dist;
}

/*This function finds a field of distances from the eye to a cylinder, if the distance does not exist, a field point
holds the value -1*/
void Cylinder_Dist_Field(vector3f EyePosition, vector3f Direction, 
	vector3f CenterPoint, float Radius, vector2f DistField[WIDTH][HEIGHT]){
	vector3f NormalizedDirection;
	vector3f Pixel_Ray;

	NormalizedDirection = Direction*(1.0/(Direction.length()));
	for (int w = 0; w < WIDTH; w ++){
		for(int h = 0; h < HEIGHT; h ++){
			Pixel_Ray = FindPR(w,h,WIDTH,HEIGHT,WIDTH_DIST);
			DistField[w][h] = Cylindar_Intersect_Distance (Pixel_Ray, 
				NormalizedDirection, CenterPoint, Radius);
		}
	}
}

main(){
	int running = GL_TRUE;

	init();

	float r;
	vector3f Direction, CenterPoint;

	cout << "What would you like to be the direction vector of your cylinder?\n";
	cout << "X Vector: ";
	cin >> Direction[0];
	cout << "\n";

	cout << "Y Vector: ";
	cin >> Direction[1];
	cout << "\n";

	cout << "Z Vector: ";
	cin >> Direction[2];
	cout << "\n";

	cout << "Please Name a point in the center of the cylinder:\n";
	cout << "X Vector: ";
	cin >> CenterPoint[0];
	cout << "\n";

	cout << "Y Vector: ";
	cin >> CenterPoint[1];
	cout << "\n";

	cout << "Z Vector: ";
	cin >> CenterPoint[2];
	cout << "\n";		

	cout << "What would you like the radius of the cylindar to be?\n";
	cin >> r;

	while(running){
	glClear(GL_COLOR_BUFFER_BIT);



	running = !glfwGetKey(GLFW_KEY_ESC) &&
		glfwGetWindowParam(GLFW_OPENED);



	//Draw Distances for a Sphere
	vector2f DistField[WIDTH][HEIGHT];
	Cylinder_Dist_Field(vector3f(0,0,0),Direction,CenterPoint,r,DistField);
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

