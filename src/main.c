#include "..\include\wifi_dumper.h"

extern void run_interfaces(struct Command *);
extern void run_profiles(struct Command *);
extern void run_drivers(struct Command *);
extern void run_networks(struct Command *);
extern void run_dump_profiles(struct Command *);
extern void run_hostednetwork(struct Command *);
extern void run_autoconfig(struct Command *);
extern void run_filters(struct Command *);

int main(void)
{
        struct Command commands[] = {
            {"Show Interfaces", "netsh wlan show interfaces", run_interfaces},
            {"Show Profiles", "netsh wlan show profiles", run_profiles},
            {"Show Drivers", "netsh wlan show drivers", run_drivers},
            {"Show Networks", "netsh wlan show networks", run_networks},
            {"Dump Saved Profile Passwords", NULL, run_dump_profiles},
            {"Show Hosted Network", "netsh wlan show hostednetwork", run_hostednetwork},
            {"Show Auto Config", "netsh wlan show autoconfig", run_autoconfig},
            {"Show Filters", "netsh wlan show filters", run_filters},
        };

        size_t num_cmds = sizeof(commands) / sizeof(commands[0]);
        remove(OUTPUT_FILE);

        for (size_t i = 0; i < num_cmds; ++i)
                commands[i].execute(&commands[i]);

        return 0;
}
