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
6. From the current working directory, cd to ros1-workspace-template repo which u just cloned
7. Open a terminal in ros1-workspace-template and type 
    > ``` code . ```
8. A VSCode popup should arise which says "Open folder in Container" where you choose Yes OR press F1,search for "Open Folder in Container" and execute the command
9. Now wait for the build process to finish, once it's completed, you have a fully functional ROS1 workspace with example packages
11. When the container is built for the first time, a error will popup saying "Failed to enable ROS Extension" , just choose the reload window option
10. Set up ROS dependencies using the following section

# VS Code tasks:

0. How to use this? Ans: Open this directory as a container(or not) and press "Ctrl+Shift+B" to get a drop down list of available tasks.<br>Like this: <br> ![Tasks](./docs/tasks.png)
1. "ROS:Build a Package" task -> This task lets you build a selected few, or all packages. CMake parrallelism limits have been added to prevent crashing during builds.
    1. Choose a build config:<br>![Build-Config](./docs/buildmode.png)
    2. Choose a package name:<br>![Package-Name](./docs/pkgname.png)
<br>choosing no package name, will build all packages in this directory
2. "ROS:Install ROS dependencies" task -> This task lets you install ros-deps which are mentioned in any package's package.xml file, which is included in this workspace.
3. "ROS: Clean" task -> This task cleans the workspace off all build artifacts

# Setting up ROS-Dependencies :

1. Run the VSCode task "ROS:Install ROS dependencies"

# Open loop controller code for a turtlebot3:

1. Once all packages are built, in 1 terminal window, run "roslaunch turtlebot3_gazebo turtlebot3_world.launch"
2. In another terminal window , run "rosrun open_loop_controller open_loop_controller_node"






