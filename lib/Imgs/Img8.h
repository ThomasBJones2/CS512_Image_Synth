#define LENGTH 1
#define CHECKBOARD 16


	object List1[LENGTH];

	List1[0].id = 1;
	List1[0].type = RECT;
	List1[0].center[0] = 0;
	List1[0].center[1] = 0;
	List1[0].center[2] = 30;
	List1[0].direction = normalize(vector3d(1,1,0));
	List1[0].biNormal = normalize(cross(vector3d(0,1,1),vector3d(1,1,0)));
	List1[0].height = 4;
	List1[0].length = 4;
	List1[0].width = 2; 
	List1[0].bdrf = 1;
	List1[0].luminar = FALSE;
	List1[0].refConst = 1.5;






