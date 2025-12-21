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

    int _currentScore;
    int _highScore;
    int _lives;

    const float SCORE_X = 100.0f;
    const float SCORE_Y = 720.0f;
    const float HIGHSCORE_OFFSET_Y = 30.0f;

    HUDManager()
        : _scoreText(nullptr),
        _highScoreText(nullptr),
        _shieldText(nullptr),
        _livesText(nullptr),
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
        _scoreText->GetTransform()->position = Vector2(SCORE_X, SCORE_Y);
        _scoreText->GetTransform()->scale = Vector2(1.2f, 1.2f);

        _highScoreText = new TextObject("0000000");
        _highScoreText->GetTransform()->position = Vector2(SCORE_X, SCORE_Y - HIGHSCORE_OFFSET_Y);
        _highScoreText->GetTransform()->scale = Vector2(1.0f, 1.0f);

        // Texto para el shield (opcional)
        _shieldText = new TextObject("SHIELD: 100");
        _shieldText->GetTransform()->position = Vector2(200.0f, SCORE_Y);
        _shieldText->GetTransform()->scale = Vector2(0.9f, 0.9f);

        // Texto para las vidas
        _livesText = new TextObject("LIVES: 3");
        _livesText->GetTransform()->position = Vector2(50.0f, 50.0f);
        _livesText->GetTransform()->scale = Vector2(1.0f, 1.0f);

        UpdateScoreDisplay();
    }

    void AddScore(int points)
    {
        _currentScore += points;

        // Verificar si es nuevo highscore
        if (_currentScore > _highScore)
        {
            _highScore = _currentScore;
            // Cambiar color a dorado para el score actual
            _scoreText->GetRenderer()->SetColor({ 255, 215, 0, 255 }); // Dorado
        }

        UpdateScoreDisplay();
    }

    void UpdateShield(int shieldValue)
    {
        if (_shieldText)
        {
            _shieldText->SetText("SHIELD: " + std::to_string(shieldValue));

            // Cambiar color según el shield
            if (shieldValue > 70)
                _shieldText->GetRenderer()->SetColor({ 0, 255, 0, 255 }); // Verde
            else if (shieldValue > 30)
                _shieldText->GetRenderer()->SetColor({ 255, 255, 0, 255 }); // Amarillo
            else
                _shieldText->GetRenderer()->SetColor({ 255, 0, 0, 255 }); // Rojo
        }
    }

    void UpdateLives(int lives)
    {
        _lives = lives;
        if (_livesText)
        {
            _livesText->SetText("LIVES: " + std::to_string(_lives));
        }
    }

    void ResetScore()
    {
        _currentScore = 0;
        _scoreText->GetRenderer()->SetColor({ 255, 255, 255, 255 }); // Blanco
        UpdateScoreDisplay();
    }

    void Update()
    {
        // Actualizar shield si hay un jugador
        Player* player = GAME_MANAGER.GetPlayer();
        if (player)
        {
            UpdateShield(player->GetShields());
        }
    }

    int GetCurrentScore() const { return _currentScore; }
    int GetHighScore() const { return _highScore; }

    TextObject* GetScoreText() { return _scoreText; }
    TextObject* GetHighScoreText() { return _highScoreText; }
    TextObject* GetShieldText() { return _shieldText; }
    TextObject* GetLivesText() { return _livesText; }

private:
    void UpdateScoreDisplay()
    {
        if (_scoreText)
        {
            _scoreText->SetText(FormatScore(_currentScore));
        }

        if (_highScoreText)
        {
            _highScoreText->SetText("HI: " + FormatScore(_highScore));
            _highScoreText->GetRenderer()->SetColor({ 200, 200, 200, 255 }); // Gris claro
        }
    }
};