#include "GameLevel.h"

GameLevel::GameLevel()
{
	auto platform = CreateGameObject("Platform");
	platform.AddComponent<SpriteComponent>("Platform");
	auto& platform_transform = platform.GetComponent<TransformComponent>();
	platform_transform.SetPosition(300.f, 600.f);

	auto& platform_rb2d = platform.AddComponent<Rigidbody2DComponent>();
	platform.AddComponent<BoxCollider2DComponent>();

	/*auto platform2 = CreateGameObject("Platform2");
	platform2.AddComponent<SpriteComponent>("Platform");
	auto& platform2_transform = platform2.GetComponent<TransformComponent>();
	platform2_transform.setPosition(300.f, 0.f);

	auto& platform2_rb2d = platform2.AddComponent<Rigidbody2DComponent>(Rigidbody2DComponent::BodyType::Dynamic);
	platform2.AddComponent<BoxCollider2DComponent>();*/
}

GameLevel::~GameLevel()
{
}

void GameLevel::OnUpdate(Timestep ts)
{
	auto view = GetView<MetadataComponent, TransformComponent, SpriteComponent, BoxCollider2DComponent>();
	for (auto entityHandle : view)
	{
		auto& [metadata, transform, sprite, bc2d] = view.get<
			MetadataComponent, TransformComponent, SpriteComponent, BoxCollider2DComponent>(entityHandle);

		// Skip inactive Entities
		if (!metadata.IsActive) continue;

		Entity entity(entityHandle, this);
		entity.OnUpdate(ts);

		// Update Physics Colliders of all entities
		m_Physics.UpdateBoxColliderFixture(bc2d, transform, sprite);

		// Update the sprite's animation
		sprite.Update(ts);
	}

	// Apply Physics
	m_Physics.OnUpdate(ts);
}

void GameLevel::OnRender()
{
	// Update the transform after applying physics for sprite rendering
	auto view = GetView<MetadataComponent, TransformComponent, SpriteComponent>();
	for (auto entity : view)
	{
		auto& [metadata, transform, sprite] = view.get<MetadataComponent, TransformComponent, SpriteComponent>(entity);

		// Skip inactive Entities
		if (!metadata.IsActive) continue;

		// Apply the transform to the sprite
		sprite.SetPosition(transform.GetPosition());
		sprite.SetRotation(transform.GetRotation());
		sprite.SetScale(transform.GetScale());

		// Draw the sprite to the render window
		m_RenderWindow->draw(sprite);
	}
}

void GameLevel::OnEvent(Event& e)
{

}