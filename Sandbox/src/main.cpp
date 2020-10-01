#include <core/Window.h>
#include <imgui/imgui.h>

#include <gfx/VertexArray.h>
#include <gfx/IndexBuffer.h>
#include <gfx/Shader.h>

int main()
{
    {
        Window window;
        window.Create("Window", 1280, 720);
        VertexArray vao;
        VertexBuffer vbo;
        IndexBuffer ibo;

        VertexBufferLayout layout;
        layout.PushFloat(3); // X Y Z
        layout.PushFloat(4); // R G B A

        float vertices[] = {
            //X   Y    Z    R    G    B    A
            0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
            1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
            1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0,
            0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0 
        };

        uint32_t indices[] = {
            0, 1 , 2,
            2, 3, 0,
        };

        vao.Bind();

        vbo.Create(vertices, sizeof(vertices));
        ibo.Create(indices, sizeof(indices));
        vao.AddBuffer(vbo, layout);

        vbo.Unbind();
        vao.Unbind();

        Shader shader;
        shader.CreateFromFile("res/shaders/base.shader");
        shader.Use();

        window.UseImGui();
        while (window.IsOpen())
        {
            window.PollEvents();

            window.Clear();

            ImGui::ShowDemoWindow();
            vao.Bind();
            ibo.Bind();
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

            window.Display();
        }
    }

    return 0;
}
