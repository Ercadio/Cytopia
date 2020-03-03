#include <SDL2/SDL.h>

#include "LanguageManager.hxx"
#include "../util/LOG.hxx"
#include "../util/filesystem.hxx"

LanguageManager::LanguageManager(GameService::ServiceTuple & context, GlobalModel & model) : 
  GameService(context), m_GlobalModel(model)
{
  std::string moFilePath = getBasePath();
  moFilePath += "languages/";
  moFilePath += std::get<Settings>(m_GlobalModel).getGameLanguage();
  moFilePath += "Cytopia.mo";

  if (moFileLib::moFileReaderSingleton::GetInstance().ReadFile(moFilePath.c_str()) == moFileLib::moFileReader::EC_SUCCESS)
  {
    LOG(LOG_INFO) << "Loaded MO file " << moFilePath;
  }
  else
  {
    LOG(LOG_ERROR) << "Failed to load MO file " << moFilePath;
  }
  LOG(LOG_DEBUG) << "Created LanguageManager";
}

LanguageManager::~LanguageManager()
{
  LOG(LOG_DEBUG) << "Destroying LanguageManager";
}
