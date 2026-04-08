#include <stddef.h>
#include <stdio.h>

enum EVENT_TYPE { EVENT_A = 0, EVENT_B, EVENT_MAX };

typedef void (*event_callback_t)(void *arg);

static event_callback_t g_callbacks[EVENT_MAX] = {0};
static void *g_callback_args[EVENT_MAX] = {0};

void register_event(enum EVENT_TYPE type, void (*callback)(void *), void *arg) {
    if ((int)type >= 0 && type < EVENT_MAX) {
        g_callbacks[type] = callback;
        g_callback_args[type] = arg;
    }
}

void trigger_event(enum EVENT_TYPE type) {
    if ((int)type >= 0 && type < EVENT_MAX && g_callbacks[type]) {
        g_callbacks[type](g_callback_args[type]);
    }
}

static void on_event_a(void *arg) {
    const char *msg = (const char *)arg;
    if (msg) {
        printf("%s\n", msg);
    }
}

int main(void) {
    const char *msg = "Event A triggered";
    register_event(EVENT_A, on_event_a, (void *)msg);
    trigger_event(EVENT_A);
    return 0;
}
