#include <GL/gl.h>
#include <GL/glfw.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <pthread.h>
#include <cml/cml.h>
#include "./ImageDef.h"
#include "../lib/Init.h"
#include "../lib/Save.h"
#include "../lib/Funcs.h"
#include "../lib/GeoShapes/ShapeDist.h"	
#include "../lib/AccDS.h"
#include "../lib/Normals.h"
#include "../lib/GeoShapes/RefShapDist.h"
#include "../lib/Reflection.h"
#include "../lib/BDRF.h"


using namespace std;
using namespace cml;




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


bool whithin_atmosphere(vector3d Cur_Eye, vector3d Cur_Ray){
 return Sphere_Intersect_Distance(Cur_Eye, Cur_Ray, vector3d(0,0,-6372), 6672)[1] > 0;
}


double lambda_shift(double lambda){
	return (lambda - 550.0)/15000.0*3;
}

double Diffuse_Prob(double lambda){
	return .95 + lambda_shift(lambda);  // - .1*clip(1.0 - abs(475.0 - lambda)/75.0);

}

vector3d Shader(vector3d Eye, vector3d Pixel_Ray, object* List, BinarySearchTree t, int w){
	dis_id check;
	vector3d Cur_Ray, Cur_Eye,normal;
	double lambda = randf()*300.0+400.0;
	bool DifBool;
	
	double absorption = 1.0;
	bool ShaderBool=TRUE;
	int count = 0;
	int innerCount = 0;
//	double RefDist=0;
//	vector3d RefRay = vector3d(0,0,0);
//	vector3d RefEye = vector3d(0,0,0);
//	vector3d RefNormal = vector3d(0,0,0);

	Cur_Ray = Pixel_Ray;
	Cur_Eye = Eye;

	while(ShaderBool){	
		count ++;
		check = t.BCS(Cur_Eye,Cur_Ray);
//		return (check.distance/100.0) * (1/LIGHTCONST) *vector3d(1,1,1); //This line is used for geometric work
		innerCount++;
		while((check.distance > 5 || check.distance < 0) && whithin_atmosphere(Cur_Eye,Cur_Ray) && ((innerCount%50) != 0)){
			check = t.BCS(Cur_Eye,Cur_Ray);
			innerCount ++;	
			Cur_Eye = Cur_Eye + 5.0*Cur_Ray;		
			if (randf() > Diffuse_Prob(lambda)){
				Cur_Ray = normalize(vector3d(randf(),randf(),randf()));			
			}
		}



		if ((check.id==0||check.distance<0) && !whithin_atmosphere(Cur_Eye,Cur_Ray)){
			absorption = 0;
			ShaderBool=FALSE;
		}
		else if((List[check.id-1].luminar) && (check.id != 0) && !whithin_atmosphere(Cur_Eye,Cur_Ray)){
			ShaderBool = FALSE;
		}
		else if(check.id > 0 && check.id < 2){
			vector3d randVec = vector3d(randf(),randf(),randf());
			normal = findNormal(check,List[check.id - 1], Cur_Eye, Cur_Ray);
//			return 1/LIGHTCONST * (normal + vector3d(1,1,1))/2.0;
			Cur_Eye = Cur_Eye + check.distance*Cur_Ray;
//			return (normalize(normal)+vector3d(1,1,1))*(1.0/LIGHTCONST)*(1.0/2.0);
			switch(List[check.id - 1].bdrf){
				case 1:
					if(randf() > .5)
					absorption = absorption*BDRF1(Cur_Ray,
						 	normal, 
							Normalize(cross(randVec+normal,normal)), 
							check , 
							List[check.id - 1] ,
							lambda);
					else
					absorption = absorption*BDRF1_0(Cur_Ray,
						 	normal, 
							Normalize(cross(randVec+normal,normal)), 
							check , 
							List[check.id - 1] ,
							lambda);										
					break;
				case 2: 
						absorption = absorption*BDRF2(Cur_Ray,
						 	normal, 
							Normalize(cross(randVec+normal,normal)), 
							check , 
							List[check.id - 1] ,
							lambda);
					break;
				case 3:
					absorption = absorption*BDRF3(Cur_Ray,
						 	normal, 
							Normalize(cross(randVec+normal,normal)), 
							check , 
							List[check.id - 1] ,
							lambda);
					break;
				case 4:
					if(randf() > fresnel(normal,Cur_Ray,1.66))
						absorption = absorption*BDRF4(Cur_Ray,
						 	normal, 
							Normalize(cross(randVec+normal,normal)), 
							check , 
							List[check.id - 1] ,
							lambda);
					else
						absorption = absorption*BDRF6(Cur_Ray,
						 	normal, 
							Normalize(cross(randVec+normal,normal)), 
							check , 
							List[check.id - 1] ,
							lambda);						
					break;
				case 5:
					absorption = absorption*BDRF5(Cur_Ray,
							Cur_Eye,
						 	normal, 
							Normalize(cross(randVec+normal,normal)), 
							check , 
							List[check.id - 1] ,
							lambda);
					break;
				case 6:
					absorption = absorption*BDRF6(Cur_Ray,
						 	normal, 
							Normalize(cross(randVec+normal,normal)), 
							check , 
							List[check.id - 1] ,
							lambda);
					break;
				default:
					cout << "Oh noes, we have a non-bdrf\n";
			}


			if(absorption < .01 || count >= 50){
				ShaderBool = FALSE;
				absorption = 0;
			}
		}
		
	}
	
	return LIGHTCONST*colorVec(lambda, absorption);
}


struct AIS{
	vector3d Eye; 
	vector3d direction; 
	BinarySearchTree t; 
	vector3d** imageField; 
	object* List;
	int threadnum;
};

void* Aquire_Img_Field(void * ptr){
	vector3d Eye = ((AIS*) ptr)->Eye;
	vector3d direction = ((AIS*) ptr)->direction;
	BinarySearchTree t = ((AIS*) ptr)->t;
	vector3d** imageField = ((AIS*) ptr)->imageField;
	object* List = ((AIS*) ptr)->List;
	int threadnum = ((AIS*) ptr)->threadnum;
	vector3f Pixel_Ray;

	for(int w = threadnum*100; w < (threadnum+1)*100; w++){
		for(int h = 0; h < HEIGHT; h ++){
			imageField[w][h] = vector3d(0,0,0);
			for(int i = 0; i < SAMPLE_SIZE; i ++){
				Pixel_Ray = FindPR(Eye, direction, w,h,WIDTH,HEIGHT,WIDTH_DIST);
				imageField[w][h] += (Shader(Eye,Pixel_Ray, List, t,w)*(1.0/((double)SAMPLE_SIZE)));
			}
			imageField[w][h] = /*LIGHTCONST*/imageField[w][h];
		if(w%10 == 0 && h%50==0)
			cout << w << " " << h << "\n";
		}
	}

}

double Get_Avg(vector3d ** imageField){
	vector3d AvgVec;
	AvgVec = vector3d(0,0,0);
	for(int i = 0; i < HEIGHT; i ++)
		for(int j = 0; j < WIDTH; j ++)
			AvgVec += imageField[i][j]*1.0/(double)(WIDTH*HEIGHT);
	return (AvgVec[0] + AvgVec[1] + AvgVec[2])/3.0;
}

void Apply_Avg(vector3d** imageField, double Avg){
	for(int i = 0; i < HEIGHT; i ++)
		for(int j = 0; j < WIDTH; j ++)
			imageField[i][j] *= Avg;	
}

double find_max(vector3d** imageField){
	double max = 0;
	for(int i = 0; i < HEIGHT; i ++)
		for(int j = 0; j < WIDTH; j ++)
			if(max < (imageField[i][j][0] + imageField[i][j][1] + imageField[i][j][2])/3.0)	
				max = (imageField[i][j][0] + imageField[i][j][1] + imageField[i][j][2])/3.0;
	return max;
}


void blur(vector3d** imageField){
	double max = 0;
	for(int i = 0; i < HEIGHT; i ++)
		for(int j = 0; j < WIDTH; j ++)
			if(i > 0 && i < HEIGHT - 1 && j > 0 && j < WIDTH - 1)
				imageField[i][j] = (imageField[i-1][j] + imageField[i+1][j] +
							 imageField[i][j+1]+ imageField[i][j-1] + imageField[i][j])/5.0;
}

void rebalance(vector3d** imageField, double max){
	double val = 0;
	for(int i = 0; i < HEIGHT; i ++)
		for(int j = 0; j < WIDTH; j ++){
			val = (imageField[i][j][0] + imageField[i][j][1] + imageField[i][j][2])/3.0;
			imageField[i][j][0] = 2.0*val/(max + val)*imageField[i][j][0];
			imageField[i][j][1] = 2.0*val/(max + val)*imageField[i][j][1];
			imageField[i][j][2] = 2.0*val/(max + val)*imageField[i][j][2];
		}
}

int main(){
	int running = GL_TRUE;
	//image field for the whole computation
	vector3d** imageField;
	pthread_t thread[THREADNUM];
	int ThreadNum[THREADNUM];
	AIS ImgInput[THREADNUM];
	char saves;	
	double AvgApp = 0;


	BinarySearchTree t;

	imageField = new vector3d*[500];
	for(int i = 0; i < 500; i ++)
		imageField[i] = new vector3d[500];

	srand ( time(NULL) );

	#include "../lib/Imgs/Img10.h"

	AccList(t, List1, LENGTH);
//	t.print_inorder();

	init();
	while(running){

	glClear(GL_COLOR_BUFFER_BIT);



	running = !glfwGetKey(GLFW_KEY_ESC) &&
		glfwGetWindowParam(GLFW_OPENED);

	for(int i = 0; i < THREADNUM; i++){
		ImgInput[i].Eye = vector3d(0,0,0);
		ImgInput[i].direction = vector3d(0,0,0);
		ImgInput[i].t = t;
		ImgInput[i].imageField = imageField;
		ImgInput[i].List = List1;
		ImgInput[i].threadnum = i;
//		cout << ImgInput[i].width << "\n";
		ThreadNum[i] = pthread_create( &thread[i], NULL, Aquire_Img_Field, (void*) (&ImgInput[i]));
//		cout << i << "\n";	
	}
	cout << "Waiting for threads\n";
	for(int i = 0; i < THREADNUM; i++){
//		cout << i << "\n";
		pthread_join(thread[i], NULL);
	}
	cout << "All Threads Joined\n";
	AvgApp = 1.0/(2.0*Get_Avg(imageField));
	Apply_Avg(imageField, AvgApp);
//	blur(imageField);
	Apply_Avg(imageField, 100);
//	rebalance(imageField, find_max(imageField));
	cout << AvgApp << "\n";	

	Draw(imageField);
	cout << "should I save this picture?\n";

	cin >> saves;
	if (saves == 'y' || saves == 'Y')
		save("./Test2.jpg");
		save("./Test.jpg");
	}
	Shut_Down(0);
	return 0;
}

