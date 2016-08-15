// *****************************************************************************
//
// Copyright (c) 2014, Southwest Research Institute® (SwRI®)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Southwest Research Institute® (SwRI®) nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *****************************************************************************

#ifndef MAPVIZ_PLUGINS_ATTITUDE_INDICATOR_PLUGIN_H_
#define MAPVIZ_PLUGINS_ATTITUDE_INDICATOR_PLUGIN_H_

// C++ standard libraries
#include <string>
#include <list>
#include <vector>

#include <mapviz/mapviz_plugin.h>
#include <GL/glut.h>

// QT libraries
#include <QGLWidget>
#include <QObject>
#include <QWidget>
#include <QColor>

// ROS libraries
#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <topic_tools/shape_shifter.h>
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>

#include <mapviz/map_canvas.h>


#include <mapviz_plugins/placeable_window_proxy.h>


// QT autogenerated files
#include "ui_attitude_indicator_config.h"

namespace mapviz_plugins
{


class AttitudeIndicatorPlugin : public mapviz::MapvizPlugin
{
  Q_OBJECT

 public:
    struct Attitude
    {
      public:
      tf::Point point;
      tf::Quaternion orientation;
      ros::Time stamp;
    };
  Attitude point_;
  bool has_message_;
  double pitch;
  double roll;
  double yaw;
  std::vector<std::string> topics_;
  AttitudeIndicatorPlugin();
  virtual ~AttitudeIndicatorPlugin();

  bool Initialize(QGLWidget* canvas);
  void Shutdown();

  void Draw(double x, double y, double scale);

  void Transform() {}

  void LoadConfig(const YAML::Node& node, const std::string& path);
  void SaveConfig(YAML::Emitter& emitter, const std::string& path);

  QWidget* GetConfigWidget(QWidget* parent);

 protected:
  void PrintError(const std::string& message);
  void PrintInfo(const std::string& message);
  void PrintWarning(const std::string& message);

  void drawBackground();
  void drawBall();
  void drawPanel();
  
  void timerEvent(QTimerEvent *);

 protected Q_SLOTS:
 //  void modeChanged();
 //  void sourceEdited();
 //  void targetEdited();
   void SelectTopic();
   void TopicEdited();
 //  void SetAnchor(QString anchor);
 //  void SetUnits(QString units);
 //  void SetOffsetX(int offset);
 //  void SetOffsetY(int offset);
 //  void SetWidth(int width);
 //  void SetHeight(int height);

 private:
  Ui::attitude_indicator_config ui_;
  QWidget* config_widget_;
  std::string topic_;
  PlaceableWindowProxy placer_;
  ros::Subscriber odometry_sub_;

  void handleMessage(const topic_tools::ShapeShifter::ConstPtr& msg);
  void AttitudeCallbackOdom(const nav_msgs::Odometry &odometry);
  void AttitudeCallbackImu(const sensor_msgs::Imu &Imu);
  void AttitudeCallbackPose(const geometry_msgs::Pose &pose);
  // Anchor anchor_;
  // Units units_;
  // int offset_x_;
  // int offset_y_;
  // int width_;
  // int height_;

  // int last_width_;
  // int last_height_;

  // std::string AnchorToString(Anchor anchor);
  // std::string UnitsToString(Units units);
};  // class AttitudeIndicatorPlugin
}  // namespace mapviz_plugins
#endif  // MAPVIZ_PLUGINS_ATTITUDE_INDICATOR_PLUGIN_H_
