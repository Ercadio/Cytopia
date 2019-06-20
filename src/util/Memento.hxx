#ifndef MEMENTO_HXX_
#define MEMENTO_HXX_

#include "TransitiveModel.hxx"

/**
 * @brief A TransitiveModel in which operations can be applied and unapplied sequentially
 * @details A model in which all transitions must be seperately schedulable and invertible.
 *          That means that applying any set of Transition in any order could never
 *          lead to an error state.
 */
template <typename State, typename Model>
class RevertibleModel : TransitiveModel<Model>
{
protected:
  inline void apply(Transition&& transition) noexcept
  {
    State::applyTransition(transition);
    notifyObservers();
  }
  inline void applyInverse(Transition&& transition) noexcept
  {
    State::applyTransition(transition);
    notifyObservers();
  }
  /* Template method */
  inline void applyTransition(Transition&&) = 0 noexcept;

  friend Memento<Model>;
};

/**
 * @brief A Controller that allows the undoing and redoing of Operations
 */
template <typename State>
class Memento : public Observer<typename State::Model>
{
  using TransitionType = typename State::Transition;

  State m_Target;
  Deque<TransitionType> m_RingApplied;
  Deque<TransitionType> m_RingUnapplied;

public:
  
  using MaximumStoreSize = Constant<128>;

  Memento(State target) : m_Target(target) { }

  void undo(void) noexcept 
  {
    if(m_RingApplied.empty()) return;
    TransitionType operation = m_RingApplied.front();
    m_RingApplied.pop_front();
    m_RingUnapplied.push_front(operation);
    static_assert(std::is_same_v<void(Transition&&) noexcept, typename GetMemberType<decltype(&State::applyInverse)>::type>, "void State::applyInverse(Transition&&) noexcept must be implemented to support undo operations");
    m_Target.applyInverse(operation);
  }

  void redo(void) noexcept 
  {
    if(m_RingUnapplied.empty()) return;
    TransitionType operation = m_RingUnapplied.front();
    m_RingUnapplied.pop_front();
    m_RingApplied.push_front(operation);
    static_assert(std::is_same_v<void(Transition&&) noexcept, typename GetMemberType<decltype(&State::apply)>::type>, "void State::apply(Transition&&) noexcept must be implemented to support redo operations");
    m_Target.apply(operation);
  }

private:

  void update(Transition transition) noexcept
  {
    Transition& last = m_RingApplied.front();
    m_RingUnapplied.clear()
    if constexpr(IsMergeable<State, last.getType(), transition.getType()>::value)
    {
      static_assert(std::is_same_v<Transition(const Transition&, const Transition&) noexcept, State::merge>, "Transition State::merge(const Transition&, const Transition&) noexcept must be implemented to support transition chunks");
      last = State::merge(last, transition);
    }
    else
    {
      if(m_RingApplied.size() == MaximumStoreSize::value)
      {
        m_RingApplied.pop_back();
      }
      m_RingApplied.push_front(transition);
    }
  }

  friend Observer<typename State::Model>;

};

#endif
