// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces:msg/MyMessage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "custom_interfaces/msg/my_message.hpp"


#ifndef CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__BUILDER_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_interfaces/msg/detail/my_message__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_interfaces
{

namespace msg
{

namespace builder
{

class Init_MyMessage_name
{
public:
  explicit Init_MyMessage_name(::custom_interfaces::msg::MyMessage & msg)
  : msg_(msg)
  {}
  ::custom_interfaces::msg::MyMessage name(::custom_interfaces::msg::MyMessage::_name_type arg)
  {
    msg_.name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::msg::MyMessage msg_;
};

class Init_MyMessage_center
{
public:
  Init_MyMessage_center()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MyMessage_name center(::custom_interfaces::msg::MyMessage::_center_type arg)
  {
    msg_.center = std::move(arg);
    return Init_MyMessage_name(msg_);
  }

private:
  ::custom_interfaces::msg::MyMessage msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::msg::MyMessage>()
{
  return custom_interfaces::msg::builder::Init_MyMessage_center();
}

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__MY_MESSAGE__BUILDER_HPP_
