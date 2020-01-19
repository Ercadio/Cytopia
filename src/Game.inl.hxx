
template <typename ArgumentType> void Game::UIVisitor::operator()(ArgumentType &&event)
{
  static_assert(std::is_void_v<std::void_t<ArgumentType>>,
                "UIVisitor does not know how to handle this event. You must specialize the functor");
}

#ifdef USE_AUDIO
template <typename AudioEventType>
EnableIf<ContainsType<AudioEvents, AudioEventType>, void> Game::GameVisitor::operator()(AudioEventType &&event)
{
  GetService<AudioMixer>().handleEvent(std::move(event));
}
#endif // USE_AUDIO

template <typename MouseEventType>
EnableIf<ContainsType<MouseEvents, MouseEventType>, void> Game::GameVisitor::operator()(MouseEventType &&event)
{
  GetService<MouseController>().handleEvent(std::move(event));
}

template <typename ArgumentType> void Game::GameVisitor::operator()(const ArgumentType &&event)
{
  throw UnimplementedError(TRACE_INFO "Unimplemented Error");
}
