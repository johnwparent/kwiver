project(sprokit_python_sprokit_pipeline_util)

if( NOT WIN32 )



autopybind11_add_module(pipeline_util
                      YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/pipeline_utils_wrapper.yml
                      DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                      LINK_LIBRARIES sprokit_pipeline sprokit_pipeline_util vital vital_util sprokit_python_util vital_vpm vital_python_util
                      GEN_ONLY TRUE
                      INCLUDE_DIRS ${BOOST_ROOT_ARG}/include)
get_target_property(pipeline_util_srcs pipeline_util_files SOURCES)

kwiver_add_python_library(pipeline_util
  sprokit/pipeline_util
  ${pipeline_util_srcs}
)
target_link_libraries(python-sprokit.pipeline_util-pipeline_util
  LINK_PRIVATE
    sprokit_pipeline
    sprokit_pipeline_util
    sprokit_python_util
    vital_python_util
    ${Boost_IOSTREAMS_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    vital_vpm
  )

kwiver_add_python_library(bake
  sprokit/pipeline_util
  bake.cxx)

target_link_libraries(python-sprokit.pipeline_util-bake
  LINK_PRIVATE
    sprokit_pipeline
    sprokit_pipeline_util
    sprokit_python_util
    vital_python_util
    ${Boost_IOSTREAMS_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    vital_vpm
  )

kwiver_add_python_library(export_
  sprokit/pipeline_util
  export.cxx)

target_link_libraries(python-sprokit.pipeline_util-export_
  LINK_PRIVATE
    sprokit_pipeline
    sprokit_pipeline_util
    vital_python_util
    sprokit_python_util)


kwiver_add_python_library(load
  sprokit/pipeline_util
  load.cxx)
target_link_libraries(python-sprokit.pipeline_util-load
  LINK_PRIVATE
    sprokit_pipeline
    sprokit_pipeline_util
    sprokit_python_util
    vital_python_util
    vital_util
    ${Boost_IOSTREAMS_LIBRARY})






kwiver_add_python_module(${CMAKE_CURRENT_SOURCE_DIR}/__init__.py
                         sprokit/pipeline_util
                         __init__)
endif()
