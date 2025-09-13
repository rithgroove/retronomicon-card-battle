#pragma once

#include <vector>
#include <memory>
#include <string>
#include "retronomicon/lib/card-battle/data/card.h"
#include "retronomicon/lib/card-battle/data/deck.h"
#include "retronomicon/lib/card-battle/data/hand.h"

namespace retronomicon::lib::cardBattle::battle {
    using retronomicon::lib::cardBattle::data::Deck;
    using retronomicon::lib::cardBattle::data::Card;
    using retronomicon::lib::cardBattle::data::Hand;
    enum class PlayerId {
        Player,
        Enemy
    };

    struct PlayerState {
        PlayerId id;
        std::unique_ptr<Deck> deck;
        std::unique_ptr<Hand> hand;
        int maxHandSize;
        int energy;
        int maxEnergy;

        bool isAlive() const;
    };

    class BattleContext {

    public:
        BattleContext() = default;
        BattleContext(std::unique_ptr<Deck> playerDeck,
                      std::unique_ptr<Deck> enemyDeck,
                      int handSize);


        PlayerState& getActivePlayer();
        PlayerState& getOpponent();
        void swapActivePlayer();

        bool isBattleOver() const;
        PlayerId getWinner() const;

        bool checkWinCondition();

    private:
            PlayerState player;
            PlayerState enemy;
            PlayerId activePlayer;
            bool battleOver;
            PlayerId winner;
    };

} // namespace retronomicon::lib::cardBattle::batle
