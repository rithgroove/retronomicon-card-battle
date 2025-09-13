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
            /***************************** Constructor *****************************/

            /**
             * @brief constructor for palyer
             * 
             * @param id the player id in string format
             */
            Player(const std::string& id);

            /***************************** Getter *****************************/

            /**
             * @brief a method to get player id
             * 
             * @return the id
             */
            const std::string& getId() const { return m_id; }

            /**
             * @brief a method to get the deck
             * 
             * @return the deck
             */
            Deck& getDeck() { return m_deck; }

            /**
             * @brief a method to get the hand
             * 
             * @return the hand
             */
            Hand& getHand() { return m_hand; }

            /**
             * @brief a method to get the player health
             * 
             * @return the player health
             */
            virtual int getHealth(){return m_health;}

            /***************************** Main Method *****************************/

            /**
             * @brief a method to move card from deck to hand
             * 
             * @param number of cards to draw
             */
            void drawCards(int count);

            /**
             * @brief discard all cards in hand
             */
            void discardHand();

            /**
             * @brief discard x number of cards randomly
             * 
             * @param number of cards to discards
             */
            void discardRandomCard(int amount);

        private:
            /***************************** Attribute *****************************/
            std::string m_id;   // could be "player1", "enemyA", etc.
            Deck m_deck;
            Hand m_hand;
            int m_health;

    };

} // namespace retronomicon::lib::battle
