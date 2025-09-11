#pragma once

#include "card.h"
#include <string>
#include <unordered_map>
/**
 * @brief The namespace for card database
 */
namespace retronomicon::lib::cardBattle::data {
    using retronomicon::lib::asset::ImageAsset;
    using retronomicon::lib::asset::TextAsset;

    /**
     * @brief An reaction card entity
     */
    class ReactionCard : public Card {

        public:
            /**
             * @brief the constructor
             * 
             * @param name card name
             * @param cost unordered_map for the cost of this card
             * @param image the ImageAsset representing card image
             * @param effectScript the TextAsset representing the script. (might change to script asset so we could run both lua or python)
             * @param damage if this card hits, how many cards are discarded from opponent hand
             */
            ReactionCard(const std::string& name,
                       const std::unordered_map<std::string, int>& cost,
                       const std::shared_ptr<ImageAsset> & image,
                       const std::shared_ptr<TextAsset> & effectScript);

            /***************************** Main Method *****************************/

            /**
             * @brief override method to be used when the card is played
             */
            void play() override;

            /**
             * @brief override method to clone the card useful to build deck/ duplicate cards on run
             */
            std::unique_ptr<Card> clone() const override; 

    };

} // namespace retronomicon::lib::cardBattle::data
