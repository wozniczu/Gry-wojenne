#include "Archer.h"

Archer::Archer(float x, float y, bool team)
    : Unit(x, y, team, 80.f, 10.f, 0.7f, 300.f) {
    std::string texturePath = team ? "archer_blue.png" : "archer_red.png";

    if (!unitTexture.loadFromFile(texturePath)) {
        std::cerr << "Nie mo¿na za³adowaæ tekstury piechoty!" << std::endl;
    }
    unitSprite.setTexture(unitTexture, true);
    unitSprite.setPosition({ x, y });
    unitSprite.setScale({ 1.f, 1.f });
}