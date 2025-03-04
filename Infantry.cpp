#include "Infantry.h"

Infantry::Infantry(float x, float y, bool team)
    : Unit(x, y, team, 120.f, 15.f, 0.5f, 1.f) {
    std::string texturePath = team ? "infantry_blue.png" : "infantry_red.png";

    if (!unitTexture.loadFromFile(texturePath)) {
        std::cerr << "Nie mo¿na za³adowaæ tekstury piechoty!" << std::endl;
    }
    unitSprite.setTexture(unitTexture, true);
    unitSprite.setPosition({ x, y });
    unitSprite.setScale({ 0.15f, 0.15f });
}

