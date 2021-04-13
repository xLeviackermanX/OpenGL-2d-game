#include "headers.h"
using namespace std;
#define pb push_back

Map :: Map(){
  score = 0;
  health = 100;
  srand((unsigned)time(0));
  for(int i=0;i<50;i++){
    for(int j=0;j<50;j++){
      gridH[i][j] = 1;
      gridV[i][j] = 1;
      extra[i][j] = 1;
    }
  }
  for(int i=2;i<50;i+=2){
    for(int j=2;j<50;j+=2){
      if(i==24 && j==24){
        gridH[i][j] = 1, gridV[i][j] = 1;
        continue;
      }
      if(i==2 || i==48 || j==2 || j==48){
        if(i==2 || i==48){
          gridV[i][j]=0;
          gridV[i][j+1]=0;
        }
         if(j==2 || j==48){
          gridH[i][j]=0;
          gridH[i+1][j]=0;
        }
        continue;
      }
      int num = rand()%3;
      if(num==0)
        gridV[i][j]=0,gridV[i][j+1]=0;
      else
        gridV[i][j]=1,gridV[i][j+1]=1;
      num = rand()%3;
      if(num==0)
        gridH[i][j]=0,gridH[i+1][j]=0;
      else
        gridH[i][j]=1,gridH[i+1][j]=1;
    }
  }  
  for(int i=3;i<47;i+=2){
    for(int j=3;j<47;j+=2){
      if(i==25 && j==25){
        extra[i][j] = 1, extra[i][j] = 1;
        continue;
      }
      int num = rand()%18;
      if(num==0)
        extra[i][j]=0;
      else if(num==1 || num==2)
        extra[i][j]=-1;
     
    }
  }
  eButX = 2*(rand()%23+1)+1-25.0; 
  eButY = 2*(rand()%23+1)+1-25.0;
  rButX = 2*(rand()%23+1)+1-25.0;
  rButY = 2*(rand()%23+1)+1-25.0; 
  while(eButY==rButY && eButX==rButX)
  {
    rButX = 2*(rand()%24)+1-25.0;
  rButY = 2*(rand()%24)+1-25.0;
  }
}

int Map :: Draw(unsigned int *t , unsigned int *VBO){
  vector<float> vi;
  for(int i=0;i<50;i+=2){
    for(int j=0;j<50;j+=2){
      if(gridV[i][j]==0){
        vi.insert(vi.end(),{i-25,j-25,-0.0,0.5,0.0,0.5,i-25,j-23,-0.0,0.5,0.0,0.5});
      }
      if(gridH[i][j]==0){
        vi.insert(vi.end(),{i-25,j-25,-0.0,0.5,0.0,0.5,i-23,j-25,-0.0,0.5,0.0,0.5});
      }
    }
  }
  int k = vi.size();
  float v[k];
  for(int i=0;i<k;i++){
    v[i] = vi[i];
  }
  glGenVertexArrays(1, t);
  glGenBuffers(1, VBO);
  // first parameter is for number of buffer objects to create
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(*t);

  glBindBuffer(GL_ARRAY_BUFFER, *VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
  
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  return k/6;
}

int Map :: Collision(float *x, float *y, int dir){
  if((*x)<-23.0){
    score+=100;
    return -1;
  }
  *x+=25.0 , *y+=25;

  if(dir == 0 || dir==1){
    int j;
    if(dir == 0)
      j = (*x+0.5);
    else
      j = (*x-0.5 + (1.0-((*x-0.5)-((int)(*x-0.5)))));
    int i = (*y-0.5);
    int i1 = (*y);
    int i2 = (*y+0.99);
    *x-=25.0;
    *y-=25.0;
    // std::cout<<*x+25.0<<"coordinates"<<*y+25.0<<"\n"<<i<<"index"<<j<<"\n";
    if(gridV[j][i]==0 || gridV[j][i1]==0 || gridV[j][i2]==0){
      if(dir == 0)
        *x = ((float)j)-25.0-0.51;
      else
        *x = (float)j-25.0 + 0.51;
      return 1;
    }
    int d = (*y+25.0-0.49);
    if((gridH[j][i1]==0 && d!=i1) || gridH[j][i2]==0){
      if(dir == 0)
        *x = ((float)j)-25.0-0.51;
      else
        *x = (float)j-25.0 + 1.51;
      return 1;
    }
    if(dir==1){
      j= (*x-0.5+25.0);
      // std::cout<<j<<"_index_"<<i2<<"\n"<<*x+25.0<<"_coordinates"<<*y+25.0<<"\n";
      if((gridH[j][i1]==0 && d!=i1) ||gridH[j][i2]==0)
      {
        *x = (float)j-25.0 + 1.51;
        return 1;
      }
    }
  }
  
  
  else{
    int j;
    if(dir == 2)
      j = (*y+1.0);
    else
      j = (*y-0.5 + (1.0-((*y-0.5)-((int)(*y-0.5)))));
    int i = (*x-0.5);
    int i1 = (*x+0.49);
    *x-=25.0;
    *y-=25.0;
    // std::cout<<*x+25.0<<"coordinates"<<*y+25.0<<"\n"<<i<<"index"<<j<<"\n";
    if(gridH[i][j]==0 || gridH[i1][j]==0){
      if(dir == 2)
        *y = ((float)j)-25.0-1.01;
      else
        *y = (float)j-25.0 + 0.51;
      return 1;
    }
    i = (*x+25.0);
    int d = (*x+25.0-0.49);
    if((gridV[i][j]==0 && d!=i) || gridV[i1][j]==0){
      if(dir == 2)
        *y = ((float)j)-25.0-1.01;
      else
        *y = (float)j-25.0 + 0.51;
      return 1;
    }
    if(dir==3){
      j= (*y-0.5+25.0);
      if((gridV[i][j]==0 && d!=i) || gridV[i1][j]==0)
      {
        *y = (float)j-25.0 + 1.51;
        return 1;
      }
    }
  }
  return 0;
}

void Map::Lighting(unsigned int *t, unsigned int *VBO , unsigned int *t1, unsigned int *VBO1,int *st, int *sl,float x ,float y){
  float r = 3.0;
  vector <float > vt,vl;
  for(int i=0;i<360;i+=1){
    float theta = ((float)i)*3.14159/180.0;
    float delta = 3.14159/180.0;
    vt.insert(vt.begin(),{
          x+cos(theta)*r,       y+r*sin(theta),       -0.02,    0.4,0.5,0.3,
          x+cos(theta+delta)*r, y+r*sin(theta+delta), -0.02,    0.4,0.5,0.3,
          x+0.0,                y,                    -0.02,    0.4,0.5,0.3,
    });

    vt.insert(vt.begin(),{
          x+cos(theta)*r,       y+r*sin(theta),        0.02,    0.0,0.0,0.0,
          x+cos(theta+delta)*r, y+r*sin(theta+delta),  0.02,    0.0,0.0,0.0,
          x+cos(theta+delta)*30.0,y+sin(theta+delta)*30.0,                     0.02,    0.0,0.0,0.0,

          x+cos(theta)*r,       y+r*sin(theta),        0.02,    0.0,0.0,0.0,
          x+cos(theta)*30.0, y+sin(theta)*30.0,  0.02,    0.0,0.0,0.0,
          x+cos(theta+delta)*30.0,y+sin(theta+delta)*30.0,                     0.02,    0.0,0.0,0.0,
    });
  }
  for(int i=x+20;i<x+31;i++){
    for(int j=y+20;j<y+31;j++){
      if(gridH[i][j]==0){
        float u = i-25.0 , v = j-25.0;
        float q = v-y;
        float p = u-x;
        u = 1.01*p+x; v = 1.01*q+y;
        q = 10*q + y; p = 10*p+x;
        float u1 = i-24.0 , v1 = j-25.0;
        float q1 = v1-y;
        float p1 = u1-x;
        u1 = 1.01*p1+x; v1 = 1.01*q1+y;
        q1 = 10*q1 + y; p1 = 10*p1+x;
        vt.insert(vt.begin(),{
          u,v,0.02,     0.0,0.0,0.0,
          p,q,0.02,     0.0,0.0,0.0,
          p1,q1,0.02,     0.0,0.0,0.0,

          u,v,0.02,     0.0,0.0,0.0,
          u1,v1,0.02,     0.0,0.0,0.0,
          p1,q1,0.02,     0.0,0.0,0.0
        });
      }
      if(gridV[i][j]==0){
        float u = i-25.0 , v = j-25.0;
        float q = v-y;
        float p = u-x;
        u = 1.01*p+x; v = 1.01*q+y;
        q = 100*q + y; p = 100*p+x;
        float u1 = i-25.0 , v1 = j-24.0;
        float q1 = v1-y;
        float p1 = u1-x;
        u1 = 1.01*p1+x; v1 = 1.01*q1+y;
        q1 = 100*q1 + y; p1 = 100*p1+x;
        vt.insert(vt.begin(),{
          u,v,0.02,     0.0,0.0,0.0,
          p,q,0.02,     0.0,0.0,0.0,
          p1,q1,0.02,     0.0,0.0,0.0,

          u,v,0.02,     0.0,0.0,0.0,
          u1,v1,0.02,     0.0,0.0,0.0,
          p1,q1,0.02,     0.0,0.0,0.0
        });
      }
    }
  }
  // 
  int k1 = vt.size();
  int k2  = vl.size();
  *st = k1;
  *sl = k2;
  float v[k1], v1[k2];
  for(int i=0;i<k1;i++){
    v[i] = vt[i];
  }
  for(int i=0;i<k2;i++){
    v1[i] = vl[i];
  }
  glGenVertexArrays(1, t);
  glGenBuffers(1, VBO);
  // first parameter is for number of buffer objects to create
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(*t);

  glBindBuffer(GL_ARRAY_BUFFER, *VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
  
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glGenVertexArrays(1, t1);
  glGenBuffers(1, VBO1);
  // first parameter is for number of buffer objects to create
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(*t1);

  glBindBuffer(GL_ARRAY_BUFFER, *VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v1), v1, GL_STATIC_DRAW);
  
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

int Map::DrawExtra(unsigned int *t , unsigned int *VBO){
  vector<float> vi;
  for(int i=1;i<50;i+=2){
    for(int j=1;j<50;j+=2){
      if(extra[i][j]==0){
        vi.insert(vi.end(),{i-25.0,j+0.2-25.0,0.0,1.0,0.0,0.0, i-0.2-25.0,j-25.0,0.0,1.0,0.0,0.0, i+0.2-25.0,j-25.0,0.0,1.0,0.0,0.0,});
      }
       else if(extra[i][j]==-1){
        vi.insert(vi.end(),{i-25.0,j+0.2-25.0,0.0,0.0,1.0,0.0, i-0.2-25.0,j-25.0,0.0,0.0,1.0,0.0, i+0.2-25.0,j-25.0,0.0,0.0,1.0,0.0,});
      }
    }
  }
  int k = vi.size();
  float v[k];
  for(int i=0;i<k;i++){
    v[i] = vi[i];
  }
  glGenVertexArrays(1, t);
  glGenBuffers(1, VBO);
  // first parameter is for number of buffer objects to create
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(*t);

  glBindBuffer(GL_ARRAY_BUFFER, *VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
  
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  return k/6;
}

int Map :: CollisionExtra(float *x, float *y, int dir){
  Map::CollisionCoin(x,y,dir);
  *x+=25.0 , *y+=25;
  int counter  = 0;
  if(dir == 0 || dir==1){
    int j;
    if(dir == 0)
      j = (*x+0.5);
    else
      j = (*x-0.5 + (1.0-((*x-0.5)-((int)(*x-0.5)))));
    int i = (*y-0.5);
    int i1 = (*y);
    int i2 = (*y+0.99);
    *x-=25.0;
    *y-=25.0;
    // std::cout<<*x+25.0<<"coordinates"<<*y+25.0<<"\n"<<i<<"index"<<j<<"\n";
    if(extra[j][i]==0 || extra[j][i1]==0 || extra[j][i2]==0){
      if(extra[j][i]==0){
        extra[j][i]=1;
        counter++;
      }
      if(extra[j][i1]==0){
        extra[j][i1]=1;
        counter++;
      }
      if(extra[j][i2]==0){
        extra[j][i2]=1;
        counter++;
      }
      
    }
    int d = (*y+25.0-0.49);
    if((extra[j][i1]==0 && d!=i1) || extra[j][i2]==0){
      if(extra[j][i1]==0 && d!=i1){
        extra[j][i1]=1;
        counter++;
      }
      if(extra[j][i2]==0){
        extra[j][i2]=1;
        counter++;
      }
    }
    if(dir==1){
      j= (*x-0.5+25.0);
      // std::cout<<j<<"_index_"<<i2<<"\n"<<*x+25.0<<"_coordinates"<<*y+25.0<<"\n";
      if(extra[j][i1]==0 && d!=i1)
      {
        extra[j][i1]=1;
        counter++;
      }
      if(extra[j][i2]==0){
        extra[j][i2]=1;
        counter++;
      }
    }
    return counter;
  }
  
  
  else{
    int j;
    if(dir == 2)
      j = (*y+1.0);
    else
      j = (*y-0.5 + (1.0-((*y-0.5)-((int)(*y-0.5)))));
    int i = (*x-0.5);
    int i1 = (*x+0.49);
    *x-=25.0;
    *y-=25.0;
    // std::cout<<*x+25.0<<"coordinates"<<*y+25.0<<"\n"<<i<<"index"<<j<<"\n";
    if(extra[i][j]==0 || extra[i1][j]==0){
      if(extra[i][j]==0){
        extra[i][j]=1;
        counter++;
      }
      if(extra[i1][j]==0){
        extra[i1][j]=1;
        counter++;
      }
    }
    i = (*x+25.0);
    int d = (*x+25.0-0.49);
    if((extra[i][j]==0 && d!=i) || extra[i1][j]==0){
      if(extra[i][j]==0 && d!=i){
        extra[i][j]=1;
        counter++;
      }
      if(extra[i1][j]==0){
        extra[i1][j]=1;
        counter++;
      }
    }
    if(dir==3){
      j= (*y-0.5+25.0);
      if(extra[i][j]==0 && d!=i){
        extra[i][j]=1;
        counter++;
      }
      if(extra[i1][j]==0){
        extra[i1][j]=1;
        counter++;
      }
    }
  }
  if(counter>0)
    health -= 10;
  return counter;
}


int Map :: CollisionCoin(float *x, float *y, int dir){
  
  *x+=25.0 , *y+=25;
  int counter  = 0;
  if(dir == 0 || dir==1){
    int j;
    if(dir == 0)
      j = (*x+0.5);
    else
      j = (*x-0.5 + (1.0-((*x-0.5)-((int)(*x-0.5)))));
    int i = (*y-0.5);
    int i1 = (*y);
    int i2 = (*y+0.99);
    *x-=25.0;
    *y-=25.0;
    // std::cout<<*x+25.0<<"coordinates"<<*y+25.0<<"\n"<<i<<"index"<<j<<"\n";
    if(extra[j][i]==-1 || extra[j][i1]==-1 || extra[j][i2]==-1){
      if(extra[j][i]==-1){
        extra[j][i]=1;
        counter++;
      }
      if(extra[j][i1]==-1){
        extra[j][i1]=1;
        counter++;
      }
      if(extra[j][i2]==-1){
        extra[j][i2]=1;
        counter++;
      }
      
    }
    int d = (*y+25.0-0.49);
    if((extra[j][i1]==-1 && d!=i1) || extra[j][i2]==-1){
      if(extra[j][i1]==-1 && d!=i1){
        extra[j][i1]=1;
        counter++;
      }
      if(extra[j][i2]==-1){
        extra[j][i2]=1;
        counter++;
      }
    }
    if(dir==1){
      j= (*x-0.5+25.0);
      // std::cout<<j<<"_index_"<<i2<<"\n"<<*x+25.0<<"_coordinates"<<*y+25.0<<"\n";
      if(extra[j][i1]==-1 && d!=i1)
      {
        extra[j][i1]=1;
        counter++;
      }
      if(extra[j][i2]==-1){
        extra[j][i2]=1;
        counter++;
      }
    }
    return counter;
  }
  
  
  else{
    int j;
    if(dir == 2)
      j = (*y+1.0);
    else
      j = (*y-0.5 + (1.0-((*y-0.5)-((int)(*y-0.5)))));
    int i = (*x-0.5);
    int i1 = (*x+0.49);
    *x-=25.0;
    *y-=25.0;
    // std::cout<<*x+25.0<<"coordinates"<<*y+25.0<<"\n"<<i<<"index"<<j<<"\n";
    if(extra[i][j]==-1 || extra[i1][j]==-1){
      if(extra[i][j]==-1){
        extra[i][j]=1;
        counter++;
      }
      if(extra[i1][j]==-1){
        extra[i1][j]=1;
        counter++;
      }
    }
    i = (*x+25.0);
    int d = (*x+25.0-0.49);
    if((extra[i][j]==-1 && d!=i) || extra[i1][j]==-1){
      if(extra[i][j]==-1 && d!=i){
        extra[i][j]=1;
        counter++;
      }
      if(extra[i1][j]==-1){
        extra[i1][j]=1;
        counter++;
      }
    }
    if(dir==3){
      j= (*y-0.5+25.0);
      if(extra[i][j]==-1 && d!=i){
        extra[i][j]=1;
        counter++;
      }
      if(extra[i1][j]==-1){
        extra[i1][j]=1;
        counter++;
      }
    }
  }
  if(counter  > 0){
    if(light == 0)
      score+= 10;
    else
      score+= 20;
  }
  return counter;
}

int Map::DrawEnemyButton(unsigned int *t, unsigned int *VBO){
  float x = eButX , y = eButY;
  float v[360*18];
  for(int i=0;i<360;i+=1){
    float theta = ((float)i)*3.14159/180.0;
    float delta = 3.14159/180.0;
    float tempTriangle[] = {
      x+cos(theta)*0.5,       y+0.5*sin(theta),       0.0,    1.0,0.3,0.0,
      x+cos(theta+delta)*0.5, y+0.5*sin(theta+delta), 0.0,    1.0,0.3,0.0,
      x+0.0,                  y,                      0.0,    1.0,0.3,0.0,
    };
    for(int j=0;j<18;j++){
      v[i*18+j] = tempTriangle[j];
    }
  }
  glGenVertexArrays(1, t);
  glGenBuffers(1, VBO);
  // first parameter is for number of buffer objects to create
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(*t);

  glBindBuffer(GL_ARRAY_BUFFER, *VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
  
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  return 0;
}
int Map::DrawReleaseButton(unsigned int *t,unsigned int *VBO){
  float x = rButX , y = rButY;
  float v[360*18];
  for(int i=0;i<360;i+=1){
    float theta = ((float)i)*3.14159/180.0;
    float delta = 3.14159/180.0;
    float tempTriangle[] = {
      x+cos(theta)*0.5,       y+0.5*sin(theta),       0.0,    1.0,0.9,0.0,
      x+cos(theta+delta)*0.5, y+0.5*sin(theta+delta), 0.0,    1.0,0.9,0.0,
      x+0.0,                  y,                      0.0,    1.0,0.9,0.0,
    };
    for(int j=0;j<18;j++){
      v[i*18+j] = tempTriangle[j];
    }
  }
  glGenVertexArrays(1, t);
  glGenBuffers(1, VBO);
  // first parameter is for number of buffer objects to create
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(*t);

  glBindBuffer(GL_ARRAY_BUFFER, *VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
  
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  return 0;
}

void Map::computeShortestPath(){
  for(int i=0;i<50;i++){
    for(int j=0;j<50;j++){
      for(int i1=0;i1<50;i1++){
        for(int j1 =0;j1<50;j1++){
          dp[i][j][i1][j1] = 1e6;
        }
      }
      dp[i][j][i][j] = 0;
    }
  }
  // std::cout<<dp[3][3][3][3]<<"\n";
  for(int i=3;i<48;i++){
    for(int j=3;j<48;j++){
      if(gridH[i][j]==0 || gridV[i][j]==0)
        continue;
      std::queue<pair<int , int>> q;
      int vis[50][50];
      for(int m=0;m<50;m++){
        for(int n=0;n<50;n++)
          vis[m][n]=0;
      }
      vis[i][j]=1;
      q.push(make_pair(i,j));
      while(!q.empty()){
        int x = q.front().first , y = q.front().second;
        // std::cout<<x<<"  "<<y<<"\n";
        if(x>3 && dp[i][j][x-1][y] == 1e6 && gridH[x-2][y]==1 && gridV[x-1][y]==1 && vis[x-1][y]==0){
          dp[i][j][x-1][y] = dp[i][j][x][y]+1;
          vis[x-1][y]=1;
          q.push(make_pair(x-1,y));
        }
        if(x<48 && dp[i][j][x+1][y] == 1e6 && gridH[x+1][y]==1 && gridV[x+1][y]==1 && vis[x+1][y]==0){
          dp[i][j][x+1][y] = dp[i][j][x][y]+1;
          vis[x+1][y]=1;
          q.push(make_pair(x+1,y));
        }
        if(y>3 && dp[i][j][x][y-1] == 1e6 && gridH[x][y-1]==1 && gridV[x][y-2]==1 && vis[x][y-1]==0){
          dp[i][j][x][y-1] = dp[i][j][x][y]+1;
          vis[x][y-1]=1;
          q.push(make_pair(x,y-1));
        }
         if(y<48 && dp[i][j][x][y+1] == 1e6 && gridH[x][y+1]==1 && gridV[x][y+1]==1 && vis[x][y+1]==0){
          dp[i][j][x][y+1] = dp[i][j][x][y]+1;
          vis[x][y+1]=1;
          q.push(make_pair(x,y+1));
        }
        q.pop();
      }
    }
  }

  // for(int i=3;i<6;i++){
  //   for(int j=3;j<6;j++){
  //     for(int i1=3;i1<6;i1++){
  //       for(int j1 =3;j1<6;j1++){
  //         std::cout<<dp[i][j][i1][j1]<<" --- "<<i<<","<<j<<" to "<<i1<<","<<j1<<"\n";
  //       }
  //     }
  //   }
  // }
  // std::cout<<"walls: "<<gridH[4][3]<<" "<<gridV[4][3]<<"\n";
}

void Map::openEntry(){
  for(int i=-2;i<=2;i++){
    for(int j=-2;j<=2;j++){
      gridH[3+i][25+j] = 1;
      gridV[3+i][25+j] = 1;
    }
  }
}