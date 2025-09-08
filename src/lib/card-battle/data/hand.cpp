#include "retronomicon/lib/card-battle/data/hand.h"
#include <iostream>

namespace retronomicon::lib::cardBattle::data {


Hand::Hand(size_t maxSize)
    : maxSize(maxSize) {}

bool Hand::addCard(std::unique_ptr<Card> card) {
    if (isFull()) {
        std::cout << "Hand is full, cannot add card: " 
                  << card->getName() << "\n";
        return false;
    }
    cards.push_back(std::move(card));
    return true;
}

std::unique_ptr<Card> Hand::playCard(size_t index) {
    if (index >= cards.size()) {
        std::cout << "Invalid card index\n";
        return nullptr;
    }

    std::unique_ptr<Card> selected = std::move(cards[index]);
    cards.erase(cards.begin() + index);
    return selected;
}

std::vector<std::unique_ptr<Card>> Hand::releaseAll() {
    std::vector<std::unique_ptr<Card>> released;
    released.reserve(cards.size());

    for (auto& card : cards) {
        released.push_back(std::move(card));
    }
    cards.clear();

    return released;
}

const Card* Hand::peek(size_t index) const {
    if (index >= cards.size()) {
        return nullptr;
    }
    return cards[index].get();
}

} // namespace retronomicon::lib::battle
