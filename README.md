# almasim_ur3

SIMULATION LAUNCHER and ADDED CONTENTE for erc21 almax

SETUP: TODO

USAGE: roslaunch almasim_ur3 godspeed.launch PARAM:=VALUE

params:		lite, default:false _removes gui from gazebo, rviz
		zombie, default:true _activate node respawn TODO
		pyv3, default:false _launches python3 nodes TODO
		...,... _set the models to spawn
		...,... _set used sensors

OTHER CONTENT:

nodelaunch.launch _spawns required nodes

populate.launch _spawns models for the simulation

models/ _contains .sdf model descriptors and .dae meshes

TODO _various stuff to add to our package and existing ones


WIKI:
-CONCEPTS:

(godspeed.launch)
line 7: launcher argument
line 8: arg condition (if/unless), arg NAME value usage
line 17: arg value transfer
line 21: package (in the same workspace) automatic search

(populate.launch)
line 8: package (in the same workspace) automatic search

(NAME.sdf)
line 21: automatic file search

(package.xml)
line 55: exporting to GAZEBO_PATH the (current) directory, letting all other files to automatically serach for stuff

# almasim
