#pragma once

#include <vector>
#include <memory>
#include "card.h"

/**
 * @brief The namespace for card database
 */
namespace retronomicon::lib::cardBattle::data {

    /**
     * @brief A class representing player hand
     */
    class Hand {

        public:

            /***************************** Constructor *****************************/

            /**
             * @brief constructor for hand
             * 
             * @param maxSize the max hand size for this hand.
             */
            explicit Hand(size_t maxSize = 5);

            /***************************** Getter *****************************/

            /**
            * @brief How many cards are in hand
            * 
            * @return the size of the current hand
            */
            inline size_t size() const noexcept { return m_cards.size(); }

            /**
            * @brief How many cards are in hand
            * 
            * @return Maximum allowed cards
            */
            inline size_t getMaxSize() const noexcept { return m_maxSize; }

            /***************************** Setter *****************************/

            /**
             * @brief change the size of the hand
             * 
             * @param newSize
             */
            void setHandSize(int newSize) {m_maxSize = newSize;}

            /***************************** Main Method *****************************/

            /**
             * @brief reduce the size of the hand
             * 
             * @param modifier how many card to reduce
             */
            void reduceHandSize(int modifier) {m_maxSize -= modifier;}

            /**
             * @brief expand the size of the hand
             * 
             * @param modifier how many card to expand
             */
            void expandHandSize(int modifier) {m_maxSize += modifier;}

            /**
             * @brief Add a card (if hand is full, return false)
             * 
             * @param unique pointer to the card
             * 
             * @return boolean if the addition is success or not
             */
            bool addCard(std::unique_ptr<Card> card);

            /**
             * @brief Play a card by index (removes from hand and returns it)
             * 
             * @param index of the card
             * 
             * @return unique pointer to the card
             */
            std::unique_ptr<Card> playCard(size_t index);

            /**
             * @brief Discard a card by index (returns false if invalid index)
             * 
             * @param index of the card
             * 
             * @return true if success
             */            
            bool discardCard(size_t index);

            /**
             * @brief Discard all cards (return ownership of them)
             * 
             * @return vector of the cards
             */            
            std::vector<std::unique_ptr<Card>> discardAll();

            /**
             * @brief Discard random cards (return ownership of them)
             * 
             * @param the number of cards to be discarded
             * 
             * @return vector of the cards
             */            
            std::vector<std::unique_ptr<Card>> discardRandom(int amount);

            /**
             * @brief Is hand full?
             * 
             * @return true if full
             */  
            inline bool isFull() const noexcept { return m_cards.size() >= m_maxSize; }

            /**
             * @brief Is hand empty?
             * 
             * @return true if empty
             */  
            inline bool isEmpty() const noexcept { return m_cards.empty(); }

            /**
             * @brief peek
             * 
             * @param index of the card to peek
             * 
             * @return pointer to a card to peek.
             */  
            const Card* peek(size_t index) const;

        private:
            /***************************** Attribute *****************************/
            std::vector<std::unique_ptr<Card>> m_cards;
            size_t m_maxSize;


    };

} // namespace retronomicon::lib::cardBattle::data
