#include "retronomicon/lib/card-battle/battle/battle_scene.h"
#include <iostream>

namespace retronomicon::lib::cardBattle::battle {
    BattleScene::BattleScene()
    : Scene("conversation") {}

    void BattleScene::init() {
        std::cout<<"init kepanggil" << std::endl;
            this->start();
            // this->m_childEntities.push_back(background);
        }
    }

    // InputMap* ConversationScene::generateInputMap(){
    //     std::cout << "[Splash Scene] setup input map" <<std::endl;
    //     InputMap* inputMap = new InputMap();
    //     inputMap->bindAction(SDL_SCANCODE_SPACE, "confirm");
    //     inputMap->bindAction(SDL_SCANCODE_RETURN, "confirm");
    //     inputMap->bindAction(SDL_SCANCODE_A, "left");
    //     inputMap->bindAction(SDL_SCANCODE_W, "up");
    //     inputMap->bindAction(SDL_SCANCODE_S, "down");
    //     inputMap->bindAction(SDL_SCANCODE_D, "right");
    //     inputMap->bindAction(SDL_SCANCODE_ESCAPE,"quit");
    //     return inputMap;        
    // }

    // void ConversationScene::setupSystem(){
    //     //setup input map and update inputstate to use thesep
    //     auto inputState = m_engine->getInputState();
    //     inputState->setInputMap(this->generateInputMap());

    //     // setup systems
    //     std::cout << "[Splash Scene] setup systems" <<std::endl;

    //     // setup animation system used for timer until changing to next scene
    //     // this->addSystem(std::make_unique<AnimationSystem>());
    //     this->addSystem(std::make_unique<ConversationSystem>());
    //     // setup render system used to draw to screen
    //     this->addSystem(std::make_unique<RenderSystem>(m_engine->getRenderer()));
    //     // setup scene change system to trigger scene change to the next one
    //     // this->addSystem(std::make_unique<SceneChangeSystem>(m_engine));
    //     // setup input system to skip to next scene
    //     this->addSystem(std::make_unique<InputSystem>(inputState));
    //     // this->addSystem(std::make_unique<MenuInteractionSystem>(inputState));
    //     // this->addSystem(std::make_unique<ExitGameSystem>(m_engine));
    // }

