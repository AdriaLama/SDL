#pragma once
#include "TextObject.h"
#include "GameManager.h"
#include <string>
#include <sstream>
#include <iomanip>

#define HUD_MANAGER HUDManager::Instance()

class HUDManager
{
private:
    TextObject* _scoreText;
    TextObject* _highScoreText;
    TextObject* _shieldText;
    TextObject* _livesText;
    TextObject* _cannonText;
    TextObject* _laserText;
    int _currentScore;
    int _highScore;
    int _lives;

    HUDManager()
        : _scoreText(nullptr),
        _highScoreText(nullptr),
        _shieldText(nullptr),
        _livesText(nullptr),
        _cannonText(nullptr),
        _laserText(nullptr),
        _currentScore(0),
        _highScore(0),
        _lives(3)
    {
    }

    HUDManager(const HUDManager&) = delete;
    HUDManager& operator=(const HUDManager&) = delete;

    std::string FormatScore(int score)
    {
        std::stringstream ss;
        ss << std::setw(7) << std::setfill('0') << score;
        return ss.str();
    }

public:
    static HUDManager& Instance()
    {
        static HUDManager instance;
        return instance;
    }

    void Initialize()
    {
        _scoreText = new TextObject("0000000");
        _scoreText->GetTransform()->position = Vector2(150.f, RM->WINDOW_HEIGHT - 20.f);
        _scoreText->GetTransform()->scale = Vector2(1.5f, 1.5f);
        _highScoreText = new TextObject("0000000");
        _highScoreText->GetTransform()->position = Vector2(100.f, RM->WINDOW_HEIGHT - 50.f);
        _highScoreText->GetTransform()->scale = Vector2(1.5f, 1.5f);
        _shieldText = new TextObject("SHIELD: 100");
        _shieldText->GetTransform()->position = Vector2(500.0f, RM->WINDOW_HEIGHT - 50.f);
        _shieldText->GetTransform()->scale = Vector2(1.5f, 1.5f);
        _cannonText = new TextObject("CANNON: --");
        _cannonText->GetTransform()->position = Vector2(800.0f, RM->WINDOW_HEIGHT - 50.f);
        _cannonText->GetTransform()->scale = Vector2(1.5f, 1.5f);
        _cannonText->GetRenderer()->SetColor({ 150, 150, 150, 255 });
        _laserText = new TextObject("LASER: --");
        _laserText->GetTransform()->position = Vector2(1100.0f, RM->WINDOW_HEIGHT - 50.f);
        _laserText->GetTransform()->scale = Vector2(1.5f, 1.5f);
        _laserText->GetRenderer()->SetColor({ 150, 150, 150, 255 });

        UpdateScoreDisplay();
    }

    void AddScore(int points)
    {
        _currentScore += points;

        if (_currentScore > _highScore)
        {
            _highScore = _currentScore;
            _scoreText->GetRenderer()->SetColor({ 255, 215, 0, 255 });
        }

        UpdateScoreDisplay();
    }

    void UpdateShield(int shieldValue)
    {
        if (_shieldText)
        {
            _shieldText->SetText("SHIELD: " + std::to_string(shieldValue));

            if (shieldValue > 70)
                _shieldText->GetRenderer()->SetColor({ 0, 255, 0, 255 });
            else if (shieldValue > 30)
                _shieldText->GetRenderer()->SetColor({ 255, 255, 0, 255 });
            else
                _shieldText->GetRenderer()->SetColor({ 255, 0, 0, 255 });
        }
    }

    void UpdateCannonEnergy(float currentEnergy, float maxEnergy, bool hasCannons)
    {
        if (_cannonText)
        {
            if (currentEnergy <= 1.f)
            {
                _cannonText->SetText("CANNON: --");
                _cannonText->GetRenderer()->SetColor({ 150, 150, 150, 255 }); 
            }
            else
            {
                int energyPercent = static_cast<int>((currentEnergy / maxEnergy) * 100.f);
                _cannonText->SetText("CANNON: " + std::to_string(energyPercent));

                if (energyPercent > 50)
                    _cannonText->GetRenderer()->SetColor({ 0, 200, 255, 255 });
                else if (energyPercent > 25)
                    _cannonText->GetRenderer()->SetColor({ 255, 165, 0, 255 });
                else
                    _cannonText->GetRenderer()->SetColor({ 255, 0, 0, 255 });
            }
        }
    }

    void UpdateLaserEnergy(float currentEnergy, float maxEnergy, bool hasLaser)
    {
        if (_laserText)
        {
            if (currentEnergy <= 1.f)
            {
                _laserText->SetText("LASER: --");
                _laserText->GetRenderer()->SetColor({ 150, 150, 150, 255 }); 
            }
            else
            {
                int energyPercent = static_cast<int>((currentEnergy / maxEnergy) * 100.f);
                _laserText->SetText("LASER: " + std::to_string(energyPercent));

                if (energyPercent > 50)
                    _laserText->GetRenderer()->SetColor({ 255, 0, 255, 255 });
                else if (energyPercent > 25)
                    _laserText->GetRenderer()->SetColor({ 255, 165, 0, 255 });
                else
                    _laserText->GetRenderer()->SetColor({ 255, 0, 0, 255 });
            }
        }
    }  

    void ResetScore()
    {
        _currentScore = 0;
        _scoreText->GetRenderer()->SetColor({ 255, 255, 255, 255 });
        UpdateScoreDisplay();
    }

    void Update()
    {
        Player* player = GAME_MANAGER.GetPlayer();
        if (player)
        {
            UpdateShield(player->GetShields());
            UpdateCannonEnergy(player->GetCannonEnergy(), player->GetMaxCannonEnergy(), player->HasCannons());
            UpdateLaserEnergy(player->GetLaserEnergy(), player->GetMaxLaserEnergy(), player->HasLaser());
        }
    }
    int GetCurrentScore() const { return _currentScore; }
    int GetHighScore() const { return _highScore; }

    TextObject* GetScoreText() { return _scoreText; }
    TextObject* GetHighScoreText() { return _highScoreText; }
    TextObject* GetShieldText() { return _shieldText; }
    TextObject* GetLivesText() { return _livesText; }
    TextObject* GetCannonText() { return _cannonText; }
    TextObject* GetLaserText() { return _laserText; }

private:
    void UpdateScoreDisplay()
    {
        if (_scoreText)
        {
            _scoreText->SetText(FormatScore(_currentScore));
        }

        if (_highScoreText)
        {
            _highScoreText->SetText("SCORE: " + FormatScore(_highScore));
            _highScoreText->GetRenderer()->SetColor({ 200, 200, 200, 255 }); 
        }
    }
};