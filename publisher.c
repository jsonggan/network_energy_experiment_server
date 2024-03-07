#include <stdio.h>
#include <string.h>
#include <mosquitto.h>

int main(int argc, char *argv[]) {
    struct mosquitto *mosq;
    int rc;

    mosquitto_lib_init();

    mosq = mosquitto_new("publisher-test", true, NULL);
    if(!mosq){
        fprintf(stderr, "Error: Out of memory.\n");
        return 1;
    }

    rc = mosquitto_connect(mosq, "localhost", 1883, 60);
    if(rc){
        fprintf(stderr, "Could not connect to Broker with return code %d\n", rc);
        return rc;
    }

    mosquitto_publish(mosq, NULL, "test/topic", strlen("Hello, MQTT!"), "Hello, MQTT!", 0, false);

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}


