//
// Created by lianglongqun on 2023/7/18.
//

#include "kafkaservice.h"
#include <iostream>

std::string get_string_from_env(const char *name, std::string defaultvalue) {
    char *value = std::getenv(name);
    if (NULL == value) {
        return defaultvalue;
    }
    return value;
}

kafkaservice::kafkaservice() {
    std::string brokers = get_string_from_env("KAFKA_SERVER", "10.12.81.66:9092");

    this->topic = get_string_from_env("KAFKA_TOPIC", "ops-httpflow");
    std::string topic = this->topic;

    std::cout << "create kafka producer,server=" << brokers << ",topic=" << this->topic << std::endl;

    // 创建全局配置
    RdKafka::Conf* conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);

    // 错误信息
    std::string errstr;

    // 设置集群
    if (conf->set("bootstrap.servers", brokers, errstr) !=
        RdKafka::Conf::CONF_OK) {
        std::cerr << "ERROR " << errstr << std::endl;
        exit(1);
    }

    // 创建消费者实例
    RdKafka::Producer* producer = RdKafka::Producer::create(conf, errstr);
    if (!producer) {
        std::cerr << "ERROR Failed to create producer: "
                  << errstr
                  << std::endl;
        exit(1);
    }
    this->producer = producer;

    delete conf;
}

void kafkaservice::writemessage(const std::string &msg) {
    RdKafka::ErrorCode err = producer->produce(
            // 主题
            topic,
            //任何分区：内置分区器将
            //用于将消息分配给基于主题的在消息键上，或没有设定密钥
            RdKafka::Topic::PARTITION_UA,
            // 创建副本？
            RdKafka::Producer::RK_MSG_COPY,
            // 值
            const_cast<char *>(msg.c_str()), msg.size(),
            // 键
            NULL, 0,
            // 投递时间，默认当前时间
            0,
            // 消息头
            NULL,
            NULL);

    if (err != RdKafka::ERR_NO_ERROR) {
        std::cerr << "% 发布主题错误 " << topic << ": "
                  << RdKafka::err2str(err) << std::endl;
    } else {
        std::cerr << "% 队列消息 ("
                  << msg.size()
                  << " bytes) "
                  << " 主题： "
                  << topic
                  << std::endl;
    }

    producer->poll(0);
}
