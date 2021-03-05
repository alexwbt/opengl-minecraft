#pragma once

#include "camera.h"

namespace game
{
    struct RenderInfo
    {
        gl::Camera& camera;
        glm::mat4& pv;
    };
}
