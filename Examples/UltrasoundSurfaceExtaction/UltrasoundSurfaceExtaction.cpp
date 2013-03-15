#include <fstream>;

#include <OpenGLHelpers/OpenGLInfo.h>
#include <Util/StopClock.h>

#include <gl/glfw.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Image\Image.h>

#include <Geometry\Clustering\Clusterer.h>

#include <string>
#include <iostream>

#include <Geometry\Mesh\IndexedMesh.h>

#include <Physics\SpringDamperSystem.h>

#include <Geometry\CSG\MarchingTetrahedra.h>

#include <Volume\ScalarField.h>

#include "RBF\RBF.h"

struct SourceFile{
	char *path;
	int w,h,d;
};

const SourceFile files[] = {
	{"C:/Thesis Data/ContextVision/Volumes for rendering/raw/I0000013-orig_SC-467x255x124.raw",467,255,124}, //0
	{"C:/Thesis Data/ContextVision/Volumes for rendering/raw/I0000013-ENH-1_SC-467x255x124.raw",467,255,124}, //1
	{"C:/Thesis Data/ContextVision/Volumes for rendering/raw/I0000013-ENH-2_SC-467x255x124.raw",467,255,124}, //2
	{"C:/Thesis Data/ContextVision/Volumes for rendering/raw/I0000013-ENH-3_SC-467x255x124.raw",467,255,124}, //3

	{"C:/Thesis Data/ContextVision/Volumes for rendering/raw/I0000016-orig_SC-478x247x79x22.raw",478,247,79}, //4
	{"C:/Thesis Data/ContextVision/Volumes for rendering/raw/I0000016-ENH-1_SC-478x247x79x22.raw",478,247,79}, //5
	{"C:/Thesis Data/ContextVision/Volumes for rendering/raw/I0000016-ENH-2_SC-478x247x79x22.raw",478,247,79}, //6
	{"C:/Thesis Data/ContextVision/Volumes for rendering/raw/I0000016-ENH-3_SC-478x247x79x22.raw",478,247,79}, //7

	{"C:/Thesis Data/ContextVision/Volumes for rendering/raw/I0000030_orig_SC-679x307x174.raw",679,307,174}, //8
	{"C:/Thesis Data/ContextVision/Volumes for rendering/raw/I0000030_ENH-1_SC-679x307x174.raw",679,307,174}, //9
	{"C:/Thesis Data/ContextVision/Volumes for rendering/raw/I0000030_ENH-2_SC-679x307x174.raw",679,307,174}, //10
	{"C:/Thesis Data/ContextVision/Volumes for rendering/raw/I0000030_ENH-3_SC-679x307x174.raw",679,307,174}, //11

	{"C:/Thesis Data/ContextVision/new volume/I0000027_SC--467x255x101.raw",467,255,101}, //12
	{"C:/Thesis Data/ContextVision/new volume/I0000027_TEMP-1-ENH-3-467x255x101.raw",467,255,101}, //13
	{"C:/Thesis Data/ContextVision/new volume/I0000027_TEMP-1-ENH-3_ENH-1-467x255x101.raw",467,255,101}, //14

	{"C:/Thesis Data/ContextVision/2012-12-10/I0000027-enh3_SC-fLOOD-sc-0-516x244x124.raw",516,244,124}, //15
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000027-enh3_SC-fLOOD-sc-0-n516x244x124.raw",516,244,124}, //16
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000027-enh3_SC-fLOOD-sc-0_2-516x244x124.raw",516,244,124}, //17
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000027-enh3_SC-fLOOD-sc-0_3-516x244x124.raw",516,244,124}, //18
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000027-enh3_SC-fLOOD-sc-0_4-516x244x124.raw",516,244,124}, //19
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000027_SC516x244x124.raw",516,244,124}, //20

	{"C:/Thesis Data/ContextVision/2012-12-10/I0000029-ENH3_SC-fLOOD-sc-1-688x404x124.raw",688,404,124}, //21
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000029-ENH3_SC-fLOOD-sc-1-n688x404x124.raw",688,404,124}, //22
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000029-ENH3_SC-fLOOD-sc-1_2-688x404x124.raw",688,404,124}, //23
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000029-ENH3_SC-fLOOD-sc-1_3-688x404x124.raw",688,404,124}, //24
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000029-ENH3_SC-fLOOD-sc-1_4-688x404x124.raw",688,404,124}, //25
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000029_SC-688x404x124.raw",688,404,124}, //26

	{"C:/Thesis Data/ContextVision/2012-12-10/I0000042-ENH3_SC-fLOOD-sc-0-516x244x124.raw",516,244,124}, //27
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000042-ENH3_SC-fLOOD-sc-0-n516x244x124.raw",516,244,124}, //28
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000042-ENH3_SC-fLOOD-sc-0_2-516x244x124.raw",516,244,124}, //29
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000042-ENH3_SC-fLOOD-sc-0_3-516x244x124.raw",516,244,124}, //30
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000042-ENH3_SC-fLOOD-sc-0_4-516x244x124.raw",516,244,124}, //31
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000042_SC516x244x124.raw",516,244,124}, //32

	{"C:/Thesis Data/ContextVision/2012-12-10/I0000047-ENH3_SC-fLOOD-sc-2-624x327x124.raw" ,624,327,124}, //33
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000047-ENH3_SC-fLOOD-sc-2-n624x327x124.raw",624,327,124}, //34
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000047-ENH3_SC-fLOOD-sc-2_2-624x327x124.raw",624,327,124}, //35
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000047-ENH3_SC-fLOOD-sc-2_3-624x327x124.raw",624,327,124}, //36
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000047_SC624x327x124.raw",624,327,124}, //37

	{"C:/Thesis Data/ContextVision/2012-12-10/I0000048-ENH3_SC-fLOOD-sc-3-n645x432x124.raw",645,432,124}, //38
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000048-ENH3_SC-fLOOD-sc-3_2_645x432x124.raw",645,432,124}, //39
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000048-ENH3_SC-fLOOD-sc-3_3_645x432x124.raw",645,432,124}, //40
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000048-ENH3_SC-fLOOD-sc-3_4_645x432x124.raw",645,432,124}, //41
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000048-ENH3_SC-fLOOD-sc-3_645x432x124.raw",645,432,124}, //42
	{"C:/Thesis Data/ContextVision/2012-12-10/I0000048_SC645x432x124.raw",645,432,124} //43

};
const unsigned int numDatasets = 44;

PointCluster *cluster;
std::vector<Vertex> surfacePoints;
	
int niceCases[]= {3,7,11,14,19,25,31,42};
const int numNiceCases = 8;
int _case = 3;

StopClock s(true);

Mesh *m;

glm::ivec2 winSize;

float threshold = 128.0/255;

ScalarField *vol = 0;
KDTree<Vertex,3,float>* points;
std::vector<PointCluster> clusters;

bool mouse0State = false;
float rx = 0,ry = 0,scale = 1;


RBFSystem<InverseMultiQuadricRBF> *rbf0;
RBFSystem<Biharmonic> *rbf1;
RBFSystem<Triharmonic> *rbf2;
RBFSystem<MultiQuadricRBF> *rbf3;
RBFSystem<GausianRBF> *rbf4;
RBFSystem<ThinPlateSplineRBF> *rbf5;


int meshRes = 50;
float bounds = 1.0;

void draw(){
	chkGLErr();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(glm::lookAt(glm::vec3(0,0,3),glm::vec3(0,0,0),glm::vec3(0,1,0))));
	glRotatef(ry,1,0,0);
	glRotatef(rx,0,1,0);
	glScalef(scale,scale,scale);

	glColor3f(1,1,1);
	vol->getBoundingAABB().draw();


	KDTree<Vertex,3,float>::NodeIterator point;
	//std::vector<PointCluster>::iterator cluster;
	srand(0);
	//for(cluster = clusters.begin();cluster != clusters.end();++cluster){
		float r,g,b;
		r = rand() / float(RAND_MAX);
		g = rand() / float(RAND_MAX);
		b = rand() / float(RAND_MAX);
		r = (r + 0.5) / 1.5;
		g = (g + 0.5) / 1.5;
		b = (b + 0.5) / 1.5;
		glColor3f(r,g,b);
		glBegin(GL_POINTS);
		/*for(point = cluster->getPoints()->begin();point != cluster->getPoints()->end();++point){
			glVertex3fv(point->getPosition());
		}*/
		glEnd();
	//}

	float s = 1;
	glBegin(GL_LINES);
	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(s,0,0);
	
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,s,0);
	
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,s);


	glEnd();

	
	glColor3f(1,1,1);
	static_cast<IndexedMesh*>(m)->draw();

	glPointSize(3);
	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);
	for(auto p = surfacePoints.begin();p != surfacePoints.end();++p){
		glColor3f(0,0,1);
		if(p->getPosition().w < -0.00001)
			glColor3f(1,0,0);
		else if(p->getPosition().w > 0.000001)
			glColor3f(0,1,0);
		glVertex3f(p->getPosition().x,p->getPosition().y,p->getPosition().z);
	}
	glEnd();
	glEnable(GL_LIGHTING);


	glfwSwapBuffers();
	chkGLErr();
}


void loadPoints(){
	if(vol != 0)
		delete vol;
	StopClock sw;
	sw.start();
	
	vol = ScalarField::ReadFromRawfile(files[niceCases[_case]].path,files[niceCases[_case]].w,files[niceCases[_case]].h,files[niceCases[_case]].d);	
	
	std::cout << "Dataset loaded " << files[niceCases[_case]].path << ": " << sw.getFractionElapsedSeconds() << " seconds" << std::endl;
	sw.restart();

	points = vol->getSurfacePoints(threshold);
	std::cout << "Points extracted: " << points->size() << " number of points, " << sw.getFractionElapsedSeconds() << " seconds" << std::endl;
	sw.restart();

	glm::vec3 dir = vol->getBoundingAABB().getPosition(glm::vec3(1,1,1)) - vol->getBoundingAABB().getPosition(glm::vec3(0,0,0));
	dir /= vol->getDimensions();

	clusters = Clusterer::ClusterPoints(points,glm::length(dir) * 1,50);
	std::cout << "Points clustered: " << sw.getFractionElapsedSeconds() << " seconds" << std::endl;
	sw.restart();

	unsigned long _max = 0;
	std::cout << "Created " << clusters.size() << " clusters" << std::endl;
	for(int i = 0;i<clusters.size();i++){
		unsigned long size = clusters[i].getPoints()->size();
		std::cout << '\t' << "Cluster " << i << ": " << size << " points" << std::endl;
		if(size>_max){
			_max = size;
			cluster = &clusters[i];
		}
	}

	auto points = cluster->getPoints()->getAsVector();
	int s = points.size();
	
	float d = 0.005;
	int inc = 3*s / 9000;
	surfacePoints.clear();
	for(int i = 0;i<s;i += inc){
		glm::vec4 p0,p1,p2;
		
		glm::vec3 n = points[i].getNormal();
		if(!(n.x == n.x))
			continue;
		glm::vec3 p = glm::vec3(points[i].getPosition());

		p0 = glm::vec4(p + n * d, d);
		p1 = glm::vec4(p - n * d,-d);
		p2 = glm::vec4(p,0);

		surfacePoints.push_back(Vertex(p0,n));
		surfacePoints.push_back(Vertex(p1,n));
		surfacePoints.push_back(Vertex(p2,n));
	}

	std::cout << surfacePoints.size() << std::endl;

	std::cout << "InverseMultiQuadricRBF" << std::endl;
	rbf0 = RBFSystem<InverseMultiQuadricRBF>::CreateFromPoints(surfacePoints);

	std::cout<< std::endl << std::endl << "Biharmonic" << std::endl;
	rbf1 = RBFSystem<Biharmonic>::CreateFromPoints(surfacePoints);

	std::cout<< std::endl << std::endl << "Triharmonic" << std::endl;
	rbf2 = RBFSystem<Triharmonic>::CreateFromPoints(surfacePoints);

	std::cout<< std::endl << std::endl << "MultiQuadricRBF" << std::endl;
	rbf3 = RBFSystem<MultiQuadricRBF>::CreateFromPoints(surfacePoints);

	std::cout<< std::endl << std::endl << "GausianRBF" << std::endl;
 	rbf4 = RBFSystem<GausianRBF>::CreateFromPoints(surfacePoints);//*/

	/*std::cout<< std::endl << std::endl << "ThinPlateSplineRBF" << std::endl;
 	rbf5 = RBFSystem<ThinPlateSplineRBF>::CreateFromPoints(surfacePoints);*/

	
	std::cout << "RBFs fitted: " << sw.getFractionElapsedSeconds() << " seconds" << std::endl;
	sw.restart();
	
	m = MarchingTetrahedra::March<IndexedMesh>(rbf0,BoundingAABB(glm::vec3(-bounds,-bounds,-bounds),glm::vec3(bounds,bounds,bounds)),glm::ivec3(meshRes,meshRes,meshRes));
	
	sw.stop();
	std::cout << "Surface extracted: " << sw.getFractionElapsedSeconds()  << " seconds" << std::endl;


}

int prevScroll = 0;
void wheel(int i){
	//scale *= 1+((i-prevScroll)*0.01);
	threshold += i/255.0;
	//loadPoints();

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

void keyboard(int button,int state){
	if(button == 'N' && state){
		_case++;
		if(_case>=numNiceCases){
			_case = 0;
		}
		loadPoints();
	}
	if(button == 'M' && state){
		_case--;
		if(_case<0){
			_case = numNiceCases-1;
		}
		loadPoints();
	}
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

void resize(int width,int height){
	chkGLErr();
	glMatrixMode(GL_PROJECTION);
	chkGLErr();
	
	winSize.x = width;
	winSize.y = height;
	float ar = width;
	ar /= height;
	glLoadMatrixf(glm::value_ptr(glm::perspective(45.0f, ar,0.1f,100.0f)));
	chkGLErr();
	

	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,width,height);
	chkGLErr();
}


void init(){
	chkGLErr();
	glClearColor(0,0,0,0);

	
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

	
	loadPoints();
	
	chkGLErr();
}

int main( int argc, char* argv[] )
{
	if (glfwInit() != GL_TRUE){
		std::cout << "Could not init glfw"<< std::endl;
		return 2;
	}

	if (glfwOpenWindow(600, 600, 8, 8, 8, 8, 32, 0, GLFW_WINDOW) != GL_TRUE){
		std::cout << "Could not create window"<< std::endl;
		return 3;
	}
	glfwSetWindowTitle ("rGraphicsLibrary - Ultrsound Surface Extraction");

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

	double f[3] = {2,1,-1};
	Polynomial<> p(2,f);
	double d = p.evaluate(1);
	double d2 = p.evaluate(2);

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
