#include <GL/gl.h>
#include <GL/glfw.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <pthread.h>
#include "./ImageDef.h"
#include "../lib/Init.h"
#include "../lib/Save.h"
#include <cml/cml.h>
#include "../lib/GeoShapes/ShapeDist.h"	
#include "../lib/AccDS.h"
#include "../lib/Normals.h"



using namespace std;
using namespace cml;
/*
float Find_Max(const dis_id Distance_Field[WIDTH][HEIGHT]){
	float max = Distance_Field[0][0].distance;
	for(int i = 0; i < WIDTH; i ++)
		for(int j = 0; j < HEIGHT; j++)
			if(max < Distance_Field[i][j].distance)
				max = Distance_Field[i][j].distance;		
	return max;
}

float Find_Min(const dis_id Distance_Field[WIDTH][HEIGHT]){
	float min = Find_Max(Distance_Field);
	for(int i = 0; i < WIDTH; i ++)
		for(int j = 0; j < HEIGHT; j++)
			if(Distance_Field[i][j].distance > 0)
				if(min > Distance_Field[i][j].distance)
					min = Distance_Field[i][j].distance;	
	return min;
}*/

void Draw(vector3d** Distance_Field)
{
	float image[WIDTH * HEIGHT * 3];

  	for(int i = 0;i < WIDTH*HEIGHT;i++) {
		image[i*3] = (float)Distance_Field[i%WIDTH][i/HEIGHT][0];
		image[i*3+1] = (float)Distance_Field[i%WIDTH][i/HEIGHT][1];
		image[i*3+2] = (float)Distance_Field[i%WIDTH][i/HEIGHT][2];

  	} 

    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawPixels(WIDTH,HEIGHT,GL_RGB,GL_FLOAT,image);
	glfwSwapBuffers();
}


/*BRDF(double theta, double phi, double lambda, double& absorption, double& outheta, double& outphi){
	absorption = .9
	outhetha = (rand()%1000000)/(double)1000000;
	outhphi = (rand()%1000000)/(double)1000000;
	outphi = outphi*PI;
	outtheta = outtheta*PI;
}*/

double BRDF1(vector3d& Out_Ray, vector3d normal, vector3d biNormal, dis_id check, object Listobject, double lambda){
	//Here I will have to expand this to allow multiple BRDFS, but right now its okay to have just 1 (I think)...
//	double theta,phi;
	double outtheta,outphi;
	double absorption=.9;
	matrix33d phiMat,thetaMat;
	bool Theta_Bool;
	Theta_Bool = true;
//	if(Listobject.type == SPHERE)
//		cout << normal << "\n";

//	theta = 1;//Not used in this brdf
//	phi = 1;//Not used in this brdf
	

	while (Theta_Bool){
		outtheta = (((double)(rand()%1000000))/1000000.0)*PI*.5;
//		outtheta = PI*.25 - outtheta;

		if ((((double)(rand()%1000000))/1000000.0) < cos(outtheta))
			Theta_Bool = 0;
	}
	outphi = (((double)(rand()%1000000))/1000000.0)*PI*2;
//	outphi = PI*.25 - outphi;

	matrix_rotation_axis_angle(phiMat, normal, outphi);
	matrix_rotation_axis_angle(thetaMat, biNormal, outtheta);

	Out_Ray = VectMatrixMult(normal,thetaMat);	
	Out_Ray = VectMatrixMult(Out_Ray, phiMat);
	return absorption;
}

vector3d Shader(vector3d Eye, vector3d Pixel_Ray, object* List, BinarySearchTree t, int w){
	dis_id check;
	vector3d Cur_Ray, Cur_Eye,normal;
	double lambda = (rand()%1000000)/(double)1000000;
	double absorption = 1.0;
	bool ShaderBool=TRUE;
	Cur_Ray = Pixel_Ray;
	Cur_Eye = Eye;
	while(ShaderBool){	
		check = t.BCS(Cur_Eye,Cur_Ray);
		if (check.id==0||check.distance<0){
			absorption = 0;
			ShaderBool=FALSE;
		}
		else if(List[check.id-1].luminar){
			ShaderBool = FALSE;
		}
		else{

			normal = findNormal(check,List[check.id - 1], Cur_Eye, Cur_Ray);
		//	return Normalize(cross(vector3d(0,0,1),normal));
			Cur_Eye = Cur_Eye + check.distance*Cur_Ray;
			absorption = absorption*BRDF1(Cur_Ray, normal, Normalize(cross(vector3d(0,0,1)+normal,normal)), 
				check , List[check.id - 1] ,lambda);
			if(absorption < .001)
				ShaderBool = FALSE;
		}
		
	}
	check = t.BCS(Eye,Pixel_Ray);
	if(check.distance > 0)
		return vector3d(1,1,1)*absorption + vector3d(.1,.1,.1);
	else 
		return vector3d(1,1,1)*absorption;
}


struct AIS{
	vector3d Eye; 
	vector3d direction; 
	BinarySearchTree t; 
	vector3d** imageField; 
	object* List;
	int width;
};

void* Aquire_Img_Field(void * ptr){
	vector3d Eye = ((AIS*) ptr)->Eye;
	vector3d direction = ((AIS*) ptr)->direction;
	BinarySearchTree t = ((AIS*) ptr)->t;
	vector3d** imageField = ((AIS*) ptr)->imageField;
	object* List = ((AIS*) ptr)->List;
	int w = ((AIS*) ptr)->width;
	vector3f Pixel_Ray;

	for(int h = 0; h < HEIGHT; h ++){
		imageField[w][h] = vector3d(0,0,0);
		for(int i = 0; i < SAMPLE_SIZE; i ++){
			Pixel_Ray = FindPR(Eye, direction, w,h,WIDTH,HEIGHT,WIDTH_DIST);
			imageField[w][h] += (Shader(Eye,Pixel_Ray, List, t,w)*(1.0/((double)SAMPLE_SIZE)));
		}
	if(w%10 == 0 && h%10==0)
		cout << w << " " << h << "\n";
	}

}


#define DIST1 3
#define DIST2 10

#define LENGTH 7
#define SQRTLENGTH 10

int main(){
	int running = GL_TRUE;
	//image field for the whole computation
	vector3d** imageField;
	pthread_t thread[WIDTH];
	int ThreadNum[WIDTH];
	AIS ImgInput[WIDTH];
	char saves;

	object List1[LENGTH];
	BinarySearchTree t;

	imageField = new vector3d*[500];
	for(int i = 0; i < 500; i ++)
		imageField[i] = new vector3d[500];

	srand ( time(NULL) );


	List1[0].id = 1;
	List1[0].type = SPHERE;
	List1[0].center[0] = 10;
	List1[0].center[1] = 0;
	List1[0].center[2] = 50;
	List1[0].radius = 5;
	List1[0].direction = vector3d(0,0,1);
	List1[0].col1 = vector3d(.25,0,0);
	List1[0].col2 = vector3d(0,.1,0);
	List1[0].col3 = vector3d(0,0,.25);
	List1[0].luminar = FALSE;

	List1[1].id = 2;
	List1[1].type = RECT;
	List1[1].center[0] = -30;
	List1[1].center[1] = 0;
	List1[1].center[2] = 0;
	List1[1].direction = vector3d(0,1,0);
	List1[1].biNormal = vector3d(.2,0,1);
	List1[1].height = 50;
	List1[1].length = 50;
	List1[1].width = .5000; 
	List1[1].luminar = TRUE;

	List1[2].id = 3;
	List1[2].type = ELLIPS;
	List1[2].center[0] = 10;
	List1[2].center[1] = -20;
	List1[2].center[2] = 50;
	List1[2].radius = 5;
	List1[2].direction = vector3d(0,0,1);
	List1[2].col1 = vector3d(.25,0,0);
	List1[2].col2 = vector3d(0,.1,0);
	List1[2].col3 = vector3d(0,0,.25);
	List1[2].luminar = FALSE;


	List1[3].id = 4;
	List1[3].type = TRI;
	List1[3].center[0] = 8;
	List1[3].center[1] = -10;
	List1[3].center[2] = 50;
	List1[3].pt1 = List1[3].center + vector3d(0,3.5,-1);
	List1[3].pt2 = List1[3].center + vector3d(-3.5,0,0);
	List1[3].pt3 = List1[3].center + vector3d(3.5,0,-1);
	List1[3].luminar = FALSE;


	List1[4].id = 5;
	List1[4].type = CONE;
	List1[4].center[0] = 10;
	List1[4].center[1] = 10;
	List1[4].center[2] = 50;
	List1[4].radius = 3;
	List1[4].direction = vector3d(0,1,0);
	List1[4].length = 8;
	List1[4].luminar = FALSE;


	List1[5].id = 6;
	List1[5].type = CYLINDER;
	List1[5].center[0] = 10;
	List1[5].center[1] = 20;
	List1[5].center[2] = 50;
	List1[5].radius = 2;
	List1[5].direction = vector3d(0,1,0);
	List1[5].length = 8;
	List1[5].luminar = FALSE;


	List1[6].id = 7;
	List1[6].type = RECT;
	List1[6].center[0] = 15;
	List1[6].center[1] = -10;
	List1[6].center[2] = 50;
	List1[6].direction = Normalize(vector3d(0,-1,1));
	List1[6].biNormal = Normalize(cross(vector3d(0,-1,1),vector3d(1,1,1)));
	List1[6].height = 2;
	List1[6].length = 2;
	List1[6].width = 2;
	List1[6].luminar = FALSE;

/*	for(int i = 0; i < SQRTLENGTH; i ++){
		for(int j = 0; j < SQRTLENGTH; j ++){
			if((j+i)%6 == 0){
				List1[SQRTLENGTH*i+j].id = SQRTLENGTH*i+j+1;
				List1[SQRTLENGTH*i+j].type = SPHERE;
				List1[SQRTLENGTH*i+j].center[0] = i-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[1] = j-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[2] = DIST2-2;
				List1[SQRTLENGTH*i+j].radius = .5;
				List1[SQRTLENGTH*i+j].direction = vector3d(0,0,1);
				List1[SQRTLENGTH*i+j].luminar = FALSE;
			}
			else if((j+i)%6 == 1){
				List1[SQRTLENGTH*i+j].id = SQRTLENGTH*i+j+1;
				List1[SQRTLENGTH*i+j].type = SPHERE;//CONE;
				List1[SQRTLENGTH*i+j].center[0] = i-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[1] = j-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[2] = DIST2-2;
				List1[SQRTLENGTH*i+j].radius = .5;
				List1[SQRTLENGTH*i+j].direction = vector3d(0,0,1);
				List1[SQRTLENGTH*i+j].length = .4;
				List1[SQRTLENGTH*i+j].luminar = FALSE;

			}
			else if((j+i)%6 == 2){
				List1[SQRTLENGTH*i+j].id = SQRTLENGTH*i+j+1;
				List1[SQRTLENGTH*i+j].type = CYLINDER;
				List1[SQRTLENGTH*i+j].center[0] = i-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[1] = j-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[2] = DIST2;
				List1[SQRTLENGTH*i+j].radius = .5;
				List1[SQRTLENGTH*i+j].direction = vector3d(0,0,1);
				List1[SQRTLENGTH*i+j].length = 1;
				List1[SQRTLENGTH*i+j].luminar = FALSE;
			}
			else if((j+i)%6 == 3){
				List1[SQRTLENGTH*i+j].id = SQRTLENGTH*i+j+1;
				List1[SQRTLENGTH*i+j].type = ELLIPS;
				List1[SQRTLENGTH*i+j].center[0] = i-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[1] = j-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[2] = DIST2; 
				List1[SQRTLENGTH*i+j].direction = vector3d(0,1,1);
				List1[SQRTLENGTH*i+j].col1 = vector3d(4,0,0);
				List1[SQRTLENGTH*i+j].col2 = vector3d(0,10,0);
				List1[SQRTLENGTH*i+j].col3 = vector3d(0,0,4);
				List1[SQRTLENGTH*i+j].luminar = FALSE;

			}
			else if((j+i)%6 == 4){
				List1[SQRTLENGTH*i+j].id = SQRTLENGTH*i+j+1;
				List1[SQRTLENGTH*i+j].type = RECT;
				List1[SQRTLENGTH*i+j].center[0] = i-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[1] = j-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[2] = DIST2;
				List1[SQRTLENGTH*i+j].direction = vector3d(0,-1,1);
				List1[SQRTLENGTH*i+j].biNormal = vector3d(0,1,1);
				List1[SQRTLENGTH*i+j].height = .05;
				List1[SQRTLENGTH*i+j].length = .3;
				List1[SQRTLENGTH*i+j].width = .4;
				List1[SQRTLENGTH*i+j].luminar = FALSE;
			

			}
			else if((j+i)%12 == 5){
				List1[SQRTLENGTH*i+j].id = SQRTLENGTH*i+j+1;
				List1[SQRTLENGTH*i+j].type = TRI;
				List1[SQRTLENGTH*i+j].center[0] = i-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[1] = j-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[2] = DIST2;
				List1[SQRTLENGTH*i+j].pt1 = List1[SQRTLENGTH*i+j].center + vector3d(0,.35,0);
				List1[SQRTLENGTH*i+j].pt2 = List1[SQRTLENGTH*i+j].center + vector3d(-.35,0,0);
				List1[SQRTLENGTH*i+j].pt3 = List1[SQRTLENGTH*i+j].center + vector3d(.35,0,0);
				List1[SQRTLENGTH*i+j].luminar = FALSE;
			}
			else if((j+i)%12 == 11){
				List1[SQRTLENGTH*i+j].id = SQRTLENGTH*i+j+1;
				List1[SQRTLENGTH*i+j].type = TRI;
				List1[SQRTLENGTH*i+j].center[0] = i-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[1] = j-SQRTLENGTH/2;
				List1[SQRTLENGTH*i+j].center[2] = DIST2;
				List1[SQRTLENGTH*i+j].pt1 = List1[SQRTLENGTH*i+j].center + vector3d(0,.35,0);
				List1[SQRTLENGTH*i+j].pt2 = List1[SQRTLENGTH*i+j].center + vector3d(0,-.35,0);
				List1[SQRTLENGTH*i+j].pt3 = List1[SQRTLENGTH*i+j].center + vector3d(.35,0,0);
				List1[SQRTLENGTH*i+j].luminar = FALSE;
			}
			if((j+i)%6 == 0){
				List1[SQRTLENGTH*i+j].luminar = TRUE;
				List1[SQRTLENGTH*i+j].center[2] = DIST1;
				List1[SQRTLENGTH*i+j].pt1 = List1[SQRTLENGTH*i+j].center + vector3d(0,.35,0);
				List1[SQRTLENGTH*i+j].pt2 = List1[SQRTLENGTH*i+j].center + vector3d(-.35,0,0);
				List1[SQRTLENGTH*i+j].pt3 = List1[SQRTLENGTH*i+j].center + vector3d(.35,0,0);
			}		
		}
	}*/


	AccList(t, List1, LENGTH);
//	t.print_inorder();

	init();
	while(running){

	glClear(GL_COLOR_BUFFER_BIT);



	running = !glfwGetKey(GLFW_KEY_ESC) &&
		glfwGetWindowParam(GLFW_OPENED);

	for(int i = 0; i < WIDTH; i++){
		ImgInput[i].Eye = vector3d(0,0,0);
		ImgInput[i].direction = vector3d(0,0,0);
		ImgInput[i].t = t;
		ImgInput[i].imageField = imageField;
		ImgInput[i].List = List1;
		ImgInput[i].width = i;
//		cout << ImgInput[i].width << "\n";
		ThreadNum[i] = pthread_create( &thread[i], NULL, Aquire_Img_Field, (void*) (&ImgInput[i]));
//		cout << i << "\n";	
	}
	cout << "Waiting for threads\n";
	for(int i = 0; i < WIDTH; i++){
//		cout << i << "\n";
		pthread_join(thread[i], NULL);
	}
	cout << "All Threads Joined\n";
	Draw(imageField);
	cout << "should I save this picture?\n";

	cin >> saves;
	if (saves == 'y' || saves == 'Y')
		save("./Test2.jpg");
		if(glfwGetKey('S')){
			while(glfwGetKey('S')){
				glfwPollEvents();
			}
			save("./Test.jpg");
		}
	}
	Shut_Down(0);
	return 0;
}

