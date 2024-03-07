#include <stdio.h>
#include <mosquitto.h>

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {
    printf("Received message '%s' on topic '%s'\n", (char *)message->payload, message->topic);
}

int main(int argc, char *argv[]) {
    struct mosquitto *mosq;
    int rc;

    mosquitto_lib_init();

    mosq = mosquitto_new("subscriber-test", true, NULL);
    if(!mosq){
        fprintf(stderr, "Error: Out of memory.\n");
        return 1;
    }

    mosquitto_message_callback_set(mosq, on_message);

    rc = mosquitto_connect(mosq, "localhost", 1883, 60);
    if(rc){
        fprintf(stderr, "Could not connect to Broker with return code %d\n", rc);
        return rc;
    }

    mosquitto_subscribe(mosq, NULL, "test/topic", 0);

    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}
