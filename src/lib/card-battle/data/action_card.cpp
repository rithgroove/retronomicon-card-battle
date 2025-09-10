#include "retronomicon/lib/card-battle/data/action_card.h"
#include <iostream>

namespace retronomicon::lib::cardBattle::data {

ActionCard::ActionCard(const std::string& name,
                       const std::string& image,
                       const std::unordered_map<std::string, int>& cost,
                       int damage,
                       const std::string& effectScript)
    : Card(name, image,effectScript),
      cost(cost),
      damage(damage){}

void ActionCard::play() {
    std::cout << "Playing ActionCard: " << name
              << " (Damage: " << damage << ")\n";
    std::cout << "  Costs: ";
    for (const auto& [type, amount] : cost) {
        std::cout << amount << " " << type << " ";
    }
    std::cout << "\n";
    std::cout << "  Effect Script: " << m_effectScript << "\n";
    // TODO: hook into Lua scripting later
}
std::unique_ptr<Card> ActionCard::clone() const {
    return std::make_unique<ActionCard>(*this);
}
} // namespace retronomicon::lib::cardBattle::data
