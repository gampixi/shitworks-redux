#include "transform.h"
#include "swlog.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

glm::mat4 Transform::getWorldMatrix() {
    auto result = glm::mat4(1.0f);
    result = glm::translate(result, position);
    result = result * glm::mat4_cast(rotation);
    result = glm::scale(result, scale);
    return result;
}

glm::mat4 Transform::getViewMatrix() {
    auto result = glm::mat4(1.0f);
    // result = glm::scale(result, scale);
    result = result * glm::mat4_cast(glm::inverse(rotation));
    result = glm::translate(result, position * -1.0f);
    return result;
}