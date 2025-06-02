#pragma once

#include "Rose/Core/Core.hpp"
#include "Rose/Graphics/Texture.hpp"
#include "Rose/Graphics/Shader.hpp"
#include "Rose/Graphics/Buffer.hpp"
#include "glm/glm.hpp"

namespace Rose {

class ROSE_API UIRenderer {
public:
    struct RenderCommand {
        std::string text;
        glm::vec2 pos;
        float scale;
        glm::vec3 color;
    };
public:
    void Init(std::filesystem::path &fontPath);
    void queueText(const RenderCommand &cmd);
    void render(glm::mat4 projection);
private:
    struct Glyph {
        Texture texture;
        glm::ivec2 size;
        glm::ivec2 bearing;
        GLuint advance;
    };
    
    std::map<char, Glyph> m_Glyphs;
    std::vector<RenderCommand> m_Commands;
    
    Shader m_Shader;
    VertexArray m_VAO;
    VertexBuffer m_VBO;

};

}
