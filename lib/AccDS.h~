#include "./Obj.h"
#include "./BTree.h"


void Bound(object* inobject){
			double x,y,z;
			double dim[3];	
			double max_eig_val2 = 0;
			dim[0]=dim[1]=dim[2]=1.0;
			x = y = z = 0;
			double Trix[2],Triy[2],Triz[2];
			Trix[0] = max((inobject->pt1)[0], max((inobject->pt2)[0],(inobject->pt3)[0]));
			Triy[0] = max((inobject->pt1)[1], max((inobject->pt2)[1],(inobject->pt3)[1]));
			Triz[0] = max((inobject->pt1)[2], max((inobject->pt2)[2],(inobject->pt3)[2]));

			Trix[1] = min((inobject->pt1)[0], min((inobject->pt2)[0],(inobject->pt3)[0]));
			Triy[1] = min((inobject->pt1)[1], min((inobject->pt2)[1],(inobject->pt3)[1]));
			Triz[1] = min((inobject->pt1)[2], min((inobject->pt2)[2],(inobject->pt3)[2]));


			matrix33d A;
			A.set((inobject->col1)[0],(inobject->col2)[0], (inobject->col3)[0], 
				(inobject->col1)[1],(inobject->col2)[1], (inobject->col3)[1], 
				(inobject->col1)[2],(inobject->col2)[2], (inobject->col3)[2]
			);
			vector3d binorm2, dir2;
			binorm2 = abs(inobject->biNormal);
			dir2 = abs(inobject->direction);
			vector3d adder = (inobject->length)*Normalize(dir2) + 
				Normalize(binorm2)*(inobject->height) + 
				vector3d(1,1,1)*(inobject->width);
	switch (inobject->type) {
  		case SPHERE:
        		inobject->FCorner=vector3d((inobject->center)[0]+(inobject->radius),
				(inobject->center)[1]+(inobject->radius),(inobject->center)[2]+(inobject->radius));
			inobject->BCorner=vector3d((inobject->center)[0]-(inobject->radius),
				(inobject->center)[1]-(inobject->radius),(inobject->center)[2]-(inobject->radius));
    			break;
 		case CONE:
        		inobject->FCorner=vector3d((inobject->center)[0] + ((inobject->radius)+1)*(inobject->length),
				(inobject->center)[1] + ((inobject->radius)+1)*(inobject->length),
				(inobject->center)[2] + ((inobject->radius)+1)*(inobject->length));
			inobject->BCorner=vector3d((inobject->center)[0] - ((inobject->radius)+1)*(inobject->length),
				(inobject->center)[1] - ((inobject->radius)+1)*(inobject->length),
				(inobject->center)[2] - ((inobject->radius)+1)*(inobject->length));
    			break;
		case CYLINDER:
        		inobject->FCorner=vector3d((inobject->center)[0] + (inobject->radius) + (inobject->length),
				(inobject->center)[1] + (inobject->radius) + (inobject->length),
				(inobject->center)[2] + (inobject->radius) + (inobject->length));
			inobject->BCorner=vector3d((inobject->center)[0] - ((inobject->radius)+1)*(inobject->length),
				(inobject->center)[1] - (inobject->radius) - (inobject->length),
				(inobject->center)[2] - (inobject->radius) - (inobject->length));
    			break;
 		case RECT:
        		inobject->FCorner=inobject->center + adder;
			inobject->BCorner=inobject->center - adder;
    			break;
 		case ELLIPS:
			A = inverse(A);
			for(int i = 0; i < 10; i ++){
				x = A.basis_element(0,0)*dim[0]+A.basis_element(1,0)*dim[1]+A.basis_element(2,0)*dim[2] ;
				y = A.basis_element(0,1)*dim[0]+A.basis_element(1,1)*dim[1]+A.basis_element(2,1)*dim[2]  ;
				z = A.basis_element(0,2)*dim[0]+A.basis_element(1,2)*dim[1]+A.basis_element(2,2)*dim[2] ;
				dim[0]=x ; dim[1]=y ; dim[2]=z ;


				max_eig_val2 = max(max(dim[0],dim[1]),dim[2]);
				for(int j = 0;j < 3;j ++)
					dim[j] = dim[j]/max_eig_val2 ;
			}

			max_eig_val2 = abs(max_eig_val2);
			//Here we take the sqrt since the eigenvalues only give us the squares...
			max_eig_val2 = sqrt(max_eig_val2);
	      		inobject->FCorner=vector3d((inobject->center)[0] + max_eig_val2,
				(inobject->center)[1] + max_eig_val2,
				(inobject->center)[2] + max_eig_val2);
			inobject->BCorner=vector3d((inobject->center)[0] - max_eig_val2,
				(inobject->center)[1] - max_eig_val2,
				(inobject->center)[2] - max_eig_val2);
    			break;
 		case TRI:
        		inobject->FCorner=vector3d(Trix[0]+.0001,Triy[0]+.0001,Triz[0]+.0001);
			inobject->BCorner=vector3d(Trix[1]-.0001,Triy[1]-.0001,Triz[1]-.0001);
    			break;
		default:
			cout << "ERRROR WILL ROBINSON!\n\n";
	}
}

void BoundObjects(object* List, int Length){
	for(int i = 0; i < Length; i ++)
		Bound(&List[i]);
}

void AccList(BinarySearchTree& t, object* List, int Length){
	BoundObjects(List, Length);
	t.SkeletonTree(List, 0, Length);
	for(int i=0; i <Length; i ++)
		t.insert(List[i]);
	t.ReboundTree();
}
		
