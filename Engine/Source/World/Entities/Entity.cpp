#include "Enginepch.h"
#include "Entity.h"

namespace Engine {

	Entity::Entity(entt::entity handle, World* world)
		: m_EntityHandle(handle), m_World(world)
	{
		
	}

	void Entity::OnUpdate(Timestep ts)
	{
		if (GetComponent<MetadataComponent>().OnUpdate)
		{
			GetComponent<MetadataComponent>().OnUpdate(ts);
		}
	}
}