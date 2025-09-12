#include "retronomicon/lib/card-battle/data/card_database.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp> // JSON lib (https://github.com/nlohmann/json)
#include "retronomicon/lib/asset/image_asset.h"
#include "retronomicon/lib/asset/text_asset.h"

using json = nlohmann::json;
/**
 * @brief The namespace for card database
 */
namespace retronomicon::lib::cardBattle::data {
    using retronomicon::lib::asset::ImageAsset;
    using retronomicon::lib::asset::TextAsset;
    /**
     * @brief method to load from filePath
     * 
     * @param filePath (theFilePath)
     */
    bool CardDatabase::loadFromFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Failed to open card JSON: " << filePath << "\n";
            return false;
        }
        if (!m_assetManager){
            std::cerr << "[Card Database] asset manager not set \n";
            return false;            
        }

        json data;
        file >> data;

        for (const auto& cardJson : data["cards"]) {
            std::string id = cardJson["id"];
            std::string type = cardJson["type"];
            std::string name = cardJson["name"];
            std::string image = cardJson["image"];
            std::string effectScript = cardJson.value("effectScript", "");
            std::shared_ptr<ImageAsset> imageAsset = m_assetManager->loadImage(image,image);
            std::shared_ptr<TextAsset> effectScriptAsset = m_assetManager->loadText(effectScript,effectScript);

            std::cout << "[Card - "<< cardJson["type"]<< "] " ;
            std::cout << cardJson["name"] << "\n" ; 
            std::cout << "- " << cardJson["image"] << "\n" ;   
            std::cout << "- " << cardJson["effectScript"] << "\n" ;
            std::cout << std::endl;   

            std::unordered_map<std::string, int> cost;
            for (auto it = cardJson["cost"].begin(); it != cardJson["cost"].end(); ++it) {
                cost[it.key()] = it.value().get<int>();
            }

            if (type == "action") {
                
                int damage = cardJson["damage"];
                registry[id] = std::make_unique<ActionCard>(name,cost, imageAsset, effectScriptAsset, damage);
                // TODO: store effectScript link somewhere (later: Lua integration)
            }
            else if (type == "reaction") {
                registry[id] = std::make_unique<ReactionCard>(name,cost, imageAsset, effectScriptAsset);
                // TODO: store effectScript link
            }
            else {
                std::cerr << "Unknown card type: " << type << "\n";
            }
        }

        return true;
    }

    std::unique_ptr<Card> CardDatabase::createCard(const std::string& id) const {
        auto it = registry.find(id);
        if (it == registry.end()) {
            std::cerr << "Card not found: " << id << "\n";
            return nullptr;
        }

        return it->second->clone(); 
    }

    void CardDatabase::listCards() const {
        std::cout << "=== Card Database ===\n";
        for (const auto& [id, card] : registry) {
            std::cout << id << " -> " << card->getName() << "\n";
        }
    }


    bool CardDatabase::hasCard(const std::string& id) const {
        return registry.find(id) != registry.end();
    }


} // namespace retronomicon::lib::battle
