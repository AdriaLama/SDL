#pragma once
#include "Scene.h"
#include "ImageObject.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

class SplashScreen : public Scene
{
private:
    ImageObject* _splashImage;
    float _timer;
    const float _displayDuration = 3.0f;

public:
    SplashScreen()
        : _splashImage(nullptr), _timer(0.0f)
    {
    }

    void OnEnter() override
    {
        _timer = 0.0f;

      
        _splashImage = new ImageObject("resources/images/SplashScreen.png", Vector2(0.f, 0.f), Vector2(0.0f, 0.0f));

        _splashImage->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2, RM->WINDOW_HEIGHT / 2);
        _splashImage->GetTransform()->scale = Vector2(13.75f, 9.25f);
        _splashImage->GetTransform()->rotation = 0.f;

        _objects.push_back(_splashImage);
    }

    void OnExit() override
    {
        Scene::OnExit();
    }

    void Update() override
    {
        _timer += TM.GetDeltaTime();

        if (_timer >= _displayDuration)
        {
            SM.SetNextScene("MenuScene");
        }

        Scene::Update();
    }

    void Render() override
    {
        Scene::Render();
    }
};