#pragma once

#include "KeyFrame.h"
#include "interfaces/msg/new_key_frame_bows.hpp"
#include "interfaces/msg/new_key_frames.hpp"
#include "interfaces/msg/successfully_merged.hpp"
#include "interfaces/srv/get_current_map.hpp"
#include <boost/uuid/uuid.hpp>
#include <interfaces/srv/detail/get_current_map__struct.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/service.hpp>
#include <rclcpp/subscription.hpp>

using namespace std;

class Agent {
public:
  Agent(rclcpp::Node::SharedPtr rosNode, uint agentId);

  uint getId();
  bool getSuccessfullyMerged();
  set<boost::uuids::uuid> getSentKeyFrameUuids();
  set<boost::uuids::uuid> getSentKeyFrameBowUuids();
  ORB_SLAM3::KeyFrame* getReferenceKeyFrame();

  void setReferenceKeyFrame(ORB_SLAM3::KeyFrame* referenceKeyFrame);
  void setSuccessfullyMerged(bool successfullyMerged);
  void addSentKeyFrameUuids(
    _Rb_tree_const_iterator<boost::uuids::uuid> first, _Rb_tree_const_iterator<boost::uuids::uuid> last);
  void addSentKeyFrameUuid(boost::uuids::uuid uuid);
  void addSentKeyFrameBowUuids(
    _Rb_tree_const_iterator<boost::uuids::uuid> first, _Rb_tree_const_iterator<boost::uuids::uuid> last);
  void addSentKeyFrameBowUuid(boost::uuids::uuid uuid);

  rclcpp::Publisher<interfaces::msg::NewKeyFrames>::SharedPtr newKeyFramesPub;
  rclcpp::Publisher<interfaces::msg::NewKeyFrameBows>::SharedPtr newKeyFrameBowsPub;
  rclcpp::Publisher<interfaces::msg::SuccessfullyMerged>::SharedPtr successfullyMergedPub;
  rclcpp::Client<interfaces::srv::GetCurrentMap>::SharedPtr getCurrentMapClient;

protected:
  uint agentId;

  set<boost::uuids::uuid> sentKeyFrameUuids;
  set<boost::uuids::uuid> sentKeyFrameBowUuids;
  bool successfullyMerged;
  ORB_SLAM3::KeyFrame* referenceKeyFrame;

  rclcpp::Node::SharedPtr rosNode;
};