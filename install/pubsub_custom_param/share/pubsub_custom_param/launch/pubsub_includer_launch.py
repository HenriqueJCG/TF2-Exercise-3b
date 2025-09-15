from launch import LaunchDescription
from launch_ros.actions import Node

from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import PathJoinSubstitution


def generate_launch_description():

    #share folder of the package that contains the launch file to be included
    pkg_dir = FindPackageShare('pubsub_custom_param')
    #launch file to be included is pubsub_launch.py that creates a publisher and a subscriber
    launch_to_include = PathJoinSubstitution([pkg_dir,'launch', 'pubsub_launch.py'])
    #include the launch file
    subpub_nodes = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(launch_to_include)
    )
    
    #define a second subscriber
    sub_node2 = Node(
        name='subscriber_node2',
        package='pubsub_custom_param',
        executable='subscriber_class',
        output='screen'
    )

    ld = LaunchDescription()
    ld.add_action(subpub_nodes)
    ld.add_action(sub_node2)

    return ld

