double BDRF1(vector3d& Out_Ray, vector3d normal, vector3d biNormal, dis_id check, object Listobject, double lambda){
	//Here I will have to expand this to allow multiple BRDFS, but right now its okay to have just 1 (I think)...
//	double theta,phi;
	double outtheta,outphi;
	double absorption=.99;
	matrix33d phiMat,thetaMat;

	outtheta = PhongTheta1();
	outphi = randf()*PI*2;
	matrix_rotation_axis_angle(phiMat, normal, outphi);
	matrix_rotation_axis_angle(thetaMat, biNormal, outtheta);

	Out_Ray = VectMatrixMult(normal,thetaMat);	
	Out_Ray = VectMatrixMult(Out_Ray, phiMat);
	Out_Ray = normalize(Out_Ray);
	return absorption;
}

double BDRF1_0(vector3d& Out_Ray, vector3d normal, vector3d biNormal, dis_id check, object Listobject, double lambda){
//	double theta,phi;
	double outtheta,outphi;
	vector3d biNormal2;
	
	double absorption=.99;


	Out_Ray = reflect(normal, Out_Ray);
	biNormal2 = normalize(cross(Out_Ray,normal));

	matrix33d phiMat,thetaMat;
	outtheta = PhongTheta(100);
	outphi = randf()*PI*2;

	matrix_rotation_axis_angle(phiMat, Out_Ray, outphi);
	matrix_rotation_axis_angle(thetaMat, biNormal2, outtheta);

	Out_Ray = VectMatrixMult(Out_Ray,thetaMat);	
	Out_Ray = VectMatrixMult(Out_Ray, phiMat);
	Out_Ray = normalize(Out_Ray);
	return min(absorption,.99);
}

double BDRF2(vector3d& Out_Ray, vector3d normal, vector3d biNormal, dis_id check, object Listobject, double lambda){
	//Here I will have to expand this to allow multiple BRDFS, but right now its okay to have just 1 (I think)...
//	double theta,phi;
	double outtheta,outphi;
	
	double absorption=.49*clip(1.0 - abs(550.0 - lambda)/75.0) +.5;
	matrix33d phiMat,thetaMat;

	outtheta = PhongTheta1();
	outphi = randf()*PI*2;

	matrix_rotation_axis_angle(phiMat, normal, outphi);
	matrix_rotation_axis_angle(thetaMat, biNormal, outtheta);

	Out_Ray = VectMatrixMult(normal,thetaMat);	
	Out_Ray = VectMatrixMult(Out_Ray, phiMat);
	Out_Ray = normalize(Out_Ray);
	return min(absorption,.99);
}


double BDRF2_0(vector3d& Out_Ray, vector3d normal, vector3d biNormal, dis_id check, object Listobject, double lambda){
//	double theta,phi;
	double outtheta,outphi;
	vector3d biNormal2;
	
	double absorption=.49*clip(1.0 - abs(550.0 - lambda)/75.0) +.5;


	Out_Ray = reflect(normal, Out_Ray);
	biNormal2 = normalize(cross(Out_Ray,normal));

	matrix33d phiMat,thetaMat;
	outtheta = PhongTheta(100);
	outphi = randf()*PI*2;

	matrix_rotation_axis_angle(phiMat, Out_Ray, outphi);
	matrix_rotation_axis_angle(thetaMat, biNormal2, outtheta);

	Out_Ray = VectMatrixMult(Out_Ray,thetaMat);	
	Out_Ray = VectMatrixMult(Out_Ray, phiMat);
	Out_Ray = normalize(Out_Ray);
	return min(absorption,.99);
}

//This is the redish wavelenth I believe. 
double BDRF3(vector3d& Out_Ray, vector3d normal, vector3d biNormal, dis_id check, object Listobject, double lambda){
	//Here I will have to expand this to allow multiple BRDFS, but right now its okay to have just 1 (I think)...
//	double theta,phi;
	double outtheta,outphi;
	double absorption=.49*clip(1.0 - abs(625.0 - lambda)/75.0) +.5;
	matrix33d phiMat,thetaMat;
	
	outtheta = PhongTheta1();
	outphi = randf()*PI*2;

	matrix_rotation_axis_angle(phiMat, normal, outphi);
	matrix_rotation_axis_angle(thetaMat, biNormal, outtheta);

	Out_Ray = VectMatrixMult(normal,thetaMat);	
	Out_Ray = VectMatrixMult(Out_Ray, phiMat);
	Out_Ray = normalize(Out_Ray);
	return min(absorption,.99);
}

double BDRF4(vector3d& Out_Ray, vector3d normal, vector3d biNormal, dis_id check, object Listobject, double lambda){
	//Here I will have to expand this to allow multiple BRDFS, but right now its okay to have just 1 (I think)...
//	double theta,phi;
	double outtheta,outphi;
	double absorption=.49*clip(1.0 - abs(475.0 - lambda)/75.0) +.5;
	matrix33d phiMat,thetaMat;
	
	outtheta = PhongTheta1();
	outphi = randf()*PI*2;

	matrix_rotation_axis_angle(phiMat, normal, outphi);
	matrix_rotation_axis_angle(thetaMat, biNormal, outtheta);

	Out_Ray = VectMatrixMult(normal,thetaMat);	
	Out_Ray = VectMatrixMult(Out_Ray, phiMat);
	Out_Ray = normalize(Out_Ray);
	return min(absorption,.99);
}

//This is the refraction 'bdrf' function which handles all refraction calculations
double BDRF5(vector3d& Out_Ray, vector3d& Out_Eye, vector3d normal, vector3d biNormal, dis_id check, object Listobject, double lambda){
	vector3d RefRay = vector3d(0,0,0);
	vector3d RefEye,OSEye=vector3d(0,0,0);
	vector3d RefNormal = vector3d(0,0,0);
	double absorption = 0;
	double RefDist = 0;
	bool RefCheck;
	RefCheck = TRUE;
	int count = 0;
	double refDistCount=0;
	if(randf() > fresnel(normal, Out_Ray, Listobject.refConst)){

		RefRay = Ref_Ray(normal, Out_Ray, Listobject.refConst); //Get a refracted ray
		RefEye = Out_Eye; //Reset the Reference eye to be right next to the object

		while(RefCheck){
			count ++;
			switch(Listobject.type){
				case SPHERE:		
					RefDist = Ref_Sphere_Intersect_Distance(RefEye, 
						RefRay, 
						Listobject.center, 
						Listobject.radius)[1];
					break;
				case RECT:
					RefDist = Ref_Rect_Intersect_Distance(RefEye, 
						RefRay, 
						Listobject.direction, 
						Listobject.biNormal,
						Listobject.center,
						Listobject.length,
						Listobject.width,
						Listobject.height)[1];
					break;
				case CYLINDER:
					RefDist = Ref_Cylindar_Intersect_Distance(RefEye, 
						RefRay, 
						Listobject.direction, 
						Listobject.center,
						Listobject.radius,
						Listobject.length)[0];
					break;
				case ELLIPS:
					RefDist = Ref_Ellips_Intersect_Distance(RefEye, 
						RefRay, 
						Listobject.col1,
						Listobject.col2,
						Listobject.col3,
						Listobject.center)[0];
					break;
				case CONE:
					RefDist = Ref_Cone_Intersect_Distance(RefEye, 
						RefRay, 
						Listobject.direction, 
						Listobject.center,
						Listobject.radius,
						Listobject.length)[1];
					break;
				default:
					break;

			}

//			return (normalize(RefRay)+vector3d(1,1,1))*(1.0/LIGHTCONST)*(1.0/2.0);
//			if(RefDist <= -50)
//				return vector3d(1.0/LIGHTCONST,0,0);
//			return (RefDist*vector3d(1,1,1))*(1.0/LIGHTCONST)*(1.0/10.0);

			refDistCount += RefDist;
			//good up to this point...
			check.distance = 10.0;//change distance to 10 in order to find normal on other side of object
			OSEye = RefEye + (RefDist + check.distance)*RefRay; //Move the reference eye to the opposite side of the object
			//and add 10 more points distant...
			RefNormal = findNormal(check,Listobject, OSEye, -1.0*RefRay);
			//Find the normal at the other side (this involves inverting the RefRay).

			RefEye = RefEye + RefDist*RefRay;
			if(randf() > fresnel(RefNormal, RefRay, 1.0/Listobject.refConst))
				RefRay = Ref_Ray(-RefNormal,RefRay,1.0/Listobject.refConst);
			else
				RefRay = reflect(-RefNormal, RefRay);

			RefCheck = (dot(normalize(RefRay),normalize(RefNormal)) < 0) && !(count >= 10);

		}


		Out_Ray = RefRay;
		Out_Eye = RefEye;

		absorption = pow(.99,refDistCount);


		if(count >= 10)
			absorption = 0;
	}
	else{
		Out_Ray = reflect(normal,Out_Ray);	
		absorption = .99;	
	}
//	return vector3d(1,1,1)*1.0/LIGHTCONST;
	return absorption;
}


double BDRF6(vector3d& Out_Ray, vector3d normal, vector3d biNormal, dis_id check, object Listobject, double lambda){
	//Here I will have to expand this to allow multiple BRDFS, but right now its okay to have just 1 (I think)...
//	double theta,phi;
	double absorption=.99;

	Out_Ray = reflect(normal, Out_Ray);	
	return absorption;
}

