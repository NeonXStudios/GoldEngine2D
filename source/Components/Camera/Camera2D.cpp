//#include "Camera2D.h";
//
//
//Camera::Camera(int width, int height, glm::vec3 position)
//{
//	Camera::width = width;
//	Camera::height = height;
//	Position = position;
//}
//
//void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
//{
//	float rotationXAngle360 = fmod(rotationXAngle, 360);
//	float rotationYAngle360 = fmod(rotationYAngle, 360);
//	float rotationZAngle360 = fmod(rotationZAngle, 360);
//
//	// Aplicar las rotaciones en los ejes X, Y y Z a los quaterniones
//	glm::quat rotationX = glm::angleAxis(glm::radians(rotationXAngle360), glm::vec3(1.0f, 0.0f, 0.0f));
//	glm::quat rotationY = glm::angleAxis(glm::radians(rotationYAngle360), glm::vec3(0.0f, 1.0f, 0.0f));
//	glm::quat rotationZ = glm::angleAxis(glm::radians(rotationZAngle360), glm::vec3(0.0f, 0.0f, 1.0f));
//
//	// Combinar las rotaciones en un solo quaternion
//	cameraRotation = rotationZ * rotationY * rotationX;
//
//	// Convertir el quaternion a una matriz de rotación
//	glm::mat4 rotationMatrix = glm::mat4_cast(cameraRotation);
//
//	float screenWidth = static_cast<float>(AppSettings::instance->ScreenWidth);
//	float screenHeight = static_cast<float>(AppSettings::instance->ScreenHeight);
//	projection = glm::ortho(-screenWidth / 2.0f * zoom, screenWidth / 2.0f * zoom,
//		-screenHeight / 2.0f * zoom, screenHeight / 2.0f * zoom, -1000.0f, 1000.0f);
//
//	// Aplicar la rotación a la dirección de la cámara usando la matriz de rotación
//	cameraFront = glm::mat3(rotationMatrix) * glm::vec3(0.0f, 0.0f, -1.0f);
//
//	view = glm::lookAt(Position, Position + cameraFront, Up);
//	//float aspectRatio = static_cast<float>(AppSettings::instance->ScreenWidth) / static_cast<float>(AppSettings::instance->ScreenHeight);
//	//// Makes camera look in the right direction from the right position
//
//	//// Adds perspective to the scene
//	//projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 10000000.0f);
//	////projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
//
//	//view = glm::lookAt(Position, Position + Orientation, Up);
//
//	//// Sets new camera matrix
//	//cameraMatrix = projection * view;
//}
//
//void Camera::Matrix(Shader& shader, const char* uniform)
//{
//	// Exports camera matrix
//	//glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
//}
//
//
//
//void Camera::Inputs (GLFWwindow* window)
//{
//	// Handles key inputs
//	/*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//	{
//		Position += speed * Orientation;
//	}
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//	{
//		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
//	}
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//	{
//		Position += speed * -Orientation;
//	}
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//	{
//		Position += speed * glm::normalize(glm::cross(Orientation, Up));
//	}
//	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//	{
//		Position += speed * Up;
//	}
//	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//	{
//		Position += speed * -Up;
//	}
//	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//	{
//		speed = 0.4f;
//	}
//	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
//	{
//		speed = 0.1f;
//	}*/
//
//
//	// Handles mouse inputs
//	//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
//	//{
//	//	// Hides mouse cursor
//	//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
//
//	//	// Prevents camera from jumping on the first click
//	//	if (firstClick)
//	//	{
//	//		glfwSetCursorPos(window, (width / 2), (height / 2));
//	//		firstClick = false;
//	//	}
//
//	//	// Stores the coordinates of the cursor
//	//	double mouseX;
//	//	double mouseY;
//	//	// Fetches the coordinates of the cursor
//	//	glfwGetCursorPos(window, &mouseX, &mouseY);
//
//	//	// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
//	//	// and then "transforms" them into degrees 
//	//	float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
//	//	float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;
//
//	//	// Calculates upcoming vertical change in the Orientation
//	//	glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
//
//	//	// Decides whether or not the next vertical Orientation is legal or not
//	//	if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
//	//	{
//	//		Orientation = newOrientation;
//	//	}
//
//	//	// Rotates the Orientation left and right
//	//	Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
//
//	//	// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
//	//	glfwSetCursorPos(window, (width / 2), (height / 2));
//	//}
//	//else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
//	//{
//	//	// Unhides cursor since camera is not looking around anymore
//	//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//	//	// Makes sure the next time the camera looks around it doesn't jump
//	//	firstClick = true;
//	//}
//}