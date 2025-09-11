#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "retronomicon/lib/asset/image_asset.h"
#include "retronomicon/lib/asset/text_asset.h"
/**
 * @brief The namespace for card database
 */
namespace retronomicon::lib::cardBattle::data {
    using retronomicon::lib::asset::ImageAsset;
    using retronomicon::lib::asset::TextAsset;

    /**
     * @brief A card entity
     */
    class Card {
        public:

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
                  std::shared_ptr<ImageAsset> image, 
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

            /**
             * @brief get the name of this card
             */
            const std::string& getName() const noexcept { return m_name; }

            /**
             * @brief get the image of this card
             */
            const std::shared_ptr<ImageAsset> getImage() const noexcept { return m_image; }

            /**
             * @brief get effect script of this card
             */
            const std::shared_ptr<TextAsset> getEffectScript() const noexcept { return m_effectScript; }

            /**
             * @brief get the cost of this card
             */
            const std::unordered_map<std::string, int>& getCost() const noexcept { return m_cost; }

            /***************************** Setter *****************************/

            /**
             * @brief set the name of this card
             */
            void setName(const std::string& newName) noexcept { m_name = newName; }

            /**
             * @brief set the image of this card
             */
            void setImage(std::shared_ptr<ImageAsset> newImage) noexcept { m_image = newImage; }

            /**
             * @brief set effect script of this card
             */
            void setEffectScript(std::shared_ptr<TextAsset> effectScript) noexcept { m_effectScript = effectScript; }

            /**
             * @brief set the cost of this card
             */
            void setCost(std::unordered_map<std::string, int>& cost) noexcept { m_cost = cost;}

            /***************************** Main Method *****************************/

            /**
             * @brief virtual method to be used when the card is played
             */
            virtual void play() = 0;

            /**
             * @brief method to clone the card useful to build deck/ duplicate cards on run
             */
            virtual std::unique_ptr<Card> clone() const = 0;

            /**
             * @brief method to reset the card on the end of turn
             */
            void reset(){
                m_active = true;
            }

            /**
             * @brief method to deactivate the card effect (based on other card)
             */
            void negate(){
                m_active = false;
            }

        protected:
            /***************************** attribute *****************************/
            std::string m_name;
            std::shared_ptr<ImageAsset> m_image;
            std::shared_ptr<TextAsset>  m_effectScript;
            std::unordered_map<std::string, int> m_cost;
            bool m_active = true;
    };

} // namespace retronomicon::lib::battle
