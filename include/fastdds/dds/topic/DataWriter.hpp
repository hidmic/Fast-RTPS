// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

/**
 * @file DataWriter.hpp
 */

#ifndef _FASTRTPS_DATAWRITER_HPP_
#define _FASTRTPS_DATAWRITER_HPP_

#include <fastrtps/rtps/common/Time_t.h>
#include <fastrtps/qos/DeadlineMissedStatus.h>
#include <fastrtps/qos/IncompatibleQosStatus.hpp>

namespace eprosima {
namespace fastrtps{

class WriterQos;
class LivelinessLostStatus;
class TopicAttributes;

namespace rtps
{
class RTPSWriter;
class RTPSParticipant;
class WriteParams;
class WriterAttributes;
class InstanceHandle_t;
class GUID_t;
}

} // namespace fastrtps

namespace fastdds {
namespace dds {

class PublisherListener;
class PublisherImpl;
class Publisher;

class TypeSupport;

class DataWriterImpl;
class DataWriterListener;

/**
 * Class DataWriter, contains the actual implementation of the behaviour of the DataWriter.
 * @ingroup FASTDDS_MODULE
 */
class DataWriter
{
    friend class PublisherImpl;
    friend class DataWriterImpl;

    /**
     * Create a data writer, assigning its pointer to the associated writer.
     * Don't use directly, create Publisher using DomainRTPSParticipant static function.
     */
    DataWriter(
            DataWriterImpl* impl);

public:

    virtual ~DataWriter();

    /**
     * Write data to the topic.
     * @param data Pointer to the data
     * @return True if correct
     * @par Calling example:
     * @snippet fastrtps_example.cpp ex_PublisherWrite
     */
    bool write(
            void* data);

    /**
     * Write data with params to the topic.
     * @param data Pointer to the data
     * @param params Extra write parameters.
     * @return True if correct
     * @par Calling example:
     * @snippet fastrtps_example.cpp ex_PublisherWrite
     */
    bool write(
            void* data,
            fastrtps::rtps::WriteParams& params);

    /**
     * Write data with handle.
     * @param data Pointer to the data
     * @param handle InstanceHandle_t.
     * @return True if correct
     * @par Calling example:
     * @snippet fastrtps_example.cpp ex_PublisherWrite
     */
    bool write(
            void* data,
            const fastrtps::rtps::InstanceHandle_t& handle);

    /**
     *
     * @return
     */
    const fastrtps::rtps::GUID_t& guid();

    fastrtps::rtps::InstanceHandle_t get_instance_handle() const;

    /**
     * Get topic data type
     * @return Topic data type
     */
    TypeSupport get_type() const;

    bool wait_for_acknowledgments(
            const fastrtps::Duration_t& max_wait);

    /**
     * @brief Returns the offered deadline missed status
     * @param Deadline missed status struct
     */
    void get_offered_deadline_missed_status(
            fastrtps::OfferedDeadlineMissedStatus& status);

    bool set_attributes(const fastrtps::rtps::WriterAttributes& att);

    const fastrtps::rtps::WriterAttributes& get_attributes() const;

    bool set_qos(const fastrtps::WriterQos& qos);

    const fastrtps::WriterQos& get_qos() const;

    bool set_topic(const fastrtps::TopicAttributes& att);

    const fastrtps::TopicAttributes& get_topic() const;

    const DataWriterListener* get_listener() const;

    bool set_listener(DataWriterListener* listener);

    bool get_key_value(
            void* key_holder,
            const fastrtps::rtps::InstanceHandle_t& handle);

    bool dispose(
            void* data,
            const fastrtps::rtps::InstanceHandle_t& handle);

    bool dispose(
            void* data);

    bool get_liveliness_lost_status(
            fastrtps::LivelinessLostStatus& status);

    bool get_offered_incompatible_qos_status(
            fastrtps::OfferedIncompatibleQosStatus& status)
    {
        // Not implemented
        (void)status;
        return false;
    }

    const Publisher* get_publisher() const;

    bool assert_liveliness();

    //! Remove all listeners in the hierarchy to allow a quiet destruction
    void disable();

private:
    DataWriterImpl* impl_;
};

} /* namespace dds */
} /* namespace fastdds */
} /* namespace eprosima */

#endif //_FASTRTPS_DATAWRITER_HPP_
