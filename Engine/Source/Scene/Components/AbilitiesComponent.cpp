#include "Enginepch.h"

#include "Scene/Entities/Entity.h"
#include "Scene/Entities/Ability.h"

#include "AbilitiesComponent.h"

namespace Engine {

    AbilitiesComponent::AbilitiesComponent()
    {

    }

    bool AbilitiesComponent::ActivateAbility(size_t index, Entity& caster)
    {
        if (index < m_Abilities.size())
        {
            Ref<Ability> ability = m_Abilities[index];
            if (ability->OnCooldown()) return false;
            ability->Activate(caster);
            return true;
        }
        else
        {
            ENGINE_ERROR("Ability index out of range");
        }
        return false;
    }

    const std::vector<Ref<Ability>>& AbilitiesComponent::GetAbilities() const
    {
        return m_Abilities;
    }
}
