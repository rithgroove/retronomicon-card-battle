#pragma once

#include <string>
#include "deck.h"
#include "hand.h"

namespace retronomicon::lib::cardBattle::data {

class Player {
private:
    std::string id;   // could be "player1", "enemyA", etc.
    Deck deck;
    Hand hand;

public:
    Player(const std::string& id);

    // Accessors
    const std::string& getId() const { return id; }
    Deck& getDeck() { return deck; }
    Hand& getHand() { return hand; }

    // Core actions
    void drawCards(int count);
    void discardHand();
    void discardRandomCard(int amount);
};

} // namespace retronomicon::lib::battle
