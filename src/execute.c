#include "..\include\wifi_dumper.h"

void execute_command(struct Command *cmd)
{
	FILE *fp;
	char buff[MAX_LINE_LEN];

	fp = _popen(cmd->cmd, "r");
	if (!fp)
		return;

	FILE *out = fopen(OUTPUT_FILE, "a");
	if (!out)
	{
		_pclose(fp);
		return;
	}

	fprintf(out, "\n===== %s =====\n", cmd->desc);

	while (fgets(buff, sizeof(buff), fp))
		fprintf(out, "%s", buff);

	fprintf(out, "===============================\n");

	fclose(out);
	_pclose(fp);
}
