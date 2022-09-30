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
 * vmax = max linear velocity
 * v(t) = t*(4*vmax/T)-(4*vmax/(T^2))t^2
 * x(0) = xInitial, x(T) = xFinal where x(t) is x coordinate's positon wrt to time
 * T = (6/4*vmax) * (xFinal - xInitial) //solving integralv(t)dt and adding boundary conditions , we get this
 */
static const constexpr double vmax = 0.22; //turtlebot seems to lose all controllability at higher velocities. // this number is taken from turtlebot3_teleop

double getXLinearVelocity(const double& t,const double& T){
    return  t*(4*vmax/T)+(-(4*vmax/(T*T))*t*t);
}
double getT(const double&  xInitial, const double& xFinal){
    return (6/(4*vmax))*(xFinal - xInitial);
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

    const double loopRate = 500; //500 times a second

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
    const double xInit = -2.00021;  // in the chosen gazebo world, initial pose of x = -2.0021
    const double xFinal = 0;
    const double totalTime = getT(xInit,xFinal);

    std::cout<<"total time:"<<totalTime<<std::endl;

    while (ros::ok()) {
        
        ros::spinOnce();

        velCommand.linear.x = getXLinearVelocity(time,totalTime);

        velocityPub.publish(velCommand);

        loop_rate.sleep();

        time += timeIncrement;

        if(time>=totalTime){
            velCommand.linear.x = 0;
            velocityPub.publish(velCommand);
            ros::spinOnce();
            break;
        }
    }
    std::cout<<"Open loop controller action over, exiting program"<<std::endl;
return 0;
}