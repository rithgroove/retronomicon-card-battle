#pragma once

#include "card.h"
#include <string>

namespace retronomicon::lib::cardBattle::data {

class ActionCard : public Card {
private:
    int cost;
    int damage;

public:
    ActionCard(const std::string& name,
               const std::string& image,
               int cost,
               int damage);

    int getCost() const { return cost; }
    int getDamage() const { return damage; }

    void play() override;
};

} // namespace retronomicon::lib::battle
