#include "LightRenderer.h"


LightRenderer::LightRenderer(MeshType meshType, Camera* camera) {

	this->camera = camera;
	this->position = glm::vec3{0.5, 0.5, 0.5};
	switch (meshType) {
		case kTriangle: Mesh::setTriData(vertices, indices); break;
		case kQuad: Mesh::setQuadData(vertices, indices); break;
		case kCube: Mesh::setCubeData(vertices, indices); break;
		case kSphere: Mesh::setSphereData(vertices, indices); break;
	}

	// Generate and bind vertex attribute object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Generate and bind vertex buffer object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Stores the vertex data in the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Enable position attribute of the vertex
	glEnableVertexAttribArray(0);	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	
	// Enable color attribute of the vertex
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::color)));

	// Generate and binds elements buffer object
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// Stores de indices data in the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);


	// Unbind buffer and vertex array, as a precaution
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}



void LightRenderer::draw() {

	// Creates the model
	glm::mat4 model = glm::mat4(1.0f);

	// Translate the model onto 'position'
	model = glm::translate(glm::mat4(1.0), position);

	// Take in a shader program. The model, view, and projection matrices are set in the vertex shader. Information is sent to the shader
	glUseProgram(this->program);

	// Then, we can send the information through the uniform variables
	GLint modelLoc = glGetUniformLocation(program, "model");

	// Now we can set the value of the model matrix using the glUniform function
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// Pass view and projection matrices as well
	glm::mat4 view = camera->getViewMatrix();
	GLint vLoc = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(view));
	glm::mat4 proj = camera->getProjectionMatrix();
	GLint pLoc = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(proj));

	// Binds the vao buffer object and draws the object
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	// For safety, unbind vertex array and program variable
	glBindVertexArray(0);
	glUseProgram(0);
}

LightRenderer::~LightRenderer() {
}
void LightRenderer::setPosition(glm::vec3 _position) {
	position = _position;
}
void LightRenderer::setColor(glm::vec3 _color) {
	this->color = _color;
}
void LightRenderer::setProgram(GLuint _program) {
	this->program = _program;
}
//getters
glm::vec3 LightRenderer::getPosition() {
	return position;
}
glm::vec3 LightRenderer::getColor() {
	return color;
}