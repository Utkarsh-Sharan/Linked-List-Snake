#include "Player/BodyPart.h"

#include "Level/LevelView.h"
#include "Global/Config.h"

namespace Player
{
	using namespace UI::UIElement;
	using namespace Global;
	using namespace Level;

	BodyPart::BodyPart()
	{
		grid_position = sf::Vector2i(0, 0);

		createBodyPartImage();
	}

	BodyPart::~BodyPart()
	{
		destroy();
	}

	void BodyPart::createBodyPartImage()
	{
		bodypart_image = new ImageView();
	}

	void BodyPart::initialize(float width, float height, sf::Vector2i pos, Direction dir)
	{
		bodypart_width = width;
		bodypart_height = height;
		grid_position = pos;
		direction = dir;

		initializeBodyPartImage();
	}

	void BodyPart::initializeBodyPartImage()
	{
		bodypart_image->initialize(Config::snake_body_texture_path, bodypart_width, bodypart_height, getBodyPartScreenPosition());
		bodypart_image->setOriginAtCentre();
	}

	void BodyPart::updatePosition()
	{
		bodypart_image->setPosition(getBodyPartScreenPosition());
		bodypart_image->setRotation(getRotationAngle());
		bodypart_image->update();
	}


	sf::Vector2f BodyPart::getBodyPartScreenPosition()
	{
		float x_screen_position = LevelView::border_offset_left + (grid_position.x * bodypart_width) + (bodypart_width / 2);
		float y_screen_position = LevelView::border_offset_top + (grid_position.y * bodypart_height) + (bodypart_height / 2);

		return sf::Vector2f(x_screen_position, y_screen_position);
	}

	float BodyPart::getRotationAngle()
	{
		switch (direction)
		{
		case Direction::UP:
			return 270.f;

		case Direction::DOWN:
			return 90.f;

		case Direction::RIGHT:
			return 0;

		case Direction::LEFT:
			return 180.f;
		}
	}

	void BodyPart::render()
	{
		bodypart_image->render();
	}

	void BodyPart::setDirection(Direction direction)
	{
		this->direction = direction;
	}

	void BodyPart::destroy()
	{
		bodypart_image = nullptr;

		delete(bodypart_image);
	}
}