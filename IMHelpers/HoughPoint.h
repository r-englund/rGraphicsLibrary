#ifndef _HOUGHPOINT_H_
#define _HOUGHPOINT_H_


#include <cmath>

struct HoughPoint{
	int v;

	float rho,theta;
	int x,y;


	HoughPoint(int v,int x,int y,float rhoMax):
	v(v)
	{
		this->x = x;
		this->y = y;
		theta = x;
		rho = y - rhoMax;
				
		theta /= 180;
		theta *= 3.14159265359;
		/*rho /= 180;
		rho *= 3.14159265359;*/
	}

	void ykxm(float &k,float&m,int w,int h){
		k = -std::cos(theta)/sin(theta);
		m = (rho + (w/2.0)*std::cos(theta) + (h/2.0)*std::sin(theta))/std::sin(theta);
	}


	bool operator==(const HoughPoint &p)const{
		if(this == &p)
			return true;
		/*float dr = std::abs(rho - p.rho);
		if(dr>1.1)
			return false;
		float dt = std::abs(theta - p.theta);
		if(dt>=0.02)
			return false;
		return true;*/


		int dx,dy;
		dx = p.x - x;
		dy = p.y - y;
		float d = std::sqrtf(dx*dx + dy*dy);
		return d <= 5;
	}

	bool operator<(const HoughPoint &p)const{
		return v>p.v;
	}
};


#endif