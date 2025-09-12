#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "action_card.h"
#include "reaction_card.h"
#include "retronomicon/lib/asset/asset_manager.h"
/**
 * @brief The namespace for card database
 */
namespace retronomicon::lib::cardBattle::data {    
    using retronomicon::lib::asset::AssetManager;
    /**
     * @brief the Database of Cards we're using
     */
    class CardDatabase {
        public:
            /***************************** Constructor *****************************/

            /**
             * @brief default constructor
             */
            CardDatabase() = default;

            /***************************** Setter *****************************/

            /**
             * @brief setter for asset manager
             * 
             * @param assetManager the assetManager
             */
            void setAssetManager(std::shared_ptr<AssetManager> assetManager) {m_assetManager = assetManager;}


            /***************************** Main Methods *****************************/

            /**
             * @brief method to load from filePath
             * 
             * @param filePath (theFilePath)
             */
            bool loadFromFile(const std::string& filePath);

            /**
             * @brief Get a copy of a card (clone from prototype in map)
             * 
             * @param id the id of the card
             */
            std::unique_ptr<Card> createCard(const std::string& id) const;

            /**
             * @brief method to debug by listing all cards
             */
            void listCards() const;

            /**
             * @brief method to check if we have the card with the provided id
             * 
             * @param id the id of the card
             */
            bool hasCard(const std::string& id) const;   
        private:
            /***************************** Attribute *****************************/
            std::unordered_map<std::string, std::unique_ptr<Card>> registry;

            std::shared_ptr<AssetManager> m_assetManager = nullptr;
    };

} // namespace retronomicon::lib::battle
