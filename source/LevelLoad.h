#pragma once
#include "../dependencies/inc/xml/rapidxml.hpp"
#include "../dependencies/inc/xml/rapidxml_iterators.hpp"
#include "../dependencies/inc/xml/rapidxml_print.hpp"
#include "../dependencies/inc/xml/rapidxml_utils.hpp"
#include <string>
#include <vector>
#include <iostream>
#include<SDL3/SDL.h>

class LevelLoader
{
public:
    bool LoadLevel(std::string& path, std::vector<int>& wave, std::vector<int>& amount)
    {
        try {
            rapidxml::file<> xmlFile(path.c_str());
            rapidxml::xml_document<> doc;
            doc.parse<0>(xmlFile.data());

            rapidxml::xml_node<>* level = doc.first_node("level");
            if (!level) {
                throw SDL_GetError();
                return false;
            }

            for (rapidxml::xml_node<>* waves = level->first_node("wave");
                waves != nullptr;
                waves = waves->next_sibling("wave")) {

                rapidxml::xml_node<>* enemyIdNode = waves->first_node("spawned_enemy_id");
                rapidxml::xml_node<>* amountNode = waves->first_node("amount");

                if (!enemyIdNode || !enemyIdNode->value() || !amountNode || !amountNode->value()) {
                    continue;
                }

                wave.push_back(std::stoi(enemyIdNode->value()));
                amount.push_back(std::stoi(amountNode->value()));
            }

            return true;

        }
        catch (std::exception& e) {
            throw SDL_GetError();
            return false;
        }
    }
};