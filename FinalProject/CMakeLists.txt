set(ENV{ZEPHYR_BASE} /home/alexandre/Zephyr/zephyr)
set(ENV{ZEPHYR_TOOLCHAIN_VARIANT} zephyr)
set(ENV{ZEPHYR_SDK_INSTALL_DIR} /opt/zephyr-sdk)

set(BOARD "bbc_microbit")

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
#include($ENV{ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
project(FinalProject)

#message(WARNING "Main file: ${PROJECT_SOURCE_DIR}/src/main.c")

# Generate version file
include(build.version.cmake NO_POLICY_SCOPE)

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
     "$ENV{ZEPHYR_BASE}/include"
    )

#FILE(GLOB app_sources src/*.c)

list(APPEND SOURCES
   "${PROJECT_SOURCE_DIR}/src/main.c"
   "${PROJECT_SOURCE_DIR}/src/view/display.c"
   "${PROJECT_SOURCE_DIR}/src/view/i2c_device.c"
   "${PROJECT_SOURCE_DIR}/src/view/i2c_util.c"
   "${PROJECT_SOURCE_DIR}/src/view/thermometer.c"
   "${PROJECT_SOURCE_DIR}/src/view/button.c"
   
#"${PROJECT_SOURCE_DIR}/src/controller/bas.c"
#"${PROJECT_SOURCE_DIR}/src/controller/dis.c"
#"${PROJECT_SOURCE_DIR}/src/controller/bluetooth.c"
#"${PROJECT_SOURCE_DIR}/src/controller/bluetooth_hci_usart.c"

   "${PROJECT_SOURCE_DIR}/src/model/compass.c"
   "${PROJECT_SOURCE_DIR}/src/model/accelerometer.c"
   "${PROJECT_SOURCE_DIR}/src/model/state_machine.c"
 )


# Schedule a new version file generation after every build
add_custom_command(
    TARGET app
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}"
    -DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}
    -DPROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}
    -P ${PROJECT_SOURCE_DIR}/build.version.cmake
    )

target_sources(app PRIVATE ${SOURCES})
