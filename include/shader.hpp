#ifndef SHADER_HPP
#define SHADER_HPP
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

unsigned int loadShader();
class Shader
{
private:
    void checkCompileErrors(unsigned int shader, std::string type);
public:
    unsigned int ID;
    Shader(const char * vertexPath, const char * fragmentPath);
    void use() const;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};
#endif
