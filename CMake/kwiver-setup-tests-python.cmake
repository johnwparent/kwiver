#
# Script to set up environment for python PYTESTs
#


# results of tests being run will be exported to an Xunit xml file
if (PYTEST_RUNNER)
  set(no_install TRUE)
  string(TOLOWER "${CMAKE_PROJECT_NAME}" project_name)

  if (WIN32)
    set(kwiver_test_output_path    "${KWIVER_BINARY_DIR}/$<CONFIG>/bin" )
  else ()
    set(kwiver_test_output_path    "${KWIVER_BINARY_DIR}/tests/bin" )
  endif ()
  if(VENV_CREATED)
      if(Python3_INTERPRETER_ID STREQUAL "Anaconda")
        set(PYTEST_COMMAND "$ENV{CONDA_EXE} activate testing_venv && ")
      else()
        set(PYTEST_COMMAND "source ${KWIVER_BINARY_DIR}/testing_venv/bin/activate && ")
      endif()
  else()
    set(PYTEST_COMMAND)
  endif()
  set(kwiver_test_working_path    "${CTEST_BINARY_DIRECTORY}" )

  set(kwiver_test_runner "${PYTEST_RUNNER} ${mod_dst}")
endif()
