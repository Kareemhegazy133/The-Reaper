#pragma once

#include <typeindex>

#include "Core/GameApplication.h"
#include "Core/Timestep.h"

#include "UIElement.h"

namespace Engine {

	class UIScreen
	{
	public:
		virtual ~UIScreen()
		{
			for (auto& pair : m_Elements)
			{
				for (auto element : pair.second)
				{
					delete element;
				}
				pair.second.clear();
			}
			m_Elements.clear();
			m_OrderedElements.clear();
		}

		virtual void Initialize() = 0;
		
		template<typename T, typename... Args>
		T& AddElement(Args&&... args)
		{
			T* element = new T(std::forward<Args>(args)...);
			m_Elements[typeid(T)].emplace_back(element);
			m_OrderedElements.emplace_back(element);
			return *element;
		}

		//virtual void OnUpdate(Timestep ts) = 0;

		virtual void OnRender()
		{
			for (UIElement* element : m_OrderedElements)
			{
				ENGINE_ASSERT(element, "Element must not be nullptr!");
				element->OnRender(m_RenderWindow);
			}
		}

		virtual void OnEvent(Event& e) = 0;

		inline virtual void SetVisibility(bool visible) { m_IsVisible = visible; }
		inline virtual bool IsVisible() const { return m_IsVisible; }
		
	protected:
		sf::RenderWindow* m_RenderWindow = GameApplication::GetRenderWindow();
		bool m_IsVisible = false;

		// To group elements by type
		std::unordered_map<std::type_index, std::vector<UIElement*>> m_Elements;
		// To track insertion order for rendering
		std::vector<UIElement*> m_OrderedElements;
	};
}
