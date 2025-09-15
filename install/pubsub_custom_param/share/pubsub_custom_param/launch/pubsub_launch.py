from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    pub_node = Node(
        package='pubsub_custom_param',
        executable='publisher_class',
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
