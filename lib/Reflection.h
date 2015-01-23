inline vector3d reflect(vector3d normal, vector3d Cur_Ray){
	double theta1 = 0; 
	if(dot(normal,Cur_Ray) <=0)
		theta1 = acos(-1.0*dot(normalize(normal),normalize(Cur_Ray)));
	else
		theta1 = acos(dot(normalize(normal),normalize(Cur_Ray)));
	vector3d out;	
		
	vector3d tangent = normalize(cross(normal, Cur_Ray));
	vector3d biNormal = normalize(cross(normal,tangent));

	if(dot(Cur_Ray,biNormal) < 0)
		biNormal = -biNormal;

	if(tangent == vector3d(0,0,0))
		out = Cur_Ray;
	else
		out =  normalize(normalize(normal)*(cos(theta1)) +  biNormal*(sin(theta1)));
	return out;

}

inline double fresnel(vector3d normal, vector3d Cur_Ray, double refConst){
	double theta1 = 0; 
	if(dot(normal,Cur_Ray) <=0)
		theta1 = acos(-1.0*dot(normalize(normal),normalize(Cur_Ray)));
	else
		theta1 = acos(dot(normalize(normal),normalize(Cur_Ray)));
	double theta2 = asin(1.0/refConst*sin(theta1));

	double R_s = (cos(theta1)-refConst*cos(theta2))/(cos(theta1)+refConst*cos(theta2));
	double R_p = (cos(theta2)-refConst*cos(theta1))/(cos(theta2)+refConst*cos(theta1));
	return (R_s*R_s + R_p*R_p)/2.0;
}
