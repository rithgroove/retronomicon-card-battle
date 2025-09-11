#pragma once

#include <string>
#include <memory>
#include "retronomicon/lib/asset/image_asset.h"
#include "retronomicon/lib/asset/text_asset.h"
/**
 * @brief The namespace for card database
 */
namespace retronomicon::lib::cardBattle::data {
    using retronomicon::lib::asset::ImageAsset;
    using retronomicon::lib::asset::TextAsset;

    /**
     * @brief Component responsible for managing animation clip states and playback.
     */
    class Card {
        public:

            /***************************** Constructor *****************************/

            /**
             * @brief the constructor
             * 
             * @param name card name
             * @param cost unordered_map for the cost of this card
             * @param image the ImageAsset representing card image
             * @param effectScript the TextAsset representing the script. (might change to script asset so we could run both lua or python)
             */
            Card( const std::string& name, 
                  const std::unordered_map<std::string, int>& cost,
                  std::shared_ptr<ImageAsset> std::string& image, 
                  std::shared_ptr<TextAsset>  effectScript
                )
                : m_name(name), 
                  m_image(image), 
                  m_effectScript(effectScript) {}

            /***************************** Destructor *****************************/

            /**
             * @brief the default destructor
             */
            virtual ~Card() = default;

            /***************************** Getter *****************************/

            const std::string& getName() const { return m_name; }
            const std::string& getImage() const { return m_image; }
            const std::string& getEffectScript() const { return m_effectScript; }
            const std::unordered_map<std::string, int>& getCost() const { return m_cost; }

            /***************************** Setter *****************************/

            void setName(const std::string& newName) { m_name = newName; }
            void setImage(const std::string& newImage) { m_image = newImage; }
            void setEffectScript(const std::string& effectScript) { m_effectScript = effectScript; }
            std::unordered_map<std::string, int> setCost(std::unordered_map<std::string, int>& cost) { m_cost = cost;}

            /***************************** Main Method *****************************/

            /**
             * @brief virtual method to be used when the card is played
             */
            virtual void play() = 0;

            /**
             * @brief method to clone the card useful to build deck/ duplicate cards on run
             */
            virtual std::unique_ptr<Card> clone() const = 0;

        protected:
            /***************************** attribute *****************************/
            std::string m_name;
            std::shared_ptr<ImageAsset> m_image;
            std::shared_ptr<TextAsset>  m_effectScript;
            std::unordered_map<std::string, int> m_cost;
    };

} // namespace retronomicon::lib::battle
