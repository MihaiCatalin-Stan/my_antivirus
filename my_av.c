// 315CAb_StanMihai-Catalin
#include <stdio.h>
#include <string.h>
#include <math.h>

int read_database(char database[1000][1000])
{
	FILE *file = fopen("data/urls/domains_database", "rt");
	int k = 0;
	char buffer[1000];
	while (fgets(buffer, sizeof(buffer), file)) {
		buffer[strlen(buffer) - 1] = '\0';
		strcpy(database[k], buffer);
		k++;
	}
	fclose(file);
	return k;
}

void task1(char database[1000][1000], int k)
{
	char buffer[1000], *p;
	int cnt, ok;
	FILE *filein = fopen("data/urls/urls.in", "rt");
	FILE *fileout = fopen("urls-predictions.out", "wt");
	while (fgets(buffer, sizeof(buffer), filein)) {
		buffer[strlen(buffer) - 1] = '\0';
		ok = 1;
		if (strcmp(buffer + strlen(buffer) - 4, ".exe") == 0 && ok) {
			fprintf(fileout, "1\n");
			ok = 0;
		}
		p = strtok(buffer, "/");
		for (int i = 0 ; i < k ; i++) {
			if (strstr(buffer, database[i])) {
				fprintf(fileout, "1\n");
				ok = 0;
				break;
			}
		}
		cnt = 0;
		for (int i = 0 ; i < strlen(p) && ok ; i++) {
			if (p[i] >= '0' && p[i] <= '9')
				cnt++;
			if (cnt >= strlen(p) / 10 && cnt) {
				fprintf(fileout, "1\n");
				ok = 0;
				break;
			}
		}
		if (ok)
			fprintf(fileout, "0\n");
	}
	fclose(filein);
	fclose(fileout);
}

void task2(void)
{
	FILE *filein = fopen("data/traffic/traffic.in", "rt");
	FILE *fileout = fopen("traffic-predictions.out", "wt");
	char buffer[1000], *p, *t;
	int ok;
	fgets(buffer, sizeof(buffer), filein);
	while (fgets(buffer, sizeof(buffer), filein)) {
		buffer[strlen(buffer) - 1] = '\0';
		ok = 2;
		p = strtok(buffer, ",:");
		for (int i = 0 ; i < 6 ; i++)
			p = strtok(NULL, ",:");
		if (p[1] != '0' && strlen(p) > 2)
			ok = 1;
		for (int i = 0 ; i < 12 ; i++)
			p = strtok(NULL, ",");
		if ((p[0] != '0' || p[strlen(p)] != 0) && ok == 1) {
			fprintf(fileout, "1\n");
			ok = 0;
		}
		while (p)
			p = strtok(NULL, ",");
		if (ok)
			fprintf(fileout, "0\n");
	}
	fclose(filein);
	fclose(fileout);
}

int main(void)
{
	char database[1000][1000], k;
	k = read_database(database);
	task1(database, k);
	task2();
}
