#pragma once

#include "World/Components/Component.h"

#include "Enginepch.h"

namespace Engine {

    class BoxCollider2DComponent: public Component
    {
    public:
        sf::Vector2f Offset = { 0.0f, 0.0f };

        float Density = 1.0f;
        float Friction = 0.5f;
        float Restitution = 0.0f;
        float RestitutionThreshold = 0.0f;

        // Storage for runtime
        void* RuntimeFixture = nullptr;

        BoxCollider2DComponent() = default;
        BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
    };
}