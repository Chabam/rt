#ifndef RT_TIME_STEP_H
#define RT_TIME_STEP_H

#include <chrono>

namespace rt
{

struct TimeStep
{
    std::chrono::duration<double> m_render_time;
    std::chrono::time_point<std::chrono::system_clock> m_next_frame_deadline;
};

} // namespace rt

#endif // RT_TIME_STEP_H