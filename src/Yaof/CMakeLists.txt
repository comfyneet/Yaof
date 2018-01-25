if (WIN32)
   find_package(OpenGL REQUIRED)
   find_package(GLEW REQUIRED)
   find_package(GLFW REQUIRED)
   find_package(FreeImage REQUIRED)
   find_package(TinyXML2 REQUIRED)
elseif (UNIX)
   find_package(PkgConfig REQUIRED)
   pkg_search_module(OpenGL REQUIRED gl)
   pkg_search_module(GLEW REQUIRED glew)
   pkg_search_module(GLFW REQUIRED glfw3)
   pkg_search_module(FreeImage REQUIRED freeimage) # TODO
   pkg_search_module(TinyXML2 REQUIRED tinyxml2)   # TODO
endif()

add_definitions(-DGLFW_INCLUDE_GLCOREARB -DGLFW_DLL)
add_definitions(-DYAOF_COMPILE)

include_directories("../../include")
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${FreeImage_INCLUDE_DIRS})
include_directories(${TINYXML2_INCLUDE_DIRS})

file(GLOB YAOF_SOURCES
        "../../include/Yaof/*.hpp"
        "../../include/Yaof/Core/*.hpp"
        "../../include/Yaof/Graphics/*.hpp"
        "../../include/Yaof/Misc/*.hpp"
        "../../include/Yaof/Window/*.hpp"
        "*.cpp"
        "Core/*.cpp"
        "Graphics/*.cpp"
        "Misc/*.cpp"
        "Window/*.cpp")

add_library(Yaof SHARED ${YAOF_SOURCES})

target_link_libraries(Yaof ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${FreeImage_LIBRARIES} ${TINYXML2_LIBRARIES})

install(TARGETS Yaof DESTINATION ${INSTALL_DIR})
if (WIN32)
   install(DIRECTORY "${CMAKE_SOURCE_DIR}/extlibs/libs-msvc/${ARCHITECTURE}/bin/" DESTINATION ${INSTALL_DIR})
endif()