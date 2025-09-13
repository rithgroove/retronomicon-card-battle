#include "retronomicon/lib/card-battle/battle/battle_context.h"

namespace retronomicon::lib::cardBattle::batle {

    bool PlayerState::isAlive() const {
        return !deck->isEmpty() || !hand->isEmpty();
    }

    BattleContext::BattleContext(std::unique_ptr<data::Deck> playerDeck,
                                 std::unique_ptr<data::Deck> enemyDeck,
                                 int handSize)
        : activePlayer(PlayerId::Player),
          battleOver(false),
          winner(PlayerId::Player) // default, updated later
    {
        player = {
            PlayerId::Player,
            std::move(playerDeck),
            std::make_unique<data::Hand>(),
            handSize,
            0,
            3 // default max energy
        };

        enemy = {
            PlayerId::Enemy,
            std::move(enemyDeck),
            std::make_unique<data::Hand>(),
            handSize,
            0,
            3
        };

        // Draw starting hands
        for (int i = 0; i < handSize; i++) {
            if (!player.deck->isEmpty()) player.hand->addCard(player.deck->draw());
            if (!enemy.deck->isEmpty()) enemy.hand->addCard(enemy.deck->draw());
        }
    }

    PlayerState& BattleContext::getActivePlayer() {
        return (activePlayer == PlayerId::Player) ? player : enemy;
    }

    PlayerState& BattleContext::getOpponent() {
        return (activePlayer == PlayerId::Player) ? enemy : player;
    }

    void BattleContext::swapActivePlayer() {
        activePlayer = (activePlayer == PlayerId::Player) ? PlayerId::Enemy : PlayerId::Player;
    }

    bool BattleContext::isBattleOver() const {
        return battleOver;
    }

    PlayerId BattleContext::getWinner() const {
        return winner;
    }

    bool BattleContext::checkWinCondition() {
        if (!player.isAlive()) {
            battleOver = true;
            winner = PlayerId::Enemy;
            return true;
        }
        if (!enemy.isAlive()) {
            battleOver = true;
            winner = PlayerId::Player;
            return true;
        }
        return false;
    }

} // namespace retronomicon::lib::cardBattle::batle
