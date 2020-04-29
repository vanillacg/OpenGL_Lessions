//
//  main.cpp
//  OpenGL_Triangle
//
//  Created by chenguang on 2020/4/27.
//  Copyright © 2020 chenguang. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "三角形", NULL, NULL);
    if (window == NULL) {
        std::cout << "failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewInit();// crash fix https://stackoverflow.com/questions/12329082/glcreateshader-is-crashing/23541855#23541855
    //I solved that problem by calling glewInit() after glfwMakeContextCurrent().
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //顶点着色器
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    char infoLog[512];
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //着色器程序对象
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //把着色器对象链接到程序对象以后，记得删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // 3. 绘制物体
    //一个三角形
//    float vertices[] = {
//        -0.5f, -0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
//        0.0f, 0.5f, 0.0f
//    };
    //两个三角形
    float vertices[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,  // left
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top
        // second triangle
         0.0f, -0.5f, 0.0f,  // left
         0.9f, -0.5f, 0.0f,  // right
         0.45f, 0.5f, 0.0f   // top
    };
    
    //可以看到，有几个顶点叠加了。我们指定了右下角和左上角两次！一个矩形只有4个而不是6个顶点，这样就产生50%的额外开销。当我们有包括上千个三角形的模型之后这个问题会更糟糕，这会产生一大堆浪费。更好的解决方案是只储存不同的顶点，并设定绘制这些顶点的顺序。这样子我们只要储存4个顶点就能绘制矩形了，之后只要指定绘制的顺序就行了。如果OpenGL提供这个功能就好了，对吧？

   // 很幸运，索引缓冲对象的工作方式正是这样的。和顶点缓冲对象一样，EBO也是一个缓冲，它专门储存索引，OpenGL调用这些顶点的索引来决定该绘制哪个顶点。所谓的索引绘制(Indexed Drawing)正是我们问题的解决方案。
    //当时用索引的时候，我们只定义了4个顶点，而不是6个
//    float vertices[] = {
//        0.5f, 0.5f, 0.0f,   // 右上角
//        0.5f, -0.5f, 0.0f,  // 右下角
//        -0.5f, -0.5f, 0.0f, // 左下角
//        -0.5f, 0.5f, 0.0f   // 左上角
//    };
//
//    unsigned int indices[] = { // 注意索引从0开始!
//        0, 1, 3, // 第一个三角形
//        1, 2, 3  // 第二个三角形
//    };
    
//    unsigned int EBO;
//    glGenBuffers(1, &EBO);
//    //复制我们的索引数组到一个索引缓冲中，供OpenGL使用
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    unsigned int VAO;
    //创建VAO
    glGenVertexArrays(1, &VAO);
    //绑定VAO
    glBindVertexArray(VAO);
    //复制顶点数组到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //设置顶点属性指针
    //这里的第一个参数对0 对应vertexShaderSource, layout (location = 0)指将 location位置属性 glVertexAttribPointer定点属性设置为0后, location 再取出的就是Pointer 第一个参数为0 的属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //以顶点属性位置值作为参数，启用顶点属性(顶点属性默认是禁用的)
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        
        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //渲染一个物体时要使用着色器程序
        glUseProgram(shaderProgram);
        
        //绘制三角形
        glBindVertexArray(VAO);
        //第一个参数是我们打算绘制的OpenGL图元的类型,第二个参数指定了顶点数组的起始索引,最后一个参数指定我们打算绘制多少个顶点
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
//        //绘制矩形
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
