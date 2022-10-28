// Adam Motaouakkil
// ID: 260956145

#include "ArcBall.h"
#include "MatrixStack.h"
#include "Program.h"

#include <iostream>
#include <cassert>

#include "GLSL.h"

using namespace std;


ArcBall::ArcBall():R(glm::mat4(1.0)), fit(0.5), gain(5), Rmem(glm::mat4(1.0)), p0(glm::vec3(1.0)), p1(glm::vec3(1.0))
{
}

ArcBall::~ArcBall()
{
}

glm::vec3 ArcBall::computeVecFromMousePos(double mousex, double mousey, int windowWidth, int windowHeight) {
	//TODO: compute the projection of mouse coords on the arcball
	// return glm::vec3(0,0,0);
    int smallestDim = min(windowWidth, windowHeight);
    double radius = (smallestDim) / fit;
    double posX = (mousex - (windowWidth / 2)) / radius;
    double posY = -(mousey - (windowHeight / 2)) / radius;
    double posZ = 0;
    double r = (posX * posX) + (posY * posY);
    double s = 0;
    if (r > 1.0)
    {
        s = 1.0 / sqrt(r);
        posX = s * posX;
        posY = s * posY;
        posZ = 0;
    }
    else
    {
        posZ = sqrt(1.0 - r);
    }
    return glm::vec3(posX, posY, posZ);
}

double computeVectorAngle(glm::vec3& v1, glm::vec3& v2) {
	double vDot = glm::dot(v1, v2);
	if (vDot < -1.0) vDot = -1.0;
	if (vDot > 1.0) vDot = 1.0;
	return((double)(acos(vDot)));
}

void ArcBall::startRotation(double mousex, double mousey, int windowWidth, int windowHeight) {
	Rmem = R;
	p0 = computeVecFromMousePos(mousex, mousey, windowWidth, windowHeight);
}

void ArcBall::updateRotation(double mousex, double mousey, int windowWidth, int windowHeight) {
	// TODO: compute the rotation update for the view camera
	// R = glm::mat4(1.0);
    //p0 = glm::normalize(p0);
    p1 = computeVecFromMousePos(mousex, mousey, windowWidth, windowHeight);
    //p1 = glm::normalize(p1);
    glm::vec3 theCross = glm::cross(p0, p1);
    float theAngle = computeVectorAngle(p0, p1);
    theAngle *= gain;
    // glm::quat angleAxis = glm::normalize(glm::angleAxis(theAngle, theCross));
    R = glm::rotate(Rmem, theAngle, theCross);
}
