# Build SoLoud with the miniaudio backend
add_definitions(-DWITH_MINIAUDIO)

file(GLOB SOLOUD_CORE
    src/core/*.cpp
)

file(GLOB SOLOUD_AUDIO
    src/audiosource/*.cpp
    src/audiosource/wav/*.cpp
)

# stb_vorbis (OGG loader)
set(STB_VORBIS
    src/audiosource/wav/stb_vorbis.c
)

# miniaudio backend (only .cpp here)
file(GLOB MINIAUDIO_BACKEND
    src/backend/miniaudio/*.cpp
)

add_library(soloud STATIC
    ${SOLOUD_CORE}
    ${SOLOUD_AUDIO}
    ${STB_VORBIS}
    ${MINIAUDIO_BACKEND}
)

target_include_directories(soloud PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
