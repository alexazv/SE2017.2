set(ENV{ZEPHYR_BASE} /home/alexandre/Zephyr/zephyr)
set(ENV{ZEPHYR_TOOLCHAIN_VARIANT} zephyr)
set(ENV{ZEPHYR_SDK_INSTALL_DIR} /opt/zephyr-sdk)

set(BOARD "bbc_microbit")

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(FinalProject)

#message(WARNING "Main file: ${PROJECT_SOURCE_DIR}/src/main.c")

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
     "$ENV{ZEPHYR_BASE}/include"
    )

list(APPEND SOURCES
    "${PROJECT_SOURCE_DIR}/src/main.c"
    )

target_sources(app PRIVATE ${SOURCES})
