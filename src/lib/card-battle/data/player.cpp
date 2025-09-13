#include "retronomicon/lib/card-battle/data/player.h"
#include <iostream>
/**
 * @brief The namespace for card database
 */
namespace retronomicon::lib::cardBattle::data {
    /***************************** Constructor *****************************/

    /**
     * @brief constructor for palyer
     * 
     * @param id the player id in string format
     */
    Player::Player(const std::string& id)
        : m_id(id) {}

    /***************************** Main Method *****************************/

    /**
     * @brief a method to move card from deck to hand
     * 
     * @param number of cards to draw
     */
    void Player::drawCards(int count) {
        for (int i = 0; i < count; ++i) {
            std::unique_ptr<Card> card = m_deck.draw();
            if (card) {
                m_hand.addCard(std::move(card));
            } else {
                std::cout << m_id << " cannot draw more cards — deck is empty.\n";
                break;
            }
        }
    }

    /**
     * @brief discard all cards in hand
     */
    void Player::discardHand() {
        auto cards = m_hand.discardAll();
        for (auto& card : cards) {
            m_deck.discard(std::move(card));
        }
    }

    /**
     * @brief discard x number of cards randomly
     * 
     * @param number of cards to discards
     */
    void Player::discardRandomCard(int amount){
        auto cards = m_hand.discardRandom(amount);
        for (auto& card : cards) {
            m_deck.discard(std::move(card));
        }
    }
} // namespace retronomicon::lib::battle
