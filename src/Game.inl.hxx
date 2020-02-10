
#ifdef USE_AUDIO
template <typename AudioEventType>
EnableIf<ContainsType<AudioEvents, AudioEventType>, void> 
Game::GameVisitor::operator()(AudioEventType &&event)
{
  GetService<AudioMixer>().handleEvent(std::move(event));
}
#endif // USE_AUDIO

template <typename MouseEventType>
EnableIf<ContainsType<MouseEvents, MouseEventType>, void> 
Game::GameVisitor::operator()(MouseEventType &&event)
{
  GetService<MouseController>().handleEvent(std::move(event));
}

