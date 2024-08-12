#include <Engine.h>
#include <Core/EntryPoint.h>

#include "GameTheme.h"
#include "Layers/GameLayer.h"

// TODO: Abstract sf::X from Game

class TheReaper : public Engine::GameApplication
{

public:
	// TODO Support Multiple Resolutions
	TheReaper(GameApplicationCommandLineArgs args)
		: GameApplication("The Reaper", 1280, 720, args)
	{
		LoadAssets();
		PushLayer(new GameLayer());
	}

	void LoadAssets()
	{
		FontManager::LoadFont("Euljiro", "Assets/Font/Euljiro.ttf");

		TextureManager::LoadTexture("PlayerIdle", "Assets/Player/Reaper/ReaperIdle.png");
		TextureManager::LoadTexture("PlayerWalk", "Assets/Player/Reaper/ReaperWalk.png");
		TextureManager::LoadTexture("PlayerThrow", "Assets/Player/Reaper/ReaperThrow.png");
		TextureManager::LoadTexture("PlayerIcon", "Assets/Player/Reaper/ReaperIcon.png");
		TextureManager::LoadTexture("FireballActive", "Assets/Abilities/Fireball.png");
		TextureManager::LoadTexture("Platform", "Assets/Platform.png");

		TextureManager::LoadTexture("LargeButton", "Assets/UI/Buttons/LargeButton.png");
		TextureManager::LoadTexture("LargeButtonHovered", "Assets/UI/Buttons/LargeButtonHovered.png");
		TextureManager::LoadTexture("MediumButton", "Assets/UI/Buttons/MediumButton.png");
		TextureManager::LoadTexture("MediumButtonHovered", "Assets/UI/Buttons/MediumButtonHovered.png");

		TextureManager::LoadTexture("MainMenu", "Assets/UI/Menus/MainMenu.png");
		TextureManager::LoadTexture("PauseMenu", "Assets/UI/Menus/PauseMenu.png");

		TextureManager::LoadTexture("CharacterInfoMenu", "Assets/UI/Menus/CharacterInfoMenu.png");
		TextureManager::LoadTexture("CloseButton", "Assets/UI/Buttons/CloseButton.png");
		TextureManager::LoadTexture("CloseButtonHovered", "Assets/UI/Buttons/CloseButtonHovered.png");
		TextureManager::LoadTexture("CommonButton", "Assets/UI/Buttons/CommonButton.png");
		TextureManager::LoadTexture("CommonButtonHovered", "Assets/UI/Buttons/CommonButtonHovered.png");
		TextureManager::LoadTexture("CommonButtonDisabled", "Assets/UI/Buttons/CommonButtonDisabled.png");
		TextureManager::LoadTexture("RightArrowButton", "Assets/UI/Buttons/RightArrowButton.png");
		TextureManager::LoadTexture("RightArrowButtonHovered", "Assets/UI/Buttons/RightArrowButtonHovered.png");
		TextureManager::LoadTexture("RightArrowButtonDisabled", "Assets/UI/Buttons/RightArrowButtonDisabled.png");
		TextureManager::LoadTexture("LeftArrowButton", "Assets/UI/Buttons/LeftArrowButton.png");
		TextureManager::LoadTexture("LeftArrowButtonHovered", "Assets/UI/Buttons/LeftArrowButtonHovered.png");
		TextureManager::LoadTexture("LeftArrowButtonDisabled", "Assets/UI/Buttons/LeftArrowButtonDisabled.png");
		TextureManager::LoadTexture("CoinIcon", "Assets/UI/Icons/CoinIcon.png");
		TextureManager::LoadTexture("DiamondIcon", "Assets/UI/Icons/DiamondIcon.png");

		GameTheme::Initialize();
	}

};

Engine::GameApplication* Engine::CreateGameApplication(GameApplicationCommandLineArgs args)
{
	return new TheReaper(args);
}
