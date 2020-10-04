#include "Enemy.h"

Enemy::Enemy(std::string name, GLuint texture, GLuint shaderProgram, Camera* camera, LightRenderer* light, irrklang::ISoundEngine* soundEngine, btDiscreteDynamicsWorld* dynamicsWorld, btVector3 shape, btVector3 position, btScalar mass) :
	GORectangle( name, texture, shaderProgram, camera, light, soundEngine, dynamicsWorld, shape, position, mass) {

}

void Enemy::FixedUpdate(btScalar deltaTime) {
	if (!_dead){
		btTransform t(_rigidbody->getWorldTransform());
		MoveToPosition(t.getOrigin() + btVector3(-15, 0, 0) * deltaTime);

		// Check if offScreen
		if (t.getOrigin().x() <= -18.0f) {
			MoveToPosition(btVector3(18, 1, 0));
			_dead = true;
		}

	}
}

void Enemy::Update() {


}

void Enemy::OnCollision(GameObject* object) {
	if (object->GetName() == "player") {
		btTransform b(_rigidbody->getWorldTransform());
		b.setOrigin(btVector3(18, 1, 0));
		_rigidbody->setWorldTransform(b);
		_rigidbody->getMotionState()->setWorldTransform(b);
	}

}

void Enemy::Restart() {
	_dead = false;
	MoveToPosition(btVector3(18, 1, 0));
	
}

bool Enemy::IsDead() { return _dead; }