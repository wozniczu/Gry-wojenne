#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow()
    : window(sf::VideoMode({ 1400, 800 }), "Symulacja Wojny", sf::Style::Close),
      currentState(GameState::SETUP),
      battle(nullptr),
      infantrySliderA(250, 170),
      archerSliderA(250, 270),
      cavalrySliderA(250, 370),
      infantrySliderB(1000, 170),
      archerSliderB(1000, 270),
      cavalrySliderB(1000, 370),
      startButton(600, 600, 200, 80, "START", font),
      teamATitle(font, "Niebiescy"),
      teamBTitle(font, "Czerwoni"),
      labelInfantryA(font, "Piechota:"),
      labelArcherA(font, "Łucznicy:"),
      labelCavalryA(font, "Kawaleria:"),
      labelInfantryB(font, "Piechota:"),
      labelArcherB(font, "Łucznicy:"),
      labelCavalryB(font, "Kawaleria:"),
      mouseReleased(true)
{
    if (!font.openFromFile("fonts/arial.ttf")) {
        std::cerr << "Nie można załadować czcionki!" << std::endl;
    }

    initializeUI();
}

MainWindow::~MainWindow() {
    if (battle) {
        delete battle;
    }
}

void MainWindow::initializeUI() {
    // Inicjalizacja suwaków dla drużyny A
    infantrySliderA.create(0, 50);
    infantrySliderA.setSliderValue(10);
    archerSliderA.create(0, 50);
    archerSliderA.setSliderValue(10);
    cavalrySliderA.create(0, 50);
    cavalrySliderA.setSliderValue(10);

    // Inicjalizacja suwaków dla drużyny B
    infantrySliderB.create(0, 50);
    infantrySliderB.setSliderValue(10);
    archerSliderB.create(0, 50);
    archerSliderB.setSliderValue(10);
    cavalrySliderB.create(0, 50);
    cavalrySliderB.setSliderValue(10);

    // Inicjalizacja tytułów drużyn
    teamATitle.setFont(font);
    teamATitle.setString("Niebiescy");
    teamATitle.setCharacterSize(30);
    teamATitle.setPosition({ 150, 50 });
    teamATitle.setFillColor(sf::Color::Blue);

    teamBTitle.setFont(font);
    teamBTitle.setString("Czerwoni");
    teamBTitle.setCharacterSize(30);
    teamBTitle.setPosition({ 900, 50 });
    teamBTitle.setFillColor(sf::Color::Red);

    // Inicjalizacja etykiet dla drużyny A
    labelInfantryA.setFont(font);
    labelInfantryA.setString(L"Piechota:");
    labelInfantryA.setCharacterSize(24);
    labelInfantryA.setPosition({ 100, 150 });
    labelInfantryA.setFillColor(sf::Color::Black);

    labelArcherA.setFont(font);
    labelArcherA.setString(L"Łucznicy:");
    labelArcherA.setCharacterSize(24);
    labelArcherA.setPosition({ 100, 250 });
    labelArcherA.setFillColor(sf::Color::Black);

    labelCavalryA.setFont(font);
    labelCavalryA.setString(L"Kawaleria:");
    labelCavalryA.setCharacterSize(24);
    labelCavalryA.setPosition({ 100, 350 });
    labelCavalryA.setFillColor(sf::Color::Black);

    // Inicjalizacja etykiet dla drużyny B
    labelInfantryB.setFont(font);
    labelInfantryB.setString(L"Piechota:");
    labelInfantryB.setCharacterSize(24);
    labelInfantryB.setPosition({ 850, 150 });
    labelInfantryB.setFillColor(sf::Color::Black);

    labelArcherB.setFont(font);
    labelArcherB.setString(L"Łucznicy:");
    labelArcherB.setCharacterSize(24);
    labelArcherB.setPosition({ 850, 250 });
    labelArcherB.setFillColor(sf::Color::Black);

    labelCavalryB.setFont(font);
    labelCavalryB.setString(L"Kawaleria:");
    labelCavalryB.setCharacterSize(24);
    labelCavalryB.setPosition({ 850, 350 });
    labelCavalryB.setFillColor(sf::Color::Black);
}

void MainWindow::drawSetupScreen() {
    window.clear(sf::Color::White);

    // Rysowanie tytułów drużyn
    window.draw(teamATitle);
    window.draw(teamBTitle);

    // Rysowanie etykiet
    window.draw(labelInfantryA);
    window.draw(labelArcherA);
    window.draw(labelCavalryA);
    window.draw(labelInfantryB);
    window.draw(labelArcherB);
    window.draw(labelCavalryB);

    // Rysowanie suwaków
    infantrySliderA.draw(window);
    archerSliderA.draw(window);
    cavalrySliderA.draw(window);
    infantrySliderB.draw(window);
    archerSliderB.draw(window);
    cavalrySliderB.draw(window);

    // Rysowanie przycisku startu
    startButton.draw(window);

    window.display();
}

void MainWindow::handleSetupState() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        // Obsługa przycisku startu
        if (startButton.isClicked(window) && mouseReleased) {
            mouseReleased = false;
            if (battle != nullptr) {
                delete battle;
            }

            battle = new Battle(
                static_cast<int>(infantrySliderA.getSliderValue()),
                static_cast<int>(archerSliderA.getSliderValue()),
                static_cast<int>(cavalrySliderA.getSliderValue()),
                static_cast<int>(infantrySliderB.getSliderValue()),
                static_cast<int>(archerSliderB.getSliderValue()),
                static_cast<int>(cavalrySliderB.getSliderValue())
            );

            currentState = GameState::BATTLE;
        }
        if (event->is<sf::Event::MouseButtonReleased>()) {
            mouseReleased = true;
        }
    }
    drawSetupScreen();
}

void MainWindow::handleBattleState() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }

    if (battle && !battle->isFinished()) {
        battle->update();
        battle->draw(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    else if (battle && battle->isFinished()) {
        battle->draw(window);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        currentState = GameState::SETUP;
        delete battle;
        battle = nullptr;
        mouseReleased = true;
    }

    window.display();
}

void MainWindow::run() {
    while (window.isOpen()) {
        if (currentState == GameState::SETUP) {
            handleSetupState();
        }
        else if (currentState == GameState::BATTLE) {
            handleBattleState();
        }
    }
} 