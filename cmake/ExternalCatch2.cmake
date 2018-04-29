project(external_catch2 CXX)
include(ExternalProject)
find_package(Git REQUIRED)

set(CATCH2_EXTERNAL_ROOT ${CMAKE_BINARY_DIR}/externals/catch2)
set(CATCH2_EXTERNAL_REPO "https://github.com/philsquared/Catch.git")

ExternalProject_Add(
    catch
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
ExternalProject_Get_Property(catch source_dir)
add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE ${source_dir}/single_include)
