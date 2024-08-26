#pragma once

#include "SFML/Graphics.hpp"

#include "Core/Base.h"
#include "Core/Log.h"

#include "Window.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Core/Timestep.h"

#include "Utils/TextureManager.h"
#include "Utils/FontManager.h"

int main(int argc, char** argv);

namespace Engine {

	struct GameApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			ENGINE_ASSERT(index < Count);
			return Args[index];
		}
	};

	class GameApplication
	{
	public:
		GameApplication(
			const std::string& name = "Game App",
			const uint32_t width = 1280,
			const uint32_t height = 720,
			GameApplicationCommandLineArgs args = GameApplicationCommandLineArgs()
		);
		virtual ~GameApplication();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Window& GetWindow() { return *(s_Instance->m_Window); }
		inline static sf::RenderWindow* GetRenderWindow() { return static_cast<sf::RenderWindow*>(s_Instance->GetWindow().GetNativeWindow()); }
		inline float SFMLGetTime() { return clock.getElapsedTime().asSeconds(); }

		inline static GameApplication& Get() { return *s_Instance; }

		GameApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }
	private:
		void Run();
		
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		GameApplicationCommandLineArgs m_CommandLineArgs;
		Scope<Window> m_Window;
		LayerStack m_LayerStack;
		sf::Clock clock;
		float m_LastFrameTime = 0.0f;
	private:
		static GameApplication* s_Instance;
		Scope<TextureManager> m_TextureManager;
		Scope<FontManager> m_FontManager;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in GAME
	GameApplication* CreateGameApplication(GameApplicationCommandLineArgs args);
}