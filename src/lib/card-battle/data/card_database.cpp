#include "retronomicon/lib/card-battle/data/card_database.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp> // JSON lib (https://github.com/nlohmann/json)

using json = nlohmann::json;

namespace retronomicon::lib::cardBattle::data {
bool CardDatabase::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open card JSON: " << filePath << "\n";
        return false;
    }

    json data;
    file >> data;

    for (const auto& cardJson : data["cards"]) {
        std::string id = cardJson["id"];
        std::string type = cardJson["type"];
        std::string name = cardJson["name"];
        std::string image = cardJson["image"];
        std::string effectScript = cardJson.value("effectScript", "");

        if (type == "action") {
            std::unordered_map<std::string, int> cost;
            for (auto it = cardJson["cost"].begin(); it != cardJson["cost"].end(); ++it) {
                cost[it.key()] = it.value().get<int>();
            }
            int damage = cardJson["damage"];
            registry[id] = std::make_unique<ActionCard>(name, image, cost, damage, effectScript);
            // TODO: store effectScript link somewhere (later: Lua integration)
        }
        else if (type == "resource") {
            std::unordered_map<std::string, int> value;
            for (auto it = cardJson["value"].begin(); it != cardJson["value"].end(); ++it) {
                value[it.key()] = it.value().get<int>();
            }
            registry[id] = std::make_unique<ResourceCard>(name, image, value,effectScript);
            // TODO: store effectScript link
        }
        else {
            std::cerr << "Unknown card type: " << type << "\n";
        }
    }

    return true;
}

std::unique_ptr<Card> CardDatabase::createCard(const std::string& id) const {
    auto it = registry.find(id);
    if (it == registry.end()) {
        std::cerr << "Card not found: " << id << "\n";
        return nullptr;
    }

    return it->second->clone(); // ✅ cleaner
}

void CardDatabase::listCards() const {
    std::cout << "=== Card Database ===\n";
    for (const auto& [id, card] : registry) {
        std::cout << id << " -> " << card->getName() << "\n";
    }
}


bool CardDatabase::hasCard(const std::string& id) const {
    return registry.find(id) != registry.end();
}


} // namespace retronomicon::lib::battle
