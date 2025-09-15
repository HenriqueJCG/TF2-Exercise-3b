from launch import LaunchDescription
from launch_ros.actions import Node

from launch_ros.substitutions import FindPackageShare
from launch.substitutions import PathJoinSubstitution

def generate_launch_description():

    pkg_dir = FindPackageShare('pubsub_custom_param')
    param_file = PathJoinSubstitution([pkg_dir,'config', 'params.yaml'])

    pub_node = Node(
        package='pubsub_custom_param',
        executable='publisher_class',
        parameters=[param_file],
        output='screen'
    )
    sub_node = Node(
        package='pubsub_custom_param',
        executable='subscriber_class',
        output='screen'
    )

    ld = LaunchDescription()
    ld.add_action(pub_node)
    ld.add_action(sub_node)

    return ld
