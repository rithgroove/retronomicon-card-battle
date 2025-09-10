#pragma once

#include "card.h"
#include <string>
#include <unordered_map>

namespace retronomicon::lib::cardBattle::data {

    class ActionCard : public Card {
    private:
        std::unordered_map<std::string, int> cost;
        int damage;

    public:
        ActionCard(const std::string& name,
                   const std::string& image,
                   const std::unordered_map<std::string, int>& cost,
                   int damage,
                   const std::string& effectScript);

        const std::unordered_map<std::string, int>& getCost() const { return cost; }
        int getDamage() const { return damage; }

        void play() override;

        std::unique_ptr<Card> clone() const override; 
    };

} // namespace retronomicon::lib::cardBattle::data
