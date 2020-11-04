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
set_target_properties(triangle PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

juce_add_gui_app(translate_cpu)
target_sources(translate_cpu PRIVATE ${COMMON_SOURCES} source/translate_cpu/GLComponent.cpp)
target_include_directories(translate_cpu PRIVATE include include/translate_cpu)
target_link_libraries(translate_cpu PRIVATE ${COMMON_LIBS})
set_target_properties(translate_cpu PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

juce_add_gui_app(model_cpu)
target_sources(model_cpu PRIVATE ${COMMON_SOURCES} source/model_cpu/GLComponent.cpp)
target_include_directories(model_cpu PRIVATE include include/model_cpu)
target_link_libraries(model_cpu PRIVATE ${COMMON_LIBS})
set_target_properties(model_cpu PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

juce_add_gui_app(modelviewprojection_cpu)
target_sources(modelviewprojection_cpu PRIVATE ${COMMON_SOURCES} source/modelviewprojection_cpu/GLComponent.cpp)
target_include_directories(modelviewprojection_cpu PRIVATE include include/modelviewprojection_cpu)
target_link_libraries(modelviewprojection_cpu PRIVATE ${COMMON_LIBS})
set_target_properties(modelviewprojection_cpu PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

juce_add_gui_app(modelviewprojection_gpu)
target_sources(modelviewprojection_gpu PRIVATE ${COMMON_SOURCES} source/modelviewprojection_gpu/GLComponent.cpp)
target_include_directories(modelviewprojection_gpu PRIVATE include include/modelviewprojection_gpu)
target_link_libraries(modelviewprojection_gpu PRIVATE ${COMMON_LIBS})
set_target_properties(modelviewprojection_gpu PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

juce_add_gui_app(animation)
target_sources(animation PRIVATE ${COMMON_SOURCES} source/animation/GLComponent.cpp)
target_include_directories(animation PRIVATE include include/animation)
target_link_libraries(animation PRIVATE ${COMMON_LIBS})
set_target_properties(animation PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

juce_add_gui_app(depth)
target_sources(depth PRIVATE ${COMMON_SOURCES} source/depth/GLComponent.cpp)
target_include_directories(depth PRIVATE include include/depth)
target_link_libraries(depth PRIVATE ${COMMON_LIBS})
set_target_properties(depth PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

juce_add_gui_app(varying)
target_sources(varying PRIVATE ${COMMON_SOURCES} source/varying/GLComponent.cpp)
target_include_directories(varying PRIVATE include include/varying)
target_link_libraries(varying PRIVATE ${COMMON_LIBS})
set_target_properties(varying PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

juce_add_gui_app(attributes)
target_sources(attributes PRIVATE ${COMMON_SOURCES} source/attributes/GLComponent.cpp)
target_include_directories(attributes PRIVATE include include/attributes)
target_link_libraries(attributes PRIVATE ${COMMON_LIBS})
set_target_properties(attributes PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

juce_add_gui_app(lighting)
target_sources(lighting PRIVATE ${COMMON_SOURCES} source/lighting/GLComponent.cpp)
target_include_directories(lighting PRIVATE include include/lighting)
target_link_libraries(lighting PRIVATE ${COMMON_LIBS})
set_target_properties(lighting PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

juce_add_gui_app(culling)
target_sources(culling PRIVATE ${COMMON_SOURCES} source/culling/GLComponent.cpp)
target_include_directories(culling PRIVATE include include/culling)
target_link_libraries(culling PRIVATE ${COMMON_LIBS})
set_target_properties(culling PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

juce_add_gui_app(texture)
target_sources(texture PRIVATE ${COMMON_SOURCES} source/texture/GLComponent.cpp)
target_include_directories(texture PRIVATE include include/texture)
target_link_libraries(texture PRIVATE ${COMMON_LIBS})
set_target_properties(texture PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

juce_add_gui_app(blur)
target_sources(blur PRIVATE ${COMMON_SOURCES} source/blur/GLComponent.cpp)
target_include_directories(blur PRIVATE include include/blur)
target_link_libraries(blur PRIVATE ${COMMON_LIBS})
set_target_properties(blur PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

