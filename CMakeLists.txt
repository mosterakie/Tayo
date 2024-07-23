cmake_minimum_required(VERSION 3.20)

# Set the project name
project(Tayo VERSION 1.0 LANGUAGES CXX C)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
    # MSVC specific options
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
    add_compile_options(/EHsc)
else()
    # Non-MSVC specific options
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
endif()


add_compile_definitions(TY_PLATFORM_WINDOWS)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

########################################################################
# For GTK
# option(TY_BUILD_LINUX "Build Tayo to run on Linux platforms using GTK specific APIs" OFF)
# if (TY_BUILD_LINUX)
#   # The `pkg_check_modules` function is created with this call
#   find_package(PkgConfig REQUIRED)

#   # These calls create special `PkgConfig::<MODULE>` variables
#   pkg_check_modules(GTKMM_PKG IMPORTED_TARGET gtkmm-3.0)
# endif()

########################################################################
# To use GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${Tayo_SOURCE_DIR}/Tayo/vendor/GLFW)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
add_subdirectory(${Tayo_SOURCE_DIR}/Tayo/vendor/glm)
find_package(OpenGL REQUIRED)

# add_subdirectory(${Tayo_SOURCE_DIR}/Tayo/vendor/yaml-cpp)
# set(YAML_CPP_BUILD_TESTS=OFF CACHE BOOL "" FORCE)

########################################################################
# CXX FLAGS
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -DGLFW_INCLUDE_NONE")
set(CMAKE_CXX_FLAGS "-DGLFW_INCLUDE_NONE")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DTY_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

########################################################################
# For Vulkan support
# find_package(Vulkan REQUIRED COMPONENTS glslang shaderc_combined SPIRV-Tools)

# if(NOT Vulkan_FOUND)
#   message(FATAL_ERROR "Vulkan::Vulkan was NOT found!")
# endif()

#add_library(glslang_lib INTERFACE)
#if(Vulkan_glslang_FOUND)
#  message("Vulkan::glslang was found!")
#  target_link_libraries(glslang_lib Vulkan::glslang)
#else()
#  message("Vulkan::glslang was NOT found!")
#  message(" Attempting to set manually...")
#  add_library(glslang_tmp STATIC IMPORTED)
#  set_target_properties(glslang_tmp PROPERTIES
#    IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libglslang.a"
#    INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
#  )
#  target_link_libraries(glslang_lib INTERFACE
#    glslang_tmp
#  )
#endif()

# add_library(shaderc_combined_lib INTERFACE)
# if(Vulkan_shaderc_combined_FOUND)
#   target_link_libraries(shaderc_combined_lib Vulkan::shaderc_combined)
# else()
#   message("Vulkan::shaderc_combined was NOT found!")
#   message(" Attempting to set manually...")
#   add_library(shaderc_combined_tmp STATIC IMPORTED)
#   set_target_properties(shaderc_combined_tmp PROPERTIES
#     IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libshaderc_combined.a"
#     INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
#   )
#   target_link_libraries(shaderc_combined_lib INTERFACE
#     shaderc_combined_tmp
#   )
# endif()

#add_library(SPIRV-Tools_lib INTERFACE)
#if(Vulkan_SPIRV-Tools_FOUND)
#  message("Vulkan::SPIRV-Tools was found!")
#  target_link_libraries(SPIRV-Tools_lib Vulkan::SPIRV-Tools)
#else()
#  message("Vulkan::SPIRV-Tools was NOT found!")
#  message(" Attempting to set manually...")
#  add_library(SPIRV-Tools_tmp STATIC IMPORTED)
#  set_target_properties(SPIRV-Tools_tmp PROPERTIES
#    IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libSPIRV-Tools.a"
#    INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
#  )
#  target_link_libraries(SPIRV-Tools_lib INTERFACE
#    SPIRV-Tools_tmp
#  )
#endif()

########################################################################
# For spirv-cross
# add_library(spirv-cross INTERFACE)

# add_library(spirv-cross-c_lib STATIC IMPORTED)
# set_target_properties(spirv-cross-c_lib PROPERTIES
#   IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-c.a"
#   INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
# )
# add_library(spirv-cross-core_lib STATIC IMPORTED)
# set_target_properties(spirv-cross-core_lib PROPERTIES
#   IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-core.a"
#   INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
# )
# add_library(spirv-cross-cpp_lib STATIC IMPORTED)
# set_target_properties(spirv-cross-cpp_lib PROPERTIES
#   IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-cpp.a"
#   INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
# )
# add_library(spirv-cross-glsl_lib STATIC IMPORTED)
# set_target_properties(spirv-cross-glsl_lib PROPERTIES
#   IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-glsl.a"
#   INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
# )
# add_library(spirv-cross-hlsl_lib STATIC IMPORTED)
# set_target_properties(spirv-cross-hlsl_lib PROPERTIES
#   IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-hlsl.a"
#   INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
# )
# add_library(spirv-cross-msl_lib STATIC IMPORTED)
# set_target_properties(spirv-cross-msl_lib PROPERTIES
#   IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-msl.a"
#   INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
# )
# add_library(spirv-cross-reflect_lib STATIC IMPORTED)
# set_target_properties(spirv-cross-reflect_lib PROPERTIES
#   IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-reflect.a"
#   INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
# )
# add_library(spirv-cross-util_lib STATIC IMPORTED)
# set_target_properties(spirv-cross-util_lib PROPERTIES
#   IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-util.a"
#   INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
# )

# target_link_libraries(spirv-cross INTERFACE
#   spirv-cross-c_lib
#   spirv-cross-core_lib
#   spirv-cross-cpp_lib
#   spirv-cross-glsl_lib
#   spirv-cross-hlsl_lib
#   spirv-cross-msl_lib
#   spirv-cross-reflect_lib
#   spirv-cross-util_lib
# )

########################################################################
# For Box2D support
# set(BOX2D_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
# set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
# add_subdirectory(${Tayo_SOURCE_DIR}/Tayo/vendor/Box2D)

########################################################################
# For Mono support
# option(TY_BUILD_LINUX "Build Tayo to run on Linux platforms using Mono specific APIs" OFF)
# if (TY_BUILD_LINUX)
#   # These calls create special `PkgConfig::<MODULE>` variables
#   pkg_check_modules(MONO_PKG IMPORTED_TARGET mono-2 monosgen-2)
# endif()

#add_library(MONO INTERFACE)
##add_library(mono-btls-shared_so SHARED IMPORTED)
##add_library(mono-llvm_so SHARED IMPORTED)
##add_library(mono-native_so SHARED IMPORTED)
##add_library(MonoPosixHelper_so SHARED IMPORTED)
#add_library(monosgen-2.0_so SHARED IMPORTED)
##add_library(MonoSupportW_so SHARED IMPORTED)
##set_target_properties(mono-btls-shared_so PROPERTIES
##  IMPORTED_LOCATION "/usr/lib/libmono-btls-shared.so"
##  INTERFACE_INCLUDE_DIRECTORIES "/usr/include/mono-2.0"
##)
##set_target_properties(mono-llvm_so PROPERTIES
##  IMPORTED_LOCATION "/usr/lib/libmono-llvm.so"
##  INTERFACE_INCLUDE_DIRECTORIES "/usr/include/mono-2.0"
##)
##set_target_properties(mono-native_so PROPERTIES
##  IMPORTED_LOCATION "/usr/lib/libmono-native.so"
##  INTERFACE_INCLUDE_DIRECTORIES "/usr/include/mono-2.0"
##)
##set_target_properties(MonoPosixHelper_so PROPERTIES
##  IMPORTED_LOCATION "/usr/lib/libMonoPosixHelper.so"
##  INTERFACE_INCLUDE_DIRECTORIES "/usr/include/mono-2.0"
##)
#set_target_properties(monosgen-2.0_so PROPERTIES
#  IMPORTED_LOCATION "/usr/lib/libmonosgen-2.0.so"
#  INTERFACE_INCLUDE_DIRECTORIES "/usr/include/mono-2.0"
#)
##set_target_properties(MonoSupportW_so PROPERTIES
##  IMPORTED_LOCATION "/usr/lib/libMonoSupportW.so"
##  INTERFACE_INCLUDE_DIRECTORIES "/usr/include/mono-2.0"
##)
#target_link_libraries(MONO INTERFACE
#  monosgen-2.0_so
#  #mono-btls-shared_so mono-llvm_so mono-native_so MonoPosixHelper MonoSupportW
#)

########################################################################
# Include directories
include_directories(
  ${Tayo_SOURCE_DIR}/Tayo/src
  ${Tayo_SOURCE_DIR}/Tayo/vendor
  ${Tayo_SOURCE_DIR}/Tayo/vendor/spdlog/include
  ${Tayo_SOURCE_DIR}/Tayo/vendor/GLFW/include
  ${Tayo_SOURCE_DIR}/Tayo/vendor/Glad/include
  ${Tayo_SOURCE_DIR}/Tayo/vendor/imgui
  ${Tayo_SOURCE_DIR}/Tayo/vendor/glm
  ${Tayo_SOURCE_DIR}/Tayo/vendor/stb_image
#   ${Tayo_SOURCE_DIR}/Tayo/vendor/entt/include
#   ${Tayo_SOURCE_DIR}/Tayo/vendor/yaml-cpp/include
#   ${Tayo_SOURCE_DIR}/Tayo/vendor/ImGuizmo
#   ${Tayo_SOURCE_DIR}/Tayo/vendor/Box2D/include
#   ${Tayo_SOURCE_DIR}/Tayo/vendor/filewatch
)

########################################################################
# Compile C# scripts
# add_subdirectory(${Tayo_SOURCE_DIR}/Tayo-ScriptCore)
# add_subdirectory(${Tayo_SOURCE_DIR}/Tayonut/SandboxProject/Assets/Scripts)

########################################################################
# Add libraries
# add_library(ImGuizmo
#   ${Tayo_SOURCE_DIR}/Tayo/vendor/ImGuizmo/ImGuizmo.cpp
# )

add_library(stb_image
  ${Tayo_SOURCE_DIR}/Tayo/vendor/stb_image/stb_image.cpp
)

add_library(glad
  ${Tayo_SOURCE_DIR}/Tayo/vendor/Glad/src/glad.c
)

add_library(imgui
  ${Tayo_SOURCE_DIR}/Tayo/vendor/imgui/imgui.cpp
  ${Tayo_SOURCE_DIR}/Tayo/vendor/imgui/imgui_draw.cpp
  ${Tayo_SOURCE_DIR}/Tayo/vendor/imgui/imgui_tables.cpp
  ${Tayo_SOURCE_DIR}/Tayo/vendor/imgui/imgui_widgets.cpp
  ${Tayo_SOURCE_DIR}/Tayo/vendor/imgui/imgui_demo.cpp
)

# add_library(TY_Tayo_Project
#   ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Project/ProjectSerializer.cpp
#   ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Project/Project.cpp
# )

# add_library(TY_Tayo_Scripting
#   ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Scripting/ScriptGlue.cpp
#   ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Scripting/ScriptEngine.cpp
# )

# add_library(TY_Tayo_Math
#   ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Math/Math.cpp
# )

# add_library(TY_Tayo_Scene
#   ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Scene/Scene.cpp
#   ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Scene/Entity.cpp
#   ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Scene/SceneCamera.cpp
#   ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Scene/SceneSerializer.cpp
# )

add_library(TY_Tayo_ImGui
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/ImGui/ImGuiLayer.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/ImGui/ImGuiBuild.cpp
)

add_library(TY_Tayo_Renderer
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/Shader.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/Buffer.cpp
  # ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/GraphicsContext.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/Renderer.cpp
  # ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/Renderer2D.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/VertexArray.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/RenderCommand.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/RendererAPI.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/OrthographicCamera.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/Texture.cpp
  # ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/OrthographicCameraController.cpp
  # ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/Framebuffer.cpp
  # ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/EditorCamera.cpp
  # ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Renderer/UniformBuffer.cpp
)

add_library(TY_Platform_OpenGL
  ${Tayo_SOURCE_DIR}/Tayo/src/Platform/OpenGL/OpenGLContext.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Platform/OpenGL/OpenGLBuffer.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Platform/OpenGL/OpenGLVertexArray.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Platform/OpenGL/OpenGLRendererAPI.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Platform/OpenGL/OpenGLShader.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Platform/OpenGL/OpenGLTexture.cpp
  # ${Tayo_SOURCE_DIR}/Tayo/src/Platform/OpenGL/OpenGLFramebuffer.cpp
  # ${Tayo_SOURCE_DIR}/Tayo/src/Platform/OpenGL/OpenGLUniformBuffer.cpp
)

# add_library(TY_Platform_Linux
#   ${Tayo_SOURCE_DIR}/Tayo/src/Platform/Linux/LinuxWindow.cpp
#   ${Tayo_SOURCE_DIR}/Tayo/src/Platform/Linux/LinuxInput.cpp
#   ${Tayo_SOURCE_DIR}/Tayo/src/Platform/Linux/LinuxPlatformUtils.cpp
#   ${Tayo_SOURCE_DIR}/Tayo/src/Platform/Linux/LinuxDialogWindow.cpp
# )

add_library(TY_Tayo_Core
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Application.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Log.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Layer.cpp
  ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/LayerStack.cpp
  # ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Core/Window.cpp
  # ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Core/UUID.cpp
  # ${Tayo_SOURCE_DIR}/Tayo/src/Tayo/Core/FileSystem.cpp
)

add_library(Tayo INTERFACE)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
#  ${Tayo_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/Sandbox/
#)
#
#add_executable(Sandbox.exe
#  ${Tayo_SOURCE_DIR}/Sandbox/src/SandboxApp.cpp
#  ${Tayo_SOURCE_DIR}/Sandbox/src/Sandbox2D.cpp
#  ${Tayo_SOURCE_DIR}/Sandbox/src/ExampleLayer.cpp
#)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${Tayo_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/Sandbox/
)

add_executable(Sandbox.exe
  # ${Tayo_SOURCE_DIR}/Sandbox/src/Panels/ContentBrowserPanel.cpp
  # ${Tayo_SOURCE_DIR}/Sandbox/src/Panels/SceneHierarchyPanel.cpp
  # ${Tayo_SOURCE_DIR}/Sandbox/src/EditorLayer.cpp
  # ${Tayo_SOURCE_DIR}/Sandbox/src/TayonutApp.cpp
  ${Tayo_SOURCE_DIR}/Sandbox/src/SandboxApp.cpp
)

########################################################################
# Link libraries together
# target_link_libraries(TY_Tayo_Project
#   yaml-cpp
# )

# target_link_libraries(TY_Tayo_Scripting
#   TY_Tayo_Core
#   PkgConfig::MONO_PKG
# )

# target_link_libraries(TY_Platform_OpenGL
#   Vulkan::Vulkan shaderc_combined_lib spirv-cross
# )

target_link_libraries(TY_Tayo_Core
  TY_Platform_Linux TY_Tayo_ImGui TY_Tayo_Scripting
)

# target_link_libraries(TY_Platform_Linux
#   TY_Platform_OpenGL TY_Tayo_Renderer
#   PkgConfig::GTKMM_PKG
# )

target_link_libraries(TY_Tayo_Renderer
  TY_Platform_OpenGL TY_Tayo_Core
)

# target_link_libraries(TY_Tayo_Scene
#   TY_Tayo_Core
# )

target_link_libraries(Tayo INTERFACE
  TY_Tayo_Core TY_Platform_OpenGL TY_Tayo_Renderer TY_Tayo_ImGui
  glfw OpenGL::GL glad imgui glm stb_image
)

target_link_libraries(Sandbox.exe
 Tayo
)

# target_link_libraries(Tayonut.exe
#   Tayo
# )
