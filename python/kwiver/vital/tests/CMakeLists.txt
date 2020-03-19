#
# Python support
#

add_subdirectory(cpp_helpers)

# Define modules with tests in them
set(__testable_modnames
  test_algorithms_common
  test_algorithm_factory
  test_activity_type
  test_camera
  test_camera_intrinsics
  test_category_hierarchy
  test_config
  test_camera_map
  test_color
  test_covariance
  test_database_query
  test_descriptor
  test_descriptor_request
  test_descriptor_set
  test_detected_object_type
  test_detected_object
  test_feature
  test_feature_descriptor_io
  test_feature_set
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
  test_local_cartesian
  test_metadata
  test_metadata_tags
  test_object_track_state
  test_object_track_set
  test_query_result
  test_rotation
  test_point
  test_polygon
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

# Add files to the vital.tests python module
foreach (modname IN LISTS __all_modnames)
  kwiver_add_python_module( ${CMAKE_CURRENT_SOURCE_DIR}/${modname}.py
    vital/tests
    ${modname})
endforeach()

add_subdirectory(alg)
