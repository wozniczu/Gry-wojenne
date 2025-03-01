#include "Battle.h"
#include <ctime>
#include <iostream>

Battle::Battle() : rng(std::time(nullptr)) {
    const float battlefieldWidth = 800.f;
    const float battlefieldHeight = 600.f;

    const int unitsPerRow = 10;
    const float rowSpacing = 20.f;
    const float columnSpacing = 20.f;

    const float bottomSideY = 500.f;
    const float topSideY = 100.f;

    for (int i = 0; i < 45; ++i) {
        float x = 100.f + (i % unitsPerRow) * columnSpacing;
        float y = bottomSideY + (i / unitsPerRow) * rowSpacing;

        if (i < 20) {
            team.push_back(new Infantry(x, y, true));
        }
        else {
            team.push_back(new Archer(x, y, true));
        }
    }

    for (int i = 0; i < 50; ++i) {
        float x = 100.f + (i % unitsPerRow) * columnSpacing;
        float y = topSideY + (i / unitsPerRow) * rowSpacing;

        if (i < 20) {
            teamB.push_back(new Infantry(x, y, false));
        }
        else {
            teamB.push_back(new Archer(x, y, false));
        }
    }
}

Battle::~Battle() {
    for (auto unit : team) delete unit;
    for (auto unit : teamB) delete unit;
}

void Battle::update() {
    for (auto& unit : team) unit->update(teamB);
    for (auto& unit : teamB) unit->update(team);
    removeDeadUnits();
}

void Battle::draw(sf::RenderWindow& window) {
    for (const auto& unit : team) window.draw(unit->getShape());
    for (const auto& unit : teamB) window.draw(unit->getShape());
}

bool Battle::isFinished() {
    return team.empty() || teamB.empty();
}

void Battle::removeDeadUnits() {
    auto removeDead = [](std::vector<Unit*>& team) {
        for (auto it = team.begin(); it != team.end();) {
            if (!(*it)->isAlive()) {
                delete* it;
                it = team.erase(it);
            }
            else {
                ++it;
            }
        }
        };

    removeDead(team);
    removeDead(teamB);
}

void Battle::displayUnitsHealth(){
    std::cout << "=== Stan jednostek ===" << std::endl;

    std::cout << "Dru¿yna A (Niebiescy):" << std::endl;
    for (const auto& unit : team) {
        std::cout << "HP: " << unit->getHealth() << " | Pozycja: ("
            << unit->getPosition().x << ", " << unit->getPosition().y << ")"
            << (unit->isAlive() ? " [¯yje]" : " [Martwy]") << std::endl;
    }

    std::cout << "Dru¿yna B (Czerwoni):" << std::endl;
    for (const auto& unit : teamB) {
        std::cout << "HP: " << unit->getHealth() << " | Pozycja: ("
            << unit->getPosition().x << ", " << unit->getPosition().y << ")"
            << (unit->isAlive() ? " [¯yje]" : " [Martwy]") << std::endl;
    }

    std::cout << "======================" << std::endl;
}