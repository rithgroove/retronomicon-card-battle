#include "retronomicon/lib/card-battle/data/resource_card.h"
#include <iostream>

namespace retronomicon::lib::cardBattle::data {

  ResourceCard::ResourceCard(const std::string& name,
                             const std::string& image,
                             const std::unordered_map<std::string, int>& value,
                             const std::string& effectScript)
      : Card(name, image,effectScript),
        value(value){}

  void ResourceCard::play() {
      std::cout << "Playing ResourceCard: " << name << "\n";
      std::cout << "  Provides: ";
      for (const auto& [type, amount] : value) {
          std::cout << amount << " " << type << " ";
      }
      std::cout << "\n";
      std::cout << "  Effect Script: " << m_effectScript << "\n";
      // TODO: hook into Lua scripting later
  }
} // namespace retronomicon::lib::battle
