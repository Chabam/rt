#ifndef RT_CAMERA_CONTROLLER_H
#define RT_CAMERA_CONTROLLER_H

#include <rt/engine/engine_component.hpp>

namespace rt
{

class Camera;
class Window;

class CameraController final : public EngineComponent
{
  public:
    CameraController(Camera& camera, const Window& window);
    void update(const TimeStep& time_step) override;

  private:
    struct MouseInfoCache
    {
        double m_last_x = -1.0;
        double m_last_y = -1.0;
    } m_mouse_info_cache;

    struct WindowInfoCache
    {
        unsigned int m_last_width = -1;
        unsigned int m_last_height = -1;
    } m_window_info_cache;

    Camera& m_camera;
    const Window& m_window;
};

} // namespace rt

#endif // RT_CAMERA_CONTROLLER_H