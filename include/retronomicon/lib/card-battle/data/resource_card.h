#pragma once

#include "card.h"
#include <string>

namespace retronomicon::lib::cardBattle::data {

class ResourceCard : public Card {
private:
    int value; // how much resource this card gives when used

public:
    ResourceCard(const std::string& name,
                 const std::string& image,
                 int value);

    int getValue() const { return value; }

    void play() override;
};

} // namespace retronomicon::lib::battle
