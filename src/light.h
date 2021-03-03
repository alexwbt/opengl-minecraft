#pragma once

namespace gl
{
    enum class LightType {
        SUN, POINT, SPOT
    };

    struct Light
    {
        LightType type;
        glm::vec3 position, direction, ambient, diffuse, specular;
        float constant, linear, quadratic, cutOff, outerCutOff;
    };
}
