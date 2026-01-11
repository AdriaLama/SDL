#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "Button.h"
#include "RankingManager.h"
#include "ScoreManager.h"
#include "InputManager.h"
#include <string>

class RankingNameScene : public Scene {
private:
    std::string _playerName;
    TextObject* _nameDisplay;
    TextObject* _instructionText;
    TextObject* _scoreText;
    int _finalScore;
    bool _isTopScore;


    bool _backspacePressed;
    bool _enterPressed;
    bool _escapePressed;

public:
    RankingNameScene() : _playerName(""), _nameDisplay(nullptr),
        _instructionText(nullptr), _scoreText(nullptr),
        _finalScore(0), _isTopScore(false),
        _backspacePressed(false), _enterPressed(false), _escapePressed(false) {
    }

    void SetFinalScore(int score) {
        _finalScore = score;
        _isTopScore = RANKING_MANAGER.IsTopScore(score);
    }

    void OnEnter() override {
      
        TextObject* titleText = new TextObject("GAME OVER");
        titleText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f - 200.f, 100.f);
        titleText->GetTransform()->scale = Vector2(3.f, 3.f);
        titleText->GetRenderer()->SetColor({ 255, 0, 0, 255 });
        _ui.push_back(titleText);

        // Mostrar score final
        _scoreText = new TextObject("FINAL SCORE: " + std::to_string(_finalScore));
        _scoreText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f - 250.f, 200.f);
        _scoreText->GetTransform()->scale = Vector2(2.f, 2.f);
        if (_isTopScore) {
            _scoreText->GetRenderer()->SetColor({ 255, 215, 0, 255 }); // Dorado
        }
        _ui.push_back(_scoreText);

        // Mensaje según si es top score o no
        if (_isTopScore) {
            _instructionText = new TextObject("NEW HIGH SCORE! ENTER YOUR NAME:");
            _instructionText->GetRenderer()->SetColor({ 0, 255, 0, 255 });
        }
        else {
            _instructionText = new TextObject("ENTER YOUR NAME:");
        }
        _instructionText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f - 300.f, 300.f);
        _instructionText->GetTransform()->scale = Vector2(1.5f, 1.5f);
        _ui.push_back(_instructionText);

        _nameDisplay = new TextObject("_");
        _nameDisplay->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f - 150.f, 380.f);
        _nameDisplay->GetTransform()->scale = Vector2(2.5f, 2.5f);
        _nameDisplay->GetRenderer()->SetColor({ 255, 255, 255, 255 });
        _ui.push_back(_nameDisplay);

        TextObject* hintText = new TextObject("PRESS ENTER TO SUBMIT");
        hintText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f - 250.f, 500.f);
        hintText->GetTransform()->scale = Vector2(1.2f, 1.2f);
        hintText->GetRenderer()->SetColor({ 150, 150, 150, 255 });
        _ui.push_back(hintText);

        _playerName = "";
    }

    void Update() override {
        

        if (IM->GetEvent(SDLK_BACKSPACE, DOWN) && !_playerName.empty()) {
            _playerName.pop_back();
            UpdateNameDisplay();
        }

        if (IM->GetEvent(SDLK_RETURN, DOWN) && !_playerName.empty()) {
            SubmitScore();
        }

        if (IM->GetEvent(SDLK_ESCAPE, DOWN)) {
            SM.SetNextScene("MenuScene");
        }

      
        for (int key = SDLK_A; key <= SDLK_Z; ++key) {
            if (IM->GetEvent(key, DOWN) && _playerName.length() < 15) {
                char c = static_cast<char>(key);
                _playerName += c;
                UpdateNameDisplay();
            }
        }

        for (int key = SDLK_0; key <= SDLK_9; ++key) {
            if (IM->GetEvent(key, DOWN) && _playerName.length() < 15) {
                char c = static_cast<char>(key);
                _playerName += c;
                UpdateNameDisplay();
            }
        }

        if (IM->GetEvent(SDLK_SPACE, DOWN) && _playerName.length() < 15) {
            _playerName += ' ';
            UpdateNameDisplay();
        }

        Scene::Update();
    }

    void OnExit() override {
        _nameDisplay = nullptr;
        _instructionText = nullptr;
        _scoreText = nullptr;
        Scene::OnExit();
    }

    void Render() override {
        Scene::Render();
    }

private:
    void UpdateNameDisplay() {
        if (_nameDisplay) {
            std::string displayText = _playerName.empty() ? "_" : _playerName + "_";
            _nameDisplay->SetText(displayText);
        }
    }

    void SubmitScore() {
        if (!_playerName.empty()) {
            RANKING_MANAGER.AddScore(_playerName, _finalScore);
            SM.SetNextScene("Ranking");
        }
    }
};