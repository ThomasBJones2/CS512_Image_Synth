using namespace std;

void Shut_Down(int return_code){
	if (return_code)
		cout << "Oh Noes, There was an Error!\n";
	glfwTerminate();
	exit(return_code);
}

inline void init(void)
{
//  cout << "got here\n";
  if (glfwInit() != GL_TRUE){
	cout << "Oh noes, we got the initizialization error!\n";  
	  Shut_Down(1);
  }
//	cout << "got here too\n";


  if (glfwOpenWindow(WIDTH, HEIGHT, REDBITS, 
		BLUEBITS, GREENBITS,
                DEPTHBITS, ALPHABITS, 
		STENCBITS, GLFW_WINDOW) != GL_TRUE)
    Shut_Down(1);
  glfwSetWindowTitle("The Pixelator");
 
  // set the projection matrix to a normal frustum with a max depth of 50
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspect_ratio = ((float)HEIGHT) / ((float)WIDTH);
  glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);
  glMatrixMode(GL_MODELVIEW);
}
