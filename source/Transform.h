#pragma once
#include "Vector2.h"

class Transform {
public:
	Vector2 position;
	float rotation;
	Vector2 scale;

	Transform()
		: position(Vector2(0.f, 0.f)), rotation(0.f), scale(Vector2(1.f, 1.f)) {}

	Transform(Vector2 _position, float _rotation, Vector2 _scale)
		: position(_position), rotation(_rotation), scale(_scale) {}
};