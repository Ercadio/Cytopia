set(SOURCE_FILES
  Events.hxx
  Game.cxx
  Game.hxx
  Game.inl.hxx
  GameService.cxx
  GameService.hxx
  GameService.inl.hxx
  GlobalModel.hxx
  Scripting/ScriptEngine.cxx
  Scripting/ScriptEngine.hxx
  Windows/cytopia.ico
  Windows/icon_cytopia.rc
  Windows/icon_tiledataeditor.rc
  Windows/resource.h
  Windows/tiledataeditor.ico
  engine/DefaultGenerator.hxx
  engine/DefaultGenerator.cxx
  engine/MessageQueue.hxx
  engine/MessageQueue.inl.hxx
  engine/iGenerator.hxx
  engine/iGenerator.cxx
  events/MouseEvents.cxx
  events/MouseEvents.hxx
  events/UIEvents.hxx
  main.cxx
  model/Map.cxx
  model/Map.hxx
  model/Map.inl.hxx
  model/MapEditor.cxx
  model/MapEditor.hxx
  model/MousePosition.cxx
  model/MousePosition.hxx
  model/Settings.hxx
  model/Settings.cxx
  services/GameClock.cxx
  services/GameClock.hxx
  services/GameClock.inl.hxx
  services/LanguageManager.cxx
  services/LanguageManager.hxx
  services/MouseController.cxx
  services/MouseController.hxx
  services/Randomizer.cxx
  services/Randomizer.hxx
  services/ResourceManager.cxx
  services/ResourceManager.hxx
  services/ResourceManager.inl.hxx
  util/Exception.cxx
  util/Exception.hxx
  util/IEquatable.hxx
  util/IEquatable.inl.hxx
  util/LOG.cxx
  util/LOG.hxx
  util/LOG.inl.hxx
  util/Meta.hxx
  util/Model.hxx
  util/Observer.hxx
  util/Point.cxx
  util/Point.hxx
  util/Singleton.hxx
  util/filesystem.hxx
  view/AbsoluteLayout.hxx
  view/AbsoluteLayout.cxx
  view/BoxSizing.hxx
  view/BoxSizing.inl.hxx
  view/BoxSizing.cxx
  view/ButtonWidget.cxx
  view/ButtonWidget.hxx
  view/MainMenuActivity.cxx
  view/MainMenuActivity.hxx
  view/iRenderer.hxx
  view/iRenderer.cxx
  view/Shape.hxx
  view/Shape.cxx
  view/Window.cxx
  view/Window.hxx
  view/iActivity.cxx
  view/iActivity.hxx
  view/iLayout.hxx
  view/iLayout.cxx
  view/iView.hxx
  view/iView.cxx
  view/iWidget.hxx
  view/iWidget.cxx
  view/SDLRenderer.hxx
  view/SDLRenderer.cxx
  )

list(APPEND _include_directories
  engine
  util
  events
  model
  services
  util
  view
  )

if (ENABLE_AUDIO)
  list(APPEND SOURCE_FILES
    engine/audio/Soundtrack.{hxx,cxx}
    services/AudioMixer.{hxx,cxx}
    events/AudioEvents.hxx
    )
endif ()

if (ENABLE_ANGELSCRIPT)
  list(APPEND SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/external/as_add_on/scriptbuilder/scriptbuilder.cpp
    ${CMAKE_SOURCE_DIR}/external/as_add_on/scriptbuilder/scriptbuilder.h
    ${CMAKE_SOURCE_DIR}/external/as_add_on/scriptstdstring/scriptstdstring.h
    ${CMAKE_SOURCE_DIR}/external/as_add_on/scriptstdstring/scriptstdstring.cpp
    Scripting/ScriptEngine.{hxx,cxx}
    )
endif ()

if (ENABLE_MICROPROFILE)
  list(APPEND SOURCE_FILES
    ${microprofile_SOURCE_DIR}/microprofile.h
    ${microprofile_SOURCE_DIR}/microprofile_html.h
    ${microprofile_SOURCE_DIR}/microprofile.cpp
    )
endif (ENABLE_MICROPROFILE)

# Expand file extensions (i.e. path/to/file.{h,cpp} becomes path/to/file.h;path/to/file.cpp)
expand_file_extensions(SOURCE_FILES ${SOURCE_FILES})

# Generate source groups for use in IDEs
generate_source_groups(${SOURCE_FILES})

set(MAIN_EXE_SOURCE_FILES "${SOURCE_FILES}" PARENT_SCOPE)

if (MSVC)
  set(SOURCE_FILES ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/src/Windows/icon_cytopia.rc)
endif ()

if (APPLE)
  file(GLOB_RECURSE MAC_RESOURCE_FILES ${CMAKE_SOURCE_DIR}/data/resources/*)

  # not working now, we need a special icon file for apple
  set(ICON_PATH ${CMAKE_SOURCE_DIR}/data/resources/images/app_icons/cytopia_icon_iso.icns)
  set(MACOSX_BUNDLE_ICON_FILE cytopia_icon_iso.icns)

  # set each file as resources file for the app image.
  foreach (resources_file ${MAC_RESOURCE_FILES})
    get_filename_component(buildDirRelFilePath ${resources_file} DIRECTORY)
    string(REPLACE "${CMAKE_SOURCE_DIR}/" "" buildDirRelFilePath ${buildDirRelFilePath})
    set_source_files_properties(${resources_file} PROPERTIES MACOSX_PACKAGE_LOCATION Resources/${buildDirRelFilePath})
  endforeach ()
  # set_source_files_properties(${PROJECT_SOURCE_DIR}/Cytopia_Resources/music  PROPERTIES MACOSX_PACKAGE_LOCATION Resources/resources/audio/music)
  set_source_files_properties(${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
  set_source_files_properties(${myApp_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

  add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCE_FILES} ${ICON_PATH} ${MAC_RESOURCE_FILES})
else ()
  # create a new executable with the same name as the project
  add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif ()

# enable C++17
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO)

list(APPEND _compile_definitions VERSION="${PROJECT_NAME} ${PROJECT_VERSION} - tech preview")


target_include_directories(${PROJECT_NAME} PRIVATE ${_include_directories})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${_compile_definitions})
target_link_libraries(${PROJECT_NAME} PRIVATE ${_link_libraries})

# copy the resources to the compiled directory

add_custom_target(
  copy_resources
  ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/resources/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/ 
  COMMENT "Copy the resources to the compiled directory"
  VERBATIM
  )

if (MSVC)
  # set startup project for Visual Studio Builds
  set_property(
    DIRECTORY ${PROJECT_SOURCE_DIR}
    PROPERTY
    VS_STARTUP_PROJECT ${PROJECT_NAME}
    )
  # set Visual Studio working directory to the Configuration directory
  set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/$(Configuration)"
    )
endif ()

install(TARGETS ${PROJECT_NAME} DESTINATION .)
if (NOT APPLE)
  install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/resources/ DESTINATION resources)
endif ()

install(FILES ${CMAKE_SOURCE_DIR}/ReleaseNotes.txt ${CMAKE_SOURCE_DIR}/credits.txt DESTINATION .)

if (APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE RESOURCE TRUE)
endif ()
