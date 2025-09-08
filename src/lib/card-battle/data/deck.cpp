#include "retronomicon/lib/card-battle/data/deck.h"
#include <chrono>
#include <iostream>


namespace retronomicon::lib::cardBattle::data {

Deck::Deck() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(static_cast<unsigned long>(seed));
}

void Deck::addCard(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), rng);
}

std::unique_ptr<Card> Deck::draw() {
    if (cards.empty()) {
        reshuffleFromDiscard();
    }

    if (cards.empty()) {
        return nullptr; // still empty after reshuffle
    }

    std::unique_ptr<Card> drawn = std::move(cards.back());
    cards.pop_back();
    return drawn;
}

void Deck::discard(std::unique_ptr<Card> card) {
    discardPile.push_back(std::move(card));
}

void Deck::reshuffleFromDiscard() {
    if (discardPile.empty()) {
        return; // nothing to reshuffle
    }

    for (auto& card : discardPile) {
        cards.push_back(std::move(card));
    }
    discardPile.clear();

    shuffle();
}

} // namespace retronomicon::lib::battle
