#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "action_card.h"
#include "reaction_card.h"

namespace retronomicon::lib::cardBattle::data {
class CardDatabase {
private:
    std::unordered_map<std::string, std::unique_ptr<Card>> registry;

public:
    CardDatabase() = default;

    // Load cards from JSON file
    bool loadFromFile(const std::string& filePath);

    // Get card prototype (returns clone)
    std::unique_ptr<Card> createCard(const std::string& id) const;

    // Debug: list all cards
    void listCards() const;

    bool hasCard(const std::string& id) const;   
};

} // namespace retronomicon::lib::battle
