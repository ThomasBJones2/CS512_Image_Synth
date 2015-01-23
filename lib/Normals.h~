
inline vector3d Rect_Normal(vector3d Eye, vector3d Pixel_Ray, vector3d Direction, vector3d BiNormal, vector3d CenterPoint, double Length,
	double width, double height){
	vector2d dist;
	double distances[6];
	bool bound[4];
	int plane=0;
	dist[0] = dist[1] = -100.0;
	bound[0] = bound[1] = bound[2] = bound[3] = FALSE;

	//First get the exclusion
	vector3d Exclusion = cross(Direction,BiNormal);
	Exclusion = Normalize(Exclusion);


	//First, check the planes along the direction

	distances[0]=(Plane_Intersect_Distance(Eye, Pixel_Ray, CenterPoint+Direction*Length, Direction))[0];
	distances[1]=(Plane_Intersect_Distance(Eye, Pixel_Ray, CenterPoint-Direction*Length, Direction))[0];

	distances[2]=(Plane_Intersect_Distance(Eye, Pixel_Ray, CenterPoint+BiNormal*height, BiNormal))[0];
	distances[3]=(Plane_Intersect_Distance(Eye, Pixel_Ray, CenterPoint-BiNormal*height, BiNormal))[0];

	distances[4]=(Plane_Intersect_Distance(Eye, Pixel_Ray, CenterPoint+Exclusion*width, Exclusion))[0];
	distances[5]=(Plane_Intersect_Distance(Eye, Pixel_Ray, CenterPoint-Exclusion*width, Exclusion))[0];

	//Now we find if they are bound inside of the other planes, first we check dist[0]
	
	//first we check the directional planes
	if(distances[0] > 0){
		bound[0] = ((Plane_Intersect_Distance(Pixel_Ray*distances[0]+Eye, BiNormal, CenterPoint+BiNormal*height, BiNormal))[0] > 0);
		bound[1] = ((Plane_Intersect_Distance(Pixel_Ray*distances[0]+Eye,-1*BiNormal, CenterPoint-BiNormal*height, -1*BiNormal))[0] > 0);

		bound[2] = ((Plane_Intersect_Distance(Pixel_Ray*distances[0]+Eye, Exclusion, CenterPoint+Exclusion*width, Exclusion))[0] > 0);
		bound[3] = ((Plane_Intersect_Distance(Pixel_Ray*distances[0]+Eye,-1*Exclusion, CenterPoint-Exclusion*width, -1*Exclusion))[0] > 0);
		if(!bound[0]||!bound[1]||!bound[2]||!bound[3]){
			distances[0] = -100.0;		
		}
	}

	if(distances[1] > 0){
		bound[0] = ((Plane_Intersect_Distance(Pixel_Ray*distances[1]+Eye, BiNormal, CenterPoint+BiNormal*height, BiNormal))[0] > 0);
		bound[1] = ((Plane_Intersect_Distance(Pixel_Ray*distances[1]+Eye,-1*BiNormal, CenterPoint-BiNormal*height, -1*BiNormal))[0] > 0);

		bound[2] = ((Plane_Intersect_Distance(Pixel_Ray*distances[1]+Eye, Exclusion, CenterPoint+Exclusion*width, Exclusion))[0] > 0);
		bound[3] = ((Plane_Intersect_Distance(Pixel_Ray*distances[1]+Eye,-1*Exclusion, CenterPoint-Exclusion*width, -1*Exclusion))[0] > 0);
		if(!bound[0]||!bound[1]||!bound[2]||!bound[3])
			distances[1] = -100.0;
	}

	//Next, the binormal planes
	if(distances[2] > 0){
		bound[0] = ((Plane_Intersect_Distance(Pixel_Ray*distances[2]+Eye, Direction, CenterPoint+Direction*Length, Direction))[0] > 0);
		bound[1] = ((Plane_Intersect_Distance(Pixel_Ray*distances[2]+Eye,-1*Direction, CenterPoint-Direction*Length, -1*Direction))[0] > 0);

		bound[2] = ((Plane_Intersect_Distance(Pixel_Ray*distances[2]+Eye, Exclusion, CenterPoint+Exclusion*width, Exclusion))[0] > 0);
		bound[3] = ((Plane_Intersect_Distance(Pixel_Ray*distances[2]+Eye,-1*Exclusion, CenterPoint-Exclusion*width, -1*Exclusion))[0] > 0);
		if(!bound[0]||!bound[1]||!bound[2]||!bound[3])
			distances[2] = -100.0;
	}

	if(distances[3] > 0){
		bound[0] = ((Plane_Intersect_Distance(Pixel_Ray*distances[3]+Eye, Direction, CenterPoint+Direction*Length, Direction))[0] > 0);
		bound[1] = ((Plane_Intersect_Distance(Pixel_Ray*distances[3]+Eye,-1*Direction, CenterPoint-Direction*Length, -1*Direction))[0] > 0);

		bound[2] = ((Plane_Intersect_Distance(Pixel_Ray*distances[3]+Eye, Exclusion, CenterPoint+Exclusion*width, Exclusion))[0] > 0);
		bound[3] = ((Plane_Intersect_Distance(Pixel_Ray*distances[3]+Eye,-1*Exclusion, CenterPoint-Exclusion*width, -1*Exclusion))[0] > 0);
		if(!bound[0]||!bound[1]||!bound[2]||!bound[3])
			distances[3] = -100.0;
	}

	//Lastly, we check the exclusionary planes
	if(distances[4] > 0){
		bound[0] = ((Plane_Intersect_Distance(Pixel_Ray*distances[4]+Eye, BiNormal, CenterPoint+BiNormal*height, BiNormal))[0] > 0);
		bound[1] = ((Plane_Intersect_Distance(Pixel_Ray*distances[4]+Eye,-1*BiNormal, CenterPoint-BiNormal*height, -1*BiNormal))[0] > 0);

		bound[2] = ((Plane_Intersect_Distance(Pixel_Ray*distances[4]+Eye, Direction, CenterPoint+Direction*Length, Direction))[0] > 0);
		bound[3] = ((Plane_Intersect_Distance(Pixel_Ray*distances[4]+Eye,-1*Direction, CenterPoint-Direction*Length, -1*Direction))[0] > 0);
		if(!bound[0]||!bound[1]||!bound[2]||!bound[3])
			distances[4] = -100.0;
	}

	if(distances[5] > 0){
		bound[0] = ((Plane_Intersect_Distance(Pixel_Ray*distances[5]+Eye, BiNormal, CenterPoint+BiNormal*height, BiNormal))[0] > 0);
		bound[1] = ((Plane_Intersect_Distance(Pixel_Ray*distances[5]+Eye,-1*BiNormal, CenterPoint-BiNormal*height, -1*BiNormal))[0] > 0);

		bound[2] = ((Plane_Intersect_Distance(Pixel_Ray*distances[5]+Eye, Direction, CenterPoint+Direction*Length, Direction))[0] > 0);
		bound[3] = ((Plane_Intersect_Distance(Pixel_Ray*distances[5]+Eye,-1*Direction, CenterPoint-Direction*Length, -1*Direction))[0] > 0);
		if(!bound[0]||!bound[1]||!bound[2]||!bound[3])
			distances[5] = -100.0;
	}

	for(int i = 0; i < 6; i++){
		if(dist[0] < 0 && distances[i] > 0){
			dist[0] = distances[i];
			plane = i;
		}
		if(dist[0] > distances[i] && distances[i] > 0){
			dist[0] = distances[i];
			plane = i;
		}
	}

	vector3d NormalRet;

	switch(plane){
		case 0: 
			NormalRet = Direction;
			break;	
		case 1: 
			NormalRet = -1.0*Direction;
			break;
		case 2: 
			NormalRet = BiNormal;
			break;
		case 3: 
			NormalRet = -1.0*BiNormal;
			break;
		case 4: 
			NormalRet = Exclusion;
			break;
		case 5: 
			NormalRet = -1.0*Exclusion;
			break;
	}

	return NormalRet;
}


//This finds the normal of an object...
inline vector3d findNormal(dis_id check,object inobject, vector3d Cur_Eye, vector3d Cur_Ray){
	vector3d centerToPoint = (Cur_Eye+check.distance*Cur_Ray) - inobject.center;
	vector3d biNormal = cross(inobject.direction,centerToPoint);
	double checker;
	double epsilon = .01;
	vector3d EllipsDerx = vector3d(1,1,1);
	vector3d EllipsDery = vector3d(1,1,1);
	double EllipsDerX1Dist = 0;
	double EllipsDerX2Dist = 0;
	double EllipsDerY1Dist = 0;
	double EllipsDerY2Dist = 0;
	vector3d normal;

	switch (inobject.type) {
  		case SPHERE:
			return Normalize(centerToPoint); 
    			break;
 		case CONE:
			checker = dot(normalize((check.distance*Cur_Ray + Cur_Eye - inobject.center)),normalize(inobject.direction));
			if (checker <= -1/sqrt(1+inobject.radius*inobject.radius) - epsilon)
				return -inobject.direction;
			if (checker >= 1/sqrt(1+inobject.radius*inobject.radius) + epsilon)
				return inobject.direction;
		
			if(dot(Cur_Ray, cross(biNormal,centerToPoint)) > 0)
				return -1.0*Normalize(cross(biNormal,centerToPoint));
			else
				return Normalize(cross(biNormal,centerToPoint));
    			break;
		case CYLINDER:
			checker = dot(normalize((check.distance*Cur_Ray + Cur_Eye - inobject.center)),normalize(inobject.direction));
			if (checker < -inobject.length/sqrt(inobject.length*inobject.length+inobject.radius*inobject.radius))
			{		
				return -inobject.direction;
			}			
			if (checker > inobject.length/sqrt(inobject.length*inobject.length+inobject.radius*inobject.radius)){
				return inobject.direction;
			}
			if(dot(Cur_Ray, cross(biNormal,inobject.direction)) > 0)
				return -1.0*Normalize(cross(biNormal,inobject.direction));
			else
				return Normalize(cross(biNormal,inobject.direction));			   
 			break;
 		case RECT:
			return Normalize(Rect_Normal(Cur_Eye, 
				Cur_Ray, inobject.direction, 
				inobject.biNormal, inobject.center, 					inobject.length, inobject.width,
				inobject.height));
    			break;
 		case ELLIPS:

			EllipsDerX1Dist = Ellips_Intersect_Distance(inobject.center, 
				normalize(centerToPoint + vector3d(.01,0,0)), inobject.col1,
				inobject.col2, inobject.col3, inobject.center)[1];

			EllipsDerX2Dist = Ellips_Intersect_Distance(inobject.center, 
				normalize(centerToPoint + vector3d(-.01,0,0)), inobject.col1,
				inobject.col2, inobject.col3, inobject.center)[1];

			EllipsDerY1Dist = Ellips_Intersect_Distance(inobject.center, 
				normalize(centerToPoint + vector3d(0,.01,0)), inobject.col1,
				inobject.col2, inobject.col3, inobject.center)[1];

			EllipsDerY2Dist = Ellips_Intersect_Distance(inobject.center, 
				normalize(centerToPoint + vector3d(0,-.01,0)), inobject.col1,
				inobject.col2, inobject.col3, inobject.center)[1];

			if(EllipsDerX1Dist <= -50.0 || EllipsDerX2Dist <= -50.0)
				return vector3d(1,0,0);
			else{	
				EllipsDerx = (EllipsDerX1Dist*normalize(centerToPoint + vector3d(.01,0,0)) + inobject.center) -
						(EllipsDerX2Dist*normalize(centerToPoint + vector3d(-.01,0,0)) + inobject.center);

			}
			if(EllipsDerY1Dist <= -50.0 || EllipsDerY2Dist <= -50.0)
				return vector3d(0,1,0);
			else{
				EllipsDery = (EllipsDerY1Dist*normalize(centerToPoint + vector3d(0,.01,0)) + inobject.center) -
						(EllipsDerY2Dist*normalize(centerToPoint + vector3d(0,-.01,0)) + inobject.center);

			}
 		
			normal = normalize(cross(EllipsDerx,EllipsDery));
			if(dot(centerToPoint,normal) < 0)
				normal = -normal;

			return normal;
    			break;
 		case TRI:
			if(dot(Cur_Ray,cross(inobject.pt1 - inobject.pt2, inobject.pt2 - inobject.pt3))>0){			
				return -1.0*Normalize(cross(inobject.pt1 - inobject.pt2, inobject.pt2 - inobject.pt3));		
			}
			else{
				return Normalize(cross(inobject.pt1 - inobject.pt2, inobject.pt2 - inobject.pt3));
			}
    			break;
		default:
			cout << "ERRROR WILL ROBINSON! AGAIN!\n\n";
			return vector3d(0,0,1);
	}

}
