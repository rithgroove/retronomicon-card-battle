#pragma once

#include <vector>
#include <memory>
#include <string>
#include "retronomicon/lib/card-battle/data/card.h"
#include "retronomicon/lib/card-battle/data/deck.h"
#include "retronomicon/lib/card-battle/data/hand.h"

namespace retronomicon::lib::cardBattle::batle {

    enum class PlayerId {
        Player,
        Enemy
    };

    struct PlayerState {
        PlayerId id;
        std::unique_ptr<data::Deck> deck;
        std::unique_ptr<data::Hand> hand;
        int maxHandSize;
        int energy;
        int maxEnergy;

        bool isAlive() const;
    };

    class BattleContext {
    private:
        PlayerState player;
        PlayerState enemy;
        PlayerId activePlayer;
        bool battleOver;
        PlayerId winner;

    public:
        BattleContext(std::unique_ptr<data::Deck> playerDeck,
                      std::unique_ptr<data::Deck> enemyDeck,
                      int handSize);

        PlayerState& getActivePlayer();
        PlayerState& getOpponent();
        void swapActivePlayer();

        bool isBattleOver() const;
        PlayerId getWinner() const;

        bool checkWinCondition();
    };

} // namespace retronomicon::lib::cardBattle::batle
