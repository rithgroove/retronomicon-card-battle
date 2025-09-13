#pragma once

#include <string>
#include "deck.h"
#include "hand.h"
/**
 * @brief The namespace for card database
 */
namespace retronomicon::lib::cardBattle::data {
    /**
     * @brief A class representing the player
     */
    class Player {
        public:
            /**
             * @brief constructor for palyer
             * 
             * @param id the player id in string format
             */
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
