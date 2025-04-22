#include "MainWindow.h"

/**
 * @brief Konstruktor głównego okna aplikacji
 * 
 * Inicjalizuje okno aplikacji, ładuje zasoby (czcionki, tekstury),
 * tworzy i konfiguruje elementy interfejsu użytkownika (suwaki, przyciski, etykiety).
 * Ustawia początkowy stan gry na SETUP (ekran konfiguracji).
 */
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
      startButton(700, 600, 200, 80, L"START", font),
      exitButton(700, 700, 200, 80, L"WYJDŹ", font),
      teamATitle(font, "Niebiescy"),
      teamBTitle(font, "Czerwoni"),
      labelInfantryA(font, "Piechota:"),
      labelArcherA(font, "Łucznicy:"),
      labelCavalryA(font, "Kawaleria:"),
      labelInfantryB(font, "Piechota:"),
      labelArcherB(font, "Łucznicy:"),
      labelCavalryB(font, "Kawaleria:"),
      mouseReleased(true),
      menuSprite(menuTexture)
{
    if (!font.openFromFile("fonts/arial.ttf")) {
        std::cerr << "Nie można załadować czcionki!" << std::endl;
    }
    if (!menuTexture.loadFromFile("textures/menu.png")) {
        std::cerr << "Nie można załadować tekstury menu!" << std::endl;
    }
    menuSprite.setTexture(menuTexture, true);
    menuSprite.setScale({
        1400.f / menuTexture.getSize().x,
        800.f / menuTexture.getSize().y
        });
    initializeUI();
}
   
/**
 * @brief Destruktor głównego okna aplikacji
 * 
 * Zwalnia pamięć zajmowaną przez obiekt bitwy (jeśli istnieje)
 */
MainWindow::~MainWindow() {
    if (battle) {
        delete battle;
    }
}

/**
 * @brief Inicjalizuje interfejs użytkownika
 * 
 * Konfiguruje wszystkie elementy UI:
 * - Ustawia zakresy i wartości początkowe suwaków
 * - Konfiguruje wygląd i pozycje etykiet
 * - Ustawia kolory i style tekstów
 */
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
    teamATitle.setPosition({ 200, 50 });
    teamATitle.setFillColor(sf::Color::Blue);
    teamATitle.setOutlineColor(sf::Color::Black);
    teamATitle.setOutlineThickness(1);

    teamBTitle.setFont(font);
    teamBTitle.setString("Czerwoni");
    teamBTitle.setCharacterSize(30);
    teamBTitle.setPosition({ 950, 50 });
    teamBTitle.setFillColor(sf::Color::Red);
    teamBTitle.setOutlineColor(sf::Color::Black);
    teamBTitle.setOutlineThickness(1);

    // Inicjalizacja etykiet dla drużyny A
    labelInfantryA.setFont(font);
    labelInfantryA.setString(L"Piechota:");
    labelInfantryA.setCharacterSize(24);
    labelInfantryA.setPosition({ 100, 150 });
    labelInfantryA.setFillColor(sf::Color::White);
    labelInfantryA.setOutlineColor(sf::Color::Black);
    labelInfantryA.setOutlineThickness(1);

    labelArcherA.setFont(font);
    labelArcherA.setString(L"Łucznicy:");
    labelArcherA.setCharacterSize(24);
    labelArcherA.setPosition({ 100, 250 });
    labelArcherA.setFillColor(sf::Color::White);
    labelArcherA.setOutlineColor(sf::Color::Black);
    labelArcherA.setOutlineThickness(1);

    labelCavalryA.setFont(font);
    labelCavalryA.setString(L"Kawaleria:");
    labelCavalryA.setCharacterSize(24);
    labelCavalryA.setPosition({ 100, 350 });
    labelCavalryA.setFillColor(sf::Color::White);
    labelCavalryA.setOutlineColor(sf::Color::Black);
    labelCavalryA.setOutlineThickness(1);

    // Inicjalizacja etykiet dla drużyny B
    labelInfantryB.setFont(font);
    labelInfantryB.setString(L"Piechota:");
    labelInfantryB.setCharacterSize(24);
    labelInfantryB.setPosition({ 850, 150 });
    labelInfantryB.setFillColor(sf::Color::White);
    labelInfantryB.setOutlineColor(sf::Color::Black);
    labelInfantryB.setOutlineThickness(1);

    labelArcherB.setFont(font);
    labelArcherB.setString(L"Łucznicy:");
    labelArcherB.setCharacterSize(24);
    labelArcherB.setPosition({ 850, 250 });
    labelArcherB.setFillColor(sf::Color::White);
    labelArcherB.setOutlineColor(sf::Color::Black);
    labelArcherB.setOutlineThickness(1);

    labelCavalryB.setFont(font);
    labelCavalryB.setString(L"Kawaleria:");
    labelCavalryB.setCharacterSize(24);
    labelCavalryB.setPosition({ 850, 350 });
    labelCavalryB.setFillColor(sf::Color::White);
    labelCavalryB.setOutlineColor(sf::Color::Black);
    labelCavalryB.setOutlineThickness(1);
}

/**
 * @brief Rysuje ekran konfiguracji jednostek
 * 
 * Metoda odpowiedzialna za renderowanie:
 * - Tła menu
 * - Tytułów drużyn
 * - Etykiet jednostek
 * - Suwaków wyboru liczby jednostek
 * - Przycisków startu i wyjścia
 */
void MainWindow::drawSetupScreen() {
    window.clear(sf::Color::White);
    window.draw(menuSprite);
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

    // Rysowanie przycisków
    startButton.draw(window);
    exitButton.draw(window);
    
    window.display();
}

/**
 * @brief Obsługuje stan konfiguracji jednostek
 * 
 * Metoda odpowiedzialna za:
 * - Obsługę zdarzeń okna
 * - Reakcję na kliknięcia przycisków
 * - Tworzenie nowej bitwy na podstawie ustawień suwaków
 * - Przełączenie stanu gry na BATTLE po kliknięciu startu
 */
void MainWindow::handleSetupState() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        // Obsługa przycisku wyjścia
        if (exitButton.isClicked(window)) {
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

/**
 * @brief Obsługuje stan trwającej bitwy
 * 
 * Metoda odpowiedzialna za:
 * - Obsługę zdarzeń okna
 * - Aktualizację i rysowanie bitwy
 * - Sprawdzenie warunków zakończenia bitwy
 * - Powrót do stanu SETUP po zakończeniu bitwy
 */
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

/**
 * @brief Uruchamia główną pętlę aplikacji
 * 
 * Metoda odpowiedzialna za:
 * - Główną pętlę gry
 * - Wybór odpowiedniej metody obsługi w zależności od stanu gry
 * - Zarządzanie przejściami między stanami SETUP i BATTLE
 */
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
