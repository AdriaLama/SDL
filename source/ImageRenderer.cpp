#include "ImageRenderer.h"
#include <cassert>
#include <SDL3_image/SDL_image.h>


void ImageRenderer::Update(float dt)
{
	Vector2 offset = (Vector2(-_transform->size.x, -_transform->size.y) / 2.0f) * _transform -> scale;

	_destinationRect.x = _transform->position.x + offset.x;
	_destinationRect.y = _transform->position.y + offset.y;

	_destinationRect.w = _transform->size.x * _transform->scale.x;
	_destinationRect.h = _transform->size.y * _transform->scale.y;

}

void ImageRenderer::Render()
{
	SDL_RenderTextureRotated
	(
		RM->GetRenderer(),
		RM->GetTexture(_resourcePath),
		&_sourceRect,
		&_destinationRect,
		_transform->rotation,
		NULL,
		SDL_FLIP_NONE
	);

}
