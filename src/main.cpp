#include "pch.h"

#include "glfw-manager.h"
#include "game.h"

struct RenderHandler : public glfw::GlfwRenderHandler
{
    game::Game& game;

    RenderHandler(game::Game& _game)
        : game(_game) {}

    void Render()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game.Render();
    }
};

int main()
{
    try
    {
        glfw::GlfwManager::Init();

        game::Game game;

        auto render_handler = std::make_shared<RenderHandler>(game);
        auto window = glfw::GlfwManager::CreateWindow(800, 600, "OpenGL Minecraft");
        glfw::GlfwManager::SetRenderHandler(window, render_handler);

        constexpr int64_t kOneSecond = 1000000000;
        constexpr double kTimeStep = kOneSecond / 60.0;
        auto start_time = std::chrono::high_resolution_clock::now();
        double delta_time = 0.0;
        auto update_timer = std::chrono::high_resolution_clock::now();
        int update_counter = 0;
        while (!glfw::GlfwManager::AllWindowShouldClose())
        {
            auto now = std::chrono::high_resolution_clock::now();
            delta_time += (double)std::chrono::duration_cast<std::chrono::nanoseconds>(now - start_time).count() / kTimeStep;
            start_time = now;

            bool should_update = delta_time >= 1;
            while (delta_time >= 1)
            {
                game.Update();
                update_counter++;
                delta_time--;
            }

            if (should_update)
                glfw::GlfwManager::HandleRender();

            if (std::chrono::duration_cast<std::chrono::nanoseconds>(now - update_timer).count() >= kOneSecond)
            {
                std::cout << "updated: " << update_counter << std::endl;
                update_counter = 0;
                update_timer = now;
            }

            glfw::GlfwManager::PollEvents();
        }

        glfw::GlfwManager::Terminate();
    }
    catch (const std::runtime_error& err)
    {
        std::cout << err.what() << std::endl;
    }
}
