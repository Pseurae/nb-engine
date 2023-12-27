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
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <NB/ECS/System.h>

#include <GL/gl3w.h>

const char *vertexShaderSource = R"glsl(
#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out vec2 v_uv;
uniform mat4 proj = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 model = mat4(1.0);

void main()
{
    gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
    v_uv = uv;
}
)glsl";

const char *fragmentShaderSource = R"glsl(
#version 330 core

out vec4 fragColor;
in vec2 v_uv;

uniform sampler2D myTexture;
uniform float u_alpha = 1.0;

void main()
{
    fragColor = texture2D(myTexture, v_uv) * u_alpha;
}
)glsl";

const char *fragmentShaderSource1 = R"glsl(
#version 330 core

out vec4 fragColor;
in vec2 v_uv;

uniform sampler2D myTexture;
uniform vec4 u_color;

void main()
{
    fragColor = u_color;
}
)glsl";

class MyApp : public tonic::App
{
public:
    virtual void OnInitialize() 
    {
        const float vertices[] = {
            -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.0f, 0.0f
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

        auto proj = glm::perspective(45.0f, 800.0f / 600.0f, 0.01f, 100.0f);
        auto view = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        auto model = glm::rotate(glm::mat4(1.0), glm::radians((float)tonic::core::Time::elapsedTime * 10.0f), glm::vec3(0.0, 1.0, 0.0));

        m_Shader->SetUniform("proj", proj);
        m_Shader->SetUniform("view", view);
        m_Shader->SetUniform("model", model);

        m_Shader->SetUniform("u_alpha", 1.0f);
        m_Shader->SetUniform("myTexture", 0);

        tonic::graphics::RenderAPI::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        m_Shader1->Use();
        m_VAO->Bind();
        m_EBO->Bind();

        m_Shader1->SetUniform("u_color", glm::vec4(1.0, 1.0, 1.0, 0.8));
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

tonic::App *tonic::CreateApplication(const LaunchArguments &launchArguments)
{
    return new MyApp();
}
