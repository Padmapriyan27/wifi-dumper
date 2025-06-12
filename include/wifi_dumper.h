#ifndef WIFI_DUMPER_H
#define WIFI_DUMPER_H

/* Shared definitions and interface for Wi-Fi credential dumper */

#define OUTPUT_FILE "result.txt"
#define MAX_CMD_LEN 512
#define MAX_LINE_LEN 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct Command - Represents a command entry
 * @desc:     Description of the command
 * @cmd:      The actual shell command to run (NULL if custom-built)
 * @execute:  Pointer to the execution function for this command
 */
struct Command
{
	const char *desc;
	const char *cmd;
	void (*execute)(struct Command *);
};

/* Execute a generic command and write output to OUTPUT_FILE */
void execute_command(struct Command *cmd);

#endif /* WIFI_DUMPER_H */
