#pragma once

#include "World/Components/Component.h"

#include "Enginepch.h"

namespace Engine {

    class AbilityComponent : public Component
    {
    public:

        AbilityComponent() = default;
        AbilityComponent(const AbilityComponent&) = default;

    public:
        Entity* Caster = nullptr;
        float Speed;

        float ActiveDuration = 0.0f;
        float MaxDuration = 2.f;
    };
}

