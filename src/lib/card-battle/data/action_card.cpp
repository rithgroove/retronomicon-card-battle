#include "retronomicon/lib/card-battle/data/action_card.h"
#include <iostream>

namespace retronomicon::lib::cardBattle::data {

ActionCard::ActionCard(const std::string& name,
                       const std::string& image,
                       int cost,
                       int damage)
    : Card(name, image), cost(cost), damage(damage) {}

void ActionCard::play() {
    std::cout << "Playing ActionCard: " << name
              << " (Cost: " << cost
              << ", Damage: " << damage << ")\n";
    // TODO: apply damage, consume resources
}

} // namespace retronomicon::lib::battle
