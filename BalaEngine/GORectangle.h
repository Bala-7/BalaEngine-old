#pragma once
#include "GameObject.h"
class GORectangle : public GameObject
{
public:
	GORectangle(std::string name, GLuint texture, GLuint shaderProgram, Camera* camera, LightRenderer* light, irrklang::ISoundEngine* soundEngine, btDiscreteDynamicsWorld* dynamicsWorld, btVector3 shape,btVector3 position = btVector3(0, 0, 0), btScalar mass = 1.0);
	~GORectangle();

	void Update() override;
	void OnCollision(GameObject* object) override;
};

