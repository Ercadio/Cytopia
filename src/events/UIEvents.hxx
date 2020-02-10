#ifndef UI_EVENTS_HXX
#define UI_EVENTS_HXX

#include "../view/iActivity.hxx"

/**
 * @brief Event describing a Widget change
 * @tparam UITargetType the target widget type
 * @tparam UpdateEventType the update type
 */
template <typename UITargetType, typename UpdateEventType> struct UIChangeEvent
{
  UITargetType target;
  UpdateEventType data;
};

/**
 * @brief A tranisition to another iActivity
 */
struct ActivitySwitchEvent
{
 ActivityType activityType;
};

/**
 * @brief A change in the window's size
 */
struct WindowResizeEvent
{

};

#endif // UI_EVENTS_HXX
