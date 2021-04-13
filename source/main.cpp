#include "headers.h"
#include<map>
#include <filesystem>
Map map;
Character player(0.0,0.0,0.0);
Enemy enemy(-22.0,-22.0,0.0);
unsigned int t,VBO;
unsigned int t1,VBO1,teb,VBOeb,trb,VBOrb;
unsigned int te , VBOe;
int prevX = -22 , prevY = -22;
unsigned int VA;
float delx=0.0, dely=0.0;
int task=0, countLines;
int release = 0;
int frameCounter = 0;
int mod = 20;
int isEnemy=1;
int game=1;
    unsigned int VB;
struct Charac {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

std::map<GLchar, Charac> Characters;
float health = 100;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
void RenderText(unsigned int *s, std::string text, float x, float y, float scale);

std::string parseNumber(int num){
    std::string str;
    if(num==0)
        str = "0";
    while(num){
        str+= '0'+(char)(num%10);
        num/=10;
    }
    std::string org;
    int k = str.size();
    for(int i=k-1;i>=0;i--){
        org+=str[i];
    }
    return org;
}


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float radius = 10.0f;
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  20.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f,  0.0f);
glm::vec3 origin      = glm::vec3(0.0,0.0f,0.0f);
glm::vec3 or1 = glm::vec3(10.0f , 0.0f , 0.0f);
glm::vec3 or2   = glm::vec3(0.0f, 0.0f,  -10.0f);
glm::vec3 or3 = glm::vec3(0.0f , 10.0f , 0.0f);
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;
float cameraSpeed = 0.02f;

    int flag = 0;
     
    unsigned int vt,vl,vbot,vbol;
    int st,sl;
// "   gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
    //  "   gl_Position = model;\n"
    "   ourColor = aColor;\n"
    "   TexCoord = aTexCoord;\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "in vec2 TexCoord;\n"
    "uniform sampler2D ourTexture;\n"
    "uniform int isText;\n"
    "void main()\n"
    "{\n"
    "if(isText!=0){\n"
    "   FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);\n"
    "}\n"
    "else{\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
    "}\n"
    "}\n\0";

unsigned int to , VBOo;

int main()
{
    // glfw: initialize and configure
    map.light = 0;
   
    // how to handle the windows n all are done with this
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //   glEnable(GL_CULL_FACE);
   
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     
    // glMatrixMode( GL_PROJECTION ); 
    // glMatrixMode( GL_MODELVIEW );
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers connect to opengl implementaion from driver
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
   
   // unsigned int t1 = drawTriangle(v1);
    // You can unbind the t1 afterwards so other t1 calls won't accidentally modify this t1, but this rarely happens. Modifying other

   
    
    player.Draw(&t , &VBO);
    enemy.Draw(&te,&VBOe);
    // std::cout<<"yoman!\n";
    map.computeShortestPath();
    std::cout<<"hello!\n";
    countLines = map.Draw(&t1, &VBO1);
    int countObstacles = map.DrawExtra(&to,&VBOo);
    map.DrawEnemyButton(&teb,&VBOeb);
    map.DrawReleaseButton(&trb,&VBOrb);
    std::cout<<"release:"<<map.rButX<<" "<<map.rButY<<"\n"<<"enemy:"<<map.eButX<<" "<<map.eButY<<"\n";
    // t1s requires a call to glBindVertexArray anyways so we generally don't unbind t1s (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);
    glUseProgram(shaderProgram);
    float a =1.0f, b=1.0f;	

     FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }
	
	// load font as face
    FT_Face face;
    if (FT_New_Face(ft, "../font/arial.ttf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }
    else {
        // set size to load glyphs as
        
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Charac character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Charac>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    float nav[] = {
    -12.0,10.0,0.01,    0.0,0.0,0.0,
    -12.0,6.0,0.01,    0.0,0.0,0.0,
     12.0,10.0,0.01,    0.0,0.0,0.0,

     12.0,10.0,0.01,    0.0,0.0,0.0,
     12.0,6.0,0.01,    0.0,0.0,0.0,
    -12.0,6.0,0.01,    0.0,0.0,0.0,  
    };
    unsigned int tn,VBOn;
     glGenVertexArrays(1,&tn);
  glGenBuffers(1, &VBOn);
  // first parameter is for number of buffer objects to create
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(tn);

  glBindBuffer(GL_ARRAY_BUFFER, VBOn);
  glBufferData(GL_ARRAY_BUFFER, sizeof(nav), nav, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &VA);
    glGenBuffers(1, &VB);
    glBindVertexArray(VA);
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 8, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),  (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),  (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

   
     glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
      std::string nam = "projection";
      int location = glGetUniformLocation(shaderProgram,"projection" );
      if(location == -1)
      {
          std::cout<<"Found wrong location\n";
      }
           glUniformMatrix4fv(location, 1, GL_FALSE, &projection[0][0]);
           glUniform1i(glGetUniformLocation(shaderProgram, "isText"), 0); 
   
        //    std::cout<<*nam.c_str()<<std::endl;
    // as we only have a single shader, we could also just activate our shader once beforehand if we want to 

    // render loop
    glEnable(GL_DEPTH_TEST);
// Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // std::cout<<checkIntersection(0,0,5,0,1,1,1,-1);
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
         float currentFrame = glfwGetTime();
         if((int)currentFrame>150)
                game = 0;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        // render
        // ------
        if(map.light==1 || game==0)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        else
         glClearColor(0.4f, 0.5f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if(flag!=1){
         glm::mat4 view = glm::lookAt(cameraPos, cameraFront+cameraPos , cameraUp);
          glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        }
        else{
        // cameraPos = glm::vec3(0.0f, 0.0f , 3.0f);
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        cameraPos[0] = camX;
        cameraPos[2] = camZ;
        origin = cameraPos+cameraFront;
        glm::mat4 view;
        view = glm::lookAt(cameraPos, origin, glm::vec3(0.0, 1.0, 0.0));  
         glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        }
       
       

        // render the triangle
        // glBindVertexArray(t[0]);
        // glDrawArrays(GL_TRIANGLES, 0, 3);  
          
        glBindVertexArray(t); 
        for (int i=0;i<1;i++){
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, glm::vec3(cameraPos[0],cameraPos[1],0.0f));
            float angle = 0.0f;
            if(flag==2)
                angle = glfwGetTime()*10.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
            // model = glm::translate(model, -origin);
            std::string name = "model";
           glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
          
        }

          glDrawArrays(GL_TRIANGLES, 0, 184*3);
          glBindVertexArray(tn);
          glDrawArrays(GL_TRIANGLES, 0, 6);
          std::string str = "Health:";
           str += parseNumber((int)health);
            RenderText(&shaderProgram, str, -10.0, 7.5, 0.015);
            str = "Tasks:";  
            str += parseNumber((int)task);
            str += "/2";
            RenderText(&shaderProgram, str, 7.5, 7.5, 0.015);
            str = "Score:";
            str += parseNumber((int)map.score);
            RenderText(&shaderProgram, str, -2.0, 7.5, 0.015);
            if(map.light==0){
                str = "Light:on";
            }
            else{
                str = "Light:off";
            }
            RenderText(&shaderProgram, str, -6.0, 6.7, 0.015);
            str = "Time:";
            str += parseNumber((int)currentFrame);
            
            RenderText(&shaderProgram, str, 5.0, 6.7, 0.015);
            if(game==0){
                RenderText(&shaderProgram , "Game Over!",-6.0,0.0,0.05);
            }
          glBindVertexArray(t1);
          
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, glm::vec3(0.0,0.0,0.0f));
            // model = glm::translate(model, -origin);
            std::string name = "model";
           glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
        
          glDrawArrays(GL_LINES,0,countLines);  
          if(release==1){
            int leftObstacles = map.DrawExtra(&to,&VBOo);
            health = std::max((double)map.health,0.0);
            if(health < 1.0){
                game = 0;
            }
            glBindVertexArray(to);
          glDrawArrays(GL_TRIANGLES , 0 , countObstacles); 
          }
          else{
               glBindVertexArray(trb);
               glDrawArrays(GL_TRIANGLES , 0 , 360*3); 
          }
          
          if(isEnemy==1){  
            if(frameCounter==0){
                if(delx>0){
                    enemy.centre[0] = prevX+1; enemy.centre[1] = prevY;  
                }
                else if(delx<0){
                    enemy.centre[0] = prevX-1; enemy.centre[1] = prevY;  
                }
                else if(dely>0){
                    enemy.centre[0] = prevX; enemy.centre[1] = prevY+1;  
                }
                if(dely<0){
                    enemy.centre[0] = prevX; enemy.centre[1] = prevY-1;  
                }
                prevX = enemy.centre[0] ; prevY = enemy.centre[1];
                int dir = enemy.direction((int)(cameraPos[0]+25.0),(int)(cameraPos[1]+25.0),map.dp);
            //    std::cout<<dir<<"\n";
                if(dir==-1){
                    delx = 0.0, dely = 0.0;
                }
                else if(dir ==0){
                     delx = 0.05, dely = 0.0;
                }
                 else if(dir ==1){
                     delx = -0.05, dely = 0.0;
                }
                 else if(dir ==2){
                     delx = 0.0, dely = 0.05;
                }
                 else if(dir ==3){
                     delx = 0.0, dely = -0.05;
                }
                else if(dir == -2){
                    game = 0;
                }
            }
            enemy.Move(delx,dely);
            frameCounter = (frameCounter+1)%mod;
            enemy.Draw(&te,&VBOe);
          glBindVertexArray(te);
          glDrawArrays(GL_TRIANGLES, 0 , 184*3);
          glBindVertexArray(teb);
               glDrawArrays(GL_TRIANGLES , 0 , 360*3);
          }
        
        if(map.light==1)
        {
            map.Lighting(&vt,&vbot,&vl,&vbol,&st,&sl,cameraPos[0],cameraPos[1]);
            glBindVertexArray(vt);
             glDrawArrays(GL_TRIANGLES, 0, (st/6));
             glBindVertexArray(vl);
             glDrawArrays(GL_LINES,0,(sl/6));
        }  
        
            // glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &model[0]);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glDeleteVertexArrays(1, &t1);
    // glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    cameraSpeed = 2.5 * deltaTime; 
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
        if(game==1){
         if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            cameraPos += cameraSpeed * cameraUp;
            int l = map.Collision(&cameraPos[0],&cameraPos[1],2);
            if(l==-1)
                game = 0;
            if(release ==1)
                int h = map.CollisionExtra(&cameraPos[0],&cameraPos[1],2);
           
         //   std::cout<<cameraPos[0]<<" "<<cameraPos[1]<<std::endl;
            origin  = cameraPos + cameraFront;
            //player.Move(cameraPos[0],cameraPos[1],0.0);
            //player.Draw(&t,&VBO);
            // std::cout<<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;
         }
         if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            cameraPos -= cameraSpeed * cameraUp;
             origin  = cameraPos + cameraFront;
             int l = map.Collision(&cameraPos[0],&cameraPos[1],3);
             if(l==-1)
                game = 0;
             if(release ==1)
             int h = map.CollisionExtra(&cameraPos[0],&cameraPos[1],2);
            
             //player.Move(cameraPos[0],cameraPos[1],0.0);
            //player.Draw(&t,&VBO);

             // std::cout<<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;
}
         if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            cameraPos -= cameraRight * cameraSpeed;
            origin  = cameraPos + cameraFront;
            int l = map.Collision(&cameraPos[0],&cameraPos[1],1);
            if(l==-1)
                game = 0;
            if(release ==1)
            int h = map.CollisionExtra(&cameraPos[0],&cameraPos[1],2);
           
            // player.Move(cameraPos[0],cameraPos[1],0.0);
            //player.Draw(&t,&VBO);

            // std::cout<<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;
         }
         if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            cameraPos += cameraRight* cameraSpeed;
            origin  = cameraPos + cameraFront;
            int l = map.Collision(&cameraPos[0],&cameraPos[1],0);
            if(l==-1)
                game = 0;
            if(release ==1)
            int h = map.CollisionExtra(&cameraPos[0],&cameraPos[1],2);
            
           // player.Move(cameraPos[0],cameraPos[1],0.0);
           // player.Draw(&t,&VBO);
         }
         if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){
            map.light = 1;
            // std::cout<<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;
         }
         if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){
            map.light = 0;
            // std::cout<<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;
         }
        if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
            if(release==0){
                float d = (map.rButX-cameraPos[0])*(map.rButX-cameraPos[0])+(map.rButY-cameraPos[1])*(map.rButY-cameraPos[1]);
                if(d<(0.5*0.5)){
                    release = 1;
                    task++;
                    if(task==2){
                        map.openEntry();
                        countLines = map.Draw(&t1, &VBO1);
                    }
                }
                
            }
            if(isEnemy==1){
                float d = (map.eButX-cameraPos[0])*(map.eButX-cameraPos[0])+(map.eButY-cameraPos[1])*(map.eButY-cameraPos[1]);
                if(d<(0.5*0.5)){
                    isEnemy = 0;
                    task++;
                    if(task==2){
                        map.openEntry();
                        countLines = map.Draw(&t1, &VBO1);
                    }
                }
            }
            
            // std::cout<<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;
         }

        }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void RenderText(unsigned int *s, std::string text, float x, float y, float scale)
{
    // activate corresponding render state
    glUniform1i(glGetUniformLocation(*s, "isText"), 1);
   
    glActiveTexture(GL_TEXTURE0);
    
    glBindVertexArray(VA);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Charac ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[] = {
             xpos,     ypos + h,0.1f,    0.5f, 0.0f,0.0f, 0.0f, 0.0f,            
             xpos,     ypos,    0.1f,    0.5f, 0.0f,0.0f, 0.0f, 1.0f,
             xpos + w, ypos,    0.1f,    0.5f, 0.0f,0.0f, 1.0f, 1.0f,

             xpos,     ypos + h,0.1f,    0.5f, 0.0f,0.0f, 0.0f, 0.0f ,
             xpos + w, ypos,    0.1f,    0.5f, 0.0f,0.0f, 1.0f, 1.0f ,
             xpos + w, ypos + h,0.1f,    0.5f, 0.0f,0.0f, 1.0f, 0.0f           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VB);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUniform1i(glGetUniformLocation(*s, "isText"), 0);
}
