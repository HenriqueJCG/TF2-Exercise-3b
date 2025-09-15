from launch import LaunchDescription
from launch.actions import Shutdown

from launch_ros.actions import Node


def generate_launch_description():

    #node to simulate one turtle: turtlesim1/turtle1 
    turtlesim1_node=Node(
            namespace='turtlesim1',
            package='turtlesim',
            executable='turtlesim_node',
            name='turtlesim1_node',
    )
    #node to teleoperate turtesim1/turtle. Runs in a xterm. If killed, shutsdown all
    teleop1_node=Node(
            namespace='turtlesim1',
            package='turtlesim',
            executable='turtle_teleop_key',
            name='teleop1_node',
            prefix='xterm -e',
            on_exit=Shutdown(),
    )
    #node to simulate another turtle: turtlesim2/turtle1 
    turtlesim2_node=Node(
            namespace='turtlesim2',
            package='turtlesim',
            executable='turtlesim_node',
            name='turtlesim2_node'
    )
    #node that broadcasts the frame turtlesim1/turtle1 corresponding to the pose of turtle turtlesim1/turtle1
    boradcaster1_node=Node(
            package='learning_tf2',
            executable='turtle_tf2_broadcaster',
            name='boradcaster_node',
            parameters=[
                {'turtlename': 'turtlesim1/turtle1'}
            ]
    )
    #node that broadcasts the frame turtlesim2/turtle1 corresponding to the pose of turtle turtlesim2/turtle1
    boradcaster2_node=Node(
            package='learning_tf2',
            executable='turtle_tf2_broadcaster',
            name='boradcaster_node',
            parameters=[
                {'turtlename': 'turtlesim2/turtle1'}
            ]
    )
    #node that listens to the transform between frame turtlesim1/turtle1 and frame turtlesim2/turtle1 and sets the cmd_vel to move turtlesim2/turtle1 so as to be in the same pose as turtlesim1/turtle1
    listener1_node=Node(
            package='learning_tf2',
            executable='turtle_tf2_listener_simple',
            name='listener1_node',
    )
    

    ld = LaunchDescription()
    ld.add_action(turtlesim1_node)
    ld.add_action(teleop1_node)
    ld.add_action(turtlesim2_node)
    ld.add_action(boradcaster1_node)
    ld.add_action(boradcaster2_node)
    ld.add_action(listener1_node)

    return ld