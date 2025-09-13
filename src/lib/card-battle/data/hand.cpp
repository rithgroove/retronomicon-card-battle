#include "retronomicon/lib/card-battle/data/hand.h"
#include <iostream>
#include <numeric>     // for std::iota
#include <algorithm>   // for std::shuffle, std::sort
#include <random>      // for std::random_device, std::mt19937
/**
 * @brief The namespace for card database
 */
namespace retronomicon::lib::cardBattle::data {

    /***************************** Constructor *****************************/
    /**
     * @brief constructor for hand
     * 
     * @param maxSize the max hand size for this hand.
     */
    Hand::Hand(size_t maxSize)
        : m_maxSize(maxSize) {}

    /***************************** Main Method *****************************/

    /**
     * @brief Add a card (if hand is full, return false)
     * 
     * @param unique pointer to the card
     * 
     * @return boolean if the addition is success or not
     */
    bool Hand::addCard(std::unique_ptr<Card> card) {
        if (isFull()) {
            std::cout << "Hand is full, cannot add card: " 
                      << card->getName() << "\n";
            return false;
        }
        m_cards.push_back(std::move(card));
        return true;
    }

    /**
     * @brief Add a card (if hand is full, return false)
     * 
     * @param unique pointer to the card
     * 
     * @return boolean if the addition is success or not
     */
    std::unique_ptr<Card> Hand::playCard(size_t index) {
        if (index >= m_cards.size()) {
            std::cout << "Invalid card index\n";
            return nullptr;
        }

        std::unique_ptr<Card> selected = std::move(m_cards[index]);
        m_cards.erase(m_cards.begin() + index);
        return selected;
    }

    /**
     * @brief Play a card by index (removes from hand and returns it)
     * 
     * @param index of the card
     * 
     * @return unique pointer to the card
     */
    bool Hand::discardCard(size_t index) {
        if (index >= m_cards.size()) {
            std::cout << "Invalid card index, cannot discard\n";
            return false;
        }

        m_cards.erase(m_cards.begin() + index);
        return true;
    }

    /**
     * @brief Discard all cards (return ownership of them)
     * 
     * @return vector of the cards
     */
    std::vector<std::unique_ptr<Card>> Hand::discardAll() {
        std::vector<std::unique_ptr<Card>> released;
        released.reserve(m_cards.size());

        for (auto& card : m_cards) {
            released.push_back(std::move(card));
        }
        m_cards.clear();

        return released;
    }

   /**
     * @brief Discard random cards (return ownership of them)
     * 
     * @param the number of cards to be discarded
     * 
     * @return vector of the cards
     */   
    std::vector<std::unique_ptr<Card>> Hand::discardRandom(int amount) {
        std::vector<std::unique_ptr<Card>> released;

        if (m_cards.empty()) {
            return released; // nothing to release
        }

        // Clamp amount so we don't overrun
        size_t toRelease = std::min(static_cast<size_t>(amount), m_cards.size());

        // Generate indices [0..cards.size()-1]
        std::vector<size_t> indices(m_cards.size());
        std::iota(indices.begin(), indices.end(), 0);

        // Shuffle indices
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(indices.begin(), indices.end(), g);

        // Sort first `toRelease` indices descending so erase works safely
        std::vector<size_t> chosen(indices.begin(), indices.begin() + toRelease);
        std::sort(chosen.rbegin(), chosen.rend());

        // Move cards out
        for (size_t idx : chosen) {
            released.push_back(std::move(m_cards[idx]));
            m_cards.erase(m_cards.begin() + idx);
        }

        return released;
    }

    /**
     * @brief peek
     * 
     * @param index of the card to peek
     * 
     * @return pointer to a card to peek.
     */  
    const Card* Hand::peek(size_t index) const {
        if (index >= m_cards.size()) {
            return nullptr;
        }
        return m_cards[index].get();
    }

} // namespace retronomicon::lib::battle
