set(TARGET_NAME Model)

project(${APP_NAME}${TARGET_NAME}Root LANGUAGES CXX)

add_subdirectory(lib/${APP_NAME}${TARGET_NAME})

add_custom_target(${PROJECT_NAME}
    SOURCES
        .gitignore
        AUTHORS
        LICENSE
        README.md
)
