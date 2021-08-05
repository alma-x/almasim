#!/bin/bash
#https://unix.stackexchange.com/questions/244372/how-to-execute-shell-command-produced-using-echo-and-sed
# TODO, ci rinuncio
#echo "export GAZEBO_MODEL_PATH=${GAZEBO_MODEL_PATH}:${PWD}/models" | bash
#eval "$(echo "export GAZEBO_MODEL_PATH=${GAZEBO_MODEL_PATH}:${PWD}/models")"

# copy and run following code in a terminal in ../almasim
export GAZEBO_MODEL_PATH=${GAZEBO_MODEL_PATH}:${PWD}/models



