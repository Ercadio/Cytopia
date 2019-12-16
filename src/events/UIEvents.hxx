#ifndef UI_EVENTS_HXX
#define UI_EVENTS_HXX

/**
 * @brief Event triggered when the game must terminate
 */
struct TerminateEvent
{
};

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
 * @brief A Widget transitive change
 * @tparam TransitiveType the transitive type
 */
template <typename TransitiveType>
using TransitiveStateChange =
    UIChangeEvent<ObserverWPtr<typename TransitiveType::Transition>, typename TransitiveType::Transition>;

#endif // UI_EVENTS_HXX
