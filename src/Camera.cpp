// Adam Motaouakkil
// ID: 260956145

#include "Camera.h"

using namespace std;


Camera::Camera(float aspect):lightColor(glm::vec3(1,1,1))
{
	this->setPerspective((float)(45.0 * M_PI / 180.0), aspect, 0.01f, 100.0f);
	this->updateView();
}

Camera::~Camera()
{
}

void Camera::setPerspective(float fov, float aspect, float near, float far) {
	// P = glm::mat4(1.0);
    P = glm::perspective(fov, aspect, near, far);
}

void Camera::updateView() {
	// V = glm::mat4(1.0);
    V = glm::lookAt(position, lookAt, up);
}


void Camera::draw(const shared_ptr<Program> program, glm::mat4 P, glm::mat4 V, shared_ptr <MatrixStack> M, glm::mat4 LightPV, Axis &axis) {
	program->bind();
	M->pushMatrix();
	
	//set uniform variables
	glUniformMatrix4fv(program->getUniform("P"), 1, GL_FALSE, &P[0][0]);
	glUniformMatrix4fv(program->getUniform("V"), 1, GL_FALSE, &V[0][0]);
	glUniformMatrix4fv(program->getUniform("M"), 1, GL_FALSE, &M->topMatrix()[0][0]);
	glUniformMatrix4fv(program->getUniform("MinvT"), 1, GL_FALSE, &M->topInvMatrix()[0][0]);
	glUniformMatrix4fv(program->getUniform("lightPV"), 1, GL_FALSE, &LightPV[0][0]);
	
	// TODO: draw the light frame using a fancy axis... You must set up the right transformation!
    M->multMatrix(glm::inverse(this->V));
	axis.draw(program, M);
	//draw the camera's wirecube
	M->pushMatrix();
    
    M->multMatrix(glm::inverse(this->P));

	
	debugWireCube->draw(program, P, V, M, LightPV);

	program->unbind();

	M->pushMatrix();	
	
    M->translate(0, 0, -1);
   
	debugDepthMapQuad->draw(quadShader, P, V, M, LightPV);

	M->popMatrix();
	M->popMatrix();
	M->popMatrix();
	
	GLSL::checkError(GET_FILE_LINE);
}
