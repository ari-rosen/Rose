#pragma once

#include "Rose/Core/Core.hpp"

#include "Rose/ComponentSystem/System.hpp"
#include "Rose/Graphics/Buffer.hpp"
#include "Rose/Graphics/Shader.hpp"
#include "Rose/Graphics/Texture.hpp"

class GLFWwindow;

namespace Rose {

struct Vertex {
    glm::vec2 Position;
    glm::vec2 UV;
};

struct InstanceData {
    glm::mat4 Transform;
    uint32_t Layer;
    uint32_t TextureID;
};

class ROSE_API Renderer {
public:
    void init();
    void shutdown();
    
    uint32_t createTexture(const std::filesystem::path &path, const TextureParameter &params = TextureParameter());
    void bufferQuads(const GLfloat *instancedTransforms, size_t size, uint32_t instanceCount);
    void renderScene(GLFWwindow *window, glm::mat4 view, float zoom);

    inline void setInstanceCount(uint32_t count) { m_InstanceCount = count; }
public:
    std::vector<InstanceData> instances{};
private:
    static constexpr Vertex s_Vertices[4] = {
        { .Position = { -1, -1 }, .UV = { 0.0f, 0.0f } },
        { .Position = {  1, -1 }, .UV = { 1.0f, 0.0f } },
        { .Position = {  1,  1 }, .UV = { 1.0f, 1.0f } },
        { .Position = { -1,  1 }, .UV = { 0.0f, 1.0f } }
    };

    static constexpr GLuint s_Indices[6] = {
        0, 1, 2,
        0, 2, 3
    };

    uint32_t m_InstanceCount;

    VertexArray m_VAO;
    VertexBuffer m_VBO;
    VertexBuffer m_InstanceVBO;
    IndexBuffer m_EBO;

    Shader m_Shader;

    std::unordered_map<uint32_t, std::shared_ptr<Texture>> m_TextureMap{};
    uint32_t m_DefaultTextureID;
};

class ROSE_API RenderSystem : public System {
public:
    RenderSystem(std::shared_ptr<Renderer> renderer);
    void onUpdate(std::set<GameObject> &objects, Scene *scene, float DeltaTime) override;
private:
    std::shared_ptr<Renderer> m_RendererRef;
};

}
