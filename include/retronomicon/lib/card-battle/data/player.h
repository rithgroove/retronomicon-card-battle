#pragma once

#include <string>
#include "deck.h"
#include "hand.h"

namespace retronomicon::lib::cardBattle::data {

class Player {
    public:
        Player(const std::string& id);

        // Accessors
        const std::string& getId() const { return id; }
        Deck& getDeck() { return deck; }
        Hand& getHand() { return hand; }

        virtual int getHealth(){return m_health;}

        // Core actions
        void drawCards(int count);
        void discardHand();
        void discardRandomCard(int amount);

    private:
        std::string id;   // could be "player1", "enemyA", etc.
        Deck deck;
        Hand hand;
        int m_health;

};

} // namespace retronomicon::lib::battle
