#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

volatile sig_atomic_t keep_running = 1;

void handle_signal(int sig) {
    keep_running = 0;
}

void trigger_tv_shutdown() {
    printf("[+] Señal de apagado de TV enviada a las %ld\n", (long)time(NULL));
}

int main(int argc, char *argv[]) {
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    printf("[+] Daemon monitor de apagado iniciado.\n");

    for (int i = 0; i < 3; i++) {
        sleep(1);
        printf("Tick de monitoreo activo... ciclo %d\n", i + 1);
    }

    printf("[-] Daemon finalizado.\n");
    trigger_tv_shutdown();

    return 0;
}
