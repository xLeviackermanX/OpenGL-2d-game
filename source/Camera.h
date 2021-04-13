#ifndef CAMERA_H
#define CAMERA_H

class Camera{
private:
    float pos[3];
    float front[3];
    float up[3];
    float right[3];
public:
    Camera(float x, float y, float z);
    void Move(float x, float y);
    float *getPos();
    
};
int checkIntersection(float a, float b,float c,float d, float p, float q,float r, float s);

#endif
