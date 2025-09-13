#pragma once


namespace retronomicon::lib::cardBattle::battle {

    class BattleContext; // forward declaration

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
        BattleContext* context;
        BattleState currentState;

    public:
        explicit BattleStateMachine(BattleContext* ctx);

        void update(float dt);   // advance one step
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
