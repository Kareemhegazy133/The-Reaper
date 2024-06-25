#pragma once

#include "Scene/Components/Component.h"

#include "Enginepch.h"

namespace Engine {

    class CharacterComponent : public Component
    {
    public:

        CharacterComponent() = default;
        CharacterComponent(const CharacterComponent&) = default;

    public:
        float Speed;

    };
}