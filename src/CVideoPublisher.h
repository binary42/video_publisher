#pragma once

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

#include <sensor_msgs/image_encodings.h>
#include <ros/ros.h>

#include <opencv2/opencv.hpp>

class CVideoPublisher
{
public:
    CVideoPublisher( const std::string &fileNameIn );
    virtual ~CVideoPublisher();

    // Attributes

    // Methods
    bool Initialize();
    void Run();

private:
    // Attributes
    ros::NodeHandle                        	_nodeHandle;
    image_transport::ImageTransport     	_imageTransport;

    image_transport::Publisher           	_imagePublisherBGR8;
    image_transport::Publisher           	_imagePublisherMono8;
    std::string                            	_fileName;

    cv::VideoCapture                    	*_capture;

    // Methods


};

