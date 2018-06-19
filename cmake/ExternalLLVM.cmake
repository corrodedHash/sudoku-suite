include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_ADD(
  #--External-project-name------
  download_llvm_6_0
  #--Core-directories-----------
  PREFIX             ${CMAKE_BINARY_DIR}/externals/llvm
  #--Download step--------------
  GIT_REPOSITORY     "https://github.com/llvm-mirror/llvm.git"
  GIT_SHALLOW 1
  GIT_TAG release_60
  TIMEOUT            10
  LOG_DOWNLOAD       ON

  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
  )

ExternalProject_Get_Property(download_llvm_6_0 SOURCE_DIR)

ExternalProject_ADD(
  download_libcxx_6_0
  SOURCE_DIR ${SOURCE_DIR}/projects/libcxx

  #--Download step--------------
  GIT_REPOSITORY     "https://github.com/llvm-mirror/libcxx.git"
  GIT_SHALLOW 1
  GIT_TAG release_60
  TIMEOUT            10
  LOG_DOWNLOAD       ON

  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""

  DEPENDS download_llvm_6_0
  )

ExternalProject_ADD(
  download_libcxxabi_6_0
  SOURCE_DIR ${SOURCE_DIR}/projects/libcxxabi

  #--Download step--------------
  GIT_REPOSITORY     "https://github.com/llvm-mirror/libcxxabi.git"
  GIT_SHALLOW 1
  GIT_TAG release_60
  TIMEOUT            10
  LOG_DOWNLOAD       ON

  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""

  DEPENDS download_llvm_6_0
  )
