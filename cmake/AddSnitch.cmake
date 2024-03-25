include(FetchContent)

FetchContent_Declare(snitch
                     GIT_REPOSITORY https://github.com/snitch-org/snitch.git
                     GIT_TAG        v1.2.4)
FetchContent_MakeAvailable(snitch)

list(APPEND CMAKE_MODULE_PATH ${snitch_SOURCE_DIR}/extras)