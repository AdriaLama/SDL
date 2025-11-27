#pragma once
#include "Object.h"
#include "TextRenderer.h"

class TextObject : public Object
{
public:
	TextObject(std::string text) : Object()
	{
		_renderer = new TextRenderer(_transform, text);
		_renderer->SetColor({ 0 , 0, 0, 0xFF });
	}

	void SetText(std::string text)
	{
		dynamic_cast <TextRenderer*>(_renderer)->SetText(text);
	}
};