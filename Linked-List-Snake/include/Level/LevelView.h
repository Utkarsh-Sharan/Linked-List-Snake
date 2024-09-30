#pragma once

#include "UI/UIElement/RectangleShapeView.h"
#include <SFML/Graphics.hpp>

namespace Level
{
	class LevelView
	{
    private:
        const sf::Color background_color = sf::Color(180, 200, 160);
        const sf::Color border_color = sf::Color::Black;

        UI::UIElement::RectangleShapeView* background_rectangle;
        UI::UIElement::RectangleShapeView* border_rectangle;

        float grid_width = 0.f;
        float grid_height = 0.f;

        void createViews();
        void initializeBackground();
        void initializeBorder();
        void calculateGridExtents();
        void destroy();

    public:
        static const int border_thickness = 10;
        static const int border_offset_left = 40;
        static const int border_offset_top = 100;
        static const int border_offset_bottom = 40;

        LevelView();
        ~LevelView();

        void initialize();
        void update();
        void render();

        float getGridWidth();
        float getGridHeight();
	};
}