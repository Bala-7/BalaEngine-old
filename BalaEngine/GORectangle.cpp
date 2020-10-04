#include "GORectangle.h"


GORectangle::GORectangle(std::string name, GLuint texture, GLuint shaderProgram, Camera* camera, LightRenderer* light, irrklang::ISoundEngine* soundEngine, btDiscreteDynamicsWorld* dynamicsWorld, btVector3 shape, btVector3 position, btScalar mass) {
	_name = name;
	_texture = texture;
	_shaderProgram = shaderProgram;
	_soundEngine = soundEngine;

	// Ground Rigid body
	btCollisionShape* rectangleShape = new btBoxShape(shape);
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), position));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0.0f, motionState, rectangleShape, btVector3(0, 0, 0));

	_rigidbody = new btRigidBody(groundRigidBodyCI);
	_rigidbody->setFriction(1.0);
	_rigidbody->setRestitution(0.0);
	_rigidbody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
	dynamicsWorld->addRigidBody(_rigidbody);

	// Ground Mesh
	_mesh = new MeshRenderer(this, MeshType::kCube, name, camera, _rigidbody, light, 0.1f, 0.5f);
	_mesh->setProgram(_shaderProgram);
	_mesh->setTexture(_texture);
	_mesh->setScale(glm::vec3(shape.getX(), shape.getY(), shape.getZ()));
	_rigidbody->setUserPointer(_mesh);

}

GORectangle::~GORectangle() {
	
}

void GORectangle::Update() {
	

}

void GORectangle::OnCollision(GameObject* object) {


}