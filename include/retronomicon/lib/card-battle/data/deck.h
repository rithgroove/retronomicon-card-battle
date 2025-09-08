#pragma once

#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include "card.h"

namespace retronomicon::lib::cardBattle::data {

class Deck {
private:
    std::vector<std::unique_ptr<Card>> cards;
    std::vector<std::unique_ptr<Card>> discardPile;
    std::mt19937 rng;

public:
    Deck();

    // Add cards into the deck
    void addCard(std::unique_ptr<Card> card);

    // Shuffle the deck
    void shuffle();

    // Draw a card (returns nullptr if empty)
    std::unique_ptr<Card> draw();

    // Discard a card (after playing)
    void discard(std::unique_ptr<Card> card);

    // Reset deck from discard pile
    void reshuffleFromDiscard();

    // Getters
    size_t size() const { return cards.size(); }
    size_t discardSize() const { return discardPile.size(); }
};

} // namespace retronomicon::lib::battle
