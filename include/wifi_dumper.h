#ifndef WIFI_DUMPER_H
#define WIFI_DUMPER_H

#define OUTPUT_FILE "result.txt"
#define MAX_CMD_LEN 512
#define MAX_LINE_LEN 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Command
{
	const char *desc;
	const char *cmd;
	void (*execute)(struct Command *);
};

void execute_command(struct Command *cmd);

#endif // WIFI_DUMPER_H
