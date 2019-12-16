#ifndef MOUSE_EVENTS_HXX
#define MOUSE_EVENTS_HXX

/**
 * @brief A change in the mouse (or device)'s position
 */
struct MousePositionEvent
{
  int xPosition;
  int yPosition;
  int xVelocity;
  int yVelocity;
};

/**
 * @brief A click interaction
 */
struct ClickEvent
{
  int32_t xPosition;
  int32_t yPosition;
  /**
   * @brief One-hot encoding for the state of the mouse or device
   * @details Exactly one of {Left, Right, Middle} must be set 
   *          and exactly one of {Pressed, Released} must be set
   */
  enum State : uint8_t { 
    Left = 0b1,
    Right = 0b10, 
    Middle = 0b100,
    Pressed = 0b1000,
    Released = 0b10000,
  };
  State state;
};

/**
 * @brief A scrolling interaction
 */
struct ScrollEvent
{
  int32_t xDisplacement;
  int32_t yDisplacement;
};

using MouseEvents = TypeList<
  MousePositionEvent,
  ClickEvent,
  ScrollEvent
>;

#endif // MOUSE_EVENTS_HXX
