#include <catch2/catch.hpp>

#include "../../src/util/Observer.hxx"
#include "../../src/util/TransitiveState.hxx"
#include "../../src/util/Memento.hxx"

/**
 * Our goal is to create a TextField State which supports undo and redo operations.
 * To design this state, we need to think about three things:
 * 1. What are the operations on our state?
 *    1.1 Write character (typing)
 *    1.2 Backspace
 *    1.3 Delete
 *    1.4 Move cursor left
 *    1.5 Move cursor right
 *    1.6 Move cursor to some random location
 *    1.7 Move cursor to beginning of word (Usually with Ctrl+Left_Arrow)
 *    1.8 Move cursor to end of word (Usually with Ctrl+Right_Arrow)
 *    Note 1: 1.2 and 1.3 can be combined into a "delete section" event
 *    Note 2: 1.7 and 1.8 can be combined into the "random move" event, 
 *    because they should have the same data.
 *    Note 3: There could be many more operations here... 
 *    We could have hover, selected, etc. like button, because we might
 *    want to know when we should display a blinking caret animation
 * 2. Which operations could be undoed/redoed ?
 *    Writing a character, backspace and delete.
 *    It doesn't make sense to undo moving our cursor.
 * 3. Which revertible operations should be chunked together?
 *    All of them should be chunked with themselves. For example,
 *    if I type a series of 10 characters, and then I undo, it
 *    should undo my 10 characters. Moreover, we want to merge
 *    backspace and delete operations together.
 */

/**
 * Okay so first, we need to create our Revertible model. 
 */

class InputTextModel
{
  enum Operations
  {
    WRITE,
    DELETE
  };
  struct OperationBase
  {
    using MyModelType = InputTextModel;
  }
  struct WriteData : public OperationBase
  {
    std::size_t position;
    std::string text;
  };
  struct DeleteData : public OperationBase
  {
    std::size_t position;
    std::string text;
  };

  /* This tells TransitiveState to delegate the container to the State */
  using DelegateContainerOwnership = Constant<true>;

}

/**
 * Next, the rest of our Transitive model
 */
class NavigableTextModel
{

  enum Operations
  {
    MOVE_CURSOR, /* Triggers when our cursor moves and does not select anything */
    SELECT_TEXT, /* Triggers when we are selecting a range of text */
    MOUSE_CHANGE /* Triggers when various mouse events occur */
  };

  struct OperationBase
  {
    using MyModelType = EditableTextModel;
  }
  struct MoveCursorData : public OperationBase
  {
    std::size_t oldPosition;
    std::size_t newPosition;
  };
  struct SelectTextData : public OperationBase 
  {
    std::size_t fromPosition;
    std::size_t toPosition;
  };
  struct MouseChangeData : public OperationBase 
  {
    /**
     * Bit 1 : set if mouse is hovering
     * Bit 2 : set if field is activated
     * Bit 3 : set if field is disabled
     * Bit 4 : set if field is displayed (takes physical space)
     * Bit 5 : set if field is pressed
     * Bit 6 : set if field is focused
     * Bit 7 : set if field is visible (renders pixels)
     * Bit 8 : set if field is invalid (wrong input)
     */
    std::bitset<8> mouseState;
  };
  
  using OperationTypes =
      TypeList<WriteData, DeleteData, BackspaceData>;
  
  /* This tells TransitiveState to delegate the container to the State */
  using DelegateContainerOwnership = Constant<true>;

};

/**
 * Now, we create our compound state.
 * It's not very efficient to use two containers to store Observers for TransitiveState and RevertibleState.
 * So what we can do is delegate the ownership of the container to the State class and share it between the two Subjects
 */
class EditableTextState : public TransitiveState<NavigableTextModel>, public RevertibleState<InputTextModel>
{
public:
};

/**
 * Then, we create our Memento
 */

class EditableTextController 
{

  Memento<EditableTextState> m_Memento;

};

/**
 * Finally, we create our View
 */
class InputView
{
  
  struct Listener : public Observer<>
  {

  }

}

