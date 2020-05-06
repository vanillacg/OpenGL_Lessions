//
//  main.cpp
//  OpenGL_Shader
//
//  Created by chenguang on 2020/4/30.
//  Copyright © 2020 chenguang. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//const char *vertexShaderSource = "#version 330 core\n"
//    "layout (location = 0) in vec3 aPos;\n"
//    "layout (location = 1) in vec3 aColor;\n"
//    "out vec3 ourColor;\n"
//    "void main()\n"
//    "{\n"
//    "   gl_Position = vec4(aPos, 1.0);\n"
//    "   ourColor = aColor;\n"
//    "}\0";
//const char *fragmentShaderSource = "#version 330 core\n"
//    "out vec4 FragColor;\n"
//    "in vec3 ourColor;\n"
//    "void main()\n"
//    "{\n"
//    "   FragColor = vec4(ourColor, 1.0f);\n"
//    "}\n\0";

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main(int argc, const char * argv[])
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_HEIGHT, SCR_WIDTH, "着色器", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
//    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//    //check error
//    int success;
//    char log[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(vertexShader, 512, NULL, log);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
//    }
//    //fragment shader
//    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, log);
//        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
//    }
//    //link shaders
//    int shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    //check for linking errors
//    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
//        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << log << std::endl;
//    }
//    //delete shader afer linking
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
    //set up vertex data and configure vertex attributes
    
    Shader ourShader("/Users/chenguang/Desktop/CG/AudioVideo/OpenGL/OpenGL_Lessions/OpenGL_Shader/OpenGL_Shader/Shader/3.3.shader.vs", "/Users/chenguang/Desktop/CG/AudioVideo/OpenGL/OpenGL_Lessions/OpenGL_Shader/OpenGL_Shader/Shader/3.3.shader.fs");
    float vertices[] = {
        //positions         //colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,//bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f// top
    };
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object
    glBindVertexArray(VAO);
    // bind and set vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //configure vertex attibutes
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //position atrribute location = 0 stride = 6 * float offset= 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    //enbale attibute
    glEnableVertexAttribArray(0);
    //color attibute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //activate shader
//    glUseProgram(shaderProgram);
    //render loop
    while (!glfwWindowShouldClose(window)) {
        //input
        processInput(window);
        
        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ourShader.use();
//        ourShader.setFloat("someUniform", 1.0f);
//        //render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
//    glDeleteProgram(shaderProgram);
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

