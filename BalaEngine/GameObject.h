#pragma once
#include "ShaderLoader.h"
#include "Camera.h"
#include "LightRenderer.h"
#include "MeshRenderer.h"
#include "TextureLoader.h"
#include "Input.h"
#include "irrKlang.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void FixedUpdate(btScalar deltaTime);
	virtual void Update() = 0;
	void draw();
	virtual void OnCollision(GameObject* object);

	void MoveToPosition(btVector3 position);

	std::string GetName();	
	MeshRenderer* GetMesh();
	btRigidBody* GetRigidbody();
	
protected:	
	std::string _name = "";
	MeshRenderer* _mesh;
	btRigidBody* _rigidbody;
	GLuint _shaderProgram;
	GLuint _texture;
	irrklang::ISoundEngine* _soundEngine;
};

