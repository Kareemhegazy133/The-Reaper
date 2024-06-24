#pragma once

#include "World/Components/Component.h"

#include "Enginepch.h"

namespace Engine {

    class GameplayEntity;

    class Rigidbody2DComponent : public Component
    {
    public:
        enum class BodyType { Static = 0, Dynamic, Kinematic };

        Rigidbody2DComponent(BodyType type = BodyType::Static)
            : Type(type) {}
        Rigidbody2DComponent(const Rigidbody2DComponent&) = default;

        /**
         * @brief Function pointer for handling collision events when a collision begins.
         *
         * This function pointer is used to define custom collision behavior when a collision
         * between entities starts. It can be assigned to a member function of a class or a lambda
         * function to handle collision events. The function should take a reference to an Entity
         * object representing the other entity involved in the collision.
         * @endcode
        */
        std::function<void(GameplayEntity&)> OnCollisionBegin = nullptr;

        /**
         * @brief Function pointer for handling collision events when a collision ends.
         *
         * This function pointer is used to define custom collision behavior when a collision
         * between entities ends. It can be assigned to a member function of a class or a lambda
         * function to handle collision events. The function should take a reference to an Entity
         * object representing the other entity involved in the collision.
         * @endcode
        */
        std::function<void(GameplayEntity&)> OnCollisionEnd = nullptr;

    public:
        BodyType Type;
        bool FixedRotation = true;

        // Storage for runtime
        void* RuntimeBody = nullptr;
    };
}