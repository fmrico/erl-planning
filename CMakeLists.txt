cmake_minimum_required(VERSION 2.8.3)
project(erl_planning)


find_package(catkin REQUIRED COMPONENTS
  rospy
  roscpp
  rosplan_knowledge_msgs
	diagnostic_msgs
	rosplan_dispatch_msgs
	rosplan_knowledge_msgs
	rosplan_planning_system
	actionlib
)

catkin_package(
	LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS roscpp rospy std_msgs std_srvs actionlib rosplan_dispatch_msgs rosplan_knowledge_msgs diagnostic_msgs rosplan_planning_system
	DEPENDS
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(ball_boxes_executor_node src/ball_boxes_executor_node.cpp src/Executor.cpp src/KMS_Client.cpp)
add_executable(ERL_executor_node src/ERL_executor_node.cpp src/Executor.cpp src/KMS_Client.cpp)
add_executable(rpmoveball src/RPMoveBall.cpp src/KMS_Client.cpp)
add_executable(rp_wait_bell src/RP_wait_bell.cpp src/KMS_Client.cpp)
add_executable(rp_attend_deli src/RP_attend_deli.cpp src/KMS_Client.cpp)
add_executable(rp_attend_doctor src/RP_attend_doctor.cpp src/KMS_Client.cpp)
add_executable(rp_recognize_person src/RP_recognize_person.cpp src/KMS_Client.cpp)

add_dependencies(ball_boxes_executor_node ${catkin_EXPORTED_TARGETS})
add_dependencies(ERL_executor_node ${catkin_EXPORTED_TARGETS})
add_dependencies(rpmoveball ${catkin_EXPORTED_TARGETS})
add_dependencies(rp_wait_bell ${catkin_EXPORTED_TARGETS})
add_dependencies(rp_attend_deli ${catkin_EXPORTED_TARGETS})
add_dependencies(rp_attend_doctor ${catkin_EXPORTED_TARGETS})
add_dependencies(rp_recognize_person ${catkin_EXPORTED_TARGETS})

target_link_libraries(ball_boxes_executor_node ${catkin_LIBRARIES})
target_link_libraries(ERL_executor_node ${catkin_LIBRARIES})
target_link_libraries(rpmoveball ${catkin_LIBRARIES})
target_link_libraries(rp_wait_bell ${catkin_LIBRARIES})
target_link_libraries(rp_attend_deli ${catkin_LIBRARIES})
target_link_libraries(rp_attend_doctor ${catkin_LIBRARIES})
target_link_libraries(rp_recognize_person ${catkin_LIBRARIES})
