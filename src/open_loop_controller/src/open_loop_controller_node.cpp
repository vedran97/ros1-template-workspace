#include <cstdlib>
#include <iostream>
#include <cmath> 
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

geometry_msgs::Twist velCommand;

/**
 * Assuming 1D motion in X direction
 * Using a velocity profile which is a inverted parabola
 * T is the total time required for a motion to start and finish
 * v(t) = t*T-t^2
 * x(t) = t^2/2*T - t^3/3 + c x(0) = xInitial, x(T) = xFinal 
 */
double getXLinearVelocity(const double& time,const double& T){
    return (time*T - time*time);
}
double getT(const double&  xInitial, const double& xFinal){
    return std::cbrt(6*(xFinal-xInitial));
}



int main(int argc, char **argv) {
 
    // Initiate ROS
    ros::init(argc, argv, "open_loop_controller");

    /**
     * Setup ROS nodes 
     */
    ros::NodeHandle node;

    ros::Publisher velocityPub =
    node.advertise<geometry_msgs::Twist>("/cmd_vel", 0);

    const double loopRate = 50; //50 times a second

    ros::Rate loop_rate(loopRate); 

    geometry_msgs::Twist velCommand;

    velCommand.angular.x = 0;
    velCommand.angular.y = 0;
    velCommand.angular.z = 0;
    velCommand.linear.x = 0;
    velCommand.linear.y = 0;
    velCommand.linear.z = 0;

    double time = 0.0; // seconds (could use stl time literals as units)
    const double timeIncrement = 1/loopRate;
    const double xInit = 0;
    const double xFinal = 200.0;
    const double totalTime = getT(xInit,xFinal);

    std::cout<<"total time:"<<totalTime<<std::endl;

    while (ros::ok()) {
        
        ros::spinOnce();

        velCommand.linear.x = getXLinearVelocity(time,totalTime);

        velocityPub.publish(velCommand);

        std::cout<<"time: "<<time<<"linear vel:"<<velCommand.linear.x<<" total time:"<<totalTime<<std::endl;

        loop_rate.sleep();

        time += timeIncrement;

        if(time>=totalTime){
            velCommand.linear.x = 0;
            velocityPub.publish(velCommand);
            ros::spinOnce();
            break;
        }
    }
    std::cout<<"Open loop controller action over, exiting program";
return 0;
}