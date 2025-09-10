#pragma once

#include <string>
#include <memory>
namespace retronomicon::lib::cardBattle::data {

class Card {
protected:
    std::string name;
    std::string image; // path or asset ID
    std::string m_effectScript;

public:
    Card(const std::string& name, const std::string& image, const std::string& effectScript)
        : name(name), image(image), m_effectScript(effectScript) {}

    virtual ~Card() = default;

    // No copying restrictions for now
    const std::string& getName() const { return name; }
    const std::string& getImage() const { return image; }
    const std::string& getEffectScript() const { return m_effectScript; }

    void setName(const std::string& newName) { name = newName; }
    void setImage(const std::string& newImage) { image = newImage; }
    void setEffectScript(const std::string& effectScript) { m_effectScript = effectScript; }

    // Abstract behavior: each card must implement how it plays
    virtual void play() = 0;

    // Needed for deck loading
    virtual std::unique_ptr<Card> clone() const = 0;
};

} // namespace retronomicon::lib::battle
