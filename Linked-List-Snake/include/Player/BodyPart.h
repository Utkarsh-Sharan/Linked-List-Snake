#pragma once

#include "UI/UIElement/ImageView.h"
#include "Player/Direction.h"

namespace Player
{
	class BodyPart
	{
	private:
		void createBodyPartImage();
		void initializeBodyPartImage();

		sf::Vector2f getBodyPartScreenPosition();
		float getRotationAngle();

		sf::Vector2i getNextPositionUp();
		sf::Vector2i getNextPositionDown();
		sf::Vector2i getNextPositionLeft();
		sf::Vector2i getNextPositionRight();

		void destroy();

	protected:
		UI::UIElement::ImageView* bodypart_image;

		sf::Vector2i grid_position;
		Direction direction;
		Direction previous_direction;

		float bodypart_width;
		float bodypart_height;

	public:
		BodyPart();
		~BodyPart();

		void initialize(float width, float height, sf::Vector2i pos, Direction dir);
		void updatePosition();
		void render();

		void setDirection(Direction direction);
		Direction getDirection();

		sf::Vector2i getNextPosition();
		sf::Vector2i getPrevPosition();

		void setPosition(sf::Vector2i position);
		sf::Vector2i getPosition();
	};
}