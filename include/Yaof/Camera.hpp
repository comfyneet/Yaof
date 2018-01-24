#ifndef YAOF_CAMERA_HPP
#define YAOF_CAMERA_HPP

#include "Yaof/Core/Configuration.hpp"
#include "Yaof/Misc/NonCopyable.hpp"
#include "Yaof/Misc/Vector3.hpp"

#define YAOF_DEFAULT_CAMERA_YAW        (-90.0)
#define YAOF_DEFAULT_CAMERA_PITCH      0.0
#define YAOF_DEFAULT_CAMERA_SPEED      3.0
#define YAOF_DEFAULT_CAMERA_SENSITIVTY 0.25f
#define YAOF_DEFAULT_CAMERA_ZOOM       45.0

namespace yf
{
    enum CameraMovement
    {
        Forward,
        Backward,
        Left,
        Right
    };

    class YAOF_DLL Camera : public NonCopyable
    {
    public:
        explicit Camera(
            Vector3<float> position = Vector3<float>(0.0, 0.0, 0.0),
            Vector3<float> up = Vector3<float>(0.0, 1.0, 0.0),
            float yaw = YAOF_DEFAULT_CAMERA_YAW,
            float pitch = YAOF_DEFAULT_CAMERA_PITCH);

        Camera(
            float positionX, float positionY, float positionZ,
            float upX, float upY, float upZ,
            float yaw, float pitch);

    private:
        void updateCameraVectors();

        Vector3<float> m_position;

        Vector3<float> m_front;

        Vector3<float> m_up;

        Vector3<float> m_right;

        Vector3<float> m_worldUp;

        float m_yaw;

        float m_pitch;

        float m_movementSpeed;

        float m_mouseSensitivity;

        float m_zoom;
    };
}

#endif
