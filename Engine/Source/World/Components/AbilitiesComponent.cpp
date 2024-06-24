#include "Enginepch.h"

#include "World/Entities/GameplayEntities/GameplayEntity.h"
#include "World/Entities/GameplayEntities/Ability.h"

#include "AbilitiesComponent.h"

namespace Engine {

    AbilitiesComponent::AbilitiesComponent()
    {

    }

    void AbilitiesComponent::ActivateAbility(size_t index, GameplayEntity& caster)
    {
        if (index < m_Abilities.size())
        {
            Ref<Ability> ability = m_Abilities[index];
            if (ability->OnCooldown()) return;
            ability->Activate(caster);
        }
        else
        {
            ENGINE_ERROR("Ability index out of range");
        }
    }

    const std::vector<Ref<Ability>>& AbilitiesComponent::GetAbilities() const
    {
        return m_Abilities;
    }
}