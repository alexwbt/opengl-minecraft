#include "pch.h"
#include "glfw-manager.h"

namespace glfw
{
    std::vector<GLFWwindow*> GlfwManager::windows_;
    std::vector<std::shared_ptr<GlfwRenderHandler>> GlfwManager::render_handlers_;
    std::vector<std::shared_ptr<GlfwListener>> GlfwManager::listeners_;

    void GlfwManager::Init()
    {
        if (!glfwInit())
            throw std::runtime_error("Failed to init GLFW.");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    uint64_t GlfwManager::CreateWindow(uint32_t width, uint32_t height, const std::string& title)
    {
        GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) throw std::runtime_error("Failed to create window " + title + ".");

        glfwSetKeyCallback(window, GlfwManager::KeyCallback);
        glfwSetCursorPosCallback(window, GlfwManager::MouseCallback);
        glfwSetFramebufferSizeCallback(window, GlfwManager::ResizeCallback);

        windows_.push_back(window);
        render_handlers_.push_back(nullptr);
        listeners_.push_back(std::make_shared<GlfwListener>());
        return windows_.size() - 1;
    }

    GLFWwindow* GlfwManager::Get(uint64_t index)
    {
        return windows_[index];
    }

    void GlfwManager::SetRenderHandler(uint64_t index, std::shared_ptr<GlfwRenderHandler> handler)
    {
        render_handlers_[index] = std::move(handler);
    }

    void GlfwManager::HandleRender()
    {
        for (int i = 0; i < windows_.size(); i++)
        {
            if (!windows_[i]) continue;
            glfwMakeContextCurrent(windows_[i]);
            if (render_handlers_[i])
                render_handlers_[i]->Render();
            glfwSwapBuffers(windows_[i]);
        }
    }

    void GlfwManager::SetListener(uint64_t index, std::shared_ptr<GlfwListener> listener)
    {
        listeners_[index] = std::move(listener);
    }

    bool GlfwManager::IsKeyDown(uint64_t index, int key)
    {
        return glfwGetKey(windows_[index], key) == GLFW_PRESS;
    }

    Dimension GlfwManager::GetWindowSize(uint64_t index)
    {
        Dimension dimension{};
        glfwGetWindowSize(windows_[index], &dimension.width, &dimension.height);
        return dimension;
    }

    Point GlfwManager::GetMousePos(uint64_t index)
    {
        Point point{};
        glfwGetCursorPos(windows_[index], &point.x, &point.y);
        return point;
    }

    bool GlfwManager::AllWindowShouldClose()
    {
        bool all_should_close = true;
        for (auto& window : windows_)
        {
            if (window && !glfwWindowShouldClose(window))
                all_should_close = false;
            else
            {
                glfwDestroyWindow(window);
                window = nullptr;
            }
        }
        return all_should_close;
    }

    void GlfwManager::PollEvents()
    {
        glfwPollEvents();
    }

    void GlfwManager::Terminate()
    {
        glfwTerminate();
    }

    uint64_t GlfwManager::GetIndexOfWindow(GLFWwindow* window)
    {
        for (uint64_t i = 0; i < windows_.size(); i++)
            if (windows_[i] == window)
                return i;
        return kNullIndex;
    }

    void GlfwManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        uint64_t index = GetIndexOfWindow(window);
        if (index == kNullIndex || !listeners_[index]) return;
        switch (action)
        {
        case GLFW_PRESS:
            listeners_[index]->KeyDown(key);
            break;
        case GLFW_RELEASE:
            listeners_[index]->KeyUp(key);
            break;
        }
    }

    void GlfwManager::MouseCallback(GLFWwindow* window, double x, double y)
    {
        uint64_t index = GetIndexOfWindow(window);
        if (index == kNullIndex || !listeners_[index]) return;
        listeners_[index]->MouseMove(x, y);
    }

    void GlfwManager::ResizeCallback(GLFWwindow* window, int width, int height)
    {
        uint64_t index = GetIndexOfWindow(window);
        if (index == kNullIndex || !listeners_[index]) return;
        listeners_[index]->Resized(width, height);
    }
}
