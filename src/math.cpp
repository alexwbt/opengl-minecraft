#include "pch.h"
#include "math.h"

namespace util
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0, 1);

    float rand()
    {
        return dis(gen);
    }

    float pow(float value, int pow)
    {
        float result = 1;
        for (int i = 0; i < pow; ++i)
            result *= value;
    }
}
