//
// Created by lianglongqun on 2023/7/18.
//

#include "kafkaservice.h"

std::string get_string_from_env(const char *name, std::string defaultvalue) {
    char *value = std::getenv(name);
    if (NULL == value) {
        return defaultvalue;
    }
    return value;
}

kafkaservice::kafkaservice() {
    using namespace kafka;
    using namespace kafka::clients::producer;

    std::string kafkaserver = get_string_from_env("KAFKA_SERVER", "10.12.81.66:9092");
    this->topic = "ops-httpflow";
    const Properties props({{"bootstrap.servers", kafkaserver}});

    this->producer = std::make_shared<kafka::clients::KafkaProducer>(props);
    std::cout << "create kafka producer,server=" << kafkaserver << ",topic=" << this->topic << std::endl;
}

void kafkaservice::writemessage(const std::string &msg) {
    ProducerRecord record(this->topic, NullKey, Value(msg.c_str(), msg.size()));

    auto deliveryCb = [](const RecordMetadata &metadata, const Error &error) {
        if (!error) {
            std::cout << "Message delivered: " << metadata.toString() << std::endl;
        } else {
            std::cerr << "Message failed to be delivered: " << error.message() << std::endl;
        }
    };

    producer->send(record, deliveryCb);
}
