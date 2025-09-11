#pragma once

#include "card.h"
#include <string>
#include <unordered_map>

namespace retronomicon::lib::cardBattle::data {

class ReactionCard : public Card {
    private:
        std::unordered_map<std::string, int> value; // how much resource this card gives when used

    public:
        ReactionCard(const std::string& name,
                     const std::string& image,
                     const std::unordered_map<std::string, int>& value,
                     const std::string& effectScript);

        const std::unordered_map<std::string, int>& getValue() const { return value; }

        void play() override;
        std::unique_ptr<Card> clone() const override;
    };

} // namespace retronomicon::lib::cardBattle::data
