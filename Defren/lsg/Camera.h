#pragma once
#include "../../libs/include/glm/glm.hpp"

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 center;
	glm::vec3 up;
	glm::vec3 forward;
	glm::vec3 right;
	glm::mat4 matrix;

	
	Camera(void);
	~Camera(void);

public:
	enum DIRECTION
    {
        FORWARD = 0,
        RIGHT,
		BACK,
		LEFT
    };

	void Camera::move(DIRECTION dir);
	void rotate(float x, float y);
	void applyTransform();
	glm::vec4 applyTransformTo(glm::vec3 vec);

	static Camera* getCamera()
	{
		// Guaranteed to be destroyed, instantiated on first use.
		static Camera instance; 
		return &instance;
	}


};

