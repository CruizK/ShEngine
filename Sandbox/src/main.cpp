#include <core/Window.h>
#include <imgui/imgui.h>


#include <gfx/Renderer2D.h>
#include <gfx/Texture2D.h>
#include <glm/gtc/matrix_transform.hpp>


int main()
{
    Window window;
    window.Create("Window", 1280, 720);

    Renderer2D::Init();

    Renderable2D sprite;


    sprite.SetPosition(0, 0);
    sprite.SetScale(100);
       
    Texture2D texture;
    texture.LoadFromFile("res/textures/test.png");
    texture.Unbind();

    const float width = 1280;
    const float height = 720;

    glm::mat4 ortho = glm::ortho(0.0f, width, 0.0f, height, -0.1f, 100.0f) ;
    ortho = glm::translate(ortho, glm::vec3(width / 2, height / 2, 0));


    window.UseImGui();
    while (window.IsOpen())
    {
        window.PollEvents();

        window.Clear();

        Renderer2D::Begin(ortho);
        Renderer2D::DrawQuad(sprite.GetTransform(), sprite.GetColor());
        Renderer2D::End();
        //ImGui::ShowDemoWindow();
        //texture.Bind(0);

        window.Display();
    }
    CORE_TRACE("EXITED LOOP");
    Renderer2D::Shutdown();
    return 0;
}
