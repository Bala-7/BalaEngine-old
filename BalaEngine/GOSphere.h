#pragma once
#include "GameObject.h"
class GOSphere : public GameObject
{
public:
	GOSphere(std::string name, GLuint texture, GLuint shaderProgram, Camera* camera, LightRenderer* light, irrklang::ISoundEngine* soundEngine, btDiscreteDynamicsWorld* dynamicsWorld, btVector3 position = btVector3(0, 0, 0), btScalar mass = 1.0);
	~GOSphere();

	void Update() override;
	void OnCollision(GameObject* object) override;
};

