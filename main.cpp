#include <tonic/entry.h>
#include <tonic/log.h>
#include <tonic/graphics/vertex.h>
#include <tonic/graphics/shader.h>
#include <tonic/graphics/texture.h>
#include <tonic/core/time.h>
#include <tonic/input/keyboard.h>
#include <tonic/input/mouse.h>
#include <tonic/graphics/framebuffer.h>
#include <tonic/graphics/helpers.h>
#include <tonic/graphics/renderapi.h>
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

const char *fragmentShaderSource1 = R"glsl(
#version 330 core

out vec4 fragColor;
in vec2 v_uv;

uniform sampler2D myTexture;

void main()
{
    fragColor = vec4(vec3(1.0, 0.0, 0.0) * texture2D(myTexture, v_uv).rgb, 1.0);
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
        m_Shader1 = std::make_shared<tonic::graphics::Shader>(vertexShaderSource, fragmentShaderSource1);

        m_Texture = std::make_shared<tonic::graphics::Texture>(pixels, 4, 4, 3);
        m_Texture->SetFilter(tonic::graphics::TextureFilter::Nearest, tonic::graphics::TextureFilter::Nearest);

        m_FBO = std::make_shared<tonic::graphics::FrameBuffer>(800, 600);
    }

    virtual void OnUpdate()
    {
        glm::vec2 pos = tonic::input::Mouse::GetPosition();
        
        if (tonic::input::Mouse::GetButtonDown(tonic::input::TONIC_MOUSEBUTTON_LEFT))
            TONIC_MSG("%f %f", pos.x, pos.y);
    }

    virtual void OnRender()
    {
        m_Shader->Use();
        m_VAO->Bind();
        m_EBO->Bind();

        tonic::graphics::RenderAPI::ActivateTexture(0);
        m_Texture->Bind();

        m_Shader->SetUniform1i("myTexture", 0);
        m_FBO->Bind();
        tonic::graphics::RenderAPI::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        m_FBO->Unbind();

        m_Shader1->Use();
        m_EBO->Bind();
        m_VAO->Bind();

        tonic::graphics::RenderAPI::ActivateTexture(0);
        m_FBO->GetTexture().Bind();

        m_Shader1->SetUniform1i("myTexture", 0);
        m_Shader1->SetUniform1f("iTime", static_cast<float>(tonic::core::Time::elapsedTime));

        tonic::graphics::RenderAPI::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
private:
    std::shared_ptr<tonic::graphics::ElementBuffer> m_EBO;
    std::shared_ptr<tonic::graphics::VertexBuffer> m_VBO;
    std::shared_ptr<tonic::graphics::VertexBufferLayout> m_VBOLayout;
    std::shared_ptr<tonic::graphics::VertexArray> m_VAO;
    std::shared_ptr<tonic::graphics::Shader> m_Shader, m_Shader1;
    std::shared_ptr<tonic::graphics::Texture> m_Texture;
    std::shared_ptr<tonic::graphics::FrameBuffer> m_FBO;
};

tonic::App *tonic::CreateApplication()
{
    return new MyApp();
}
