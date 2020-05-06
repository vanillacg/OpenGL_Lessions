//
//  Shader.hpp
//  OpenGL_Shader
//
//  Created by chenguang on 2020/4/30.
//  Copyright © 2020 chenguang. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    
public:
    //程序ID
    unsigned int ID;
    //构造器读取并构建着色器
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    //使用/激活程序
    void use();
    //uniform工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif /* Shader_hpp */
