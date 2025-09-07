#include "retronomicon/lib/card-battle/data/resource_card.h"
#include <iostream>

namespace retronomicon::lib::cardBattle::data {

ResourceCard::ResourceCard(const std::string& name,
                           const std::string& image,
                           int value)
    : Card(name, image), value(value) {}

void ResourceCard::play() {
    std::cout << "Playing ResourceCard: " << name
              << " (Value: " << value << ")\n";
    // TODO: add resources to player pool
}

} // namespace retronomicon::lib::battle
