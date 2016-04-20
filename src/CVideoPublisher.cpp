#include "../../video_publisher/src/CVideoPublisher.h"

CVideoPublisher::CVideoPublisher( const std::string &fileNameIn ) : _imageTransport( _nodeHandle ) , _fileName( fileNameIn )
{
    _capture = new cv::VideoCapture();

    _imagePublisherBGR8 = _imageTransport.advertise( "/video_publisher/image_raw_bgr8", 1 );
    _imagePublisherMono8 = _imageTransport.advertise( "/video_publisher/image_raw_mono8", 1 );
}

CVideoPublisher::~CVideoPublisher()
{
    delete( _capture );
}

bool CVideoPublisher::Initialize()
{
    return _capture->open( _fileName );
}

void CVideoPublisher::Run()
{
    if( !_capture->isOpened() )
    {
        ROS_ERROR( ">>>> Could not open file <<<<" );

        return;
    }

    cv::Mat frame;
    sensor_msgs::ImagePtr message;
    sensor_msgs::ImagePtr message2;

    *_capture >> frame;

    if( !frame.empty() )
    {
        message = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame ).toImageMsg();
        message2 = cv_bridge::CvImage( std_msgs::Header(), "mono16", frame ).toImageMsg();
    }

    _imagePublisherBGR8.publish( message );
    _imagePublisherMono8.publish( message2 );
}
