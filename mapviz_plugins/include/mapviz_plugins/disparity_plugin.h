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

#ifndef MAPVIZ_PLUGINS_DISPARITY_PLUGIN_H_
#define MAPVIZ_PLUGINS_DISPARITY_PLUGIN_H_

// Include mapviz_plugin.h first to ensure GL deps are included in the right order
#include <mapviz/mapviz_plugin.h>

// C++ standard libraries
#include <list>
#include <string>

// QT libraries
#include <QColor>
#include <QGLWidget>
#include <QObject>
#include <QWidget>

// ROS libraries
#include <cv_bridge/cv_bridge.h>
#include <opencv/highgui.h>
#include <ros/ros.h>
#include <stereo_msgs/DisparityImage.h>
#include <tf/transform_datatypes.h>

#include <mapviz/map_canvas.h>

// QT autogenerated files
#include "ui_disparity_config.h"

namespace mapviz_plugins
{
  class DisparityPlugin : public mapviz::MapvizPlugin
  {
    Q_OBJECT

  public:
    enum Anchor {
      TOP_LEFT,
      TOP_CENTER,
      TOP_RIGHT,
      CENTER_LEFT,
      CENTER,
      CENTER_RIGHT,
      BOTTOM_LEFT,
      BOTTOM_CENTER,
      BOTTOM_RIGHT};

    enum Units {PIXELS, PERCENT};

    DisparityPlugin();
    virtual ~DisparityPlugin();

    bool Initialize(QGLWidget* canvas);
    void Shutdown() {}

    void Draw(double x, double y, double scale);

    void Transform() {}

    void LoadConfig(const YAML::Node& node, const std::string& path);
    void SaveConfig(YAML::Emitter& emitter, const std::string& path);

    QWidget* GetConfigWidget(QWidget* parent);

  protected:
    void PrintError(const std::string& message);
    void PrintInfo(const std::string& message);
    void PrintWarning(const std::string& message);

  protected Q_SLOTS:
    void SelectTopic();
    void TopicEdited();
    void SetAnchor(QString anchor);
    void SetUnits(QString units);
    void SetOffsetX(int offset);
    void SetOffsetY(int offset);
    void SetWidth(int width);
    void SetHeight(int height);

  private:
    Ui::disparity_config ui_;
    QWidget* config_widget_;

    std::string topic_;
    Anchor anchor_;
    Units units_;
    double offset_x_;
    double offset_y_;
    double width_;
    double height_;

    bool has_image_;

    double last_width_;
    double last_height_;

    ros::Subscriber disparity_sub_;
    bool has_message_;

    stereo_msgs::DisparityImage disparity_;

    cv::Mat_<cv::Vec3b> disparity_color_;
    cv::Mat scaled_image_;

    void disparityCallback(const stereo_msgs::DisparityImageConstPtr& image);

    void ScaleImage(double width, double height);
    void DrawIplImage(cv::Mat *image);

    std::string AnchorToString(Anchor anchor);
    std::string UnitsToString(Units units);

    const static unsigned char COLOR_MAP[];
  };
}

#endif  // MAPVIZ_PLUGINS_DISPARITY_PLUGIN_H_
