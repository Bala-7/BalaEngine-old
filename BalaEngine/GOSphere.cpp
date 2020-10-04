#include "GOSphere.h"

GOSphere::GOSphere(std::string name, GLuint texture, GLuint shaderProgram, Camera* camera, LightRenderer* light, irrklang::ISoundEngine* soundEngine, btDiscreteDynamicsWorld* dynamicsWorld, btVector3 position, btScalar mass) {
	_name = name;
	_texture = texture;
	_shaderProgram = shaderProgram;
	_soundEngine = soundEngine;

	// Rigidbody
	btCollisionShape* sphereShape = new btSphereShape(1);
	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), position));
	btVector3 sphereInertia(0, 0, 0);
	sphereShape->calculateLocalInertia(mass, sphereInertia);
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState, sphereShape, sphereInertia);
	_rigidbody = new btRigidBody(sphereRigidBodyCI);
	_rigidbody->setFriction(1.0f);
	_rigidbody->setRestitution(0.0f);
	_rigidbody->setActivationState(DISABLE_DEACTIVATION);
	dynamicsWorld->addRigidBody(_rigidbody);

	// Mesh
	_mesh = new MeshRenderer(this, MeshType::kSphere, _name ,camera, _rigidbody, light, 0.1f, 0.5f);
	_mesh->setProgram(_shaderProgram);
	_mesh->setTexture(_texture);
	_mesh->setScale(glm::vec3(1.0f));
	_rigidbody->setUserPointer(_mesh);
}

GOSphere::~GOSphere() {

}

void GOSphere::Update() {
	
}

void GOSphere::OnCollision(GameObject* object) {

}
