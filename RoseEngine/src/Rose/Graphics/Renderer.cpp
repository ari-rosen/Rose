#include "Rose/Graphics/Renderer.hpp"
#include "Rose/Util/File.hpp"
#include "Rose/ComponentSystem/GameObject.hpp"
#include "Rose/Core/Scene.hpp"
#include "Rose/Graphics/Buffer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Rose {

void Renderer::init() {
    instances.reserve(MAX_OBJECTS);

    const std::filesystem::path vertPath = "Rose/Graphics/Assets/Shaders/DefaultVert.glsl";
    const std::filesystem::path fragPath = "Rose/Graphics/Assets/Shaders/DefaultFrag.glsl";
    const std::filesystem::path texturePath = "Rose/Graphics/Assets/Textures/defaultTexture.png";

    m_Shader.create(File::createPath(vertPath),File::createPath(fragPath));

    m_DefaultTextureID = createTexture(File::createPath(texturePath)); 

    m_VAO.generate();
    m_VAO.bind();

    m_VBO.generate(BufferType::Static);
    m_VBO.bind();
    m_VBO.addData(reinterpret_cast<const GLfloat *>(s_Vertices), sizeof(s_Vertices));

     // Vertex Position
    m_VAO.addAttribute(VertexAttribute{
        .index = 0,
        .size = 2,
        .type = GL_FLOAT,
        .normalized = GL_FALSE,
        .stride = sizeof(Vertex),
        .offset = 0
    });

    m_VAO.addAttribute(VertexAttribute{
        .index = 1,
        .size = 2,
        .type = GL_FLOAT,
        .normalized = GL_FALSE,
        .stride = sizeof(Vertex),
        .offset = offsetof(Vertex, UV)
    });
    
    m_EBO.generate();
    m_EBO.bind();
    m_EBO.addIndices(s_Indices, sizeof(s_Indices));
    
    m_InstanceVBO.generate(BufferType::Dynamic);
    m_InstanceVBO.bind();
    m_InstanceVBO.addData(nullptr, sizeof(glm::mat4) * MAX_OBJECTS);

    // Instanced Transform
    for (uint8_t i = 0; i < 4; i++) {
        m_VAO.addInstancedAttribute(VertexAttribute{
            .index = static_cast<GLuint>(2 + i),
            .size = 4,
            .type = GL_FLOAT,
            .normalized = GL_FALSE,
            .stride = sizeof(glm::mat4),
            .offset = sizeof(glm::vec4) * i
        });
    }
}

uint32_t Renderer::createTexture(const std::filesystem::path &path, const TextureParameter &params) {
    std::shared_ptr<Texture> newTexture = std::make_shared<Texture>();
    newTexture->generate(path, params);
    m_TextureMap[newTexture->ID()] = newTexture;
    return newTexture->ID();
}

void Renderer::renderScene(GLFWwindow *window, glm::mat4 view, float zoom) {
    m_Shader.use();
    
    glActiveTexture(GL_TEXTURE0);

    int32_t winWidth, winHeight;
    glfwGetWindowSize(window, &winWidth, &winHeight);
    
    glm::mat4 projection = glm::ortho(
        -winWidth / 2.0f / zoom,  winWidth / 2.0f / zoom,
        -winHeight / 2.0f / zoom, winHeight / 2.0f / zoom,
        -1.0f, 1.0f
    );

    m_Shader.setUniformMat4("uProjection", projection);
    m_Shader.setUniformMat4("uView", view);
    m_Shader.setInt("uTexture", 0);

    m_VAO.bind();
    
    std::sort(instances.begin(), instances.end(), [](const InstanceData &a, const InstanceData &b) {
        return a.Layer < b.Layer;
    });
    
    uint32_t currentTexture = UINT32_MAX;
    static std::vector<glm::mat4> currentBatch;
    currentBatch.resize(instances.size());

    for (const auto &instance : instances) {
        if (instance.TextureID != currentTexture && !currentBatch.empty()) {
            bufferQuads(reinterpret_cast<const GLfloat *>(currentBatch.data()),
                        currentBatch.size() * sizeof(glm::mat4),
                        currentBatch.size());
            glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, currentBatch.size());
            currentBatch.clear();
        }

        if (instance.TextureID != currentTexture) {
            currentTexture = (instance.TextureID == 0) ? m_DefaultTextureID : instance.TextureID;
            m_TextureMap[currentTexture]->bind();
        }

        currentBatch.emplace_back(instance.Transform);
    }

    if (!currentBatch.empty()) {
        bufferQuads(reinterpret_cast<const GLfloat *>(currentBatch.data()),
                    currentBatch.size() * sizeof(glm::mat4),
                    currentBatch.size());
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, currentBatch.size());
    }

}

void Renderer::bufferQuads(const GLfloat *instancedTransforms, size_t size, uint32_t instanceCount) {
    m_InstanceCount = instanceCount;
    m_InstanceVBO.bind();
    m_InstanceVBO.updateData(instancedTransforms, size);
}

RenderSystem::RenderSystem(std::shared_ptr<Renderer> renderer) : m_RendererRef(renderer) {}

void RenderSystem::onUpdate(std::set<GameObject> &objects, Scene *scene, float DeltaTime) {
    m_RendererRef->instances.clear();

    uint32_t instanceCount = 0;
    
    for (const auto obj : objects) {
        const auto &transform = scene->getComponent<TransformComponent>(obj);
        const auto &view = scene->getComponent<ViewComponent>(obj);
        const auto &sprite = scene->getComponent<SpriteComponent>(obj);

        if (!view.Visable) {
            continue;
        }

        instanceCount++;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(transform.Position, 0.0));
        model = glm::rotate(model, glm::radians(transform.Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(transform.Scale, 1.0f));
        
        m_RendererRef->instances.push_back(InstanceData{
            .Transform = model,
            .Layer = view.Layer,
            .TextureID = sprite.TextureID
        });

        m_RendererRef->setInstanceCount(instanceCount);
    }
    
}

} // namespace Rose

