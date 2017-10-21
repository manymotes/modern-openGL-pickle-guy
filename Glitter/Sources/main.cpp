// Local Headers
#define STB_IMAGE_IMPLEMENTATION
#include "glitter.hpp"
#include "ShaderHelpers.h"
#include "ModelLoader.h"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

int main(int argc, char * argv[]) {
    
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);
    
    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }
    
    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
    
    // **************************************
    // Setup Vertex arrays here
    // **************************************
   
    
    GLuint myShader = LoadProgram("/Users/kendall/Glitter/Glitter/Shaders/basic.vert", "/Users/kendall/Glitter/Glitter/Shaders/basic.frag");
    
    //1a
    //bool LoadModel(dir, crayonBoxOBJ.obj,
    //             model_struct)
    
    //1b
    mlModel model;
    
    if (!LoadModel("/Users/kendall/Documents/maya/projects/default/scenes", "pickleObject.obj", model)) {
        
        return -1;
    }
    mlMesh meshy = model.meshes[0];
    
    //1c
    GLuint vertexbuffer;
    
                                   
   //2e
    //    Generate the VAO
    //    and Generate the VBO
    
    //    Bind the VBO
    //    Set the VBO data
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
   glGenBuffers(1, &vertexbuffer);
    
    unsigned int vaoID[1]; // Our Vertex Array Object
    glGenVertexArrays(1, &vaoID[0]); // Create our Vertex Array Object
    //bind vertex array
    
    
    glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it
    
    //    Bind the VAO
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(mlVertex)*meshy.vertices.size(), meshy.vertices.data(), GL_STATIC_DRAW);
  //  glEnableVertexAttribArray(0);
    
    
    // The following commands will talk about our 'vertexbuffer' buffer
    //add vertex array
    
    
    //    Generate the EBO
    GLuint EBO;
    glGenBuffers(1, &EBO);
    //    Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //    set the EBO data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*meshy.indices.size(), meshy.indices.data(), GL_STATIC_DRAW);
   
    
   //3a

    //   Set the VertexAttributePointer for vertex position
    glVertexAttribPointer(
                          
                          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          
                          3,                  // size
                          
                          GL_FLOAT,           // type
                          
                          GL_FALSE,           // normalized?
                          
                          sizeof(mlVertex),                  // stride
                          
                          (void*)0            // array buffer offset
                          
                          );
    
    // vertex normals
    
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    
    
//   Set the VertexAttributePointer for texture coordinate
    //skipped for now
//   Enable the VertexAttribArray for texture coordinate
    glEnableVertexAttribArray(0);
    

    
                                   
   //4a
    
    //textur begin
   // couldnt find this fild under vendor
   int xForImage;
   int yForImage;

    int compNumber;

   unsigned char* imageData = stbi_load("/Users/kendall/Desktop/greenCrayon.png", &xForImage, &yForImage, &compNumber, 3);
   if (!imageData) return 0;


    GLuint crayonBoxID;
    
   
  
    //6a
    glm::mat4 perspectiveMat4 = glm::perspective((float) glm::radians(45.0f), (float) mWidth/mHeight,  (float) 0.1, (float) 100.1);
    
    GLint unifomrNumber = glGetUniformLocation(myShader, "perspective");
   
   glm::mat4 modelviewInit;
   modelviewInit = glm::translate(perspectiveMat4, glm::vec3(3.00f, 0.0f, -50.0f));
    
 
    
    // **************************************
    
    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);
        
        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // **********************************
        // Add rendering code here
        
        
        //crayonbox
        glUseProgram(myShader);
        
        glBindVertexArray(vaoID[0]);

       
        glUniformMatrix4fv(unifomrNumber,
                           1,
                           GL_FALSE,
                           glm::value_ptr(modelviewInit));


  //glBindTexture(GL_TEXTURE_2D, crayonBoxID);

        glDrawElements(GL_TRIANGLES,
                                              meshy.indices.size(),
                                              GL_UNSIGNED_INT,
                                            0);
       //crayonbox end
        
        //render Crayon
        
        //bind 2nd vertex array to
        // glbindvetexarray(id of vertex array)
       
//         glBindVertexArray(vaoID2[0]);
//
//        glUniformMatrix4fv(    unifomrNumber2,
//                           1,
//                           GL_FALSE,
//                           glm::value_ptr(modelviewInit2));
//
//        //7a
//        //glDrawElements();
//
//
//
//        glBindTexture(GL_TEXTURE_2D, crayonPictureID);
//
//
//        glDrawElements(GL_TRIANGLES,
//                       meshy2.indices.size(),
//                       GL_UNSIGNED_INT,
//                       0);

        // **********************************
        
        
       
        
        
        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }   glfwTerminate();
    
    return EXIT_SUCCESS;
    
    //top stuff for crayon ,
    // then top stuff for box
    
    // double render stuff for both crayon and box wight after each call
}

