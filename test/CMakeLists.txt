include_directories(${SCAM_SOURCE_DIR}/src ${SCAM_SOURCE_DIR}/test)
link_directories(${SCAM_SOURCE_DIR}/src ${SCAM_SOURCE_DIR}/test)

add_executable(scam-tests test_main.cc parse_tests.cc wrap_tests.cc cons_tests.cc show_tests.cc catch.hpp ${SCAM_SOURCES})

target_link_libraries(scam-tests scam)

add_test(NAME tests COMMAND scam-tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
