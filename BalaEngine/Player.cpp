#include "Player.h"

Player::Player(std::string name, GLuint texture, GLuint shaderProgram, Camera* camera, LightRenderer* light, irrklang::ISoundEngine* soundEngine, btDiscreteDynamicsWorld* dynamicsWorld, btVector3 position, btScalar mass) :
	GOSphere(name, texture, shaderProgram, camera, light, soundEngine, dynamicsWorld, position, mass) {

}

void Player::Update() {
	// Up = jump
	//if (_input->GetKeyPressed(GLFW_KEY_UP)){
		//if (!gameover) {
			//if (grounded == true) {
				//grounded = false;
				//_rigidbody->applyImpulse(btVector3(0.0f, 100.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f));
				//printf("pressed up key \n");
			//}
		//}
	//}
}

void Player::OnCollision(GameObject* object) {
	if (object->GetName() == "ground")
		_grounded = true;

}

void Player::Jump(){
	SetGrounded(false);
	_rigidbody->applyImpulse(btVector3(0.0f, 100.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f));

	_soundEngine->play2D("Assets/Sounds/Jump.wav", false);

}

bool Player::IsGrounded() { return _grounded; }

void Player::SetGrounded(bool grounded) { _grounded = grounded; }

bool Player::IsDead() { return _dead; }

void Player::Die() { 
	_dead = true; 
	_soundEngine->play2D("Assets/Sounds/Death.wav", false);
}

void Player::Restart() {
	_dead = false;
}


void Player::OnKeyPressed(int key, int action) {

	// Up = jump
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		if (!IsDead()) {
			if (IsGrounded()) {
				Jump();
			}
		}
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		if (IsDead()) 
			Restart();
	}
}