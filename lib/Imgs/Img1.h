#define DIST1 3
#define DIST2 10

#define LENGTH 7
#define SQRTLENGTH 10

	object List1[LENGTH];

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
