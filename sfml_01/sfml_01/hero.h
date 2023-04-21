#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Hero {
public:
	Hero();
	~Hero();
	void init(string textureName, Vector2f Position, float mass);
	void update(float dt);
	void jump(float velocity);
	Sprite getSprite();
private:
	Texture m_texture;
	Sprite m_sprite;
	Vector2f m_postion;
	int jumpCount = 0;
	float m_mass;
	float m_velocity;
	const float m_gravity = 9.80f;
	bool m_grounded;
};