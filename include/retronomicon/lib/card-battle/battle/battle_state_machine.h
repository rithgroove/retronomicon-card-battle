#pragma once

#include "battle_context.h"

namespace retronomicon::lib::cardBattle::batle {

    enum class BattleState {
        StartOfBattle,
        StartOfTurn,
        PlayerAction,
        Reaction,
        EndOfTurn,
        BattleOver
    };

    class BattleStateMachine {
    private:
        BattleContext& context;
        BattleState currentState;

    public:
        explicit BattleStateMachine(BattleContext& ctx);

        void update();   // advance one step
        void setState(BattleState newState);
        BattleState getState() const { return currentState; }

    private:
        void handleStartOfBattle();
        void handleStartOfTurn();
        void handlePlayerAction();
        void handleReaction();
        void handleEndOfTurn();
    };

} // namespace retronomicon::lib::cardBattle::batle
