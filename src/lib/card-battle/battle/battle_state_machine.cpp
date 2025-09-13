#include "retronomicon/lib/card-battle/battle/battle_state_machine.h"
#include "retronomicon/lib/card-battle/battle/battle_context.h" 
#include <iostream>

namespace retronomicon::lib::cardBattle::battle {

    BattleStateMachine::BattleStateMachine(BattleContext* ctx)
        : context(ctx), currentState(BattleState::StartOfBattle) {}

    void BattleStateMachine::update(float dt) {
        if (context->isBattleOver()) {
            currentState = BattleState::BattleOver;
        }

        switch (currentState) {
            case BattleState::StartOfBattle:
                handleStartOfBattle();
                break;
            case BattleState::StartOfTurn:
                handleStartOfTurn();
                break;
            case BattleState::PlayerAction:
                handlePlayerAction();
                break;
            case BattleState::Reaction:
                handleReaction();
                break;
            case BattleState::EndOfTurn:
                handleEndOfTurn();
                break;
            case BattleState::BattleOver:
                std::cout << "Battle Over! Winner: "
                          << (context->getWinner() == PlayerId::Player ? "Player" : "Enemy")
                          << std::endl;
                break;
        }
    }

    void BattleStateMachine::setState(BattleState newState) {
        currentState = newState;
    }

    // ------------------- Handlers -------------------

    void BattleStateMachine::handleStartOfBattle() {
        // TODO: trigger any "start of battle" effects here
        std::cout << "Battle started!" << std::endl;

        setState(BattleState::StartOfTurn);
    }

    void BattleStateMachine::handleStartOfTurn() {
        auto& active = context->getActivePlayer();

        // Refill energy
        active.energy = active.maxEnergy;

        std::cout << "Start of turn: "
                  << (active.id == PlayerId::Player ? "Player" : "Enemy")
                  << std::endl;

        // TODO: trigger "start of turn" effects here

        setState(BattleState::PlayerAction);
    }

    void BattleStateMachine::handlePlayerAction() {
        auto& active = context->getActivePlayer();

        std::cout << "Waiting for action from "
                  << (active.id == PlayerId::Player ? "Player" : "Enemy")
                  << std::endl;

        // For now, just auto-skip action
        setState(BattleState::EndOfTurn);
    }

    void BattleStateMachine::handleReaction() {
        // TODO: Implement reaction logic
        std::cout << "Checking for reactions..." << std::endl;

        setState(BattleState::EndOfTurn);
    }

    void BattleStateMachine::handleEndOfTurn() {
        auto& active = context->getActivePlayer();

        // Draw until max hand size
        while (active.hand->size() < active.maxHandSize && !active.deck->isEmpty()) {
            active.hand->addCard(active.deck->draw());
        }

        // Check win conditions
        if (context->checkWinCondition()) {
            currentState = BattleState::BattleOver;
            return;
        }

        // Swap to opponent
        context->swapActivePlayer();

        setState(BattleState::StartOfTurn);
    }

} // namespace retronomicon::lib::cardBattle::batle
