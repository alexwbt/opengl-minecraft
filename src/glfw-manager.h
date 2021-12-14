#pragma once

namespace glfw
{
    struct GlfwListener
    {
        virtual void KeyDown(int key) {}
        virtual void KeyUp(int key) {}
        virtual void MouseMove(double x, double y) {}
        virtual void Resized(int width, int height)
        {
            glViewport(0, 0, width, height);
        }
        virtual ~GlfwListener() {}
    };

    struct GlfwRenderHandler
    {
        virtual void Render() = 0;
        virtual ~GlfwRenderHandler() {}
    };

    struct Dimension final
    {
        int width, height;
    };

    struct Point final
    {
        double x, y;
    };

    class GlfwManager final
    {
    public:
        static constexpr uint64_t kNullIndex = -1;

    private:
        static std::vector<GLFWwindow*> windows_;
        static std::vector<std::shared_ptr<GlfwRenderHandler>> render_handlers_;
        static std::vector<std::shared_ptr<GlfwListener>> listeners_;

    public:
        // Initializes GLFW
        static void Init();

        // Create a GLFW window.
        // returns index.
        static uint64_t CreateWindow(uint32_t width, uint32_t height, const std::string& title);
        static GLFWwindow* Get(uint64_t index);

        static void SetRenderHandler(uint64_t index, std::shared_ptr<GlfwRenderHandler> handler);
        static void HandleRender();

        static void SetListener(uint64_t index, std::shared_ptr<GlfwListener> listener);
        static bool IsKeyDown(uint64_t index, int key);
        static Dimension GetWindowSize(uint64_t index);
        static Point GetMousePos(uint64_t index);

        // Destroy window if glfwWindowShouldClose returns true.
        // returns true if all windows should close.
        static bool AllWindowShouldClose();

        static void PollEvents();

        // Terminates GLFW
        static void Terminate();

    private:
        static uint64_t GetIndexOfWindow(GLFWwindow* window);
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseCallback(GLFWwindow* window, double x, double y);
        static void ResizeCallback(GLFWwindow* window, int width, int height);

    private:
        GlfwManager() {}
    };
}
