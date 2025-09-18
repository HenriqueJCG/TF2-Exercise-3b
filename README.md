# TF2 Exercise 3b
Repository for [exercise 3b](https://sir.upc.edu/projects/ros2tutorials/3-tools/index.html#exercise-3b) related to TF2 library, using Ubuntu 24.04, ROS2 Jazzy LTS and Gazebo Harmonic.

First source the setup file: `cd ~/colcon_ws3` `colcon build` `source install/setup.bash`

To run use `ros2 launch urdf_tutorial exercise_3b.launch.py`

---

- **1)**

Add launch file (*exercise_3b.launch.py*) in *urd_tutorial* package that launches the *rviz2_marker_demo* objects and the UR3 robot. The robot description is from the *urdf/ur.urdf.xacro* file.


- **2)**

Update the node that publishes the object markers array to broadcast the transforms of each object. Updates done on *src/rviz_node.cpp* in the *rviz_marker_demo* package. 

- **3)**

Add static transform in the *exercise_3b.launch.py* launch file between tf_11 and grasp_11.

---

**Youtube Video:** [https://youtu.be/irVREaEMoP0](https://youtu.be/irVREaEMoP0)