//
// Created by lianglongqun on 2023/7/18.
//

#ifndef HTTPFLOW_KAFKASERVICE_H
#define HTTPFLOW_KAFKASERVICE_H

#include <kafka/KafkaProducer.h>

using namespace kafka;
using namespace kafka::clients::producer;

class kafkaservice {
private:
    Topic topic;
    std::shared_ptr<kafka::clients::KafkaProducer> producer;
public:
    kafkaservice();
    void writemessage(std::string const &msg);
};


#endif //HTTPFLOW_KAFKASERVICE_H
