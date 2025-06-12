// SPDX-License-Identifier: MIT License
/*
 * wifi_dumper - Windows Wi-Fi credential dumper (simulation tool)
 *
 * This utility uses netsh commands to extract Wi-Fi configuration,
 * profiles, passwords, and interfaces and writes them to a text file.
 *
 * Author: 0xD4rkEYe
 */

#include "..\include\wifi_dumper.h"

extern void run_interfaces(struct Command *cmd);
extern void run_profiles(struct Command *cmd);
extern void run_drivers(struct Command *cmd);
extern void run_networks(struct Command *cmd);
extern void run_dump_profiles(struct Command *cmd);
extern void run_hostednetwork(struct Command *cmd);
extern void run_autoconfig(struct Command *cmd);
extern void run_filters(struct Command *cmd);

int main(void)
{
        struct Command commands[] = {
            {
                .desc = "Show Interfaces",
                .cmd = "netsh wlan show interfaces",
                .execute = run_interfaces,
            },
            {
                .desc = "Show Profiles",
                .cmd = "netsh wlan show profiles",
                .execute = run_profiles,
            },
            {
                .desc = "Show Drivers",
                .cmd = "netsh wlan show drivers",
                .execute = run_drivers,
            },
            {
                .desc = "Show Networks",
                .cmd = "netsh wlan show networks",
                .execute = run_networks,
            },
            {
                .desc = "Dump Saved Profile Passwords",
                .cmd = NULL,
                .execute = run_dump_profiles,
            },
            {
                .desc = "Show Hosted Network",
                .cmd = "netsh wlan show hostednetwork",
                .execute = run_hostednetwork,
            },
            {
                .desc = "Show Auto Config",
                .cmd = "netsh wlan show autoconfig",
                .execute = run_autoconfig,
            },
            {
                .desc = "Show Filters",
                .cmd = "netsh wlan show filters",
                .execute = run_filters,
            },
        };

        size_t i;
        size_t total = sizeof(commands) / sizeof(commands[0]);

        /* Remove old output */
        remove(OUTPUT_FILE);

        for (i = 0; i < total; ++i)
                commands[i].execute(&commands[i]);

        return 0;
}
