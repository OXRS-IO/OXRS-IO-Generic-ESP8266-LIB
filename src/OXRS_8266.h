/*
 * OXRS_8266.h
 */

#ifndef OXRS_8266_H
#define OXRS_8266_H

#include <OXRS_MQTT.h>                // For MQTT pub/sub
#include <OXRS_API.h>                 // For REST API

// I2C
#define       I2C_SDA                   4
#define       I2C_SCL                   5

// REST API
#define       REST_API_PORT             80

class OXRS_8266 : public Print
{
  public:
    // These are only needed if performing manual configuration in your sketch, otherwise
    // config is provisioned via the API and bootstrap page
    void setMqttBroker(const char * broker, uint16_t port);
    void setMqttClientId(const char * clientId);
    void setMqttAuth(const char * username, const char * password);
    void setMqttTopicPrefix(const char * prefix);
    void setMqttTopicSuffix(const char * suffix);

    void begin(jsonCallback config, jsonCallback command);
    void loop(void);

    // Firmware can define the config/commands it supports - for device discovery and adoption
    void setConfigSchema(JsonVariant json);
    void setCommandSchema(JsonVariant json);

    // Helpers for registering custom REST API endpoints
    void apiGet(const char * path, Router::Middleware * middleware);
    void apiPost(const char * path, Router::Middleware * middleware);
        
    // Helpers for publishing to stat/ and tele/ topics
    bool publishStatus(JsonVariant json);
    bool publishTelemetry(JsonVariant json);

    // Implement Print.h wrapper
    virtual size_t write(uint8_t);
    using Print::write;

  private:
    void _initialiseNetwork(byte * mac);
    void _initialiseMqtt(byte * mac);
    void _initialiseRestApi(void);

    bool _isNetworkConnected(void);
};

#endif
