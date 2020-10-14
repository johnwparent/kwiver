#
# Python support
#

add_subdirectory(cpp_helpers)

# Define modules with tests in them
set(__testable_modnames
  test_algorithms_common
  test_activity
  test_algorithm_factory
  test_activity_type
  test_bounding_box
  test_camera
  test_camera_intrinsics
  test_category_hierarchy
  test_config
  test_camera_map
  test_camera_perspective
  test_camera_perspective_map
  test_camera_rpc
  test_color
  test_covariance
  test_database_query
  test_detected_object_set
  test_descriptor
  test_descriptor_request
  test_descriptor_set
  test_detected_object_type
  test_detected_object
  test_feature
  test_feature_descriptor_io
  test_feature_set
  test_feature_track_set
  test_fundamental_matrix
  test_geo_covariance
  test_geo_MGRS
  test_geo_point
  test_geo_polygon
  test_geodesy
  test_homography
  test_homography_f2f
  test_homography_f2w
  test_image
  test_image_container
  test_image_io
  test_iqr_feedback
  test_landmark
  test_landmark_map
  test_local_cartesian
  test_local_geo_cs
  test_match_set
  test_mesh
  test_metadata
  test_metadata_map
  test_metadata_tags
  test_metadata_traits
  test_object_track_state
  test_object_track_set
  test_query_result
  test_rotation
  test_point
  test_polygon
  test_sfm_constraints
  test_similarity
  test_timestamp
  test_track
  test_track_descriptor
  test_track_interval
  test_track_set
  test_track_state
  test_transform_2d_io
  test_transform_2d
  test_uid
  )

# All python filenames_we in the vital.tests module
set(__all_modnames
  __init__
  py_helpers
  ${__testable_modnames}
  )


foreach (modname IN LISTS __all_modnames)
  kwiver_add_python_module( ${CMAKE_CURRENT_SOURCE_DIR}/${modname}.py
    vital/tests
    ${modname})
endforeach()

add_subdirectory(alg)
# dont select all tests, just configure a single add test with the name vital_types
# and have nose run, exporting the output to an Xunit xml via commandline args to ctest --
# could probably have set that in the set kwiver_test_runner command or add test...
# here all we should be doing is setting a single nosetest with the path
# to the above generated module

if (KWIVER_ENABLE_TESTS AND NOSE_RUNNER)

  set(NOSE_RUNNER)
  set(modpath vital/tests/)
  set(kwiver_test_working_path)
  set(kwiver_test_output_path)

  set(_test_data
        "data/airplane.ply")

  include(kwiver-setup-tests-python)

  foreach (file_name IN LISTS _test_data)

    kwiver_python_add_test_data(${file_name}
                                ${kwiver_test_working_path})

  endforeach()



  include(kwiver-setup-tests-python)
    foreach (test IN LISTS __testable_modnames)
      kwiver_add_nosetests(${test} vital-type-)
    endforeach()

endif()
