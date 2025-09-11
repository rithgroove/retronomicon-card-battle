#include "retronomicon/lib/card-battle/data/reaction_card.h"
#include <iostream>
/**
 * @brief The namespace for card database
 */
namespace retronomicon::lib::cardBattle::data {
    
    /**
     * @brief the constructor
     * 
     * @param name card name
     * @param cost unordered_map for the cost of this card
     * @param image the ImageAsset representing card image
     * @param effectScript the TextAsset representing the script. (might change to script asset so we could run both lua or python)
     * @param damage if this card hits, how many cards are discarded from opponent hand
     */
    ReactionCard::ReactionCard(const std::string& name,
                           const std::unordered_map<std::string, int>& cost,
                           const std::shared_ptr<ImageAsset> & image,
                           const std::shared_ptr<TextAsset> & effectScript)
        : Card(name,cost, image,effectScript){}

    /**
     * @brief override method to be used when the card is played
     */
    void ReactionCard::play() {
        std::cout << "Playing ReactionCard: " << m_name << "\n";
        std::cout << "  Costs: ";
        for (const auto& [type, amount] : m_cost) {
            std::cout << amount << " " << type << " ";
        }
        std::cout << "\n";
        std::cout << "  Effect Script: " << m_effectScript->getContent() << "\n";
        // TODO: hook into Lua scripting later
    }
    /**
     * @brief override method to clone the card useful to build deck/ duplicate cards on run
     */
    std::unique_ptr<Card> ReactionCard::clone() const {
        return std::make_unique<ReactionCard>(*this);
    }

} // namespace retronomicon::lib::cardBattle::data
