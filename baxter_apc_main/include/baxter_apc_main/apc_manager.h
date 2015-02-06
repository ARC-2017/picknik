/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2014, Dave Coleman <dave@dav.ee>
 *  All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *********************************************************************/

/* Author: Dave Coleman <dave@dav.ee>
   Desc:   Main logic of APC challenge
*/

#ifndef BAXTER_APC_MAIN__SHELF_MANAGER
#define BAXTER_APC_MAIN__SHELF_MANAGER

// Amazon Pick Place Challenge
#include <baxter_apc_main/amazon_json_parser.h>
#include <baxter_apc_main/shelf.h>
#include <baxter_apc_main/manipulation_pipeline.h>
#include <baxter_apc_main/learning_pipeline.h>

// ROS
#include <ros/ros.h>
#include <tf/transform_listener.h>

// MoveIt
//#include <moveit/collision_detection/world.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
//#include <moveit/planning_pipeline/planning_pipeline.h>
//#include <moveit/kinematic_constraints/utils.h>
//#include <moveit/robot_state/conversions.h>
//#include <moveit/plan_execution/plan_execution.h>

// Grasp generation
//#include <moveit_grasps/grasps.h>
//#include <moveit_grasps/grasp_data.h>
//#include <moveit_grasps/grasp_filter.h>

namespace baxter_apc_main
{

static const std::string ROBOT_DESCRIPTION = "robot_description";
static const std::string JOINT_STATE_TOPIC = "/robot/joint_states";
static const std::string PACKAGE_NAME = "baxter_apc_main";

class APCManager
{
public:

  /**
   * \brief Constructor
   * \param verbose - run in debug mode
   */
  APCManager(bool verbose, std::string order_fp);

  /**
   * \brief Destructor
   */
  ~APCManager()
  {}

  /**
   * \brief Main program runner
   * \return true on success
   */
  bool runOrder(bool use_experience, bool show_database);

  /**
   * \brief Generate a discretized array of possible pre-grasps and save into experience database
   * \return true on success
   */
  bool trainExperienceDatabase();

  /**
   * \brief Test the end effectors
   * \param input - description
   * \return true on success
   */
  bool testEndEffectors();

  /**
   * \brief Load shelf contents
   * \return true on success
   */
  bool loadShelfContents(std::string order_fp);

  /**
   * \brief Show detailed shelf
   */
  bool visualizeShelf();

  /**
   * \brief Connect to the MoveIt! planning scene messages
   */
  bool loadPlanningSceneMonitor();

private:

  // A shared node handle
  ros::NodeHandle nh_;
  boost::shared_ptr<tf::TransformListener> tf_;

  // Show more visual and console output, with general slower run time.
  bool verbose_;

  // For visualizing things in rviz
  moveit_visual_tools::MoveItVisualToolsPtr visual_tools_;

  // Core MoveIt components
  robot_model_loader::RobotModelLoaderPtr robot_model_loader_;
  robot_model::RobotModelPtr robot_model_;
  planning_scene::PlanningScenePtr planning_scene_;
  planning_scene_monitor::PlanningSceneMonitorPtr planning_scene_monitor_;

  // Properties
  ShelfObjectPtr shelf_;
  WorkOrders orders_;
  std::string package_path_;

  // Main worker
  ManipulationPipelinePtr pipeline_;

  // Helper classes
  LearningPipelinePtr learning_;

}; // end class

} // end namespace


#endif