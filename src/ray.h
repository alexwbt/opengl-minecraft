#pragma once

namespace gl
{
    bool RayInertectsBox(const glm::vec3& origin, const glm::vec3& dir, const glm::vec3& box_min, const glm::vec3& box_max)
    {
        const glm::vec3 bounds[2] = { box_min , box_max };

        glm::vec3 invdir{ 1.0f / dir.x, 1.0f / dir.y, 1.0f / dir.z };
        bool sign[3] = { invdir.x < 0, invdir.y < 0, invdir.z < 0 };

        float tmin = (bounds[sign[0]].x - origin.x) * invdir.x;
        float tmax = (bounds[1 - sign[0]].x - origin.x) * invdir.x;
        float tymin = (bounds[sign[1]].y - origin.y) * invdir.y;
        float tymax = (bounds[1 - sign[1]].y - origin.y) * invdir.y;

        if ((tmin > tymax) || (tymin > tmax)) return false;
        if (tymin > tmin) tmin = tymin;
        if (tymax < tmax) tmax = tymax;

        float tzmin = (bounds[sign[2]].z - origin.z) * invdir.z;
        float tzmax = (bounds[1 - sign[2]].z - origin.z) * invdir.z;

        if ((tmin > tzmax) || (tzmin > tmax)) return false;
        if (tzmin > tmin) tmin = tzmin;
        if (tzmax < tmax) tmax = tzmax;

        return true;
    }
}
