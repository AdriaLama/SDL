#pragma once
#include "Object.h"
#include "TextRenderer.h"

class TextObject : public Object
{
public:
	TextObject(std::string text) : Object()
	{
		_renderer = new TextRenderer(_transform, text);
		_renderer->SetColor({ 255, 255, 255, 0xFF }); // Blanco por defecto
	}

	void SetText(std::string text)
	{
		dynamic_cast<TextRenderer*>(_renderer)->SetText(text);
	}

	// Métodos de acceso para el HUD
	Transform* GetTransform() { return _transform; }
	TextRenderer* GetRenderer() { return dynamic_cast<TextRenderer*>(_renderer); }
};