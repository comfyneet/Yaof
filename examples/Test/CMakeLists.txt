include_directories("../../include")

file(GLOB TEST_SOURCES "*.cpp")

add_executable(Test ${TEST_SOURCES})

target_link_libraries(Test Yaof)

set_target_properties(Test PROPERTIES FOLDER "examples")

install(DIRECTORY "resources" DESTINATION ${INSTALL_DIR})

install(TARGETS Test DESTINATION ${INSTALL_DIR})