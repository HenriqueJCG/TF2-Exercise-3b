// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces:msg/MyMessage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "custom_interfaces/msg/my_message.h"


#ifndef CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__STRUCT_H_
#define CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'center'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/MyMessage in the package custom_interfaces.
typedef struct custom_interfaces__msg__MyMessage
{
  geometry_msgs__msg__Point center;
  rosidl_runtime_c__String name;
} custom_interfaces__msg__MyMessage;

// Struct for a sequence of custom_interfaces__msg__MyMessage.
typedef struct custom_interfaces__msg__MyMessage__Sequence
{
  custom_interfaces__msg__MyMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__msg__MyMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__STRUCT_H_
