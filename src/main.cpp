#include "pch.h"

#include "glfw-manager.h"

#include "game.h"

struct Handler : public glfw::GlfwRenderHandler, public glfw::GlfwListener
{
    game::Game& game;
    uint64_t window;

    Handler(game::Game& _game, uint64_t _window)
        : game(_game), window(_window) {}

    virtual void KeyDown(int key) {}
    virtual void KeyUp(int key) {}

    void MouseMove(double x, double y) override
    {
        game.GetCameraControl().UpdateMouse((float)x, (float)y);
    }

    void Render()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto dimension = glfw::GlfwManager::GetWindowSize(window);
        game.Render((float)dimension.width, (float)dimension.height);
    }
};

int main()
{
    try
    {
        glfw::GlfwManager::Init();

        auto game = std::make_shared<game::Game>();

        glfwWindowHint(GLFW_SAMPLES, 8);
        auto window = glfw::GlfwManager::CreateWindow(800, 600, "OpenGL Minecraft");
        GLFWwindow* glfw_window = glfw::GlfwManager::Get(window);
        auto handler = std::make_shared<Handler>(*game, window);
        glfw::GlfwManager::SetRenderHandler(window, handler);
        glfw::GlfwManager::SetListener(window, handler);

        // Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("Failed to initialize GLAD.");

        game::Game::InitTextures();
        game::Game::InitShaders();
        game->Init();

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_FRONT);

        glEnable(GL_MULTISAMPLE);

        glEnable(GL_DEPTH_TEST);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
                game->GetCameraControl().UpdateControls({
                    glfwGetKey(glfw_window, GLFW_KEY_W) == GLFW_PRESS,
                    glfwGetKey(glfw_window, GLFW_KEY_S) == GLFW_PRESS,
                    glfwGetKey(glfw_window, GLFW_KEY_D) == GLFW_PRESS,
                    glfwGetKey(glfw_window, GLFW_KEY_A) == GLFW_PRESS,
                    glfwGetKey(glfw_window, GLFW_KEY_SPACE) == GLFW_PRESS,
                    glfwGetKey(glfw_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS });
                game->Update();
                update_counter++;
                delta_time--;
            }

            if (should_update)
                glfw::GlfwManager::HandleRender();

            if (std::chrono::duration_cast<std::chrono::nanoseconds>(now - update_timer).count() >= kOneSecond)
            {
                std::string title = "OpenGL Minecraft | ups: " + std::to_string(update_counter);
                glfwSetWindowTitle(glfw_window, title.c_str());
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
