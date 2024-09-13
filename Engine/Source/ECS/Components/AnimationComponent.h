#pragma once

#include "Enginepch.h"

#include <SFML/Graphics/Rect.hpp>

#include "Core/Timestep.h"

#include "ECS/Components/SpriteComponent.h"

enum class PlayerState;
enum class AbilityState;
enum class EnemyState;

namespace Engine {

    class AnimationComponent
    {
    public:
        AnimationComponent();

        template<typename T>
        void AddAnimation(T state,
            const std::string& textureIdentifier,
            const std::vector<glm::ivec4>& frames,
            uint8_t frameWidthPadding,
            uint8_t frameHeightPadding,
            float frameDuration,
            bool enableLooping
        );

        template<typename T>
        void SetAnimation(T state);

        // Update the animation frame based on the elapsed time
        void Update(Timestep ts);

        // Reset the animation (Mainly for abilities' use)
        void ResetAnimation();

        // Check if the current animation has finished
        bool IsFinished() const;

        const glm::ivec4& GetCurrentFrame() const;

    public:
        struct Animation
        {
            std::string TextureIdentifier;
            std::vector<glm::ivec4> Frames;
            float FrameDuration;
            bool Loop = true;
            uint8_t FrameWidthPadding = 0;
            uint8_t FrameHeightPadding = 0;

            Animation() = default;

            Animation(const std::string& textureIdentifier, const std::vector<glm::ivec4>& frames,
                float frameDuration,
                uint8_t frameWidthPadding = 0,
                uint8_t frameHeightPadding = 0,
                bool enableLooping = true
            )
                : TextureIdentifier(textureIdentifier),
                Frames(frames),
                FrameDuration(frameDuration),
                FrameWidthPadding(frameWidthPadding),
                FrameHeightPadding(frameHeightPadding),
                Loop(enableLooping)
            {}
        };

        std::unordered_map<int, Animation> Animations;
        SpriteComponent* Sprite = nullptr;
    private:
        int m_CurrentAnimation = -1;
        float m_ElapsedTime;
        unsigned int m_CurrentFrame;
    };
}