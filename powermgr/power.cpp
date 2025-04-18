// powermgr/power.cpp

#include "./power.h"

void power::sysreboot(bool do_sync) {
    if (do_sync) {
        sync();
    }

    reboot(LINUX_REBOOT_CMD_RESTART);
}

void power::syspoweroff(bool do_sync) {
    if (do_sync) {
        sync();
    }

    reboot(LINUX_REBOOT_CMD_POWER_OFF);
}