#include "Cavalry.h"

Cavalry::Cavalry(float x, float y, bool team)
    : Unit(x, y, team, 100.f, 25.f, 2.0f, 1.2f) {
    std::string texturePath = team ? "cavalry_blue.png" : "cavalry_red.png";

    if (!unitTexture.loadFromFile(texturePath)) {
        std::cerr << "Nie mo¿na za³adowaæ tekstury piechoty!" << std::endl;
    }
    unitSprite.setTexture(unitTexture, true);
    unitSprite.setPosition({ x, y });
    unitSprite.setScale({ 0.03f, 0.03f });
}