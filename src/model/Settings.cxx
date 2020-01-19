#include "Settings.hxx"
#include "../util/LOG.hxx"

bool SettingsModel::getVSync() const noexcept { return m_Flags[0]; }
bool SettingsModel::getFullscreen() const noexcept { return m_Flags[1]; }
bool SettingsModel::getMusicAllowed() const noexcept { return m_Flags[2]; }
bool SettingsModel::getSoundEffectsAllowed() const noexcept { return m_Flags[3]; }

Settings::Settings() : SettingsModel()
{ }

Settings::~Settings() 
{
  LOG(LOG_DEBUG) << "Destroying Settings";
}

void Settings::setDesiredScreenWidth(ScreenDimension sd)
{ 
  SettingsModel sm{*this};
  desiredScreenWidth = sd;
  notifyObservers(ChangeNotification{sm, static_cast<SettingsModel &>(*this)});
}

void Settings::setDesiredScreenHeight(ScreenDimension sd)
{ 
  std::swap(desiredScreenHeight, sd);
}

void Settings::setMaxElevationHeight(uint32_t maxElevation)
{ 
  std::swap(maxElevationHeight, maxElevation);
}

void Settings::setMusicVolume(VolumeLevel vl)
{ 
  std::swap(musicVolume, vl);
}

void Settings::setSoundEffectsVolume(VolumeLevel vl)
{ 
  std::swap(soundEffectsVolume, vl);
}

void Settings::setPlayback(ChannelPlayback cp)
{ 
  std::swap(playback, cp);
}

ChannelPlayback Settings::getPlayback() const noexcept { return playback; }

void Settings::setGameLanguage(LanguageType lang)
{ 
  std::swap(gameLanguage, lang);
}

LanguageType Settings::getGameLanguage() const noexcept
{
  return gameLanguage; 
}

void Settings::setFontFileName(FilePath fp)
{ 
  std::swap(fontFileName, fp);
}

void Settings::setVSync(bool vsync)
{
  bool tmp = vsync;
  vsync = m_Flags[0];
  m_Flags[0] = tmp;
}

void Settings::setFullScreen(bool fs)
{ 
  bool tmp = fs;
  fs = m_Flags[1];
  m_Flags[1] = tmp;
}

void Settings::setMusicAllowed(bool music)
{ 
  bool tmp = music;
  music = m_Flags[2];
  m_Flags[2] = tmp;
}

void Settings::setSoundEffectsAllowed(bool fx)
{ 
  bool tmp = fx;
  fx = m_Flags[3];
  m_Flags[3] = tmp;
}
