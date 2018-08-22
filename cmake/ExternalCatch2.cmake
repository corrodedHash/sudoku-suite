find_package(Catch2 QUIET)

if (NOT Catch2_FOUND)
  include(ExternalProject)
  find_package(Git REQUIRED)

  set(CATCH2_EXTERNAL_ROOT ${CMAKE_BINARY_DIR}/externals/catch2)
  set(CATCH2_EXTERNAL_REPO "https://github.com/philsquared/Catch.git")

  ExternalProject_Add(
    extlib_catch2
    PREFIX ${CATCH2_EXTERNAL_ROOT}
    GIT_REPOSITORY ${CATCH2_EXTERNAL_REPO}
    TIMEOUT 10
    #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    )

  # Expose required variable (CATCH_INCLUDE_DIR) to parent scope
  ExternalProject_Get_Property(extlib_catch2 SOURCE_DIR)
  add_library(Catch2::Catch2 INTERFACE IMPORTED)
  file(MAKE_DIRECTORY "${SOURCE_DIR}/single_include")
  add_dependencies(Catch2::Catch2 extlib_catch2)
  target_include_directories(Catch2::Catch2 SYSTEM INTERFACE ${SOURCE_DIR}/single_include)
else()
  message(STATUS "Using system Catch2")
endif()
