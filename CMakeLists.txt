
add_compile_options("-g")
add_compile_options("-Wpedantic")
add_compile_options("-Wall")
add_executable(programik pr.cpp)

enable_testing()

function(add_one_test INPUT_NAME)
  add_test(
    NAME ${INPUT_NAME}
    COMMAND /bin/bash "-c"
      "$<TARGET_FILE:programik> < ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_NAME}.txt 2>/dev/null > ${INPUT_NAME}_output.txt &&
       diff ${INPUT_NAME}_output.txt ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_NAME}_expected.txt"
  )
endfunction()

add_one_test("test_data-00")
add_one_test("test_data-01")
add_one_test("test_data-02")
add_one_test("test_data-04")
