include(FetchContent)

FetchContent_Declare(
    Catch2 
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.3
)

set(CMAKE_CXX_COMPILER "${CMAKE_CXX_COMPILER}")

FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)