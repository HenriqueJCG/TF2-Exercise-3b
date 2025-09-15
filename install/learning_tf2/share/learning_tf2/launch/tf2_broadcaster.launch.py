from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import Shutdown


def generate_launch_description():

    turtle_ahead_br = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="ahead_broadcaster",
        arguments=["1.0", "0", "0", "0", "0", "0", "1", "turtle1", "turtle1_ahead"],
    )

    turtlesim_node=Node(
        package='turtlesim',
        executable='turtlesim_node',
        name='sim',
        on_exit=Shutdown(),
    )

    broadcaster_node=Node(
        package='learning_tf2',
        executable='turtle_tf2_broadcaster',
        name='broadcaster1',
        parameters=[
            {'turtlename': 'turtle1'}
        ]
    )
    teleop_node=Node(
        package='turtlesim',
        executable='turtle_teleop_key',
        name='teleop_node',
        prefix='xterm -e',
        on_exit=Shutdown(),
    )

    ld = LaunchDescription()
    ld.add_action(turtle_ahead_br)
    ld.add_action(turtlesim_node)
    ld.add_action(broadcaster_node)
    ld.add_action(teleop_node)

    return ld