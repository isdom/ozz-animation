# sampling_job_tests
add_executable(test_sampling_job
  sampling_job_tests.cc)
target_link_libraries(test_sampling_job
  ozz_animation_offline
  gtest)
set_target_properties(test_sampling_job PROPERTIES FOLDER "ozz/tests/animation")
add_test(NAME test_sampling_job COMMAND test_sampling_job)

# blending_job_tests
add_executable(test_blending_job
  blending_job_tests.cc)
target_link_libraries(test_blending_job
  ozz_animation_offline
  gtest)
set_target_properties(test_blending_job PROPERTIES FOLDER "ozz/tests/animation")
add_test(NAME test_blending_job COMMAND test_blending_job)

# local_to_model_job_tests
add_executable(test_local_to_model_job
  local_to_model_job_tests.cc)
target_link_libraries(test_local_to_model_job
  ozz_animation_offline
  gtest)
set_target_properties(test_local_to_model_job PROPERTIES FOLDER "ozz/tests/animation")
add_test(NAME test_local_to_model_job COMMAND test_local_to_model_job)

add_executable(test_animation_archive
  animation_archive_tests.cc)
target_link_libraries(test_animation_archive
  ozz_animation_offline
  gtest)
set_target_properties(test_animation_archive PROPERTIES FOLDER "ozz/tests/animation")
add_test(NAME test_animation_archive COMMAND test_animation_archive)

add_executable(test_animation_archive_versioning
  animation_archive_versioning_tests.cc)
target_link_libraries(test_animation_archive_versioning
  ozz_animation
  ozz_options
  gtest)
set_target_properties(test_animation_archive_versioning PROPERTIES FOLDER "ozz/tests/animation")
add_test(NAME test_animation_archive_versioning_le COMMAND test_animation_archive_versioning "--file=${ozz_media_directory}/bin/versioning/animation_v4_le.ozz" "--tracks=67" "--duration=.66666667" "--name=run")
add_test(NAME test_animation_archive_versioning_be COMMAND test_animation_archive_versioning "--file=${ozz_media_directory}/bin/versioning/animation_v4_be.ozz" "--tracks=67" "--duration=.66666667" "--name=run")

# Previous versions.
add_test(NAME test_animation_archive_versioning_le_older3 COMMAND test_animation_archive_versioning "--file=${ozz_media_directory}/bin/versioning/animation_v3_le.ozz" "--tracks=67" "--duration=.66666667" "--name=")
set_tests_properties(test_animation_archive_versioning_le_older3 PROPERTIES WILL_FAIL true)
add_test(NAME test_animation_archive_versioning_le_older2 COMMAND test_animation_archive_versioning "--file=${ozz_media_directory}/bin/versioning/animation_v2_le.ozz" "--tracks=67" "--duration=1.33333302" "--name=")
set_tests_properties(test_animation_archive_versioning_le_older2 PROPERTIES WILL_FAIL true)
add_test(NAME test_animation_archive_versioning_le_older1 COMMAND test_animation_archive_versioning "--file=${ozz_media_directory}/bin/versioning/animation_v1_le.ozz" "--tracks=67" "--duration=.66666698" "--name=")
set_tests_properties(test_animation_archive_versioning_le_older1 PROPERTIES WILL_FAIL true)

add_executable(test_skeleton_archive
  skeleton_archive_tests.cc)
target_link_libraries(test_skeleton_archive
  ozz_animation_offline
  gtest)
set_target_properties(test_skeleton_archive PROPERTIES FOLDER "ozz/tests/animation")
add_test(NAME test_skeleton_archive COMMAND test_skeleton_archive)

add_executable(test_skeleton_archive_versioning
  skeleton_archive_versioning_tests.cc)
target_link_libraries(test_skeleton_archive_versioning
  ozz_animation
  ozz_options
  gtest)
set_target_properties(test_skeleton_archive_versioning PROPERTIES FOLDER "ozz/tests/animation")
add_test(NAME test_skeleton_archive_versioning_le COMMAND test_skeleton_archive_versioning "--file=${ozz_media_directory}/bin/versioning/skeleton_v1_le.ozz" "--joints=67" "--root_name=Hips")
add_test(NAME test_skeleton_archive_versioning_be COMMAND test_skeleton_archive_versioning "--file=${ozz_media_directory}/bin/versioning/skeleton_v1_be.ozz" "--joints=67" "--root_name=Hips")

add_executable(test_skeleton_utils
  skeleton_utils_tests.cc)
target_link_libraries(test_skeleton_utils
  ozz_animation_offline
  gtest)
set_target_properties(test_skeleton_utils PROPERTIES FOLDER "ozz/tests/animation")
add_test(NAME test_skeleton_utils COMMAND test_skeleton_utils)

# ozz_animation fuse tests
add_executable(test_fuse_animation
  sampling_job_tests.cc
  ${PROJECT_SOURCE_DIR}/src_fused/ozz_animation.cc)
add_dependencies(test_fuse_animation BUILD_FUSE_ozz_animation)
target_link_libraries(test_fuse_animation
  ozz_animation_offline
  gtest)
add_test(NAME test_fuse_animation COMMAND test_fuse_animation)
set_target_properties(test_fuse_animation PROPERTIES FOLDER "ozz/tests/animation")
