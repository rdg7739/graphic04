#ifndef VRTX_H
#define VRTX_H


class vrtx{
public:
	float x;
	float y;
 	float z;
	float a1;
	float a2;
	float a3;

	vrtx(){
 	x = 0;
	y = 0;
	z = 0;
	a1 = 0;
	a2 = 0;
	a3 = 0;
}	
	void setVRTX(float dx, float dy, float dz, float da1, float da2, float da3){
	x = dx;
 	y = dy;
	z = dz;
	a1 = da1;
	a2 = da2;
	a3 = da3;
	}


};

#endif
