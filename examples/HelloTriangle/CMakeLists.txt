include_directories("../../include")

file(GLOB HELLOTRIANGLE_SOURCES "*.cpp")

add_executable(HelloTriangle ${HELLOTRIANGLE_SOURCES})

target_link_libraries(HelloTriangle Yaof)

set_target_properties(HelloTriangle PROPERTIES FOLDER "examples")

install(DIRECTORY "resources" DESTINATION ${INSTALL_DIR})

install(TARGETS HelloTriangle DESTINATION ${INSTALL_DIR})