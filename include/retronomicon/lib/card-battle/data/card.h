#pragma once

#include <string>

namespace retronomicon::lib::cardBattle::data {

class Card {
protected:
    std::string name;
    std::string image; // path or asset ID

public:
    Card(const std::string& name, const std::string& image)
        : name(name), image(image) {}

    virtual ~Card() = default;

    // No copying restrictions for now
    const std::string& getName() const { return name; }
    const std::string& getImage() const { return image; }

    void setName(const std::string& newName) { name = newName; }
    void setImage(const std::string& newImage) { image = newImage; }

    // Abstract behavior: each card must implement how it plays
    virtual void play() = 0;
};

} // namespace retronomicon::lib::battle
