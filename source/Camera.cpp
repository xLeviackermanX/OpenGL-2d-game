#include "headers.h"

Camera :: Camera(float x, float y,float z){
    pos[0] = x;pos[1] = y;pos[2] = z;
    front[0] = 0.0;front[1] = 0.0;front[2] = z-1.0;
    right[0] = 0.0 ; right[1] = 0.0; right[2] = 1.0;
    up[0] = 0.0 ; up[1] = 1.0; up[2] = 0.0; 
}

void Camera :: Move(float x, float y){
    pos[0] = x; pos[1] = y;
}

float * Camera :: getPos(){
    return pos;
}

int checkIntersection(float a, float b,float c,float d, float p, float q,float r, float s){
    float m1, m2,c1,c2;
    float v1 , v2 ;
    if(a-c>-0.000001 && a-c<0.000001){
        v1 = (p-a)*(r-a);
    }
    else{
        m1 = (d-b)/(c-a);
        c1 = b-a*m1;
        v1 = (m1*p+c1-q)*(m1*r+c1-s);
    }
    if(p-r<0.000001 && p-r>-0.000001){
        v2= (a-p)*(c-p);
    }
    else{
        m2 = (s-q)/(r-p);
        c2 = q-p*m2;
        v2 = (m2*a+c2-b)*(m2*c+c2-d);
    }
    if(v1<=0 && v2<=0)
        return 1;
    else
        return 0;
}