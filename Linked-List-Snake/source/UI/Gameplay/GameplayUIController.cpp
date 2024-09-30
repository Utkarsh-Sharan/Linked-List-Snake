#include "UI/Gameplay/GameplayUIController.h"
#include "Level/LevelNumber.h"
#include "Global/ServiceLocator.h"

namespace UI
{
	namespace GameplayUI
	{
        using namespace UI::UIElement;
        using namespace Level;
        using namespace Global;

        GameplayUIController::GameplayUIController()
        {
            createTexts();
        }

        GameplayUIController::~GameplayUIController()
        {
            destroy();
        }

        void GameplayUIController::initialize()
        {
            initializeTexts();
        }

        void GameplayUIController::createTexts()
        {
            level_number_text = new TextView();
            score_text = new TextView();
            time_complexity_text = new TextView();
            operation_text = new TextView();
        }

        void GameplayUIController::initializeTexts()
        {
            initializeLevelNumberText();
            initializeScoreText();
        }

        void GameplayUIController::initializeLevelNumberText()
        {
            level_number_text->initialize("Level : 1", sf::Vector2f(level_number_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size, sf::Color::Black);
        }

        void GameplayUIController::initializeScoreText()
        {
            score_text->initialize("Score : 0", sf::Vector2f(score_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size, sf::Color::Black);
        }

        void GameplayUIController::update()
        {
            updateLevelNumberText();
            updateScoreText();
        }

        void GameplayUIController::updateLevelNumberText()
        {
            LevelNumber level_number = ServiceLocator::getInstance()->getLevelService()->getCurrentLevel();
            sf::String level_number_value = std::to_string(1 + static_cast<int>(level_number));

            level_number_text->setText("Level : " + level_number_value);
            level_number_text->update();
        }

        void GameplayUIController::updateScoreText()
        {
            int player_score = ServiceLocator::getInstance()->getPlayerService()->getPlayerScore();
            sf::String score_value = std::to_string(player_score);

            score_text->setText("Score : " + score_value);
            score_text->update();
        }

        void GameplayUIController::render()
        {
            level_number_text->render();
            score_text->render();
        }

        void GameplayUIController::show()
        {
            level_number_text->show();
            score_text->show();
        }

        void GameplayUIController::destroy()
        {
            delete (level_number_text);
            delete (score_text);
        }
	}
}