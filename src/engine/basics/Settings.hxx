#ifndef SETTINGS_HXX_
#define SETTINGS_HXX_

#include <string>

#include "../../util/Singleton.hxx"
#include "../../util/Meta.hxx"

/* Settings Types */
using ScreenWidth = StrongType<int32_t, struct ScreenWidthTag>;
using ScreenHeight = StrongType<int32_t, struct ScreenHeightTag>;
using VolumeLevel = StrongType<uint8_t, struct VolumeLevelTag>;
using MapSize = StrongType<int32_t, struct MapSizeTag>;

//struct SettingsData
//{
  //SettingsData() = default;
  //~SettingsData() = default;
  /**
   * @brief the size of the map
   * @todo add a typename
   */
  //int mapSize = 0;

  /**
   * @brief the screen width
   * @pre only apply for windowed or fullscreen mode
   */
  //ScreenDimension screenWidth = 0;

  /** 
   * @brief the screen height
   * @pre only apply for windowed or fullscreen mode
   */
  //ScreenDimension screenHeight = 0;

  /** 
   * @brief the actual screen width (can differ from the one that's set in borderless fullscreen)
   */
  //ScreenDimension currentScreenWidth = 0;

  /**
   * @brief the actual screen height (can differ from the one that's set in borderless fullscreen)
   */
  //ScreenDimension currentScreenHeight = 0;

  /**
   * @brief the maximum elevation height
   * @todo add a typename
   */
  //int maxElevationHeight = 0;

  /**
   * @todo document what this field is
   * @todo add a typename
   */
  //bool vSync = true;

  /**
   * @todo document what this field is
   * @todo add a typename
   */
  //bool fullScreen = false;

  /**
   * @todo document what this field is
   * @todo add a typename
   */
  //int fullScreenMode = 0;

  /**
   * @brief the volume of music
   */
  //VolumeLevel musicVolume = 255;

  /**
   * @brief the volume of sound effects
   */
  //VolumeLevel soundEffectsVolume = 255;

  /**
   * @todo document what this field is
   * @todo add a typename
   */
  //bool playMusic = true;

  /**
   * @todo document what this field is
   * @todo add a typename
   */
  //bool playSoundEffects = true;

  /**
   * @todo document what this field is
   * @todo add a typename
   */
  //int audioChannels = 0;

  /**
   * @todo document what this field is
   * @todo add a typename
   * @todo replace by enum when BetterEnums is implemented
   */
  //std::string buildMenuPosition = "";

  /**
   * @brief JSONFile that contains uiData
   * @todo add a typename
   */
  //std::string uiDataJSONFile = "";

  /**
   * @brief JSONFile that contains tileData
   * @todo add a typename
   */
  //std::string tileDataJSONFile = "";

  /**
   * @todo document what this field is
   * @todo add a typename
   */
  //std::string uiLayoutJSONFile = "";

  /**
   * @brief The Game language 
   */
  //std::string gameLanguage = "";

  /**
   * @brief FileName of the Font that should be used.
   */
  //std::string fontFileName = "";
//};

/**
 * @class Settings
 * @brief the settings of the client
 */
class Settings : public Singleton<Settings>
{
public:
  friend Singleton<Settings>;

  /**
   * @brief Load settings from file
   */
  void readFile();

  /**
   * @brief Save settings to file
   */
  void writeFile();

  template<typename SettingType>
  SettingType& get() noexcept { return std::get<SettingType>(m_Data); }
  
  template<typename SettingType>
  const SettingType& get() const noexcept { return std::get<SettingType>(m_Data); }

private:
  using SettingTypes = TypeList<
    ScreenWidth, ScreenHeight, MapSize
    /* Add your type here */>;
  using SettingsData = TupleType<SettingTypes>::type;
  SettingsData m_Data = { };
  Settings();
  ~Settings() = default;
};

#endif
