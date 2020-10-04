#pragma once
#include "GOSphere.h"
class Player : public GOSphere
{
public:
	Player(std::string name, GLuint texture, GLuint shaderProgram, Camera* camera, LightRenderer* light, irrklang::ISoundEngine* soundEngine, btDiscreteDynamicsWorld* dynamicsWorld, btVector3 position = btVector3(0, 0, 0), btScalar mass = 1.0);
	~Player();

	void Update() override;
	void OnCollision(GameObject* object) override;
	bool IsGrounded();
	void SetGrounded(bool grounded);
	void Jump();
	bool IsDead();
	void Die();
	void Restart();
	void OnKeyPressed(int key, int action);

private:
	bool _grounded = false;
	bool _dead = true;
};

