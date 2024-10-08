set(TARGET_NAME model)

project(${APP_NAME}${TARGET_NAME}-root LANGUAGES CXX)

add_subdirectory(lib)

add_custom_target(${PROJECT_NAME}
    SOURCES
        .gitignore
        AUTHORS
        LICENSE
        README.md
)
