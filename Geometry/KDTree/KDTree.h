#ifndef _KDTREE_H_
#define _KDTREE_H_

#include <Base\Object.h>

#include <vector>

#include <boost\iterator.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#define KD_TYPE dataType,dimmensions,floatPrecision
#define KD_TEMPLATE template <typename dataType,unsigned int dimmensions,typename floatPrecision>
#define KD_TREE		KDTree<KD_TYPE>
#define KD_NODE		KDNode<KD_TYPE>
#define KD_NODE_IT	KDNodeIterator<KD_TYPE>
#define KD_DATA_IT	KDDataIterator<KD_TYPE>
#define KD_POS_IT	KDPositionIterator<KD_TYPE>

KD_TEMPLATE class KDTree;
KD_TEMPLATE class KDNode;


#include "KDIterator.hpp"

KD_TEMPLATE
struct __KD_NEAR_NODE__{
	KD_NODE *node;
	float sqDist;
	bool operator<(const __KD_NEAR_NODE__<KD_TYPE> &rhs) const { return sqDist > rhs.sqDist; }
};

template <typename dataType,unsigned int dimmensions,typename floatPrecision = double> 
class KDNode: public Object{
	friend class KD_TREE;
	friend class KD_NODE_IT;
	friend class KD_DATA_IT;
	friend class KD_POS_IT;
	KDNode *_parent;
	KDNode *_left;
	KDNode *_right;
	//KD_TREE *_tree;
	dataType _data;
	unsigned int _dimmension;
	floatPrecision _pos[dimmensions];

	bool _goRight(const floatPrecision pos[dimmensions])const;
	bool _compare(const floatPrecision pos[dimmensions])const;
public:
	KDNode(KD_TREE *tree,const floatPrecision pos[dimmensions],const dataType &data,KDNode *parent = 0);
	virtual ~KDNode();
	
	bool isLeaf()const;
	bool isRightLeaf()const;
	bool isLeftLeaf()const;

	unsigned long depth()const;
	unsigned long size()const;

	dataType &get();
	dataType *getDataAsPointer(){return &_data;}
	floatPrecision* getPosition();

	bool isOk()const;

	KDNode *findMin(unsigned int dimmensions); 
	KDNode *findMax(unsigned int dimmensions); 

	KDNode *insert(const floatPrecision pos[dimmensions], const dataType &data);
	KDNode *find(const floatPrecision pos[dimmensions]);
	
	KDNode *getRightChild(){return _right;}
	KDNode *getLeftChild(){return _left;}
	std::pair<KDNode*,KDNode*> getChilds(){return std::pair<KDNode*,KDNode*>(_left,_right);}

	KD_NODE* findNearest(const floatPrecision pos[dimmensions],KDNode *nearest);
	void findNNearest(const floatPrecision pos[dimmensions],int amount,std::vector<__KD_NEAR_NODE__<KD_TYPE>> &current);
	void findCloseTo(const floatPrecision pos[dimmensions],const floatPrecision squaredDistance,std::vector<KDNode*> &nodes);

	static void swap(KD_NODE* n0,KD_NODE* n1);
	
	virtual std::string toString() const;
};



template <typename dataType,unsigned int dimmensions,typename floatPrecision = double> 
class KDTree: public Object{
public:
	typedef KDNode<KD_TYPE> Node;
private:
	Node *root;
	KDTree(const KDTree &tree);
	KDTree& operator=( const KDTree& rhs );
public:
	typedef KD_NODE_IT NodeIterator;
	typedef KD_DATA_IT DataIterator;
	typedef KD_POS_IT PositionIterator;
	
	KDTree();
	virtual ~KDTree();

	void erase(Node *node);
	
	KD_NODE_IT begin();
	KD_NODE_IT end();
	KD_DATA_IT begin_data();
	KD_DATA_IT end_data();
	KD_POS_IT begin_position();
	KD_POS_IT end_position();

	bool isOk()const;
	bool empty()const{return root==0;}

	void clear();

	unsigned long depth()const;
	unsigned long size()const;
	
	std::vector<dataType> getAsVector();

	Node *getRoot(){return root;}

	Node* findMin(unsigned int dimmensions);
	Node* findMax(unsigned int dimmensions);

	Node *insert(const floatPrecision pos[dimmensions], const dataType &data);
	Node *find(const floatPrecision pos[dimmensions]);
	
	Node *findNearest(const floatPrecision pos[dimmensions]);
	std::vector<Node*> findCloseTo(const floatPrecision pos[dimmensions],const floatPrecision distance);
	std::vector<Node*> findNNearest(const floatPrecision pos[dimmensions],int amount);

	virtual std::string toString() const;
};


template <typename dataType,typename floatPrecision = float> class K2DTree : public KDTree<dataType,2,floatPrecision>{
public:
	K2DTree():KDTree(){}
	virtual ~K2DTree(){}

	Node *insert(const glm::vec2 pos, const dataType &data){
		return KDTree<dataType,2,floatPrecision>::insert((const float *)glm::value_ptr(pos),data);
	}
	Node *find(const glm::vec2 pos){
		return KDTree<dataType,2,floatPrecision>::find((const float *)glm::value_ptr(pos));
	}
	
	Node *findNearest(const glm::vec2 pos){
		return KDTree<dataType,2,floatPrecision>::findNearest((const float *)glm::value_ptr(pos));
	}
	std::vector<Node*> findCloseTo(const glm::vec2 pos,const floatPrecision distance){
		return KDTree<dataType,2,floatPrecision>::findCloseTo((const float *)glm::value_ptr(pos),distance);
	}
};

template <typename dataType,typename floatPrecision = float> class K3DTree : public KDTree<dataType,3,floatPrecision>{
public:
	K3DTree():KDTree(){}
	virtual ~K3DTree(){}

	Node *insert(const glm::vec3 pos, const dataType &data){
		return KDTree<dataType,3,floatPrecision>::insert((const float *)glm::value_ptr(pos),data);
	}
	Node *find(const glm::vec3 pos){
		return KDTree<dataType,3,floatPrecision>::find((const float *)glm::value_ptr(pos));
	}
	
	Node *findNearest(const glm::vec3 pos){
		return KDTree<dataType,3,floatPrecision>::findNearest((const float *)glm::value_ptr(pos));
	}
	std::vector<Node*> findCloseTo(const glm::vec3 pos,const floatPrecision distance){
		return KDTree<dataType,3,floatPrecision>::findCloseTo((const float *)glm::value_ptr(pos),distance);
	}
};

template <typename dataType,typename floatPrecision = float> class K4DTree : public KDTree<dataType,4,floatPrecision>{
public:
	K4DTree():KDTree(){}
	virtual ~K4DTree(){}

	Node *insert(const glm::vec4 pos, const dataType &data){
		return KDTree<dataType,4,floatPrecision>::insert((const float *)glm::value_ptr(pos),data);
	}
	Node *find(const glm::vec4 pos){
		return KDTree<dataType,4,floatPrecision>::find((const float *)glm::value_ptr(pos));
	}
	
	Node *findNearest(const glm::vec4 pos){
		return KDTree<dataType,4,floatPrecision>::findNearest((const float *)glm::value_ptr(pos));
	}
	std::vector<Node*> findCloseTo(const glm::vec4 pos,const floatPrecision distance){
		return KDTree<dataType,4,floatPrecision>::findCloseTo((const float *)glm::value_ptr(pos),distance);
	}
};

#ifndef _KDTREE_HPP_
#include "KDTree.hpp"
#endif
#ifndef _KDNODE_HPP_
#include "KDNode.hpp"
#endif


#endif
