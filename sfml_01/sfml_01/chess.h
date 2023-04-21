#pragma once
#include"SFML/Graphics.hpp"
using namespace sf;
class chess {
public:
	chess(Vector2f position,Color color);
	void setcolor(bool judge);
	CircleShape getShape();
	void update();
private:
	CircleShape shape;
	Color m_color;
	Vector2f m_position;
};
chess::chess(Vector2f position, Color color)
{
	shape.setFillColor(color);
	shape.setRadius(30.f);
	shape.setOrigin(30, 30);
	shape.setPosition(position);
}
CircleShape chess::getShape()
{
	return shape;
}
void chess::setcolor(bool judge)
{
	if (judge) {
		shape.setFillColor(Color::White);
		m_color = Color::White;
	}
	else {
		shape.setFillColor(Color::Black);
		m_color = Color::Black;
	}

}
