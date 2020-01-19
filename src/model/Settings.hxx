#ifndef SETTINGS_HXX_
#define SETTINGS_HXX_

#include <betterEnums.hxx>
#include <bitset>

#include "../util/Model.hxx"

BETTER_ENUM(ChannelPlayback, uint8_t, Mono, Stereo, ThreeDimensional);

BETTER_ENUM(LanguageType, uint8_t, 
    English,
    Dutch,
    Hungarian,
    Portugese,
    Indonesian,
    Chinese,
    French,
    Finnish,
    Arabic,
    German,
    Russian,
    Spanish,
    Croatian,
    Czech,
    Slovak,
    Turkish
    );


using ScreenDimension = StrongType<uint32_t, struct ScreenDimensionTag>;
using VolumeLevel = StrongType<uint8_t, struct VolumeLevelTag>;
using FilePath = StrongType<std::string, struct FilePathTag>;

struct SettingsModel
{

  /**
   * @brief the screen width
   * @pre only applies for Windowed Mode
   */
  ScreenDimension desiredScreenWidth = ScreenDimension{640};

  /** 
   * @brief the screen height
   * @pre only applies for windowed mode
   */
  ScreenDimension desiredScreenHeight = ScreenDimension{480};

  /**
   * @brief the maximum elevation height
   */
  uint32_t maxElevationHeight = 255;

  /**
   * @brief the volume of music
   */
  VolumeLevel musicVolume = VolumeLevel{190};

  /**
   * @brief the volume of sound effects
   */
  VolumeLevel soundEffectsVolume = VolumeLevel{190};
  
  /**
   * @brief the number of channels used for sound playback
   */
  ChannelPlayback playback = ChannelPlayback::ThreeDimensional;

  /**
   * @brief The language of the game
   */
  LanguageType gameLanguage = LanguageType::English;

  /**
   * @brief FilePath of the Font that should be used.
   */
  FilePath fontFileName = FilePath{"??? TODO CHANGE ME"};

  /**
   * @returns true if VSync is enabled
   */
  bool getVSync() const noexcept;
  
  /**
   * @returns true if the window is in fullscreen mode
   */
  bool getFullscreen() const noexcept;
  
  /**
   * @returns true if music is allowed to play
   */
  bool getMusicAllowed() const noexcept;

  /**
   * @returns true if sound effects are allowed to play
   */
  bool getSoundEffectsAllowed() const noexcept;

protected:

  /**
   *  @brief A set of flags
   *  @details Bit(0) => VSync
   *           Bit(1) => Fullscreen
   *           Bit(2) => Music Allowed
   *           Bit(3) => Sound Fx Allowed
   */
  std::bitset<4> m_Flags = 0b1111;

};

class Settings : public Model<SettingsModel>, private SettingsModel
{

public:

  Settings();
  
  ~Settings();
 
  /**
   * @brief sets the screen width
   * @pre only applies for Windowed Mode
   */
  void setDesiredScreenWidth(ScreenDimension);

  /** 
   * @brief sets the screen height
   * @pre only applies for windowed mode
   */
  void setDesiredScreenHeight(ScreenDimension);

  /**
   * @brief sets the maximum elevation height
   */
  void setMaxElevationHeight(uint32_t);

  /**
   * @brief sets the volume of music
   */
  void setMusicVolume(VolumeLevel);

  /**
   * @brief sets the volume of sound effects
   */
  void setSoundEffectsVolume(VolumeLevel);
  
  /**
   * @brief sets the number of channels used for sound playback
   */
  void setPlayback(ChannelPlayback);
  ChannelPlayback getPlayback() const noexcept;

  /**
   * @brief sets the language of strings
   */
  void setGameLanguage(LanguageType);
  LanguageType getGameLanguage() const noexcept;

  /**
   * @brief sets the FilePath of the Font that should be used.
   */
  void setFontFileName(FilePath);

  /**
   * @brief sets if VSync is enabled
   */
  void setVSync(bool);
  
  /**
   * @brief sets if the window is in fullscreen mode
   */
  void setFullScreen(bool);
  
  /**
   * @brief sets if music is allowed to play
   */
  void setMusicAllowed(bool);

  /**
   * @brief sets if sound effects are allowed to play
   */
  void setSoundEffectsAllowed(bool);

  static constexpr const char * AudioConfigJSONFile = "resources/data/AudioConfig.json";

};

#endif // SETTINGS_HXX_
