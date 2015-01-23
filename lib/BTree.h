//Binary Search Tree Program


class BinarySearchTree
{
    private:
        struct tree_node
        {
           tree_node* left;
           tree_node* right;
	   //object check
	   object Obj;
        };
        tree_node* root;
    
    public:
        BinarySearchTree()
        {
           root = NULL;
        }
       
        bool isEmpty() const { return root==NULL; }
        void print_inorder();
        void inorder(tree_node* p, int depth);
        void print_preorder();
        void preorder(tree_node*, int depth
);
        void print_postorder();
        void postorder(tree_node*);
        void insert(object objin);
	//The skeleton tree (and its helper) take a list and create a tree which
	//contains, at each level a centroid of the list. The centroid is only a 
	//center on a single dimension with that dimension being equal
	//to the depth mod 3. 
inline	void SkeletonTree(object* List, int start, int end);
inline	tree_node* SkeletonTreeHelper(object * List, int start, int end, int depth){
		double center1=0;		
		int dim = depth%3;
		int lowercount = 0;
		object* lower;
		object* upper;

  		if (start >= end) return NULL;
  		// same as (start+end)/2, avoids overflow

		if(start >= end - 1){
			tree_node *parent = new tree_node;
  			(parent->Obj).center[dim] = List[0].center[dim];
			(parent->Obj).type = BB;
			(parent->Obj).id = 0;
 			parent->left = NULL;
  			parent->right = NULL;
			return parent;
		}
		for(int i = start; i < end; i ++)
			center1 += List[i].center[dim];	
		center1 = center1/((double)(end-start));
		for(int i = start; i < end; i ++)
			if(List[i].center[dim] <= center1)
				lowercount ++;

		lower = new (object[lowercount]);
		upper = new (object[end-lowercount]);
	
		int j=0;
		int k = 0;
		for(int i = start; i < end; i ++){	
			if(List[i].center[dim] <= center1){
				lower[j] = List[i];
				j++;
			}
			else{
				upper[k] = List[i];
				k++;			
			}
		}

  		tree_node *parent = new tree_node;
  		(parent->Obj).center[dim] = center1;
		(parent->Obj).type = BB;
		(parent->Obj).id = 0;
 		parent->left = SkeletonTreeHelper(lower, 0, lowercount,depth+1);

  		parent->right = SkeletonTreeHelper(upper, 0, end-lowercount,depth+1);
		delete upper;
		delete lower;
  		return parent;
	};
inline	void ReboundTreeHelper(tree_node* p, vector3d Corners[2]);
inline	void ReboundTree();
inline	dis_id BCSHelp(vector3f Eye, vector3f Pixel_Ray, tree_node* p, int depth);
inline	dis_id BCS(vector3f Eye, vector3f Pixel_Ray);
	BinarySearchTree& operator=(const BinarySearchTree &rhs){root = rhs.root; return *this;};
};

inline void BinarySearchTree::ReboundTree(){
	vector3d throwaway[2];
	ReboundTreeHelper(root, throwaway);
}

inline void BinarySearchTree::ReboundTreeHelper(tree_node* p, vector3d Corners[2]){
	vector3d NewFcorner,NewBCorner;
	vector3d rightCorners[2], leftCorners[2];
	


	if(p == NULL){
		Corners[0] = vector3d(0,0,0);
		Corners[1] = vector3d(1,1,1);
	}	
	else{	
		ReboundTreeHelper(p->left, leftCorners);
		ReboundTreeHelper(p->right, rightCorners);
		//Handle a bounding box
		if((p->Obj).type == BB){	
			//Handle both children have no proper objects
			if((leftCorners[0][0] < leftCorners[1][0]) && (rightCorners[0][0] < rightCorners[1][0])){
				(p->Obj).FCorner = vector3d(0,0,0);
				(p->Obj).BCorner = vector3d(1,1,1);
			}
			//Handle both children have proper objects
			if((leftCorners[0][0] > leftCorners[1][0]) && (rightCorners[0][0] > rightCorners[1][0])){
				for(int i = 0; i < 3; i++){
					if(leftCorners[0][i] > rightCorners[0][i]){
						(p->Obj).FCorner[i] = leftCorners[0][i];
					}
					else{
						(p->Obj).FCorner[i] = rightCorners[0][i];					
					}

					if(leftCorners[1][i] < rightCorners[1][i]){
						(p->Obj).BCorner[i] = leftCorners[1][i];
					}
					else{
						(p->Obj).BCorner[i] = rightCorners[1][i];					
					}				
				}			
			}
			//Handle the cases where only one side is a child with actual data
			else if(leftCorners[0][0] > leftCorners[1][0]){
				(p->Obj).FCorner = leftCorners[0];
				(p->Obj).BCorner = leftCorners[1];
			}
			else{
				(p->Obj).FCorner = rightCorners[0];
				(p->Obj).BCorner = rightCorners[1];			
			}
		}
		Corners[0] = (p->Obj).FCorner;
		Corners[1] = (p->Obj).BCorner;
	//	if(p->Obj.id == 7)
		//	cout << p->Obj.FCorner << " " << p->Obj.BCorner << "\n";
	}
	
}

inline void BinarySearchTree::SkeletonTree(object* List, int start, int end){
	root = SkeletonTreeHelper(List, start, end, 0);
}

inline dis_id BinarySearchTree::BCSHelp(vector3f Eye, vector3f Pixel_Ray, tree_node* p, int depth){
	vector2d check;
    	double distance=-100;
    	dis_id out1,out2,finalout;
 
	//Initialize objects
    	out1.id = -1;
    	out1.distance = -100;
//	out1.Normal = vector3d(0,0,0); 
    	out2.id = -1;
    	out2.distance = -100;
//	out2.Normal = vector3d(0,0,0);
    	finalout.id = -1;
    	finalout.distance = -100;
//	finalout.Normal = vector3d(0,0,0);
	if(p != NULL){

//if(Pixel_Ray[0] <= 0.01 && Pixel_Ray[0] >= -0.01 && Pixel_Ray[1] <=0.01 && Pixel_Ray[1] >= -.01)
//	cout << (p->Obj).id << " " << (p->Obj).FCorner << " " << (p->Obj).BCorner << "\n";


		//Here we check left and right on bounding boxes!"
		if((p->Obj).type == BB){
			//here we get data for left and right
        		if(p->left){

				check = BB_Intersect_Distance(Eye, Pixel_Ray, ((p->left)->Obj).FCorner,  ((p->left)->Obj).BCorner);
				if(check[0] > 0)
					out1 = BCSHelp(Eye,Pixel_Ray,p->left, depth + 1);
			}
        		if(p->right){
				check = BB_Intersect_Distance(Eye, Pixel_Ray, ((p->right)->Obj).FCorner,  ((p->right)->Obj).BCorner);
				if(check[0] > 0)
					out2 = BCSHelp(Eye,Pixel_Ray,p->right, depth + 1);
			}

			//This is the case when both children have some distance value to yield
			if(out1.distance > 0 && out2.distance > 0){
	//			cout << "huzzah\n";
				if(out1.distance < out2.distance)
					finalout = out1;
				else
					finalout = out2;
			}
			//Here, only the left child has distance to yeild
			else if(out1.distance > 0)
				finalout = out1;
			//Here, only the right child has distance to yeild
			else if(out2.distance > 0)
				finalout = out2;
		}
		else{
			distance = CheckLocalObj(p->Obj,Eye,Pixel_Ray);
		//	if ((p->Obj).id == 7)
		//		cout << "Huzzah!\n";
    			if(distance > 0){
				finalout.id = (p->Obj).id;
				finalout.distance = distance;
			}	
    		}
	}
    	return finalout;
}

dis_id BinarySearchTree::BCS(vector3f Eye, vector3f Pixel_Ray){
	return BCSHelp(Eye, Pixel_Ray, root, 0);
} 


void BinarySearchTree::insert(object objin)
{
    int level = 0;
    tree_node* t = new tree_node;
    tree_node* parent;
    t->Obj = objin;
    t->left = NULL;
    t->right = NULL;
    parent = NULL;
    
    // is this a new tree?
    if(isEmpty()) root = t;
    else
    {
        //Note: ALL insertions are as leaf nodes
        tree_node* curr;
        curr = root;
        // Find the Node's parent
        while(curr)
        {
            parent = curr;
            if(t->Obj.center[level%3] > curr->Obj.center[level%3]) curr = curr->right;
            else curr = curr->left;

	    level ++;
        }
	if((t->Obj).id == 7)
		cout << (parent->Obj).center << " and " << (t->Obj).center << "\n";
        if(t->Obj.center[(level+1)%3] > parent->Obj.center[level%3])
           parent->right = t;
        else
           parent->left = t;
    }
}

void BinarySearchTree::print_inorder()
{
  inorder(root, 0);
}

void BinarySearchTree::inorder(tree_node* p, int depth)
{
    if(p != NULL)
    {
        if(p->left) inorder(p->left, depth+1);
	cout << "Depth: " << depth << "\n";
        cout<<(p->Obj)<<"\n";
        if(p->right) inorder(p->right, depth+1);
    }
    else return;
}

void BinarySearchTree::print_preorder()
{
    preorder(root,0);
}

void BinarySearchTree::preorder(tree_node* p, int depth)
{
    if(p != NULL)
    {
	cout << "\n\nDEPTH: " << depth;
        cout<<"\n"<<(p->Obj)<<" ";
        if(p->left) preorder(p->left, depth+1);
        if(p->right) preorder(p->right, depth+1);
    }
    else return;
}

void BinarySearchTree::print_postorder()
{
    postorder(root);
}

void BinarySearchTree::postorder(tree_node* p)
{
    if(p != NULL)
    {
        if(p->left) postorder(p->left);
        if(p->right) postorder(p->right);
        cout<<" "<<p->Obj<<" ";
    }
    else return;
}

