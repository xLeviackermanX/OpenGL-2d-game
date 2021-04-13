#ifndef MAP_H
#define MAP_H

class Map{
  private:
    int gridH[50][50];
    int gridV[50][50];
    int extra[50][50];
  public:
    int score;
    int light;
    int health;
    int dp[50][50][50][50];
    float eButX, eButY,rButX,rButY;
    Map();
    int Draw(unsigned int *t , unsigned int *VBO);
    int Collision(float *x , float *y, int dir);
    void Lighting(unsigned int *t, unsigned int *VBO , unsigned int *t1, unsigned int *VBO1,int *st, int *sl,float x ,float y);
    int DrawExtra(unsigned int *t , unsigned int *VBO);
    int CollisionExtra(float *x , float *y , int dir);
    int CollisionCoin(float *x, float *y, int dir);
    int DrawEnemyButton(unsigned int *t, unsigned int *VBO); 
    int DrawReleaseButton(unsigned int *t,unsigned int *VBO);
    void computeShortestPath();
    void openEntry();
};

#endif
