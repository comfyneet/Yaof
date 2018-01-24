#include "Yaof/Camera.hpp"
#include "glm/glm.hpp"

namespace yf
{
    Camera::Camera(const Vector3<float> position, const Vector3<float> up, const float yaw, const float pitch) :
        m_yaw(yaw),
        m_pitch(pitch),
        m_movementSpeed(0),
        m_mouseSensitivity(0),
        m_zoom(0)
    {
        m_position = position;
        m_worldUp = up;
        updateCameraVectors();
    }

    Camera::Camera(
        const float positionX, const float positionY, const float positionZ,
        const float upX, const float upY, const float upZ,
        const float yaw, const float pitch) :
        m_yaw(yaw),
        m_pitch(pitch),
        m_movementSpeed(0),
        m_mouseSensitivity(0),
        m_zoom(0)
    {
        m_position = Vector3<float>(positionX, positionY, positionZ);
        m_worldUp = Vector3<float>(upX, upY, upZ);
        updateCameraVectors();
    }

    void Camera::updateCameraVectors()
    {
        glm::vec3 glmFront;
        glmFront.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
        glmFront.y = glm::sin(glm::radians(m_pitch));
        glmFront.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
        glmFront = normalize(glmFront);

        const auto glmWorldUp = glm::vec3(m_worldUp.x, m_worldUp.y, m_worldUp.z);

        const auto glmRight = normalize(cross(glmFront, glmWorldUp));

        const auto glmUp = normalize(cross(glmRight, glmFront));

        m_front = Vector3<float>(glmFront.x, glmFront.y, glmFront.z);
        m_right = Vector3<float>(glmRight.x, glmRight.y, glmRight.z);
        m_up = Vector3<float>(glmUp.x, glmUp.y, glmUp.z);
    }
}
