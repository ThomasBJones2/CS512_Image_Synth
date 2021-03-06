
using namespace std;

enum ObjType{SPHERE, CONE, CYLINDER, RECT, ELLIPS, TRI, BB};

class object{
	public:
		//Used by all objects
		ObjType type;	
		int id;
		vector3d center;
		vector3d direction;

		//Used to predict if a collision might occure
        	vector3d FCorner;
		vector3d BCorner;

		//Used by Ellipsoid
		vector3d col1;
		vector3d col2;
		vector3d col3;

		//Used by Sphere, Cone, Cylinder
		double radius;
	

		//Used by Cone, Cylinder, Box
		double length;
		
		//Used by Box
		vector3d biNormal;
		double width;	
		double height;

		//used by triangle
		vector3d pt1;	
		vector3d pt2;
		vector3d pt3;

		bool luminar;

		int bdrf;
		double refConst;

		object& operator=(const object &rhs);
		friend ostream& operator<<(std::ostream &out, const object &rhs);
};

object& object::operator=(const object &rhs){
		if(this == &rhs)
			return *this;
		
		//Used by all objects
		type = rhs.type;
		id = rhs.id;	
		center = rhs.center;	
		direction = rhs.direction;	

		//Used to predict if a collision might occure
        	FCorner = rhs.FCorner;	
		BCorner = rhs.BCorner;	

		//Used by Ellipsoid
		col1 = rhs.col1;	
		col2 = rhs.col2;	
		col3 = rhs.col3;	

		//Used by Sphere, Cone, Cylinder
		radius = rhs.radius;	
	

		//Used by Cone, Cylinder, Box
		length = rhs.length;	
		
		//Used by Box
		biNormal = rhs.biNormal;	
		width = rhs.width;		
		height = rhs.height;	

		//used by triangle
		pt1 = rhs.pt1;		
		pt2 = rhs.pt2;	
		pt3 = rhs.pt3;	

		//This is a luminar boolean
		luminar = rhs.luminar;
		
		//This is the BRDF number
		bdrf = rhs.bdrf;

		//This is the referance constant
		refConst = rhs.refConst;
		
		return *this;
}

ostream& operator<<(std::ostream &out, const object &rhs){
			//Used by all objects
			out << "type: " << rhs.type << "\n";
			out << "ID: " << rhs.id << "\n";
			out << "center: " << rhs.center << "\n";
			out << "direction: " << rhs.direction << "\n";

			//Used to predict if a collision might occure
	        	out << "FCorner: " << rhs.FCorner << "\n";
			out << "BCorner: " << rhs.BCorner << "\n";
			out << "BDRF: " << rhs.bdrf << "\n";
			out << "refConst: " << rhs.refConst << "\n";

			if(rhs.type == ELLIPS){
				out << "col1: " << rhs.col1 << "\n";	
				out << "col2: " << rhs.col2 << "\n";
				out << "col3: " << rhs.col3 << "\n";	
			}


			if (rhs.type == SPHERE || rhs.type == CONE || rhs.type == CYLINDER)
				out << "radius: " << rhs.radius << "\n";
	

			if (rhs.type == RECT || rhs.type == CONE || rhs.type == CYLINDER)
				out << "normal: " << rhs.direction << "\n";
				out << "length: " << rhs.length << "\n";
		
			if(rhs.type == RECT){
				out << "biNormal: " << rhs.biNormal << "\n";	
				out << "width: " << rhs.width << "\n";
				out << "height: " << rhs.height << "\n";
			}

			if(rhs.type == TRI){
				out << "pt1: " << rhs.pt1 << "\n";	
				out << "pt2: " << rhs.pt2 << "\n";
				out << "pt3: " << rhs.pt3 << "\n";
			}
			if(rhs.bdrf == 5){
				out << "light constant: " << rhs.refConst << "\n";
				
			}
	out << "\n";

	return out;
}

class dis_id{
	public:
		int id;
		double distance;
		dis_id& operator=(const dis_id &rhs){id = rhs.id; distance = rhs.distance; return *this;};
};

inline double CheckLocalObj(object inobject, vector3d Eye, vector3d Pixel_Ray){
	vector2d distance = vector2d(-100,-100);
	if(inobject.type == SPHERE){
		distance = Sphere_Intersect_Distance(Eye, Pixel_Ray, inobject.center, inobject.radius);
	}
	if(inobject.type == CONE){
		distance = Cone_Intersect_Distance(Eye, Pixel_Ray, Normalize(inobject.direction), inobject.center, inobject.radius, inobject.length);
	}
	if(inobject.type == CYLINDER){
		distance = Cylindar_Intersect_Distance(Eye, Pixel_Ray, Normalize(inobject.direction), inobject.center,  
			inobject.radius, inobject.length);
	}
	if(inobject.type == ELLIPS){
		distance = Ellips_Intersect_Distance(Eye, Pixel_Ray, inobject.col1,
		inobject.col2, inobject.col3, inobject.center);
	}
	if(inobject.type == RECT){
		distance = Rect_Intersect_Distance(Eye, Pixel_Ray, Normalize(inobject.direction), Normalize(inobject.biNormal), 
			inobject.center, inobject.length, inobject.width, inobject.height);

	}
	if(inobject.type == TRI){
		distance = Tri_Intersect_Distance(Eye, Pixel_Ray, inobject.pt1, inobject.pt2, inobject.pt3);
	}

	return distance[0];
}
