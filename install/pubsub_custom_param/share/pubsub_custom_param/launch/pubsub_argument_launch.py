from launch import LaunchDescription
from launch_ros.actions import Node

from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument, OpaqueFunction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.conditions import IfCondition, UnlessCondition, LaunchConfigurationNotEquals
from launch.substitutions import PathJoinSubstitution, LaunchConfiguration
from launch_ros.substitutions import FindPackageShare

def launch_setup(context, *args, **kwargs):
    # Initialize Arguments
    number_of_subscribers_argument = LaunchConfiguration("number_of_subscribers_argument")

    #Publisher node
    pub_node = Node(
        package='pubsub_custom_param',
        executable='publisher_class',
        output='screen'
    )
    #Subscriber node
    sub_node = Node(
        package='pubsub_custom_param',
        executable='subscriber_class',
        output='screen'
    )

    #Conditional subscriber node based on a launch argument
    sub2_node = Node(
        name='subscriber_node2',
        package='pubsub_custom_param',
        executable='subscriber_class',
        output='screen',
        condition=LaunchConfigurationNotEquals('number_of_subscribers_argument', '1')
        #condition=IfCondition(number_of_subscribers_argument)
    )

    nodes_to_start = [
        pub_node,
        sub_node,
        sub2_node,
    ]

    return nodes_to_start


def generate_launch_description():
    # Declare arguments
    declared_arguments = []
    # Add arguments
    declared_arguments.append(
        DeclareLaunchArgument(
            "number_of_subscribers_argument",
            default_value='1',
            description='Specifies the number of subscribers, either 1 or 2'
            #default_value='true',
            #description='Specifies whether a second subscriber is to be executed - true/false'
        )
    )

    return LaunchDescription(declared_arguments + [OpaqueFunction(function=launch_setup)])
