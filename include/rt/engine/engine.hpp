#ifndef RT_ENGINE_H
#define RT_ENGINE_H

#include <rt/3d/scene/scene.hpp>
#include <rt/graphics/window/window.hpp>

#include <chrono>
#include <glad/gl.h>

class Engine
{
  public:
    Engine();

    static void init();
    void set_scene(const Scene& scene);
    void start();

  private:
    Window m_window;
    Scene m_scene;
    unsigned int m_fps;
    std::chrono::duration<double> m_frame_time;

    struct MouseInfo
    {
        double m_last_x;
        double m_last_y;
        bool m_pressed;
    } m_mouse_info;

    struct KeyboardInfo
    {
        bool m_forward_key_pressed;
        bool m_backward_key_pressed;
        bool m_left_key_pressed;
        bool m_right_key_pressed;
        bool m_up_key_pressed;
        bool m_down_key_pressed;

    } m_keyboardInfo;

    void on_key_press(int key_code, int action);
    void on_resize(int width, int height);
    void on_mouse_pos_changed(double x_pos, double y_pos);
    void on_mouse_pressed(int key, int action, int mod);

    void process_inputs();

    static void handle_gl_error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar* message, const void* user_param);
};

#endif // RT_ENGINE_H