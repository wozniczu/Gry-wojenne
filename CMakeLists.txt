cmake_minimum_required(VERSION 3.22)
project(projekt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/third_party/SFML-3.0.0-msvc-x64")
  else()
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/third_party/SFML-3.0.0-msvc-x86")
  endif()
endif()

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio Network)

set(SOURCES
  main.cpp
  src/Archer.cpp
  src/Assets.cpp
  src/Battle.cpp
  src/ButtonSFML.cpp
  src/Cavalry.cpp
  src/Infantry.cpp
  src/MainWindow.cpp
  src/SliderSFML.cpp
  src/Unit.cpp
)

add_executable(projekt ${SOURCES})
target_include_directories(projekt PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(projekt PRIVATE
  SFML::Graphics
  SFML::Window
  SFML::System
  SFML::Audio
  SFML::Network
)

if(MSVC)
  target_compile_definitions(projekt PRIVATE SFML_DYNAMIC)
endif()

if(CMAKE_CONFIGURATION_TYPES)
  foreach(cfg ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${cfg}" cfgU)
    set_target_properties(projekt PROPERTIES
      "RUNTIME_OUTPUT_DIRECTORY_${cfgU}" "${CMAKE_BINARY_DIR}/bin/${cfg}")
  endforeach()
else()
  set_target_properties(projekt PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

if(WIN32)
  get_filename_component(_sfml_root "${SFML_DIR}/../../.." ABSOLUTE)
  set(_sfml_bin "${_sfml_root}/bin")
  add_custom_command(TARGET projekt POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${_sfml_bin}" "$<TARGET_FILE_DIR:projekt>"
    COMMENT "Kopiowanie DLL SFML obok pliku wykonywalnego"
    VERBATIM)
endif()
