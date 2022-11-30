get_filename_component(DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" DAY ${DAY})

add_executable(${DAY} ${DAY}.cpp)

target_include_directories(${DAY} PUBLIC
    .
    ../utils
  )

# target_compile_options(${DAY} PUBLIC -std=c++17 -02)
# target_link_libraries(${DAY} utils)  


