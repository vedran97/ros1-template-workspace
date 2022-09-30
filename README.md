# Intent of the repository : 

1. I created this repository , so that fellow ros1 noetic developers have access to a dockerized ros-noetiv workspace on an ubuntu 20.04 base.
2. This workspace can be minimzed and also be used for pure c++ development, using ros as a build and execute system.
3. I have included turtlebot3 sim packages as examples , the model is set to burger
4. ros and workspace devel/setup.bash is already added in .bashrc

# Initial Setup :

1. Install vs-code editor on your ubuntu 20.04 host OS : https://linuxize.com/post/how-to-install-visual-studio-code-on-ubuntu-20-04/
2. Install docker on your ubuntu 20.04 host OS : https://docs.docker.com/engine/install/ubuntu/
3. Please remember to follow all the steps in docker installation, and verifying it's successful installation @ https://docs.docker.com/engine/install/ubuntu/#next-steps > https://docs.docker.com/engine/install/linux-postinstall/#manage-docker-as-a-non-root-user (Step 1 2 3 4)
4. Install following extensions on your VSCode: 
    1. Docker : https://marketplace.visualstudio.com/items?itemName=ms-azuretools.vscode-docker
    2. Remote-Containers :  https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers
5. Clone this repository using:
    > ``` git clone --recurse-submodules https://github.com/vedran97/ros1-workspace-template.git ```
6. From the current working directory, cd to ros2-workspace-template repo which u just cloned
7. Open a terminal in ros2-workspace-template and type 
    > ``` code . ```
8. A VSCode popup should arise which says "Open folder in Container" where you choose Yes OR press F1,search for "Open Folder in Container" and execute the command
9. Now wait for the build process to finish, once it's completed, you have a fully functional ROS2 workspace with example packages
11. When the container is built for the first time, a error will popup saying "Failed to enable ROS Extension" , just choose the reload window option
10. Set up ROS dependencies using the following section

# Setting up ROS-Dependencies :

1. Once the repo is opened in a container, you have to install ROS1-dependencies. To do this, follow these steps:
    0. Inside the container, use a bash terminal will open at the following command's path if not, run it
    1. cd /workspaces/ros1-template-workspace
    2. rosdep update
    3. sudo apt-get update
    4. rosdep install --from-paths src --ignore-src -r -y

# Building Packages:

1. cd /workspaces/ros1-template-workspace
2. catkin_make

# Open loop controller code for a turtlebot3:

1. Once all packages are built, in 1 terminal window, run "roslaunch turtlebot3_gazebo turtlebot3_world.launch"
2. In another terminal window , run "rosrun open_loop_controller open_loop_controller_node"





