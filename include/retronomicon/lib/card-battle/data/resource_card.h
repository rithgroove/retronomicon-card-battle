#pragma once

#include "card.h"
#include <string>
#include <unordered_map>

namespace retronomicon::lib::cardBattle::data {

class ResourceCard : public Card {
private:
    std::unordered_map<std::string, int> value; // how much resource this card gives when used

public:
    ResourceCard(const std::string& name,
                 const std::string& image,
                 const std::unordered_map<std::string, int>& value,
                 const std::string& effectScript);

    const std::unordered_map<std::string, int>& getValue() const { return value; }

    void play() override;
};

} // namespace retronomicon::lib::cardBattle::data
