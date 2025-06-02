#include "Rose/Graphics/UIRenderer.hpp"
#include "Rose/ComponentSystem/Component.hpp"
#include "Rose/Core/Scene.hpp"
#include "Rose/Util/File.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H

namespace Rose {

void UIRenderer::Init(std::filesystem::path &fontPath) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        throw std::runtime_error("[ROSE]: Failed to initialize FreeType");
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath.string().c_str(), 0, &face)) {
        FT_Done_FreeType(ft);
        throw std::runtime_error("[ROSE]: Failed to load font face");
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    for (unsigned char c = 32; c < 128; ++c) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            continue;
        }

        std::shared_ptr<Texture> tex;

        if (face->glyph->bitmap.width > 0 && face->glyph->bitmap.rows > 0) {
            tex = std::make_shared<Texture>();
            tex->generateFromBitmap(
                face->glyph->bitmap.buffer,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows
            );
        } else {
            tex = nullptr;
        }

        Glyph glyph;
        glyph.texture = tex;
        glyph.size = { face->glyph->bitmap.width, face->glyph->bitmap.rows };
        glyph.bearing = { face->glyph->bitmap_left, face->glyph->bitmap_top };
        glyph.advance = face->glyph->advance.x >> 6;
        m_Glyphs.insert({ c, glyph });
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    m_Shader.create(File::createPath("Rose/Graphics/Assets/Shaders/TextVert.glsl"),
                    File::createPath("Rose/Graphics/Assets/Shaders/TextFrag.glsl"));

    m_VAO.generate();
    m_VAO.bind();

    m_VBO.generate(BufferType::Dynamic);
    m_VBO.addData(nullptr, sizeof(float) * 6 * 4);

    m_VAO.addAttribute(VertexAttribute{
        .index = 0,
        .size = 2,
        .type = GL_FLOAT,
        .normalized = GL_FALSE,
        .stride = sizeof(float) * 4,
        .offset = 0
    });

    m_VAO.addAttribute(VertexAttribute{
        .index = 1,
        .size = 2,
        .type = GL_FLOAT,
        .normalized = GL_FALSE,
        .stride = sizeof(float) * 4,
        .offset = sizeof(float) * 2
    });
}

void UIRenderer::queueText(const RenderCommand &cmd) {
    m_Commands.push_back(cmd);
}

void UIRenderer::render(const glm::mat4 &projection) {
    m_Shader.use();
    m_Shader.setUniformMat4("uProjection", projection);

    m_VAO.bind();
    m_VBO.bind();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (const RenderCommand &cmd : m_Commands) {
        m_Shader.setVec3("uTextColor", cmd.color);
        float x = cmd.pos.x;
        float y = cmd.pos.y;
        for (const char& c : cmd.text) {
            auto it = m_Glyphs.find(c);
            if (it == m_Glyphs.end()) continue;

            const Glyph& glyph = it->second;

            float xpos = x + glyph.bearing.x * cmd.scale;
            float ypos = y - (glyph.size.y - glyph.bearing.y) * cmd.scale;

            float w = glyph.size.x * cmd.scale;
            float h = glyph.size.y * cmd.scale;

            float vertices[6][4] = {
                { xpos,     ypos + h, 0.0f, 0.0f },
                { xpos,     ypos,     0.0f, 1.0f },
                { xpos + w, ypos,     1.0f, 1.0f },
                { xpos,     ypos + h, 0.0f, 0.0f },
                { xpos + w, ypos,     1.0f, 1.0f },
                { xpos + w, ypos + h, 1.0f, 0.0f }
            };

            m_VBO.bind();
            m_VBO.updateData(&vertices[0][0], sizeof(vertices));
            
            if (glyph.texture) {
                glActiveTexture(GL_TEXTURE0);
                glyph.texture->bind();
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
            x += glyph.advance * cmd.scale;
        }
    }

    glDisable(GL_BLEND);

    m_VAO.unbind();
    m_VBO.unbind();

    m_Commands.clear();
}

UIRenderSystem::UIRenderSystem(std::shared_ptr<UIRenderer> ui)
    : m_UIRendererRef(ui) {}

void UIRenderSystem::onUpdate(std::set<GameObject> &objects, Scene *scene, float DeltaTime) {
    for (const GameObject obj : objects) {
        if (!scene->hasComponent<UIComponent>(obj) || scene->hasComponent<ViewComponent>(obj)) {
            continue;
        }
        const UIComponent &ui = scene->getComponent<UIComponent>(obj);
        if (!ui.Visible) {
            continue;
        }
        
        const TextLabelComponent &label = scene->getComponent<TextLabelComponent>(obj);
        if (label.Text.data()) {
            m_UIRendererRef->queueText(UIRenderer::RenderCommand{
                label.Text,
                ui.Position,
                label.Scale,
                label.Color
            });
        }
    }
}

}
