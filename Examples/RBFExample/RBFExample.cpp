#include <fstream>;

#include <OpenGLHelpers/FBO.h>
#include <OpenGLHelpers/OpenGLInfo.h>
#include <Util/StopClock.h>

#include <Geometry/Mesh/IndexedMesh.h>
#include <RBF/RBF.h>
#include <Geometry/CSG/MarchingTetrahedra.h>

#include <gl/glfw.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

StopClock s(true);
std::vector<glm::vec4> _points;

Mesh *m = 0;


RBFSystem *rbf0;
RBFSystem *rbf1;
RBFSystem *rbf2;
RBFSystem *rbf3;
RBFSystem *rbf4;
RBFSystem *rbf5;


int meshRes = 10;
float bounds = 1.1;


bool mouse0State = false;
float rx = 0,ry = 0,scale = 1;

void draw(){
	chkGLErr();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(glm::lookAt(glm::vec3(0,0,2),glm::vec3(0,0,0),glm::vec3(0,1,0))));
	glRotatef(ry,1,0,0);
	glRotatef(rx,0,1,0);
	glScalef(scale,scale,scale);
	
	glColor3f(1,1,1);
	if(m!=0)
		static_cast<IndexedMesh*>(m)->draw();
	
	glPointSize(3);
	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);
	for(auto p = _points.begin();p != _points.end();++p){
		glColor3f(0,0,1);
		if(p->w < -0.001)
			glColor3f(1,0,0);
		else if(p->w > 0.001)
			glColor3f(0,1,0);
		glVertex3f(p->x,p->y,p->z);
	}
	glEnd();
	glEnable(GL_LIGHTING);

	chkGLErr();
	glfwSwapBuffers();
}


int prevScroll = 0;
void wheel(int i){
	scale *= 1+((i-prevScroll)*0.01);
	prevScroll = i;
}

void mouseButton(int button,int state,int x,int y){
if(button == 0)
	mouse0State = state;
}

int mouseX = -1,mouseY;
void mouseMotion(int x,int y){
int dx,dy;
if(mouseX == -1){
	mouseX = x;
	mouseY = y;
}
dx = x - mouseX;
dy = y - mouseY;
mouseX = x;
mouseY = y;
if(mouse0State){
	rx += dx * 1;
	ry += dy * 1;
}
}


void resize(int width,int height){
	chkGLErr();
	glMatrixMode(GL_PROJECTION);
	chkGLErr();
	
	float ar = width;
	ar /= height;
	glLoadMatrixf(glm::value_ptr(glm::perspective(45.0f, ar,0.1f,100.0f)));
	chkGLErr();

	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,width,height);
	chkGLErr();
}


void keyboard(int button,int state){
	if(button == '1' && state){
		m = MarchingTetrahedra::March<IndexedMesh>(rbf0,BoundingAABB(glm::vec3(-bounds,-bounds,-bounds),glm::vec3(bounds,bounds,bounds)),glm::ivec3(meshRes,meshRes,meshRes));
	}
	if(button == '2' && state){
		m = MarchingTetrahedra::March<IndexedMesh>(rbf1,BoundingAABB(glm::vec3(-bounds,-bounds,-bounds),glm::vec3(bounds,bounds,bounds)),glm::ivec3(meshRes,meshRes,meshRes));
	}
	if(button == '3' && state){
		m = MarchingTetrahedra::March<IndexedMesh>(rbf2,BoundingAABB(glm::vec3(-bounds,-bounds,-bounds),glm::vec3(bounds,bounds,bounds)),glm::ivec3(meshRes,meshRes,meshRes));
	}
	if(button == '4' && state){
		m = MarchingTetrahedra::March<IndexedMesh>(rbf3,BoundingAABB(glm::vec3(-bounds,-bounds,-bounds),glm::vec3(bounds,bounds,bounds)),glm::ivec3(meshRes,meshRes,meshRes));
	}
	if(button == '5' && state){
		m = MarchingTetrahedra::March<IndexedMesh>(rbf4,BoundingAABB(glm::vec3(-bounds,-bounds,-bounds),glm::vec3(bounds,bounds,bounds)),glm::ivec3(meshRes,meshRes,meshRes));
	}
	if(button == '6' && state){
		m = MarchingTetrahedra::March<IndexedMesh>(rbf5,BoundingAABB(glm::vec3(-bounds,-bounds,-bounds),glm::vec3(bounds,bounds,bounds)),glm::ivec3(meshRes,meshRes,meshRes));
	}
}


void init(){
	chkGLErr();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 10.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_color[] = { 0.8, 0.8, 1.0 , 1.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE , light_color);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
	glEnable ( GL_COLOR_MATERIAL ) ;

	//glEnable(GL_CULL_FACE);

	//int r = 55;
	//CSGSphere s0(0.75,glm::vec3(-0.5,0,0));
	//CSGSphere s1(0.75,glm::vec3(0.5,0,0));
	//CSGCombine c(&s0,&s1,CSGOperation::Union);
	StopClock sw;
	sw.start();

	glm::vec3 p;
	for(int i = 0;i<1000;i++){
		int side = rand() % 6;
		float x = rand() / float(RAND_MAX);
		float y = rand() / float(RAND_MAX);
		glm::vec4 p;
		p.w = rand() / float(RAND_MAX);
		p.w = 2*p.w-1;
		p.w /= 7;
		
		switch(side){
		case 0:
			p.x = 1 + p.w;
			p.y = x*2-1;
			p.z = y*2-1;
			break;
		case 1:
			p.x = -1 - p.w;
			p.y = x*2-1;
			p.z = y*2-1;
			break;
		case 2:
			p.y = 1 + p.w;
			p.x = x*2-1;
			p.z = y*2-1;
			break;
		case 3:
			p.y = -1 - p.w;
			p.x = x*2-1;
			p.z = y*2-1;
			break;
		case 4:
			p.z = 1 + p.w;
			p.x = x*2-1;
			p.y = y*2-1;
			break;
		case 5:
			p.z = -1 - p.w;
			p.x = x*2-1;
			p.y = y*2-1;
			break;
		}


		_points.push_back(p);
		
/*
		p = glm::normalize((p* 2.0f) - 1.0f);

		_points.push_back(glm::vec4((p*1.1f),0.1f));
		_points.push_back(glm::vec4((p),0.0f));
		_points.push_back(glm::vec4((p*0.9f),-0.1f));*/
	}
	sw.stop();
	std::cout << "Points created: " << sw.getFractionElapsedSeconds()  << " seconds" << std::endl;
	sw.restart();
	
	std::cout << "InverseMultiQuadricRBF" << std::endl;
	rbf0 = RBFSystem::CreateFromPoints<InverseMultiQuadricRBF>(_points);

	std::cout<< std::endl << std::endl << "Biharmonic" << std::endl;
	rbf1 = RBFSystem::CreateFromPoints<Biharmonic>(_points);

	std::cout<< std::endl << std::endl << "Triharmonic" << std::endl;
	rbf2 = RBFSystem::CreateFromPoints<Triharmonic>(_points);

	std::cout<< std::endl << std::endl << "MultiQuadricRBF" << std::endl;
	rbf3 = RBFSystem::CreateFromPoints<MultiQuadricRBF>(_points);

	std::cout<< std::endl << std::endl << "GausianRBF" << std::endl;
 	rbf4 = RBFSystem::CreateFromPoints<GausianRBF>(_points);//*/

	/*
	std::cout<< std::endl << std::endl << "ThinPlateSplineRBF" << std::endl;
 	rbf5 = RBFSystem<ThinPlateSplineRBF>::CreateFromPoints(_points); //*/
	
	sw.stop();
	std::cout << "RBFs fitted: " << sw.getFractionElapsedSeconds()  << " seconds" << std::endl;
	sw.restart();

	m = MarchingTetrahedra::March<IndexedMesh>(rbf0,BoundingAABB(glm::vec3(-bounds,-bounds,-bounds),glm::vec3(bounds,bounds,bounds)),glm::ivec3(meshRes,meshRes,meshRes));
	
	sw.stop();
	std::cout << "Surface extracted: " << sw.getFractionElapsedSeconds()  << " seconds" << std::endl;


	glClearColor(0,0,0,0);
	chkGLErr();
}

int main( int argc, char* argv[] )
{
	if (glfwInit() != GL_TRUE){
		std::cout << "Could not init glfw"<< std::endl;
		return 2;
	}

	if (glfwOpenWindow(600, 400, 8, 8, 8, 8, 32, 0, GLFW_WINDOW) != GL_TRUE){
		std::cout << "Could not create window"<< std::endl;
		return 3;
	}
	glfwSetWindowTitle ("rGraphicsLibrary - Mesh Example");

	if(glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to init glew" << std::endl;
		exit(1);
	}
	chkGLErr();
	std::cout << "OpenGL Version: " << OpenGLInfo::getOpenGLVersion() << std::endl;
	std::cout << "Glew   Version: " << OpenGLInfo::getGlewVersion()   << std::endl;
	std::cout << "GLSL   Version: " << OpenGLInfo::getGLSLVersion()   << std::endl;
	std::cout << "OpenGL Vendor: "  << OpenGLInfo::getOpenGLVendor()   << std::endl;
	std::cout << "OpenGL Renderer: "<< OpenGLInfo::getOpenGLRenderer()   << std::endl;
	chkGLErr();

	init();

	glfwSetWindowSizeCallback(GLFWwindowsizefun(resize));

	glfwSetKeyCallback(GLFWkeyfun(keyboard));

	glfwSetMouseButtonCallback(GLFWmousebuttonfun(mouseButton));
	glfwSetMousePosCallback(GLFWmouseposfun(mouseMotion));
	glfwSetMouseWheelCallback(GLFWmousewheelfun(wheel));

	while(true){
		if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
			break;

		draw();
	}
	return 0;
}

