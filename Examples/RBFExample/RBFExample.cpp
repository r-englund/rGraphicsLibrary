#include <Engine\GLFWEngine.h>

#include <fstream>;

#include <Math\Plane.h>

#include <OpenGLHelpers/FBO.h>
#include <OpenGLHelpers/OpenGLInfo.h>
#include <OpenGLHelpers/AttribPusher.h>
#include <Util/StopClock.h>
#include <Util/Random.h>

#include <Geometry/Mesh/IndexedMesh.h>
#include <RBF/RBF.h>
#include <Geometry/CSG/MarchingTetrahedra.h>

#include <gl/glfw.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <iomanip>

StopClock s(true);
std::vector<glm::vec4> _points;

int numPoints = 3000;
int meshRes = 10;

struct RBFInfo : public Object{
	RBFSystem *rbf;
	IndexedMesh *m;
	std::string name;
	float fittingTime;
	float meshExtractionTime;

	virtual std::string toString()const{
		std::stringstream ss;
		
		ss << std::setw(45) << name;
		ss << std::setw(15) << fittingTime;
		ss << std::setw(25) << meshExtractionTime;
		return ss.str();
	}
};


class RBFSelecterObject : public DrawableObject, public KeyboardEventListener{
	std::vector<RBFInfo*> rbfs;
	int current;
	bool showPoints;
	bool showMesh;
	std::vector<glm::vec4> points;
	BoundingAABB aabb;

	void createRBFS();
	template<typename RBFKernel> RBFInfo *createRBF(std::vector<glm::vec4> points,std::string name,bool fastFit);

public:
	RBFSelecterObject(std::vector<glm::vec4> points):points(points),aabb(glm::vec3(0,0,0),glm::vec3(0,0,0)),current(0),showMesh(1),showPoints(1){
		aabb.minPos() = aabb.maxPos() = glm::vec3(points[0]);
		for(auto p = points.begin()+1;p!=points.end();++p){
			aabb.extend(glm::vec3(*p));
		}
		createRBFS();
	}
	~RBFSelecterObject(){}

	virtual void draw(){
		aabb.draw();
		if(showMesh && rbfs.size()>=current+1&& rbfs[current]->m != 0){
			rbfs[current]->m->draw();
		}if(showPoints){
 			AttribPusher ____a(GL_ENABLE_BIT);
			glDisable(GL_LIGHTING);
			
			glPointSize(3);
			glBegin(GL_POINTS);
			for(auto p = points.begin();p!=points.end();++p){
				glColor3f(0,0,1);
				if(p->w < -0.0001)
					glColor3f(1,0,0);
				else if(p->w > 0.0001)
					glColor3f(0,1,0);
				glVertex3fv(glm::value_ptr(*p));
			}
			glEnd();
		}
		chkGLErr();
	}

	virtual std::string toString()const{return "RBFSelecterObject";}

	void buttonPressed(int button,int state){
		if(button == 'Q' && state){
			current++;
			if(current >= rbfs.size()) current = 0;
			std::cout << "Showing: " << rbfs[current]->name << std::endl;
		}
		if(button == 'A' && state){
			current--;
			if(current < 0) current = rbfs.size()-1;
			std::cout << "Showing: " << rbfs[current]->name << std::endl;
		}
		if(button == 'P' && state) showPoints = !showPoints;
		if(button == 'M' && state) showMesh = !showMesh;

	}
};

void RBFSelecterObject::createRBFS(){
	
	std::cout << "Creating RBFS"<< std::endl;
	std::cout << std::setw(45) << "RBF Type";
	std::cout << std::setw(15) << "Fitting Time";
	std::cout << std::setw(25) << "Mesh exraction time" << std::endl;

	bool useFastFit = true;
	bool useNormalFit = false;

	if(useNormalFit)rbfs.push_back(createRBF<Biharmonic>(points,"Biharmonic",false));
	if(useFastFit)rbfs.push_back(createRBF<Biharmonic>(points,"Biharmonic fast fitting",true));

	if(useNormalFit)rbfs.push_back(createRBF<InverseMultiQuadricRBF>(points,"InverseMultiQuadricRBF",false));
	if(useFastFit)rbfs.push_back(createRBF<InverseMultiQuadricRBF>(points,"InverseMultiQuadricRBF fast fitting",true));

	if(useNormalFit)rbfs.push_back(createRBF<Triharmonic>(points,"Triharmonic",false));
	if(useFastFit)rbfs.push_back(createRBF<Triharmonic>(points,"Triharmonic fast fitting",true));

	if(useNormalFit)rbfs.push_back(createRBF<GausianRBF>(points,"GausianRBF",false));
	if(useFastFit)rbfs.push_back(createRBF<GausianRBF>(points,"GausianRBF fast fitting",true));

	if(useNormalFit)rbfs.push_back(createRBF<MultiQuadricRBF>(points,"MultiQuadricRBF",false));
	if(useFastFit)rbfs.push_back(createRBF<MultiQuadricRBF>(points,"MultiQuadricRBF fast fitting",true));

	//rbfs.push_back(createRBF<ThinPlateSplineRBF>(points,"ThinPlateSplineRBF",false));
	//rbfs.push_back(createRBF<ThinPlateSplineRBF>(points,"ThinPlateSplineRBF fast fitting",true));
}

template<typename RBFKernel>
RBFInfo* RBFSelecterObject::createRBF(std::vector<glm::vec4> points,std::string name,bool fastFit){
	RBFInfo *r = new RBFInfo();

	StopClock s(true);
	float acc = 0.0001;
	if(fastFit)
		r->rbf = RBFSystem::FastFitting<RBFKernel>(points,acc);
	else
		r->rbf = RBFSystem::CreateFromPoints<RBFKernel>(points);
	s.stop();
	r->fittingTime = s.getFractionElapsedSeconds();s.restart();
	r->m = static_cast<IndexedMesh*>(MarchingTetrahedra::March<IndexedMesh>(r->rbf,aabb,glm::ivec3(meshRes,meshRes,meshRes)));
	s.stop();
	r->meshExtractionTime = s.getFractionElapsedSeconds();
	r->name = name;

	std::cout << r << std::endl;
	return r;
}


void createPoints(){
	_points = Random::getRandomGenerator()->randomPointsCloseToCubeSurface(numPoints);
	_points = Random::getRandomGenerator()->randomPointsCloseToSphereSurface(numPoints);
}

void initGL(){
	chkGLErr();
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
}

void init(Engine *e){
	initGL();

	StopClock sw;
	sw.start();
	createPoints();
	sw.stop();
	std::cout << "Points created: " << sw.getFractionElapsedSeconds()  << " seconds" << std::endl;

	static_cast<BasicGraphicsEngine*>(GLFWEngine::getEngine()->getGraphicEngine())->addDrawableObject(new RBFSelecterObject(_points));
}

ENGINE_MAIN(GLFWEngine::CreateEngine("Radial Basis Functions"),init)