#pragma once
#include "GORectangle.h"
class Enemy : public GORectangle
{
public:
	Enemy(std::string name, GLuint texture, GLuint shaderProgram, Camera* camera, LightRenderer* light, irrklang::ISoundEngine* soundEngine, btDiscreteDynamicsWorld* dynamicsWorld, btVector3 shape, btVector3 position = btVector3(0, 0, 0), btScalar mass = 1.0);
	~Enemy();

	void Update() override;
	void FixedUpdate(btScalar deltaTime) override;
	void OnCollision(GameObject* object) override;

	bool IsDead();
	void Restart();
private:
	bool _dead = true;
};

