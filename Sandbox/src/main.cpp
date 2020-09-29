#include <core/Window.h>
#include <imgui/imgui.h>

int main()
{
    {
        Window window;
        window.Create("Window", 1280, 720);
        window.UseImGui();
        while (window.IsOpen())
        {
            window.PollEvents();

            window.Clear();

            ImGui::ShowDemoWindow();
            
            window.Display();
        }
    }

    return 0;
}