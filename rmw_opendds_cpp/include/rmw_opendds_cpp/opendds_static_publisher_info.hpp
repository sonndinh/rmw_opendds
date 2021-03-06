// Copyright 2014-2017 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RMW_OPENDDS_CPP__CONNEXT_STATIC_PUBLISHER_INFO_HPP_
#define RMW_OPENDDS_CPP__CONNEXT_STATIC_PUBLISHER_INFO_HPP_

#include <atomic>

#include "rmw_opendds_shared_cpp/types.hpp"

#include "rosidl_typesupport_opendds_cpp/message_type_support.h"

class OpenDDSPublisherListener;

extern "C"
{
struct OpenDDSStaticPublisherInfo
{
  DDS::Publisher_var dds_publisher_;
  OpenDDSPublisherListener * listener_;
  DDS::DataWriter_var topic_writer_;
  const message_type_support_callbacks_t * callbacks_;
  rmw_gid_t publisher_gid;
};
}  // extern "C"

class OpenDDSPublisherListener : public DDS::PublisherListener
{
public:
  virtual void on_publication_matched(
    DDS::DataWriter *,
    const DDS::PublicationMatchedStatus & status)
  {
    current_count_ = status.current_count;
  }

  std::size_t current_count() const
  {
    return current_count_;
  }

  void on_offered_deadline_missed(
    DDS::DataWriter_ptr writer,
    const DDS::OfferedDeadlineMissedStatus& status
  )
  {
    ACE_UNUSED_ARG(writer);
    ACE_UNUSED_ARG(status);
    // Add your implementation here
  }

  void on_offered_incompatible_qos(
    DDS::DataWriter_ptr writer,
    const DDS::OfferedIncompatibleQosStatus& status
  )
  {
    ACE_UNUSED_ARG(writer);
    ACE_UNUSED_ARG(status);
    // Add your implementation here
  }

  void on_liveliness_lost(
    DDS::DataWriter_ptr writer,
    const DDS::LivelinessLostStatus& status
  )
  {
    ACE_UNUSED_ARG(writer);
    ACE_UNUSED_ARG(status);
    // Add your implementation here
  }

private:
  std::atomic<std::size_t> current_count_;
};

#endif  // RMW_OPENDDS_CPP__CONNEXT_STATIC_PUBLISHER_INFO_HPP_
