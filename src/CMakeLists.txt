include_directories(${SCAM_SOURCE_DIR}/src)
link_directories(${SCAM_SOURCE_DIR}/src)

add_library(scam SHARED scam.hh scm.cc scm.hh predicates.cc assert.cc assert.hh values.cc accessors.cc parse.cc general.cc wrappers.cc eval.cc defun.cc show.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
