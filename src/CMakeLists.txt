add_executable(hello_world hello_world.c)

target_include_directories(hello_world PRIVATE
        ${PROJECT_SOURCE_DIR}/OpenTimelineIO-C-Bindings/include)

target_link_libraries(hello_world PUBLIC
        copentime
        copentimelineio)