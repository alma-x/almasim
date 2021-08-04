#!/bin/bash
#AGGIORNA SISTEMA E DIPENDENZE

sudo apt update && sudo apt full-upgrade -y && \
sudo apt install -y lsb-core g++ openssh-server gedit vim


#INSTALLA PREREQUISITI ROS

sudo apt install -y ros-melodic-robot-localization \
ros-melodic-interactive-marker-twist-server ros-melodic-twist-mux \
ros-melodic-pointcloud-to-laserscan ros-melodic-dwa-local-planner \
ros-melodic-moveit ros-melodic-rviz-imu-plugin


#INSTALLA ROSDEP(GESTORE PACCHETTI ROS), AGGIORNA

sudo rm /etc/ros/rosdep/sources.list.d/20-default.list && \
sudo apt install -y python-rosdep && sudo rosdep init && rosdep update


#ALTRE DIPENDENZE

sudo apt update && sudo apt install -y gdb gnupg2 apt-transport-https


#NUOVO WORKSPACE: INSERIRE IL NOME!

mkdir -p ~/uralma/src


#DOWNLOAD FILE (AGGIORNATI? NON MI PARE)

cd ~/uralma/src && git clone \
https://github.com/filesmuggler/universal_robot.git


# DOWNLOAD ur_modern_driver

cd ~/uralma/src && git clone -b kinetic-devel \
https://github.com/ros-industrial/ur_modern_driver.git


#INSTALLA PACCHETTI SCARICATI IN /src, SE NON VA: sudo

rosdep install --from-paths ~/uralma/src/ \
--ignore-src --rosdistro melodic -r -y


#INSTALLA teleop , joystick

sudo apt install -y ros-melodic-teleop* ros-melodic-joy*


#GRIPPER

cd ~/uralma/src && git clone -b erc_gripper https://github.com/kolaszko/ur_rg2_gripper.git


#MANAGER PACCHETTI PYTHON

sudo apt install -y python-pip


#CONTROLER

cd /usr/share && sudo git clone https://github.com/kolaszko/arm-lightweight-controller.git \
&& cd /usr/share/arm-lightweight-controller && pip install .


#WORLD

mkdir -p ~/.gazebo/models/workcell ~/.gazebo/models/pikachu

cp -r ~/uralma/src/universal_robot/ur_gazebo/models/workcell/* ~/.gazebo/models/workcell

cp -r ~/uralma/src/universal_robot/ur_gazebo/models/pikachu/* ~/.gazebo/models/pikachu


#MAKE
	
/bin/bash -c '. /opt/ros/melodic/setup.bash; cd ~/uralma; catkin_make'


#SBASHA TUTTE LE SORGENTI DI UR_ERC
echo LEGGETE IN FONDO A .bashrc
sleep 3
echo "#commentate i SOURCE DI ERC PRECEDENTI per\
 evitare conflitti">>$HOME/.bashrc
echo "#qui sotto il NUOVO, cancellate pure questi commenti">> $HOME/.bashrc 
echo "source ~/uralma/devel/setup.bash" >> ~/.bashrc
nano $HOME/.bashrc


