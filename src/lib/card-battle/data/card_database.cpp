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
            int cost = cardJson["cost"];
            int damage = cardJson["damage"];
            registry[id] = std::make_unique<ActionCard>(name, image, cost, damage);
            // TODO: store effectScript link somewhere (later: Lua integration)
        }
        else if (type == "resource") {
            int value = cardJson["value"];
            registry[id] = std::make_unique<ResourceCard>(name, image, value);
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

    // Right now, naive clone (reconstruct from data).
    // TODO: Proper deep copy / prototype pattern.
    const Card* proto = it->second.get();

    // Try dynamic_cast to check type
    if (auto ac = dynamic_cast<const ActionCard*>(proto)) {
        return std::make_unique<ActionCard>(ac->getName(), ac->getImage(), ac->getCost(), ac->getDamage());
    }
    else if (auto rc = dynamic_cast<const ResourceCard*>(proto)) {
        return std::make_unique<ResourceCard>(rc->getName(), rc->getImage(), rc->getValue());
    }

    return nullptr;
}

void CardDatabase::listCards() const {
    std::cout << "=== Card Database ===\n";
    for (const auto& [id, card] : registry) {
        std::cout << id << " -> " << card->getName() << "\n";
    }
}

} // namespace retronomicon::lib::battle
