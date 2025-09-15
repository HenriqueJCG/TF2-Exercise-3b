from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    OpaqueFunction,
    RegisterEventHandler,
    Shutdown,
)
from launch.conditions import IfCondition, UnlessCondition
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def launch_setup(context, *args, **kwargs):

    # General arguments
    launch_rviz = LaunchConfiguration("launch_rviz")

    rviz2_config_file = PathJoinSubstitution(
        [FindPackageShare("rviz2_marker_demo"), "rviz", "rviz2_marker_demo.rviz"]
    )

    rviz2_marker_demo = Node(
        package="rviz2_marker_demo",
        executable="rviz_node",
        name="rviz_node",
        output="screen",
    )

    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output="log",
        arguments=["-d", rviz2_config_file],
        condition=IfCondition(launch_rviz),
        on_exit=Shutdown(),
    )

    world_broadcaster = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="world_broadcaster",
        arguments=["0.3", "0", "0", "0", "0", "0", "1", "world", "assembly_frame"],
    )


    nodes_to_start = [
        rviz2_marker_demo,
        rviz_node,
        world_broadcaster,
    ]

    return nodes_to_start


def generate_launch_description():
    declared_arguments = []

    declared_arguments.append(
        DeclareLaunchArgument("launch_rviz", default_value="true", description="Launch RViz?")
    )

    return LaunchDescription(declared_arguments + [OpaqueFunction(function=launch_setup)])