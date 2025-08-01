cmake_minimum_required(VERSION 3.27)

project(${APP_NAME}${TARGET_NAME} LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Quick)

qt_standard_project_setup(
    REQUIRES 6.8
)
qt_add_library(${PROJECT_NAME})

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h include/${APP_NAME}${TARGET_NAME}/*.h)
qt_add_qml_module(${PROJECT_NAME}
    URI
        ${PROJECT_NAME}
    VERSION
        1.0
    SOURCES
        ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
        Xylitol
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/${APP_NAME}${TARGET_NAME} # This is needed by MOC, any way to get rid of it?
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        MODEL_LIBRARY
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
