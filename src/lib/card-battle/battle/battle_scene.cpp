#include <SDL.h>
#include <iostream>

#include "retronomicon/lib/card-battle/battle/battle_scene.h"
#include "retronomicon/lib/core/transform_component.h"
#include "retronomicon/lib/graphic/sprite_component.h"
#include "retronomicon/lib/ui/text_label_component.h"
#include "retronomicon/lib/input/input_system.h"
#include "retronomicon/lib/input/input_map.h"
#include "retronomicon/lib/graphic/render_system.h"
#include "retronomicon/lib/audio/audio_system.h"
#include "retronomicon/lib/audio/music_component.h"
#include "retronomicon/lib/audio/sound_effect_component.h"
#include "retronomicon/lib/engine/exit_game_system.h"
#include "retronomicon/lib/engine/exit_game_component.h"
#include "retronomicon/lib/graphic/window.h"

namespace retronomicon::lib::cardBattle::battle {
    using retronomicon::lib::core::TransformComponent;
    using retronomicon::lib::graphic::SpriteComponent;
    using retronomicon::lib::graphic::Window;
    using retronomicon::lib::input::InputMap;
    using retronomicon::lib::input::InputSystem;
    using retronomicon::lib::graphic::RenderSystem;
    using retronomicon::lib::audio::AudioSystem;
    using retronomicon::lib::audio::SoundEffectComponent;
    using retronomicon::lib::audio::MusicComponent;
    using retronomicon::lib::engine::ExitGameSystem;
    using retronomicon::lib::engine::ExitGameComponent;

    BattleScene::BattleScene()
        : Scene("battle_scene") {}

    BattleScene::BattleScene(
        GameEngine* engine,
        std::string backgroundImageFilepath,
        std::string fontAssetFilepath,
        int fontSize,
        std::string musicAssetFilepath,
        std::string soundEffectAssetFilepath)
            : Scene("battle_scene"),
              m_engine(engine),
              m_backgroundImageFilepath(backgroundImageFilepath),
              m_fontAssetFilepath(fontAssetFilepath),
              m_fontSize(fontSize),
              m_renderer(engine->getRenderer()),
              m_musicAssetFilepath(musicAssetFilepath),
              m_soundEffectAssetFilepath(soundEffectAssetFilepath),
              m_assetManager(engine->getAssetManager())
        {
            std::cout << "[BattleScene] construct battle scene with full parameters" << std::endl;
        }

    void BattleScene::init() {
        if (!m_isInitialized){
            std::cout << "[BattleScene] init()" << std::endl;

            // ---- Load assets ----
            m_backgroundImage = m_assetManager->loadImage(m_backgroundImageFilepath,"battle_background");
            m_fontAsset = m_assetManager->loadFont(m_fontAssetFilepath,"battle_font",m_fontSize);
            m_musicAsset = m_assetManager->loadMusic(m_musicAssetFilepath, "battle_music");
            m_soundEffectAsset = m_assetManager->loadSound(m_soundEffectAssetFilepath, "battle_sfx");

            // ---- Music setup ----
            auto musicComponent = this->addComponent<MusicComponent>(m_musicAsset.get(), 1000);

            // ---- Setup battle context and state machine ----
            m_battleContext = std::make_unique<BattleContext>();
            m_stateMachine = std::make_unique<BattleStateMachine>(m_battleContext.get());

            // ---- Build entities ----
            this->setupSystem();
            this->buildBackgroundImage();
            this->buildBattleUI();

            // ---- Start music ----
            musicComponent->play();
        }
        setInitialized(true);
        setActive(true);
    }

    void BattleScene::buildBackgroundImage(){
        if (m_backgroundImage){
            std::cout << "[BattleScene] setup background image" << std::endl;
            Entity* background = new Entity("battle_background");

            // -------- recalculate scaling based on window size -----
            int imageWidth = m_backgroundImage->getWidth();
            int imageHeight = m_backgroundImage->getHeight();
            int windowWidth = Window::getWidth();
            int windowHeight = Window::getHeight();

            float scaling = float(windowWidth) / float(imageWidth);
            if (float(windowHeight) / float(imageHeight) > scaling){
                scaling = float(windowHeight) / float(imageHeight);
            }

            //-------- Build Transform Component for background ---------------
            TransformComponent* backgroundTransform = background->addComponent<TransformComponent>(
                windowWidth / 2.0f,
                windowHeight / 2.0f,
                0.0f,
                scaling,
                scaling);
            backgroundTransform->setAnchor(0.5f, 0.5f);
            backgroundTransform->setRotation(0.0f);

            //-------- Build Sprite Component for background ---------------
            background->addComponent<SpriteComponent>(m_backgroundImage);

            background->start();
            this->addChildEntity(background);
        }
    }

    void BattleScene::buildBattleUI(){
        std::cout << "[BattleScene] build battle UI (placeholder)" << std::endl;

        // Example: show "Battle Start" label at top
        Entity* label = new Entity("battle_label");
        auto* transform = label->addComponent<TransformComponent>(
            Window::getWidth() / 2.0f,
            50.0f,
            0.0f,
            1.0f,
            1.0f);
        transform->setAnchor(0.5f, 0.0f);

        auto* text = label->addComponent<retronomicon::lib::ui::TextLabelComponent>(
            "Battle Start!",
            m_fontAsset,
            SDL_Color{255,255,255,255});
        // text->setAlignment("center");

        label->start();
        this->addChildEntity(label);

        // Later: build player hand zone, enemy zone, HP bars, etc.
    }

    InputMap* BattleScene::generateInputMap(){
        std::cout << "[BattleScene] setup input map" << std::endl;
        InputMap* inputMap = new InputMap();
        inputMap->bindAction(SDL_SCANCODE_SPACE, "confirm");
        inputMap->bindAction(SDL_SCANCODE_A, "left");
        inputMap->bindAction(SDL_SCANCODE_W, "up");
        inputMap->bindAction(SDL_SCANCODE_S, "down");
        inputMap->bindAction(SDL_SCANCODE_D, "right");
        inputMap->bindAction(SDL_SCANCODE_ESCAPE,"quit");
        return inputMap;        
    }

    void BattleScene::setupSystem(){
        // setup input map and update inputstate
        auto inputState = m_engine->getInputState();
        inputState->setInputMap(this->generateInputMap());

        // setup systems
        std::cout << "[BattleScene] setup systems" << std::endl;
        this->addSystem(std::make_unique<RenderSystem>(m_renderer));
        this->addSystem(std::make_unique<AudioSystem>());
        this->addSystem(std::make_unique<ExitGameSystem>(m_engine));

        // Later: add systems for card animations, battle input, etc.
    }

    void BattleScene::update(float dt){
        // Update state machine first
        if (m_stateMachine){
            m_stateMachine->update(dt);
        }

        // Update base scene (entities + systems)
        Scene::update(dt);
    }

    void BattleScene::shutdown() {
        std::cout << "[BattleScene] shutdown()" << std::endl;
        // Cleanup battle-specific resources if needed
    }

}
