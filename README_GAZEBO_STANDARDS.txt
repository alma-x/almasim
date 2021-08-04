http://gazebosim.org/tutorials/?tut=ros_roslaunch

WORLD LAUNCH

<launch>
  <!-- We resume the logic in empty_world.launch, changing only the name of the world to be launched -->
  <include file="$(find gazebo_ros)/launch/empty_world.launch">
    <arg name="world_name" value="worlds/mud.world"/> <!-- Note: the world_name is with respect to GAZEBO_RESOURCE_PATH environmental variable -->
    <arg name="paused" value="false"/>
    <arg name="use_sim_time" value="true"/>
    <arg name="gui" value="true"/>
    <arg name="recording" value="false"/>
    <arg name="debug" value="false"/>
  </include>
</launch>


WORLD FILES

  <sdf version="1.4">
    <world name="default">
      <include>
        <uri>model://sun</uri>
      </include>
      <include>
        <uri>model://ground_plane</uri>
      </include>
      <include>
        <uri>model://double_pendulum_with_base</uri>
        <name>pendulum_thick_mud</name>
        <pose>-2.0 0 0 0 0 0</pose>
      </include>
      ...
    </world>
  </sdf>


GAZEBO ROS PACKAGE TREE STANDARDS

../catkin_ws/src
    /MYROBOT_description
        package.xml
        CMakeLists.txt
        /urdf
            MYROBOT.urdf
        /meshes
            mesh1.dae
            mesh2.dae
            ...
        /materials
        /cad
    /MYROBOT_gazebo
        /launch
            MYROBOT.launch
        /worlds
            MYROBOT.world
        /models
            world_object1.dae
            world_object2.stl
            world_object3.urdf
        /materials
        /plugins


LAUNCH CUSTOM WORLD

<launch>
  <!-- We resume the logic in empty_world.launch, changing only the name of the world to be launched -->
  <include file="$(find gazebo_ros)/launch/empty_world.launch">
    <arg name="world_name" value="$(find MYROBOT_gazebo)/worlds/MYROBOT.world"/>
    <!-- more default parameters can be changed here -->
  </include>
</launch>

With MYROBOT.world:

<?xml version="1.0" ?>
<sdf version="1.4">
  <world name="default">
    <include>
      <uri>model://ground_plane</uri>
    </include>
    <include>
      <uri>model://sun</uri>
    </include>
    <include>
      <uri>model://gas_station</uri>
      <name>gas_station</name>
      <pose>-2.0 7.0 0 0 0 0</pose>
    </include>
  </world>
</sdf>


USING GAZEBO SPAWNER NODE

Cli:
rosrun gazebo_ros spawn_model -file `rospack find MYROBOT_description`/urdf/MYROBOT.urdf -urdf -x 0 -y 0 -z 1 -model MYROBOT

Roslaunch (e.g.):
<node name="spawn_urdf" pkg="gazebo_ros" type="spawn_model" args="-file $(find baxter_description)/urdf/baxter.urdf -urdf -z 1 -model baxter" />

Roslaunch,2 (e.g.):
<!-- Convert an xacro and put on parameter server -->
<param name="robot_description" command="$(find xacro)/xacro.py $(find pr2_description)/robots/pr2.urdf.xacro" />

<!-- Spawn a robot into Gazebo -->
<node name="spawn_urdf" pkg="gazebo_ros" type="spawn_model" args="-param robot_description -urdf -model pr2" />


MODEL DATABASE

../catkin_ws/src
    /MYROBOT_description
        package.xml
        CMakeLists.txt
        model.config
        /urdf
            MYROBOT.urdf
        /meshes
            mesh1.dae
            mesh2.dae
            ...
        /materials
        /plugins
        /cad

With:

    /home/user/catkin_workspace/src - this is treated as the location of a Gazebo Model Database
    /MYROBOT_description - this directory is treated as a single Gazebo model folder
    model.config - this is a required configuration file for Gazebo to find this model in its database
    MYROBOT.urdf - this is your robot description file, also used by Rviz, MoveIt!, etc
    /meshes - put your .stl or .dae files in here, just as you would with regular URDFs


FILE model.config

 <?xml version="1.0"?>
  <model>
    <name>MYROBOT</name>
    <version>1.0</version>
    <sdf>urdf/MYROBOT.urdf</sdf>
    <author>
      <name>My name</name>
      <email>name@email.address</email>
    </author>
    <description>
      A description of the model
    </description>
  </model>

ENVIRONMENTAL VARIABLE

Cli:
  export GAZEBO_MODEL_PATH=/home/user/catkin_ws/src/


EXPORTING MODELS FROM package.xml

https://www.programmersought.com/article/43738722364/

(e.g.)
<exec_depend>gazebo_ros</run_depend>
<export>
  <gazebo_ros gazebo_model_path="${prefix}/models"/>
  <gazebo_ros gazebo_media_path="${prefix}/worlds"/>
</export>

OR (e.g.)    
   <gazebo_ros
      plugin_path="${prefix}/lib"
      gazebo_media_path="${prefix}"
      gazebo_model_path="${prefix}/models"
      />


MIGRATION TO ROS2

https://github.com/ros-simulation/gazebo_ros_pkgs/wiki/ROS-2-Migration:-Gazebo-ROS-Paths#env-hooks
