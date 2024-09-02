cmake_minimum_required(VERSION 3.27)

set(TARGET_NAME model)

project(${APP_NAME}${TARGET_NAME} LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick)

qt_standard_project_setup()
qt_add_library(${PROJECT_NAME})

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h include/${APP_NAME}-${TARGET_NAME}/*.h)
file(GLOB SOURCES_PLATFORM CONFIGURE_DEPENDS src/${SYSTEM_NAME}/*.cpp src/${SYSTEM_NAME}/*.h)
qt_add_qml_module(${PROJECT_NAME}
    URI
        ${DOMAIN_NAME}.${COMPANY_NAME}.${APP_NAME}.${TARGET_NAME}
    VERSION
        1.0
    SOURCES
        ${SOURCES}
        ${SOURCES_PLATFORM}
)

add_compile_definitions(ANDROID_ABI="${ANDROID_ABI}")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
        xylitol
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/${APP_NAME}-${TARGET_NAME} # This is needed by MOC, any way to get rid of it?
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
