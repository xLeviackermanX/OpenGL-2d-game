#ifndef CHARACTER_H
#define CHARACTER_H

class Character{
private:
    /* data */
    float head[180*3*6];
    float body[2*3*6];
    float eyes[2*3*6]; 
    float centre[3];
public:
    Character(float x, float y, float z);
    void Move(float x, float y, float z);
    void SetCoordinates();
    void Draw(unsigned int *t,unsigned int *VBO);
};

#endif
