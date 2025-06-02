#pragma once

#include "Rose/Core/Core.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Rose {

class ROSE_API Shader {
public:
    Shader();
    ~Shader();
    
    void create(const std::filesystem::path &vertexPath, const std::filesystem::path &fragPath);
    void use() const;
    
    void setUniformMat4(const std::string &name, const glm::mat4 &mat);
    void setInt(const std::string &name, const int32_t num);
    void setVec3(const std::string &name, const glm::vec3 &vec);
private:
    GLuint m_Program;
private:
    static std::filesystem::path getRootDirMacOS();
    static std::string readFile(const std::filesystem::path &path);
    static GLuint compileShader(const char *source, GLenum type);
    
};

}
