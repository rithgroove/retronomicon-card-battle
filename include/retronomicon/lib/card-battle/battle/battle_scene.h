#pragma once

#include "retronomicon/lib/engine/game_engine.h"
#include "retronomicon/lib/core/scene.h"
#include "retronomicon/lib/asset/asset_manager.h"
#include <unordered_map>
#include <string>

namespace retronomicon::lib::cardBattle::battle {
    using retronomicon::lib::asset::AssetManager;
    using retronomicon::lib::engine::GameEngine;
    class VNTextboxComponent;
    class BattleScene : public retronomicon::lib::core::Scene {
    public:
        BattleScene();
        void init() override;

        void setEngine(GameEngine* engine) noexcept{
            m_engine= engine;
            m_assetManager = engine->getAssetManager();
        }

    private:

        GameEngine* m_engine;
        std::shared_ptr<AssetManager> m_assetManager;
        // void setupVNTextBox();
        // void setupSystem();
        // InputMap* generateInputMap();
        // void loadBackgrounds();
        // void setupBackground();
        // void setupCharacter(std::string name);
    };
 
} // namespace retronomicon::lib::conversation
