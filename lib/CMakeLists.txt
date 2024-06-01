cmake_minimum_required(VERSION 3.27)

set(TARGET_NAME model)
set(QML_IMPORT_PATH ${QML_IMPORT_PATH} ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING "QtCreator extra QML import paths" FORCE)

project(${APP_NAME}${TARGET_NAME} LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick)

if(QT_KNOWN_POLICY_QTP0001)
    qt_policy(SET QTP0001 NEW)
endif()

qt_standard_project_setup()

qt_add_library(${PROJECT_NAME})

file(GLOB SOURCES CONFIGURE_DEPENDS *.cpp *.h include/${APP_NAME}-${TARGET_NAME}/*.h)
qt_add_qml_module(${PROJECT_NAME}
    URI
        ${DOMAIN_NAME}.${COMPANY_NAME}.${APP_NAME}.${TARGET_NAME}
    VERSION
        1.0
    OUTPUT_DIRECTORY
        ${DOMAIN_NAME}/${COMPANY_NAME}/${APP_NAME}/${TARGET_NAME}
    SOURCES
        ${SOURCES}
)

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

add_subdirectory(platform)
