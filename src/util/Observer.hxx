#ifndef OBSERVER_HXX_
#define OBSERVER_HXX_

#include <memory>
#include <forward_list>

#include "Meta.hxx"

template <typename T> using LinkedList = std::forward_list<T>;
template <typename DataArgs> struct DefaultSubjectDispatch;
template <typename DataArgs, typename DispatchPolicy = DefaultSubjectDispatch<DataArgs>> class Subject;

/**
 * @class     Observer
 * @brief     Allows to listen to another Object's
 *            events
 * @see       https://en.wikipedia.org/wiki/Observer_pattern
 * @example   test/util/Observer.cxx
 */
template <typename DataArgs> class Observer
{
public:
  using Notification = typename VariantType<DataArgs>::type;
  virtual void update(Notification) noexcept = 0;
protected:
  Observer() noexcept = default;
  virtual ~Observer() noexcept = 0;
private:
  friend DefaultSubjectDispatch<DataArgs>;
};

template <typename DataArgs> Observer<DataArgs>::~Observer() noexcept {}
template <typename DataArgs> using ObserverWPtr = std::weak_ptr<Observer<DataArgs>>;
template <typename DataArgs> using ObserverSPtr = std::shared_ptr<Observer<DataArgs>>;

template <typename DataArgs>
struct DefaultSubjectDispatch
{
  void dispatch(ObserverSPtr<DataArgs> & observer, typename Observer<DataArgs>::Notification & notification)
  {
    observer->update(notification);
  }
};

/**
 * @class     Subject
 * @brief     Allows to notify Observers about
 *            events
 * @see       https://en.wikipedia.org/wiki/Observer_pattern
 * @example   test/util/Observer.cxx
 */
template <typename DataArgs, typename DispatchPolicy> class Subject : DispatchPolicy
{
private:
  LinkedList<ObserverWPtr<DataArgs>> m_Observers;

protected:
  
  Subject(DispatchPolicy dispatch = {}) : DispatchPolicy(dispatch) { }

  using Notification = typename VariantType<DataArgs>::type;
  using ObsIterator = typename LinkedList<ObserverWPtr<Notification>>::iterator;

  using DispatchPolicy::dispatch;

  /**
   * @brief notifies all affected observers
   * @param args the data to be sent to observers
   */
  inline void notifyObservers(Notification&& notification) noexcept
  {
    ObsIterator old;
    bool mustCleanup = false;
    m_Observers.remove_if([&mustCleanup](ObserverWPtr<DataArgs> ptr) {
      if (ptr.expired())
      {
        mustCleanup = true;
        return true;
      }
      return false;
    });
    if (mustCleanup)
    {
      onObserverExpired();
    }
    for (ObserverWPtr<DataArgs> it : m_Observers)
    {
      auto observer = it.lock();
      if (mustNotify(it, notification))
      {
        dispatch(observer, notification);
      }
    }
  }

  /**
   * @nothrow
   * @brief is called whenever an observer expires
   * @details Implement this method to cleanup weak pointers
   */
  virtual inline void onObserverExpired(void) noexcept {}

  /**
   * @nothrow @racehazard
   */
  virtual ~Subject() noexcept = 0;

  /**
   * @nothrow @racehazard @const
   * @returns true if Subject should notify the observer
   * @param observer the observer to be notified
   * @param data the data to be sent to observer
   */
  virtual inline bool mustNotify(ObserverWPtr<DataArgs> observer, const Notification & data) const noexcept { return true; }

public:
  /**
   * @strong @racehazard
   * @brief Adds an observer to listen to Subject's events
   * @param observer the observer to add
   */
  inline void addObserver(ObserverSPtr<DataArgs> observer) { m_Observers.emplace_front(observer); }
};

template <typename DataArgs, typename DispatchPolicy> Subject<DataArgs, DispatchPolicy>::~Subject() noexcept {}

#endif
