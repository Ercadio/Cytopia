#ifndef EVENTS_HXX_
#define EVENTS_HXX_

#include <string>

#include "betterEnums.hxx"
#include "util/Meta.hxx"
#include "util/TransitiveModel.hxx"
#include "engine/audio/Soundtrack.hxx"
#include "engine/audio/AudioConfig.hxx"

using std::string;

/**
 * @brief Events to be handled by the UI Loop
 */
using UIEvents = TypeList<
  struct TerminateEvent 
  /* Add UI Events here */
  >;

/**
 * @brief Events to be handled by the Game Loop
 */
using GameEvents = TypeList<
  struct TerminateEvent,
  /* All AudioEvents */
  struct AudioTriggerEvent, struct AudioTrigger3DEvent, struct AudioPlayEvent, struct AudioPlay3DEvent,
  struct AudioMusicVolumeChangeEvent, struct AudioSoundVolumeChangeEvent, struct AudioSetMutedEvent,
  struct AudioStopEvent, struct AudioPruneEvent,
  /* All MouseEvents */
  struct MousePositionEvent,
  struct ClickEvent,
  struct ScrollEvent
  /* Add Game Events here */
  >;


#include "events/AudioEvents.hxx"
#include "events/UIEvents.hxx"
#include "events/MouseEvents.hxx"

#endif
