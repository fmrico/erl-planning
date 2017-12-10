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
	mongodb_store
	move_base_msgs
)

catkin_package(
	INCLUDE_DIRS include
	LIBRARIES erl_planning
	CATKIN_DEPENDS roscpp rospy std_msgs std_srvs actionlib rosplan_dispatch_msgs rosplan_knowledge_msgs diagnostic_msgs rosplan_planning_system mongodb_store
	DEPENDS
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(erl_planning
   src/KMS_Client.cpp
   src/Action.cpp

 )
add_dependencies(erl_planning $erl_planning_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(ERL_executor_node src/ERL_executor_node.cpp src/Executor.cpp)
add_executable(rp_wait_bell src/actions/RP_wait_bell.cpp)
add_executable(rp_attend_deli src/actions/RP_attend_deli.cpp)
add_executable(rp_attend_doctor src/actions/RP_attend_doctor.cpp)
add_executable(rp_recognize_person src/actions/RP_recognize_person.cpp)
add_executable(rp_move_to src/actions/RP_move_to.cpp)
add_executable(rp_escort_to src/actions/RP_escort_to.cpp)

add_dependencies(ERL_executor_node ${catkin_EXPORTED_TARGETS})
add_dependencies(rp_wait_bell ${catkin_EXPORTED_TARGETS})
add_dependencies(rp_attend_deli ${catkin_EXPORTED_TARGETS})
add_dependencies(rp_attend_doctor ${catkin_EXPORTED_TARGETS})
add_dependencies(rp_recognize_person ${catkin_EXPORTED_TARGETS})
add_dependencies(rp_move_to ${catkin_EXPORTED_TARGETS})
add_dependencies(rp_escort_to ${catkin_EXPORTED_TARGETS})

target_link_libraries(ERL_executor_node ${catkin_LIBRARIES} erl_planning)
target_link_libraries(rp_wait_bell ${catkin_LIBRARIES} erl_planning)
target_link_libraries(rp_attend_deli ${catkin_LIBRARIES} erl_planning)
target_link_libraries(rp_attend_doctor ${catkin_LIBRARIES} erl_planning)
target_link_libraries(rp_recognize_person ${catkin_LIBRARIES} erl_planning)
target_link_libraries(rp_move_to ${catkin_LIBRARIES} erl_planning)
target_link_libraries(rp_escort_to ${catkin_LIBRARIES} erl_planning)
target_link_libraries(erl_planning ${catkin_LIBRARIES})
