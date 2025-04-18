// powermgr/power.h

#ifndef _LIBPOWER
#define _LIBPOWER

#include <unistd.h>
#include <linux/reboot.h>
#include <sys/reboot.h>

namespace power
{
    void sysreboot(bool do_sync);
    void syspoweroff(bool do_sync);
} // namespace power

#endif