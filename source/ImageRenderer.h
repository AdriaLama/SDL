#pragma once
#include "Renderer.h"
#include "RenderManager.h"

class ImageRenderer : public Renderer {

	virtual void Update(float dt) override;
	virtual void Render() override;
public:
	ImageRenderer(Transform* transform, std::string resourcePath, Vector2 sourceOffset, Vector2 sourceSize) : Renderer(transform, resourcePath)
	{
		SDL_Texture* tex = RM->GetTexture(resourcePath);

		_sourceRect = SDL_FRect
		{
			0.0f,
			0.0f,
			(float)tex->w,
			(float)tex->h
		};

		_destinationRect = SDL_FRect
		{
			transform->position.x,
			transform->position.y,
			transform->scale.x,
			transform->scale.y
		};
	}
};
