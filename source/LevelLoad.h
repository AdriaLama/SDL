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
    bool LoadLevel(const std::string& path, std::vector<int>& wave, std::vector<int>& amount)
    {
        try {
            rapidxml::file<> xmlFile(path.c_str());  
            rapidxml::xml_document<> doc;
            doc.parse<0>(xmlFile.data());

            rapidxml::xml_node<>* level = doc.first_node("level");
            if (!level) {
                std::cerr << "Error: No se encontró el nodo 'level' en el XML" << std::endl;
                return false;
            }

            wave.clear();
            amount.clear();

            for (rapidxml::xml_node<>* waves = level->first_node("wave");
                waves != nullptr;
                waves = waves->next_sibling("wave")) {

                rapidxml::xml_node<>* enemyIdNode = waves->first_node("spawned_enemy_id");
                rapidxml::xml_node<>* amountNode = waves->first_node("amount");

                if (!enemyIdNode || !enemyIdNode->value() || !amountNode || !amountNode->value()) {
                    std::cerr << "Advertencia: Wave con datos incompletos" << std::endl;
                    continue;
                }

                try {
                    wave.push_back(std::stoi(enemyIdNode->value()));
                    amount.push_back(std::stoi(amountNode->value()));
                }
                catch (const std::exception& e) {
                    std::cerr << "Error al convertir valores: " << e.what() << std::endl;
                    continue;
                }
            }

            std::cout << "? Cargadas " << wave.size() << " waves correctamente" << std::endl;
            return true;

        }
        catch (const std::exception& e) {
            std::cerr << "Error al cargar nivel: " << e.what() << std::endl;
            return false;
        }
    }
};