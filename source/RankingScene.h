#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "Button.h"
#include "RankingManager.h"
#include "SceneManager.h"
#include <sstream>
#include <iomanip>

class RankingScene : public Scene {
public:
    RankingScene() {}

    void OnEnter() override {
  
        TextObject* titleText = new TextObject("HIGH SCORES");
        titleText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f - 250.f, 50.f);
        titleText->GetTransform()->scale = Vector2(3.f, 3.f);
        titleText->GetRenderer()->SetColor({ 255, 215, 0, 255 }); 
        _ui.push_back(titleText);

        TextObject* rankHeader = new TextObject("RANK");
        rankHeader->GetTransform()->position = Vector2(200.f, 150.f);
        rankHeader->GetTransform()->scale = Vector2(1.5f, 1.5f);
        rankHeader->GetRenderer()->SetColor({ 200, 200, 200, 255 });
        _ui.push_back(rankHeader);

        TextObject* nameHeader = new TextObject("NAME");
        nameHeader->GetTransform()->position = Vector2(400.f, 150.f);
        nameHeader->GetTransform()->scale = Vector2(1.5f, 1.5f);
        nameHeader->GetRenderer()->SetColor({ 200, 200, 200, 255 });
        _ui.push_back(nameHeader);

        TextObject* scoreHeader = new TextObject("SCORE");
        scoreHeader->GetTransform()->position = Vector2(800.f, 150.f);
        scoreHeader->GetTransform()->scale = Vector2(1.5f, 1.5f);
        scoreHeader->GetRenderer()->SetColor({ 200, 200, 200, 255 });
        _ui.push_back(scoreHeader);

        const auto& rankings = RANKING_MANAGER.GetRankings();
        float startY = 220.f;
        float spacing = 45.f;

        for (size_t i = 0; i < rankings.size() && i < 10; ++i) {
            float yPos = startY + (i * spacing);

            SDL_Color color = { 255, 255, 255, 255 }; 
            if (i == 0) color = { 255, 215, 0, 255 };  
            else if (i == 1) color = { 192, 192, 192, 255 }; 
            else if (i == 2) color = { 205, 127, 50, 255 }; 

      
            TextObject* rankText = new TextObject(std::to_string(i + 1) + ".");
            rankText->GetTransform()->position = Vector2(220.f, yPos);
            rankText->GetTransform()->scale = Vector2(1.8f, 1.8f);
            rankText->GetRenderer()->SetColor(color);
            _ui.push_back(rankText);

         
            TextObject* nameText = new TextObject(rankings[i].playerName);
            nameText->GetTransform()->position = Vector2(400.f, yPos);
            nameText->GetTransform()->scale = Vector2(1.8f, 1.8f);
            nameText->GetRenderer()->SetColor(color);
            _ui.push_back(nameText);

        
            std::stringstream ss;
            ss << std::setw(7) << std::setfill('0') << rankings[i].score;
            TextObject* scoreText = new TextObject(ss.str());
            scoreText->GetTransform()->position = Vector2(800.f, yPos);
            scoreText->GetTransform()->scale = Vector2(1.8f, 1.8f);
            scoreText->GetRenderer()->SetColor(color);
            _ui.push_back(scoreText);
        }

   
        if (rankings.empty()) {
            TextObject* emptyText = new TextObject("NO SCORES YET!");
            emptyText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f - 200.f, 350.f);
            emptyText->GetTransform()->scale = Vector2(2.f, 2.f);
            emptyText->GetRenderer()->SetColor({ 150, 150, 150, 255 });
            _ui.push_back(emptyText);
        }

        float buttonY = RM->WINDOW_HEIGHT - 100.f;
        Button* backButton = new Button( []() { SM.SetNextScene("MenuScene"); }, Vector2(RM->WINDOW_WIDTH / 2.0f - 75.f, buttonY - 40.f),Vector2(300.f, 60.f) );
        _ui.push_back(backButton);

        TextObject* backText = new TextObject("BACK TO MENU");
        backText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f - 130.f, buttonY + 15.f);
        backText->GetTransform()->scale = Vector2(1.5f, 1.5f);
        _ui.push_back(backText);
    }

    void OnExit() override {
        Scene::OnExit();
    }

    void Update() override {
        Scene::Update();
    }

    void Render() override {
        Scene::Render();
    }
};