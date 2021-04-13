#ifndef ENEMY_H
#define ENEMY_H

class Enemy{
private:
    /* data */
    float head[180*3*6];
    float body[2*3*6];
    float eyes[2*3*6]; 
    
public:
float centre[3];
    Enemy(float x, float y ,float z);
    void Move(float x, float y);
    void SetCoordinates();
    void Draw(unsigned int *t,unsigned int *VBO);
    int direction(int u, int v, int dp[50][50][50][50]);
};

#endif
