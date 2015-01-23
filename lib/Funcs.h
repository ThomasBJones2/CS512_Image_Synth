using namespace cml;

inline double max(double a, double b){
	if(a > b)
		return a;
	return b;
}

inline double min(double a, double b){
	if(a < b)
		return a;
	return b;
}

inline vector3d abs(vector3d in){
	vector3d out = in;
	if(in[0] < 0)
		out[0] = -out[0];
	if(in[1] < 0)
		out[1] = -out[1];
	if(in[2] < 0)	
		out[2] = -out[2];
	return out;
}

inline vector3d Normalize(vector3d in){ return in*(1.0/in.length());}


inline vector3d VectMatrixMult(vector3d in, matrix33d inM){
	vector3d out;
	
	out[0] = in[0]*inM.basis_element(0,0) + in[1]*inM.basis_element(0,1) + in[2]*inM.basis_element(0,2);
	out[1] = in[0]*inM.basis_element(1,0) + in[1]*inM.basis_element(1,1) + in[2]*inM.basis_element(1,2);
	out[2] = in[0]*inM.basis_element(2,0) + in[1]*inM.basis_element(2,1) + in[2]*inM.basis_element(2,2);

	return out;
}

inline double randf(){
	return ((double)rand())/((double)RAND_MAX);
}	

inline double PhongTheta1(){
	double out;
	out = acos(sqrt((1 - randf())));
	return out;
}

inline double PhongTheta(int n){
	double out;
	out = acos(pow((1 - randf()), 1.0/(n+1.0) ));
	return out;
}

inline double clip(double in){
	if (in < 0)
		in = 0;
	return in;
}

inline vector3d clip(vector3d in){
	vector3d out = in;
	if(out[0] < 0)
		out[0] = 0;
	if(out[1] < 0)
		out[1] = 0;
	if(out[2] < 0)
		out[2] = 0;

	return out;
}



inline vector3d colorVec(double lambda, double absorption){
	vector3d out = absorption * vector3d((1.0 - abs(625.0 - lambda)/100.0),
		(1.0 - abs(550.0 - lambda)/100.0),
		(1.0 - abs(475.0 - lambda)/100.0));
	return clip(out);
}

