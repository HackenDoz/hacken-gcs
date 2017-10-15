cmake_minimum_required(VERSION 3.3)
project(hacken-gcs CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(SOURCE
        src/main.cpp
        src/window.cpp
        src/window.h
        src/gcs_dock_widget.cpp src/gcs_dock_widget.h)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Threads REQUIRED)

include_directories(
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Core_INCLUDE_DIRS}
)

add_executable(hacken-gcs ${SOURCE})

target_link_libraries(hacken-gcs
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        ${CMAKE_THREAD_LIBS_INIT}
        )

if(WIN32)
    target_link_libraries(hacken-gcs
            user32.lib
            gdi32.lib
            dwmapi.lib
            )
endif()

# --- RUNTIME DEPENDENCIES ---
# Only necessary on Windows.

if(WIN32)
    find_program(WINDEPLOY windeployqt PATHS ${Qt5Core_DIR}/../../../bin NO_DEFAULT_PATH)

    if (WINDEPLOY)
        add_custom_command(TARGET hacken-gcs POST_BUILD
                # Call windeployqt to copy necessary dependencies into the executable path.
                COMMAND CMD /C "SET PATH=%PATH%;${QT_DIR}/bin && ${WINDEPLOY} $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>,$<CONFIG:RelWithDebInfo>>:--release> --no-translations $<TARGET_FILE:p455w0rds>"
                )
    else()
        message(WARNING "Unable to find Qt Windows deployment tool at ${Qt5Core_DIR}/../../../bin, no runtime dependencies will be copied.")
    endif()
endif()
