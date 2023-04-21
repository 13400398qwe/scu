#include"enermy.h"
Enermy::Enermy() {};
Enermy::~Enermy() {};
void Enermy::init(std::string textureName, sf::Vector2f position, float _speed)
{
	m_speed = _speed;
	m_position = position;
	m_texture.loadFromFile(textureName.c_str());
	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(position);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}
void Enermy::update(float dt)
{
	m_sprite.move(m_speed * dt, 0);
}
sf::Sprite Enermy::getSprite()
{
	return m_sprite;
}