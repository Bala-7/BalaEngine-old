#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include "ShaderLoader.h"
#include "Camera.h"
#include "LightRenderer.h"
#include "MeshRenderer.h"
#include "TextureLoader.h"
#include <btBulletDynamicsCommon.h>
#include <chrono>
#include "TextRenderer.h"
#include "GOSphere.h"
#include "GORectangle.h"
#include <list>
#include "Input.h"
#include "Player.h"
#include "Enemy.h"
#include <Windows.h>
#include <irrKlang.h>


Camera* camera;
std::list<GameObject*> drawList;

LightRenderer* light;
Player* player;
MeshRenderer* ground;
Enemy* enemy;

// Audio
irrklang::ISoundEngine* soundEngine;


// Text
TextRenderer* label;
GLuint textProgram;

// Lightning
GLuint litTexturedShaderProgram;

btDiscreteDynamicsWorld* dynamicsWorld;
int score = 0;

void initGame();
void renderScene();
void addRigidBodies();
void myTickCallback(btDynamicsWorld* dynamicsWorld, btScalar timeStep);
void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
void UpdateScene();
void initSoundEngine();

int main(int argc, char** argv)
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, " BalaEngine - Built with OpenGL ", NULL, NULL);
	

	glfwMakeContextCurrent(window);	// Initialize OpenGL Context
	glfwSetKeyCallback(window, updateKeyboard);	// Sets 'updateKeyboard' as the callback function to manage key pressing
	glewInit();	// Initialize GLEW

	initSoundEngine();

	initGame();

	auto previousTime = std::chrono::high_resolution_clock::now();
	while (!glfwWindowShouldClose(window)) {
		// Calculate delta time and simulates physics
		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();
		dynamicsWorld->stepSimulation(dt);

		
		renderScene();	 // render our scene
		UpdateScene();
		glfwSwapBuffers(window);
		glfwPollEvents();

		previousTime = currentTime;
	}

	glfwTerminate();
	delete camera;
	delete light;

	return 0;
}

void initSoundEngine() {
	soundEngine = irrklang::createIrrKlangDevice();

}

void initGame() {

	// Enable depth testing so only the pixels in the front are drawn
	glEnable(GL_DEPTH_TEST);


	// Creates the shader loader and the program taking vertex shader and fragment shader files
	ShaderLoader shader;
	GLuint flatShaderProgram = shader.CreateProgram("Assets/Shaders/FlatModel.vs", "Assets/Shaders/FlatModel.fs");
	
	// Creates the camera
	camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 20.0f));
	
	// Creates the light
	litTexturedShaderProgram = shader.CreateProgram("Assets/Shaders/LitTexturedModel.vs", "Assets/Shaders/LitTexturedModel.fs");
	
	light = new LightRenderer(MeshType::kSphere, camera);
	light->setProgram(flatShaderProgram);
	light->setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
	light->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

	//init physics
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));
	dynamicsWorld->setInternalTickCallback(myTickCallback);

	addRigidBodies();

	// Text
	textProgram = shader.CreateProgram("Assets/Shaders/text.vs", "Assets/Shaders/text.fs");
	label = new TextRenderer("Score: 0", "Assets/fonts/FredokaOne-Regular.ttf", 64, glm::vec3(1.0f, 1.0f, 1.0f), textProgram);
	label->setPosition(glm::vec2(280.0f, 500.0f));

	


}


void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clears the buffer
	glClearColor(0.23, 0.72, 0.5, 1.0);	// Clears the render screen with the specified color

	//light->draw();
	
	for (GameObject* go : drawList)
		go->draw();


	label->draw();
}

void UpdateScene() {
	for (GameObject* go : drawList)
		go->Update();
}

void addRigidBodies() {
	ShaderLoader shader;
	TextureLoader tLoader;
	GLuint sphereTexture = tLoader.getTextureID("Assets/Textures/Concrete.jpg");
	GLuint groundTexture = tLoader.getTextureID("Assets/Textures/CrackedGround.jpg");
	GLuint flatShaderProgram = shader.CreateProgram("Assets/Shaders/FlatModel.vs", "Assets/Shaders/FlatModel.fs");
	GLuint texturedShaderProgram = shader.CreateProgram("Assets/Shaders/TexturedModel.vs", "Assets/Shaders/TexturedModel.fs");
	
	// Sphere
	player = new Player("player", sphereTexture, litTexturedShaderProgram, camera, light, soundEngine, dynamicsWorld, btVector3(0, 0.5, 0), 13.0);
	drawList.push_back(player);

	// Ground
	GORectangle* groundGO = new GORectangle("ground", groundTexture, litTexturedShaderProgram, camera, light, soundEngine, dynamicsWorld, btVector3(4.0f, 0.5f, 4.0f), btVector3(0, -1.0f, 0));
	drawList.push_back(groundGO);

	// Enemy
	enemy = new Enemy("enemy", groundTexture, litTexturedShaderProgram, camera, light, soundEngine, dynamicsWorld, btVector3(1.0f, 1.0f, 1.0f), btVector3(18.0, 1.0f, 0));
	enemy->GetRigidbody()->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	drawList.push_back(enemy);
}

void myTickCallback(btDynamicsWorld* dynamicsWorld, btScalar timeStep) {
	
	if (!player->IsDead()) {
		// Update objects
		for (GameObject* go : drawList)
			go->FixedUpdate(timeStep);


		// Check enemy state
		if (enemy->IsDead()) {
			enemy->Restart();
			score++;
			label->setText("Score: " + std::to_string(score));
		}

	}

	// Check collisions

	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++) {
		btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		int numContacts = contactManifold->getNumContacts();
		if (numContacts > 0) {
			const btCollisionObject* objA = contactManifold->getBody0();
			const btCollisionObject* objB = contactManifold->getBody1();
			MeshRenderer* meshA = (MeshRenderer*)objA->getUserPointer();
			MeshRenderer* meshB = (MeshRenderer*)objB->getUserPointer();
			
			GameObject* goA = meshA->GetGameObject();
			GameObject* goB = meshB->GetGameObject();

			goA->OnCollision(goB);
			goB->OnCollision(goA);

			if ((goA->GetName() == "player" && goB->GetName() == "enemy") ||
				(goA->GetName() == "enemy" && goB->GetName() == "player")) {
				
				player->Die();
				score = 0;
				label->setText("Score: " + std::to_string(score));
			}
		}
	}


}

void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// Esc = exit
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	player->OnKeyPressed(key, action);

}