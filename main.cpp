#include <tonic/entry.h>
#include <tonic/log.h>
#include <tonic/graphics/vertex.h>
#include <tonic/graphics/shader.h>
#include <tonic/graphics/texture.h>
#include <tonic/core/time.h>
#include <tonic/input/keyboard.h>
#include <tonic/input/mouse.h>
#include <memory>

#include <GL/gl3w.h>

const char *vertexShaderSource = R"glsl(
#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out vec2 v_uv;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    v_uv = uv;
}
)glsl";

const char *fragmentShaderSource = R"glsl(
#version 330 core

out vec4 fragColor;

uniform float iTime;
in vec2 v_uv;

uniform sampler2D myTexture;

void main()
{
    fragColor = texture2D(myTexture, v_uv);
}
)glsl";

class MyApp : public tonic::App
{
public:
    virtual void OnInitialize() 
    {
        const float vertices[] = {
            -1.0f, -1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 1.0f,
             1.0f,  1.0f,  1.0f, 0.0f,
            -1.0f,  1.0f,  0.0f, 0.0f
        };

        const unsigned int elements[] = {
            0, 1, 2,
            2, 3, 0
        };

        m_VBO = std::make_shared<tonic::graphics::VertexBuffer>((void *)vertices, (unsigned int)sizeof(vertices));
        m_VBOLayout = std::make_shared<tonic::graphics::VertexBufferLayout>();
        m_VBOLayout->Push<float>(2);
        m_VBOLayout->Push<float>(2);

        m_EBO = std::make_shared<tonic::graphics::ElementBuffer>(elements, 6);

        m_VAO = std::make_shared<tonic::graphics::VertexArray>();
        m_VAO->SubmitBuffer(*m_VBO, *m_VBOLayout);

        const unsigned char pixels[] = {
            255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0,
            0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255,
            255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0,
            0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255,
        };

        m_Shader = std::make_shared<tonic::graphics::Shader>(vertexShaderSource, fragmentShaderSource);

        m_Texture = std::make_shared<tonic::graphics::Texture>(pixels, 4, 4, 3);
        m_Texture->SetFilter(tonic::graphics::TextureFilter::Nearest, tonic::graphics::TextureFilter::Nearest);
    }

    virtual void OnUpdate()
    {
    }

    virtual void OnRender()
    {
        m_Shader->Use();
        m_EBO->Bind();

        glActiveTexture(GL_TEXTURE0);
        m_Texture->Bind();

        m_Shader->SetUniform1i("myTexture", 0);
        m_VAO->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
private:
    std::shared_ptr<tonic::graphics::ElementBuffer> m_EBO;
    std::shared_ptr<tonic::graphics::VertexBuffer> m_VBO;
    std::shared_ptr<tonic::graphics::VertexBufferLayout> m_VBOLayout;
    std::shared_ptr<tonic::graphics::VertexArray> m_VAO;
    std::shared_ptr<tonic::graphics::Shader> m_Shader;
    std::shared_ptr<tonic::graphics::Texture> m_Texture;
};

tonic::App *tonic::CreateApplication()
{
    return new MyApp();
}
