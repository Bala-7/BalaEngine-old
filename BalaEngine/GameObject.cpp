#include "GameObject.h"

GameObject::GameObject() {

}


GameObject::~GameObject() {

}

void GameObject::FixedUpdate(btScalar deltaTime) {

}

MeshRenderer* GameObject::GetMesh() { return _mesh; }

btRigidBody* GameObject::GetRigidbody() { return _rigidbody; }

std::string GameObject::GetName() { return _name; }

void GameObject::draw() { _mesh->draw(); }

void GameObject::OnCollision(GameObject* object) {}

void GameObject::MoveToPosition(btVector3 position) {
	btTransform t(_rigidbody->getWorldTransform());
	t.setOrigin(position);
	_rigidbody->setWorldTransform(t);
	_rigidbody->getMotionState()->setWorldTransform(t);

}