#include "retronomicon/lib/card-battle/data/deck.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace retronomicon::lib::cardBattle::data {
Deck::Deck() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(static_cast<unsigned long>(seed));
}

void Deck::addCard(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), rng);
}

std::unique_ptr<Card> Deck::draw() {
    if (cards.empty()) {
        reshuffleFromDiscard();
    }

    if (cards.empty()) {
        return nullptr; // still empty after reshuffle
    }

    std::unique_ptr<Card> drawn = std::move(cards.back());
    cards.pop_back();
    return drawn;
}

void Deck::discard(std::unique_ptr<Card> card) {
    discardPile.push_back(std::move(card));
}

void Deck::reshuffleFromDiscard() {
    if (discardPile.empty()) {
        return; // nothing to reshuffle
    }

    for (auto& card : discardPile) {
        cards.push_back(std::move(card));
    }
    discardPile.clear();

    shuffle();
}

bool Deck::loadFromFile(const std::string& filename, const CardDatabase& cardDb) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open deck file: " << filename << "\n";
        return false;
    }

    json data;
    file >> data;

    if (!data.contains("deck") || !data["deck"].contains("cards")) {
        std::cerr << "Invalid deck file format: " << filename << "\n";
        return false;
    }
    for (const auto& cardEntry : data["deck"]["cards"]) {
        std::string id = cardEntry["id"];
        int count = cardEntry["count"];
        if (!cardDb.hasCard(id)) {
            for (int i = 0; i < count; ++i) {
                addCard(cardDb.createCard(id)); 
            }
        }else{            
            std::cerr << "Unknown card id in deck: " << id << "\n";
            continue;
        }

    }


    shuffle();
    return true;
}


} // namespace retronomicon::lib::cardBattle::data
