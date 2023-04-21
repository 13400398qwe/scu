#include"hero.h"
Hero::Hero() {

}
Hero::~Hero()
{

}
void Hero::init(string textureName, Vector2f postion, float mass)
{
	m_postion = postion;
	m_mass = mass;
	m_grounded = false;
	m_texture.loadFromFile(textureName.c_str());
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_postion);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y/2);
}
void Hero::update(float dt)
{
	m_velocity-= m_mass * m_gravity * dt;
	m_postion.y -= m_velocity * dt;
	m_sprite.setPosition(m_postion);
	if (m_postion.y >= 768 * 0.75) {
		m_postion.y = 768 * 0.75f;
		m_velocity = 0;
		m_grounded = true;
		jumpCount = 0;
	}
}
void Hero::jump(float velocity)
{
	if (jumpCount < 2)
	{
		jumpCount++;
		m_velocity = velocity;
		m_grounded = false;
	}
}
Sprite Hero::getSprite()
{
	return m_sprite;
}