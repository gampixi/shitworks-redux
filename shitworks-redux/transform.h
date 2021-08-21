#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
public:
    glm::vec3 position = glm::vec3(0.0, 0.0, 0.0); // Zero vector
    glm::quat rotation = glm::quat(1.0, 0.0, 0.0, 0.0); // Identity quat
    glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
    glm::mat4 getWorldMatrix();
    glm::mat4 getViewMatrix();
private:
    
};