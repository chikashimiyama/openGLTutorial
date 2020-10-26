CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

project(Juce-OpenGLTutorials VERSION 1.0.0)

add_subdirectory(glm)
add_subdirectory(JUCE)
add_subdirectory(shader)

set(COMMON_SOURCES source/Application.cpp source/MainWindow.cpp)
set(COMMON_LIBS juce::juce_gui_extra  juce::juce_opengl glm::glm shader)

juce_add_gui_app(triangle)
target_sources(triangle PRIVATE ${COMMON_SOURCES} source/triangle/GLComponent.cpp)
target_include_directories(triangle PRIVATE include include/triangle)
target_link_libraries(triangle PRIVATE ${COMMON_LIBS})

juce_add_gui_app(translate_cpu)
target_sources(translate_cpu PRIVATE ${COMMON_SOURCES} source/translate_cpu/GLComponent.cpp)
target_include_directories(translate_cpu PRIVATE include include/translate_cpu)
target_link_libraries(translate_cpu PRIVATE ${COMMON_LIBS})

juce_add_gui_app(model_cpu)
target_sources(model_cpu PRIVATE ${COMMON_SOURCES} source/model_cpu/GLComponent.cpp)
target_include_directories(model_cpu PRIVATE include include/model_cpu)
target_link_libraries(model_cpu PRIVATE ${COMMON_LIBS})

juce_add_gui_app(modelview_cpu)
target_sources(modelview_cpu PRIVATE ${COMMON_SOURCES} source/modelview_cpu/GLComponent.cpp)
target_include_directories(modelview_cpu PRIVATE include include/modelview_cpu)
target_link_libraries(modelview_cpu PRIVATE ${COMMON_LIBS})