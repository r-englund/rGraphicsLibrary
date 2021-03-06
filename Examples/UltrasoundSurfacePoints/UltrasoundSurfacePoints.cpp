#include <fstream>
#include <omp.h>


#include <Engine\DrawableObject.h>

#include <SuperEngine\SuperEngine.h>

#include <Util/StopClock.h>

#include <gl/glfw.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Image\Image.h>
#include <Image\BMPWriter.h>

#include <Geometry\Clustering\Clusterer.h>

#include <string>
#include <iostream>

#include <Volume\UltrasoundSurfacePointExtractor.h>
#include <Volume\UltrasoundVariationalClassification.h>

#include <Math\Plane.h>

#include <Base\XMLObjectHandler.h>

#include <Util\TmpPointer.h>

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
	
int niceCases[]= {3,7,11,14,19,25,31,42};
const int numNiceCases = 8;
int _case = 3;



class PointRenderer : public DrawableObject{
	std::vector<Vertex> points;
	std::vector<glm::vec3> surfPoints;
public:
	PointRenderer(){
		TmpPointer<ScalarField> vol = ScalarField::ReadFromRawfile(files[niceCases[_case]].path,files[niceCases[_case]].w,files[niceCases[_case]].h,files[niceCases[_case]].d);
		//TmpPointer<ScalarField> tmp = tmp2->blur();
		//surfPoints = UltrasoundSurfacePointExtractor::ExtractPoints(tmp.get(),Z_AXIS);
		
		TmpPointer<UltrasoundVariationalClassification> usClassified = new UltrasoundVariationalClassification(vol.get(),0.12,0.03,0.5,0.5,0.9,0.8);
		TmpPointer<ScalarField> surfVol = usClassified->Canny();
		
		glm::ivec3 dim = surfVol->getDimensions();
		FOR(dim)if(z>20&&z<80 && x > 100 && x < 350)
		{
			if(surfVol->get(glm::ivec3(x,y,z)) >= 0.99){
				auto pos = surfVol->getBoundingAABB().getPosition(glm::vec3(x,y,z) / glm::vec3(dim));
				surfPoints.push_back(pos);
			}
		}

		glm::vec3 dir = usClassified->getBoundingAABB().maxPos() - surfVol->getBoundingAABB().minPos();
		dir /= dim;
		
		K3DTree<Vertex> tree;
		for(auto s = surfPoints.begin() ; s != surfPoints.end() ; ++s){
			Vertex v;
			v.setPosition(glm::vec4(s->x,s->y,s->z,1));
			tree.insert(*s,v);
		}

		auto clusters = Clusterer::ClusterPoints(&tree,glm::length(dir),100,true);
		if(clusters.size()!=0)
			points = clusters[0].getPoints()->getAsVector();
		



		for(int i = 0;i<points.size();i++){
			auto nodes = clusters[0].getPoints()->findNNearest(glm::value_ptr(points[i].getPosition()),10);
			std::vector<glm::vec3> pointsForPlane;
			for(auto node = nodes.begin();node != nodes.end() ; ++node){
				pointsForPlane.push_back(glm::vec3((*node)->getPosition()[0],(*node)->getPosition()[1],(*node)->getPosition()[2]));
			}
			Plane p(pointsForPlane);
			points[i].setNormal(p.getNormal());
		}
		


		std::ofstream file("points2.obj");
		for(int i = 0;i<points.size();i++){
			file << "v " << points[i].getPosition().x << " " << points[i].getPosition().y << " " << points[i].getPosition().z << std::endl;
			file << "vn " << points[i].getNormal().x << " " << points[i].getNormal().y << " " << points[i].getNormal().z << std::endl;
		}

		file.close();

		

		//TmpPointer<ScalarField> vol = tmp->blur();

		/*auto tree = vol->getSurfacePoints(0.4);
		
		glm::vec3 dir = vol->getBoundingAABB().maxPos() - vol->getBoundingAABB().minPos();
		dir /= vol->getDimensions();

		auto clusters = Clusterer::ClusterPoints(tree,glm::length(dir),100,true);

		points = clusters[0].getPoints()->getAsVector();*/

	}


	virtual void draw(){
		glPointSize(2);
		glBegin(GL_POINTS);
		glColor3f(1,1,1);
		for(auto p = points.begin();p!=points.end();++p){
			glVertex3fv(glm::value_ptr(p->getPosition()));
		}
		glColor3f(1,0,0);
		//for(auto p = surfPoints.begin();p!=surfPoints.end();++p){
		//	glVertex3fv(glm::value_ptr(*p));
		//}
		glEnd();
	}


	virtual std::string toString()const{return "PointRenderer";}
};




void init(int argc,char **argv,Engine *t){
	if(argc == 2)
		_case = atoi(argv[1]);
	/*else
		_case = 3;*/
	try{
		static_cast<SuperGraphicsEngine*>(SuperEngine::getEngine()->getGraphicEngine())->addDrawableObject(new PointRenderer());
	}catch(...){
		exit(1);
	}
	if(argc == 2)
		exit(0);
}

ENGINE_MAIN(SuperEngine::CreateEngine(),init)