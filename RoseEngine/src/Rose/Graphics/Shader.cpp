#include "Rose/Graphics/Shader.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace Rose {

Shader::Shader() {}
Shader::~Shader() {
    glDeleteProgram(m_Program);
}

void Shader::create(const std::filesystem::path &vertexPath, const std::filesystem::path &fragPath) {

    std::string vertexSource = readFile(vertexPath);
    std::string fragSource = readFile(fragPath);
    
    GLuint vertexShader = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragSource.c_str(), GL_FRAGMENT_SHADER);

    m_Program = glCreateProgram();
    glAttachShader(m_Program, vertexShader);
    glAttachShader(m_Program, fragmentShader);
    glLinkProgram(m_Program);

    GLint success;
    glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
    if (!success) {
        GLint infoLogLength;
        glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<GLchar> infoLog(infoLogLength);
        glGetProgramInfoLog(m_Program, infoLogLength, nullptr, infoLog.data());
        std::cerr << "[ROSE]: Shader Linking Error:\n" << infoLog.data() << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const {
    glUseProgram(m_Program);
}

void Shader::setUniformMat4(const std::string &name, const glm::mat4 &mat) {
    auto location = glGetUniformLocation(m_Program, name.c_str());

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setInt(const std::string &name, const int32_t num) {
    auto location = glGetUniformLocation(m_Program, name.c_str());
    glUniform1i(location, num);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec) {
    auto location = glGetUniformLocation(m_Program, name.c_str());
    glUniform3f(location, vec.x, vec.y, vec.z);
}

std::string Shader::readFile(const std::filesystem::path &path) {
    std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "[ROSE]: failed to read file at " << path.string() << std::endl;
    }
    std::streamsize size = file.tellg();
    std::string buffer(size, '\0');
    file.seekg(0);
    file.read(buffer.data(), size);
    
    return buffer;
}

GLuint Shader::compileShader(const char *source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<GLchar> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());
        std::cerr << "[ROSE]: Shader compilation falure:\n" << infoLog.data() << std::endl;
    }

    return shader;
}

}
