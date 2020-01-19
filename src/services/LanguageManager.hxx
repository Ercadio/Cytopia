#ifndef LANGUAGE_MANAGER_HXX
#define LANGUAGE_MANAGER_HXX

#include "../GameService.hxx"
#include "moFileReader.h"
#include "../model/Settings.hxx"
#include "../GlobalModel.hxx"

class LanguageManager : public GameService
{

  moFileLib::moFileReader reader;
  GlobalModel & m_GlobalModel;

public:

  LanguageManager(GameService::ServiceTuple &, GlobalModel &);
  ~LanguageManager();

};

#endif // LANGUAGE_MANAGER_HXX
