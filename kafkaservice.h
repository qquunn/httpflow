//
// Created by lianglongqun on 2023/7/18.
//

#ifndef HTTPFLOW_KAFKASERVICE_H
#define HTTPFLOW_KAFKASERVICE_H

#include <librdkafka/rdkafkacpp.h>

class kafkaservice {
private:
    std::string topic;
    RdKafka::Producer* producer;
public:
    kafkaservice();
    void writemessage(std::string const &msg);
};


#endif //HTTPFLOW_KAFKASERVICE_H
