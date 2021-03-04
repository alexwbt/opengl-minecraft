#pragma once

namespace gl
{
    enum class LightType {
        SUN, POINT, SPOT
    };

    struct LightColor {
        glm::vec3 ambient, diffuse, specular;
    };

    struct LightStrength {
        float constant, linear, quadratic;
    };

    struct Light
    {
        LightType type;
        glm::vec3 position{ 0 };
        glm::vec3 direction{ 0 };
        glm::vec3 ambient, diffuse, specular;
        float constant = 0, linear = 0, quadratic = 0;
        float cutOff = 0, outerCutOff = 0;

        Light(glm::vec3 _direction, LightColor color)
            : type(LightType::SUN), direction(_direction),
            ambient(color.ambient), diffuse(color.diffuse), specular(color.specular)
        {}

        Light(glm::vec3 _position, LightColor color, LightStrength strength)
            : type(LightType::POINT), position(_position),
            ambient(color.ambient), diffuse(color.diffuse), specular(color.specular),
            constant(strength.constant), linear(strength.linear), quadratic(strength.quadratic)
        {}

        Light(glm::vec3 _position, glm::vec3 _direction, LightColor color, LightStrength strength, float _cutOff, float _outerCutOff)
            : type(LightType::SPOT), position(_position), direction(_direction),
            ambient(color.ambient), diffuse(color.diffuse), specular(color.specular),
            constant(strength.constant), linear(strength.linear), quadratic(strength.quadratic),
            cutOff(glm::cos(glm::radians(cutOff))), outerCutOff(glm::cos(glm::radians(_outerCutOff)))
        {}
    };
}
