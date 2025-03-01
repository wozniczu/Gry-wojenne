#include "Battle.h"
#include <ctime>
#include <iostream>

Battle::Battle() : rng(std::time(nullptr)) {
    const float battlefieldWidth = 800.f;
    const float battlefieldHeight = 600.f;

    // Ustawienia pozycji
    const int unitsPerRow = 10;       // Liczba jednostek w jednym rzêdzie
    const float rowSpacing = 20.f;    // Odstêpy w pionie
    const float columnSpacing = 20.f; // Odstêpy w poziomie

    // Wspó³rzêdne Y dla dru¿yn
    const float bottomSideY = 500.f;  // Dru¿yna A (dó³ ekranu)
    const float topSideY = 100.f;     // Dru¿yna B (góra ekranu)

    // Tworzenie dru¿yny A (na dole)
    for (int i = 0; i < 45; ++i) {
        float x = 100.f + (i % unitsPerRow) * columnSpacing;  // Rozmieszczenie w rzêdach
        float y = bottomSideY + (i / unitsPerRow) * rowSpacing;

        if (i < 20) {
            team.push_back(new Infantry(x, y, true)); // Pierwsze 10 - piechota
        }
        else {
            team.push_back(new Archer(x, y, true));  // Pozosta³e - kawaleria
        }
    }

    // Tworzenie dru¿yny B (na górze)
    for (int i = 0; i < 50; ++i) {
        float x = 100.f + (i % unitsPerRow) * columnSpacing; // Rozmieszczenie w rzêdach
        float y = topSideY + (i / unitsPerRow) * rowSpacing;

        if (i < 20) {
            teamB.push_back(new Infantry(x, y, false)); // Pierwsze 10 - ³ucznicy
        }
        else {
            teamB.push_back(new Archer(x, y, false)); // Pozosta³e - kawaleria
        }
    }
}

// Destruktor: Usuwanie jednostek z pamiêci
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

// Usuwa martwe jednostki z dru¿yn
void Battle::removeDeadUnits() {
    auto removeDead = [](std::vector<Unit*>& team) {
        for (auto it = team.begin(); it != team.end();) {
            if (!(*it)->isAlive()) {
                delete* it;             // Zwolnienie pamiêci
                it = team.erase(it);    // Usuniêcie wskaŸnika z wektora
            }
            else {
                ++it;
            }
        }
        };

    removeDead(team); // Usuniêcie martwych z dru¿yny A
    removeDead(teamB); // Usuniêcie martwych z dru¿yny B
}

void Battle::displayUnitsHealth(){
    std::cout << "=== Stan jednostek ===" << std::endl;

    // Wyœwietlenie HP dru¿yny A (np. niebiescy)
    std::cout << "Dru¿yna A (Niebiescy):" << std::endl;
    for (const auto& unit : team) {
        std::cout << "HP: " << unit->getHealth() << " | Pozycja: ("
            << unit->getPosition().x << ", " << unit->getPosition().y << ")"
            << (unit->isAlive() ? " [¯yje]" : " [Martwy]") << std::endl;
    }

    // Wyœwietlenie HP dru¿yny B (np. czerwoni)
    std::cout << "Dru¿yna B (Czerwoni):" << std::endl;
    for (const auto& unit : teamB) {
        std::cout << "HP: " << unit->getHealth() << " | Pozycja: ("
            << unit->getPosition().x << ", " << unit->getPosition().y << ")"
            << (unit->isAlive() ? " [¯yje]" : " [Martwy]") << std::endl;
    }

    std::cout << "======================" << std::endl;
}