inline vector2d Ref_Sphere_Intersect_Distance(vector3d Eye, vector3d Pixel_Ray, vector3d Center, float Radius){
	vector2d dist;
	double a,b,c;
	double Sqrt_Val;
	
	a = 1.0;
	b = 2*(dot(Pixel_Ray,Eye)- dot(Pixel_Ray, Center));
	c = dot(Eye,Eye)- 2* dot(Eye,Center) + dot(Center, Center) - Radius*Radius;
	
	Sqrt_Val = b*b - 4*a*c;
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

inline vector2d Ref_Ellips_Intersect_Distance(vector3d Eye, vector3d Pixel_Ray, vector3d Col0, vector3d Col1, vector3d Col2, vector3d CenterPoint){
	vector2d dist;
	vector3d tempRay;
	vector3d NewEye;
	vector3d NewRay = -Pixel_Ray;
	double BoundLength = 0;
	object NewObj;
	NewObj.col1 = Col0;
	NewObj.col2 = Col1;
	NewObj.col3 = Col2;
	NewObj.center = CenterPoint;
	NewObj.type = ELLIPS;

	Bound(&NewObj);

	BoundLength = (NewObj.FCorner - NewObj.BCorner).length();

	tempRay = normalize(Pixel_Ray);
	NewEye = Eye + tempRay*BoundLength;
	dist = Ellips_Intersect_Distance(NewEye, NewRay, Col0, Col1,Col2,CenterPoint);

	dist[0] = BoundLength - dist[0]; 
	return dist;

}

inline vector2d Ref_Cone_Intersect_Distance(vector3d Eye, vector3d Pixel_Ray, vector3d Direction, vector3d CenterPoint,  double Radius, double Length){
	vector2d dist;
	/*vector3d tempRay;
	vector3d NewEye;
	vector3d NewRay = -Pixel_Ray;
	
	tempRay = normalize(Pixel_Ray);
	NewEye = Eye + tempRay*Length*Radius*Radius*8.0;*/
	//dist = Cone_Intersect_Distance(NewEye, NewRay, Direction, CenterPoint,  Radius, Length);
	dist = Cone_Intersect_Distance(Eye,Pixel_Ray,Direction,CenterPoint,Radius,Length);
	
	/*dist[0] = Length*Radius*Radius*8.0 - dist[0]; */
	return dist;
}

inline vector2d Ref_Cylindar_Intersect_Distance(vector3d Eye, vector3d Pixel_Ray, vector3d Direction, vector3d CenterPoint,  double Radius, double Length){
	vector2d dist;
	vector3d tempRay;
	vector3d NewEye;
	vector3d NewRay = -Pixel_Ray;
	
	tempRay = normalize(Pixel_Ray);
	NewEye = Eye + tempRay*Length*Radius*Radius*8.0;
	dist = Cylindar_Intersect_Distance(NewEye, NewRay, Direction, CenterPoint,  Radius, Length);

	dist[0] = Length*Radius*Radius*8.0 - dist[0]; 
	return dist;
}


inline vector2d Ref_Rect_Intersect_Distance(vector3d Eye, vector3d Pixel_Ray, vector3d Direction, vector3d BiNormal, vector3d CenterPoint, double Length,
	double width, double height){
	vector2d dist;
/*	vector3d tempRay;
	vector3d NewEye;
	vector3d NewRay = -Pixel_Ray;

	tempRay = normalize(Pixel_Ray);
	NewEye = Eye + tempRay*(sqrt(4.0*Length*Length + 4.0*width*width + 4.0*height*height)+10);
	dist = Rect_Intersect_Distance(NewEye,NewRay, Direction,BiNormal, CenterPoint, Length, width, height);
	dist[0] = (sqrt(4.0*Length*Length + 4.0*width*width + 4.0*height*height)+10) - dist[0]; */

	dist = Rect_Intersect_Distance(Eye,Pixel_Ray, Direction,BiNormal, CenterPoint, Length, width, height);

	return dist;
}


inline vector3d Ref_Ray(vector3d normal, vector3d Cur_Ray, double refConst){
	double theta1 = 0; 
//	if(dot(normal,Cur_Ray) <=0)
		theta1 = acos(dot(normalize(normal),normalize(Cur_Ray)));
//	else
//		theta1 = acos(dot(normalize(normal),normalize(Cur_Ray)));
	double theta2 = asin(1.0/refConst*sin(theta1));
	vector3d out;	
		
	vector3d tangent = normalize(cross(normal, Cur_Ray));
	vector3d biNormal = normalize(cross(normal,tangent));

	if(dot(Cur_Ray,biNormal) < 0)
		biNormal = -biNormal;

	if(tangent == vector3d(0,0,0)){
		out = Cur_Ray;
	}
	else
		out =  normalize(normalize(normal)*-1.0*(cos(theta2)) +  biNormal*(sin(theta2)));
	return out;

}


