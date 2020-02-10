
template <typename StateType, typename... Args>
StateType & iActivity::createState(Args &&... args)
{
  StateType* state = new StateType(std::forward(args)...);
  m_States.emplace_back(state);
  return *state;
}

template <typename ControllerType, typename... Args>
ControllerType & iActivity::createController(Args &&... args)
{
  ControllerType* controller = new ControllerType(std::forward<decltype(args)>(args)...);
  m_Controllers.emplace_back(controller);
  return *controller;
}
