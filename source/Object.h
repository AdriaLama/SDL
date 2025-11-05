#pragma once
#include "Vector2.h"
#include "Renderer.h"
#include <SDL3/SDL.h>
#include <string>

class Object
{
private:
	bool _isPendingDestroy = false;
	
protected:
	Renderer * _renderer = nullptr;
	Transform * _transform;
public:
	Object()
	{
		 _transform = new Transform();
	}
	
	~Object()
	{
		 delete _transform;
		 _transform = nullptr;
		
		 delete _renderer;
		 _renderer = nullptr;
	}
	
		virtual void Update()
		{
		 _renderer->Update(0.02f); 
		}
	
		virtual void Render()
		{
		 _renderer->Render();
		}
	
	Transform * GetTransform() { return _transform; }
	
	bool IsPendingDestroy() const { return _isPendingDestroy; }
	virtual void Destroy() { _isPendingDestroy = true; }
};