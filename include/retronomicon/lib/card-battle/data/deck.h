#pragma once

#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <string>
#include "card.h"
#include "card_database.h"

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

    // Load deck from a JSON file (requires card database)
    bool loadFromFile(const std::string& filename, const CardDatabase& cardDb);

    // -------------------------
    // Inline utility functions
    // -------------------------

    // Is the deck empty?
    inline bool isEmpty() const noexcept { return cards.empty(); }

    // Is the discard pile empty?
    inline bool isDiscardEmpty() const noexcept { return discardPile.empty(); }

    // How many cards in total (deck + discard)?
    inline size_t totalSize() const noexcept { return cards.size() + discardPile.size(); }

    // Just the deck size
    inline size_t size() const noexcept { return cards.size(); }

    // Just the discard pile size
    inline size_t discardSize() const noexcept { return discardPile.size(); }
};

} // namespace retronomicon::lib::cardBattle::data
