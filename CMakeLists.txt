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

juce_add_gui_app(modelviewprojection_cpu)
target_sources(modelviewprojection_cpu PRIVATE ${COMMON_SOURCES} source/modelviewprojection_cpu/GLComponent.cpp)
target_include_directories(modelviewprojection_cpu PRIVATE include include/modelviewprojection_cpu)
target_link_libraries(modelviewprojection_cpu PRIVATE ${COMMON_LIBS})

juce_add_gui_app(modelviewprojection_gpu)
target_sources(modelviewprojection_gpu PRIVATE ${COMMON_SOURCES} source/modelviewprojection_gpu/GLComponent.cpp)
target_include_directories(modelviewprojection_gpu PRIVATE include include/modelviewprojection_gpu)
target_link_libraries(modelviewprojection_gpu PRIVATE ${COMMON_LIBS})

juce_add_gui_app(animation)
target_sources(animation PRIVATE ${COMMON_SOURCES} source/animation/GLComponent.cpp)
target_include_directories(animation PRIVATE include include/animation)
target_link_libraries(animation PRIVATE ${COMMON_LIBS})