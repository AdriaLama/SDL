#pragma once
#include "Renderer.h"
#include "RenderManager.h"

class ImageRenderer : public Renderer {
	ImageRenderer(Transform* transform, std::string resourcePath, Vector2 sourceOffset, Vector2 sourceSize) : Renderer(transform, resourcePath)
	{
		RM->GetTexture(resourcePath);

		_sourceRect = SDL_FRect
		{
			sourceOffset.x,
			sourceOffset.y,
			sourceSize.x,
			sourceSize.y
		};

		_destRect = SDL_FRect
		{
			transform->position.x,
			transform->position.y,
			transform->scale.x,
			transform->scale.y
		};
	}
};
