#include "../../video_publisher/src/CVideoPublisher.h"
#include <csignal>

void SignalHandler( int signum )
{
	ROS_INFO( ">>>> Interupt Received <<<<" );
	ROS_INFO( ">>>> Exiting <<<<" );

	exit( signum );
}

int main( int argc, char** argv)
{
	signal( SIGINT, SignalHandler );

    ros::init( argc, argv, "video_publisher" );

    std::string fileName( argv[1] );

    CVideoPublisher *app = new CVideoPublisher( fileName );

    if( !app->Initialize() )
    {
        ROS_ERROR( ">>>> Could not open file <<<<" );
        return -1;
    }

    ros::Rate loopRate( 30 ); //in Hz

    ROS_INFO( ">>>> Publishing Video <<<<");

    while( ros::ok() )
    {
        app->Run();

        ros::spinOnce();

        loopRate.sleep();
    }

    ROS_INFO( ">>>> ! ros::ok() <<<<");
    ROS_INFO( ">>>> Exiting <<<<" );

    return 0;
}
