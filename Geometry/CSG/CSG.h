#ifndef _CSG_H_
#define _CSG_H_

#include <Volume\ScalarField.h>

#include "ImplicitFunction.h"
#include <glm/glm.hpp>


class CSG : public ImplicitFunction{
protected:
public:
	CSG(){}
	virtual ~CSG(){}

	virtual float eval(const glm::vec3 &worldPos) = 0;
};


enum CSGOperation{
	Union,
	Difference,
	Intersection
};

class CSGCombine : public CSG{
	std::vector<CSG*> _subs;
	CSGOperation _operation;
public:
	CSGCombine(CSGOperation _operation);
	CSGCombine(CSG *c0, CSG *c1,CSGOperation _operation);
	virtual float eval(const glm::vec3 &worldPos);

	void addCSG(CSG *c);

	virtual std::string toString()const;
};


class CSGSphere : public CSG {
	glm::vec3 _c;
	float _r;
public:
	CSGSphere(float radius = 1.0 , glm::vec3 center = glm::vec3(0,0,0));
	virtual float eval(const glm::vec3 &worldPos);
	
	virtual std::string toString()const;
};

class CSGScalarField : public CSG {
	ScalarField *_sf;
	float _t;
public:
	CSGScalarField(ScalarField *sf,float threshold = 0):_sf(sf),_t(threshold){}
	~CSGScalarField(){}
	
	virtual float eval(const glm::vec3 &worldPos){
		return -(_sf->getFromWorldPos(worldPos) - _t);
	}

	virtual std::string toString()const{return "CSGScalarField";}
};

#include "CSGCache.h"

#endif
