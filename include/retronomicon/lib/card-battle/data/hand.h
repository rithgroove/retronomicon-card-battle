#pragma once

#include <vector>
#include <memory>
#include "card.h"

namespace retronomicon::lib::cardBattle::data {


class Hand {
private:
    std::vector<std::unique_ptr<Card>> cards;
    size_t maxSize;

public:
    explicit Hand(size_t maxSize = 5);

    // Add a card (if hand is full, return false)
    bool addCard(std::unique_ptr<Card> card);

    // Play a card by index (removes from hand and returns it)
    std::unique_ptr<Card> playCard(size_t index);

    // Discard all cards (return ownership)
    std::vector<std::unique_ptr<Card>> releaseAll();

    // Accessors
    size_t size() const { return cards.size(); }
    size_t getMaxSize() const { return maxSize; }
    bool isFull() const { return cards.size() >= maxSize; }

    const Card* peek(size_t index) const; // read-only card access
};

} // namespace retronomicon::lib::battle
