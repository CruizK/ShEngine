#include <core/Window.h>
#include <imgui/imgui.h>

#include <gfx/VertexArray.h>
#include <gfx/IndexBuffer.h>
#include <gfx/Shader.h>
#include <gfx/Texture2D.h>

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
        layout.PushFloat(2); // U V

        float vertices[] = {
            //X   Y    Z    R    G    B    A    U    V
            0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, // Bottom Left
            1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, // Bottom Right
            1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, // Top Right btw
            0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0,  // Top Left
        };

        uint32_t indices[] = {
            0, 1 , 2,
            2, 3, 0,
        };

        Texture2D texture;
        texture.LoadFromFile("res/textures/test.png");

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

            //ImGui::ShowDemoWindow();
            texture.Bind(0);
            vao.Bind();
            ibo.Bind();
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

            window.Display();
        }
    }

    return 0;
}
