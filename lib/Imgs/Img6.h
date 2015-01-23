#define LENGTH 27
#define CHECKBOARD 16


	object List1[LENGTH];

	List1[0].id = 1;
	List1[0].type = RECT;
	List1[0].center[0] = 0;
	List1[0].center[1] = 0;
	List1[0].center[2] = 30;
	List1[0].direction = normalize(vector3d(1,0,0));
	List1[0].biNormal = normalize(cross(vector3d(0,1,1),vector3d(1,0,0)));
	List1[0].height = 4;
	List1[0].length = 4;
	List1[0].width = .5; 
	List1[0].bdrf = 6;
	List1[0].luminar = FALSE;

	List1[1].id = 2;
	List1[1].type = RECT;
	List1[1].center[0] = 0;
	List1[1].center[1] = 14.8;
	List1[1].center[2] = 30;
	List1[1].direction = vector3d(1,0,0);
	List1[1].biNormal = vector3d(0,0,1);
	List1[1].height = 10;
	List1[1].length = 10;
	List1[1].width = .5; 
	List1[1].bdrf = 1;
	List1[1].luminar = TRUE;

	List1[2].id = 3;
	List1[2].type = RECT;
	List1[2].center[0] = -15;
	List1[2].center[1] = 0;
	List1[2].center[2] = 0;
	List1[2].direction = vector3d(0,1,0);
	List1[2].biNormal = vector3d(0,0,1);
	List1[2].height = 50;
	List1[2].length = 50;
	List1[2].width = .5; 
	List1[2].bdrf = 2;
	List1[2].luminar = FALSE;


	List1[3].id = 4;
	List1[3].type = RECT;
	List1[3].center[0] = 15;
	List1[3].center[1] = 0;
	List1[3].center[2] = 0;
	List1[3].direction = vector3d(0,1,0);
	List1[3].biNormal = vector3d(0,0,1);
	List1[3].height = 50;
	List1[3].length = 50;
	List1[3].width = .5; 
	List1[3].bdrf = 3;
	List1[3].luminar = FALSE;


	List1[4].id = 5;
	List1[4].type = RECT;
	List1[4].center[0] = 0;
	List1[4].center[1] = -15;
	List1[4].center[2] = 0;
	List1[4].direction = vector3d(1,0,0);
	List1[4].biNormal = vector3d(0,0,1);
	List1[4].height = 50;
	List1[4].length = 50;
	List1[4].width = .5; 
	List1[4].bdrf = 4;
	List1[4].luminar = FALSE;


	List1[5].id = 6;
	List1[5].type = RECT;
	List1[5].center[0] = 0;
	List1[5].center[1] = 15;
	List1[5].center[2] = 0;
	List1[5].direction = vector3d(1,0,0);
	List1[5].biNormal = vector3d(0,0,1);
	List1[5].height = 50;
	List1[5].length = 50;
	List1[5].width = .5; 
	List1[5].bdrf = 1;
	List1[5].luminar = FALSE;


	for(int i = 0; i < CHECKBOARD; i ++){
		List1[6+i].id = 7+i;
		List1[6+i].type = RECT;
		List1[6+i].center[0] = -25.0*.60+(i/4)*12.5*.75;
		List1[6+i].center[1] = -25.0*.60+(i%4)*12.5*.75;
		List1[6+i].center[2] = 40;
		List1[6+i].direction = vector3d(0,1,0);
		List1[6+i].biNormal = vector3d(1,0,0);
		List1[6+i].height = 6.25*.75;
		List1[6+i].length = 6.25*.75;
		List1[6+i].width = .5; 
		List1[6+i].bdrf = (i%4+i/4)%4 + 1;
		List1[6+i].luminar = FALSE;
	}


	List1[22].id = 23;
	List1[22].type = SPHERE;
	List1[22].center[0] = -10;
	List1[22].center[1] = -10;
	List1[22].center[2] = 30;
	List1[22].radius = 5;
	List1[22].direction = vector3d(0,0,1);
	List1[22].col1 = vector3d(.25,0,0);
	List1[22].col2 = vector3d(0,.1,0);
	List1[22].col3 = vector3d(0,0,.25);
	List1[22].bdrf = 6;
	List1[22].luminar = FALSE;
	List1[22].refConst = 1.5;

	List1[23].id = 24;
	List1[23].type = RECT;
	List1[23].center[0] = 0;
	List1[23].center[1] = 0;
	List1[23].center[2] = -10;
	List1[23].direction = vector3d(0,1,0);
	List1[23].biNormal = vector3d(1,0,0);
	List1[23].height = 50;
	List1[23].length = 50;
	List1[23].width = .5; 
	List1[23].bdrf = 2;
	List1[23].luminar = FALSE;

	List1[24].id = 25;
	List1[24].type = ELLIPS;
	List1[24].center[0] = 10;
	List1[24].center[1] = -10;
	List1[24].center[2] = 30;
	List1[24].radius = 5;
	List1[24].direction = vector3d(0,0,1);
	List1[24].col1 = vector3d(.25,0,0);
	List1[24].col2 = vector3d(0,.1,0);
	List1[24].col3 = vector3d(0,0,.25);
	List1[24].bdrf = 6;
	List1[24].luminar = FALSE;
	List1[24].refConst = 1.5;


	List1[25].id = 26;
	List1[25].type = CONE;
	List1[25].center[0] = -8;
	List1[25].center[1] = 9;
	List1[25].center[2] = 30;
	List1[25].radius = 1;
	List1[25].direction = normalize(vector3d(1,1,1));
	List1[25].length = 3;
	List1[25].bdrf = 6;
	List1[25].luminar = FALSE;
	List1[25].refConst = 1.5;

	List1[26].id = 27;
	List1[26].type = CYLINDER;
	List1[26].center[0] = 8;
	List1[26].center[1] = 8;
	List1[26].center[2] = 30;
	List1[26].radius = 1.5;
	List1[26].length = 5;
	List1[26].direction = normalize(vector3d(1,1,1));
	List1[26].bdrf = 6;
	List1[26].luminar = FALSE;
	List1[26].refConst = 1.5;




