set( vital_config_python_headers
     config.h
    )

set( vital_config_python_sources
     config.cxx
     config_module.cxx
   )

kwiver_add_python_library( config
      vital/config
      ${vital_config_python_headers}
      ${vital_config_python_sources}
    )

target_link_libraries( python-vital.config-config
                      PRIVATE ${PYTHON_LIBRARIES} pybind11::pybind11
                      vital_config vital
                     )

kwiver_add_python_module( ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py
                          vital/config
                          __init__
)
