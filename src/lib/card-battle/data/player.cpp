#include "retronomicon/lib/card-battle/data/player.h"
#include <iostream>

namespace retronomicon::lib::cardBattle::data {

Player::Player(const std::string& id)
    : id(id) {}

void Player::drawCards(int count) {
    for (int i = 0; i < count; ++i) {
        std::unique_ptr<Card> card = deck.draw();
        if (card) {
            hand.addCard(std::move(card));
        } else {
            std::cout << id << " cannot draw more cards — deck is empty.\n";
            break;
        }
    }
}

void Player::discardHand() {
    auto cards = hand.releaseAll();
    for (auto& card : cards) {
        deck.discard(std::move(card));
    }
}

} // namespace retronomicon::lib::battle
