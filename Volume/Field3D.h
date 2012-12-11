#ifndef __FIELD3D_H__
#define __FIELD3D_H__

#define FOR(dim) for(int z = 0;z<dim.z;z++)for(int y = 0;y<dim.y;y++)for(int x = 0;x<dim.x;x++)
#define INDEX(vf,x,y,z) x+vf->getDimensions()[0]*(y+vf->getDimensions()[1]*z)

#include <glm/glm.hpp>

#include <Geometry/BoundingVolume.h>

template <typename T>
class Field3D
{
public:
	Field3D(glm::ivec3 dimensions = glm::ivec3(64,64,64),BoundingAABB boundingAABB = BoundingAABB(glm::vec3(0,0,0),glm::vec3(1,1,1)));
	virtual ~Field3D(void);

	void foreach(T (*funcPtr)(T,glm::vec3));
	void foreach(void (*funcPtr)(T&,glm::vec3));

	void set(glm::ivec3 pos,T value);
	T get(glm::ivec3 pos);
	T getFromWorldPos(glm::vec3 worldPos);
	glm::ivec3 getDimensions();
	BoundingAABB getBoundingAABB();

	void setZero();

	T getMin();
	T getMax();
	void normalize();

	T* getData();
	unsigned int getMemSize();
protected:
	unsigned int _index(glm::ivec3 pos,bool clamp = true);
	glm::vec3 _getWorldPos(glm::ivec3 pos);

	glm::ivec3 _dimensions;
	BoundingAABB _boundingAABB;
	T *_data;
private:
	void _allocate();
	void _deallocate();
};


#ifndef __FIELD3D_HPP__
#include "Field3D.hpp"
#endif

#endif