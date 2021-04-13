#include "headers.h"


Character :: Character(float x, float y, float z){
  centre[0] = x , centre[1] = y, centre[2] = z;
  Character :: SetCoordinates();
}

void Character :: SetCoordinates(){
  float x  = centre[0], y= centre[1] , z = centre[2];
  float tempBody[] = {//coordinate            Colors
    x+0.5,y+0.5,z+0.0,    0.4,0.0,0.0,
    x+0.5,y-0.5,z+0.0,    0.4,0.0,0.0,
    x-0.5,y+0.5,z+0.0,    0.4,0.0,0.0,

    x-0.5,y+0.5,z+0.0,    0.4,0.0,0.0,
    x-0.5,y-0.5,z+0.0,    0.4,0.0,0.0,
    x+0.5,y-0.5,z+0.0,    0.4,0.0,0.0    
  };
  for(int i=0;i<180;i+=1){
    float theta = ((float)i)*3.14159/180.0;
    float delta = 3.14159/180.0;
    float tempTriangle[] = {
      x+cos(theta)*0.5,       y+0.5+0.5*sin(theta),       z+0.0,    0.5,0.0,0.0,
      x+cos(theta+delta)*0.5, y+0.5+0.5*sin(theta+delta), z+0.0,    0.5,0.0,0.0,
      x+0.0,                  y+0.5,                      z+0.0,    0.5,0.0,0.0,
    };
    for(int j=0;j<18;j++){
      head[i*18+j] = tempTriangle[j];
    }
  }

  float tempEyes[] = {
    x+0.5,y+0.9,z+0.01,    0.5,0.5,0.0,
    x+0.5,y+0.7,z+0.01,    0.5,0.5,0.0,
    x-0.0,y+0.9,z+0.01,    0.5,0.5,0.0,

    x-0.0,y+0.9,z+0.01,    0.5,0.5,0.0,
    x-0.0,y+0.7,z+0.01,    0.5,0.5,0.0,
    x+0.5,y+0.7,z+0.01,    0.5,0.5,0.0,  
  };
  for(int i=0;i<36;i++){
    eyes[i] = tempEyes[i];
    body[i] = tempBody[i];
  }

}

void Character::Move(float x, float y, float z){
  centre[0] = x, centre[1] = y,centre[2] = z;
  Character::SetCoordinates();
}

void Character ::Draw(unsigned int *t, unsigned int *VBO){
  int s1 = 180*3*6,s2 = 36, s3 = 36;
  float v[s1+s2+s3];
  for(int i=0;i<s3;i++){
    v[i] = eyes[i-s1-s2];
  }

  for(int i=s3;i<s1+s3;i++){
    v[i] =head[i];
  }
  for(int i=s3+s1;i<s1+s2+s3;i++){
    v[i] = body[i-s1];
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

}
