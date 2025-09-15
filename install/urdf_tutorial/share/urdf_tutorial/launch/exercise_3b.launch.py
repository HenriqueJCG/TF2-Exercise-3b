from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    OpaqueFunction,
    RegisterEventHandler,
    LogInfo,
    Shutdown,
)
from launch.conditions import IfCondition, UnlessCondition
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def launch_setup(context, *args, **kwargs):

    prefix = LaunchConfiguration('prefix', default='')

    # UR description
    # Type/series of used UR robot.
    # choices=["ur3", "ur3e", "ur5", "ur5e", "ur10", "ur10e", "ur16e"]
    ur_type = LaunchConfiguration('ur_type', default='ur3')
    description_package = LaunchConfiguration('description_package', default='urdf_tutorial')
    description_file = LaunchConfiguration('description_file', default='ur.urdf.xacro')

    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution(
                [FindPackageShare(description_package), "urdf", description_file]
            ),
            " ",
            "name:=",
            "ur",
            " ",
            "ur_type:=",
            ur_type,
            " ",
            "prefix:=",
            prefix,
        ]
    )
    robot_description = {"robot_description": robot_description_content}

    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="both",
        parameters=[{"use_sim_time": False}, robot_description],
    )

    joint_state_publisher_node = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        name='joint_state_publisher',
        output='screen',
        parameters=[{'use_sim_time': False}]
    )


    log_robot_description = LogInfo(
            msg=robot_description.get("robot_description"),
    )

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


    ur3_base_broadcaster = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='ur3_base_broadcaster',
        arguments=['0.3', '0', '0', '0', '0', '0', 'world', 'base_link']
    )


    nodes_to_start = [
        robot_state_publisher_node,
        joint_state_publisher_node,
        rviz2_marker_demo,
        rviz_node,
        world_broadcaster,
        ur3_base_broadcaster,
        log_robot_description
    ]

    return nodes_to_start


def generate_launch_description():
    declared_arguments = []

    declared_arguments.append(
        DeclareLaunchArgument("launch_rviz", default_value="true", description="Launch RViz?")
    )

    return LaunchDescription(declared_arguments + [OpaqueFunction(function=launch_setup)])