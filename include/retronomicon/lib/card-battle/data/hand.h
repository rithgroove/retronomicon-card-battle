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

    // Discard a card by index (returns false if invalid index)
    bool discardCard(size_t index);

    // Discard all cards (return ownership of them)
    std::vector<std::unique_ptr<Card>> releaseAll();

    // Discard random cards (return ownership of them)
    std::vector<std::unique_ptr<Card>> releaseRandom(int amount);

    // -------------------------
    // Inline utility functions
    // -------------------------

    // How many cards are in hand
    inline size_t size() const noexcept { return cards.size(); }

    // Maximum allowed cards
    inline size_t getMaxSize() const noexcept { return maxSize; }

    // Is hand full?
    inline bool isFull() const noexcept { return cards.size() >= maxSize; }

    // Is hand empty?
    inline bool isEmpty() const noexcept { return cards.empty(); }

    // Read-only card access
    const Card* peek(size_t index) const;
};

} // namespace retronomicon::lib::cardBattle::data
