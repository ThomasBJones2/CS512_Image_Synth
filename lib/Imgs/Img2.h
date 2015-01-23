#define DIST1 3
#define DIST2 10

#define LENGTH 7
#define SQRTLENGTH 10

	object List1[LENGTH];


	for(int i = 0; i < SQRTLENGTH; i ++){
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
	}
