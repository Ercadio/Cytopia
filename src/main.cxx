#include <iostream>

#include "Game.hxx"
#include "Exception.hxx"
#include "LOG.hxx"

#include <signal.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <iomanip>

template <typename Key, typename Value>
using Mapping = std::unordered_map<Key, Value>;

void SIG_handler(int signal);

SDL_AssertState AssertionHandler(const SDL_AssertData *, void *);

void printHelp(char *);

/* @brief Configurations passed from the CLI */
struct CLIContext
{
  bool skipMenu = false;
};

void protected_main(CLIContext & cliContext)
{

  LOG(LOG_DEBUG) << "Initializing SDL subsystems";

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
  {
    LOG(LOG_ERROR) << "Failed to Init SDL";
    LOG(LOG_ERROR) << "SDL Error: " << SDL_GetError();
    exit(1);
  }

  if (TTF_Init() != 0)
  {
    LOG(LOG_ERROR) << "Failed to Init SDL_TTF";
    LOG(LOG_ERROR) << "SDL Error: " << TTF_GetError();
    exit(1);
  }

  LOG(LOG_DEBUG) << "Launching Cytopia";

  Game game;

  TTF_Quit();

  SDL_Quit();

}

/* @brief All allowed command-line parameters */
enum CLIParameters { SkipMenu, Help };

int main(int argc, char **argv)
{

  CLIContext cliContext;
  /* Register handler for Segmentation Fault, Interrupt, Terminate */
  signal(SIGSEGV, SIG_handler);
  signal(SIGINT, SIG_handler);
  signal(SIGTERM, SIG_handler);

  /* All SDL2 Assertion failures must be handled
   * by our handler */
  SDL_SetAssertionHandler(AssertionHandler, 0);

  /* First, we parse CLI parameters */
  {
    uint8_t i = 1;
    const Mapping <std::string, CLIParameters> parameter {
      { "--skipMenu", SkipMenu },
      { "--help", Help },
      { "-h", Help },
    };

    try
    {
      for(; i < argc; i++)
      {
        std::cout << argv[i] << std::endl;
        switch(parameter.at(argv[i]))
        {
          case SkipMenu:
            cliContext.skipMenu = true;
            break;
          case Help:
            printHelp(argv[0]);
            return 0;
        }
      }
    }
    catch(std::out_of_range & e)
    {
      std::cerr << "Invalid command line argument: " << argv[i] << std::endl;
      printHelp(argv[0]);
      return 1;
    }
  }
  /* Now we start the game */
  try
  {
    protected_main(cliContext);
  }
  catch (std::exception &e)
  {
    LOG(LOG_ERROR) << e.what();
    return 1;
  }
  catch (...)
  {
    LOG(LOG_ERROR) << "Caught unknown exception";
    return 1;
  }

  return 0;
}

void printHelp(char * programName)
{
  using OptionItem = std::pair<std::string, const char *>;
  const std::array options {
    OptionItem{ "--skipMenu", "Skips the main menu and starts a game immediately" },
    OptionItem{ "--help, -h", "Prints this help message" },
  };
  /* Compute maximum widths */
  size_t max_alias_width = std::max_element(options.cbegin(), options.cend(), 
      [](const OptionItem& it1, const OptionItem& it2) { 
        return it1.first.size() < it2.first.size(); })->first.size();
  
  std::cout << "Usage: " << programName << " [OPTIONS ...]\nOptions:\n";
  for(const OptionItem & item : options)
  {
    std::cout << std::left << std::setw(max_alias_width) << item.first;
    std::cout << std::setw(10) << ' ' << item.second << '\n';
  }
}
