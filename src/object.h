#pragma once

namespace game
{
    class Object
    {
    public:
        Object();
        virtual ~Object();

        void Update();
        void Render();
    };
}
