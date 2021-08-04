add_executable(pick_and_place_test src/pick_and_place_test.cpp)
#add_executable(pick_and_place_test src/pick_and_place_test_2.cpp)
target_link_libraries(pick_and_place_test ${catkin_LIBRARIES} ${Boost_LIBRARIES})
install(TARGETS pick_and_place_test DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
