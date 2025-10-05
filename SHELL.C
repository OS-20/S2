#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

void listCmd(char *opt, char *dir) {
    DIR *dp = opendir(dir);
    if (!dp) { perror("dir"); return; }
    struct dirent *d; int n = 0;
    if (!strcmp(opt, "f"))
        while ((d = readdir(dp))) printf("%s\n", d->d_name);
    else if (!strcmp(opt, "n")) {
        while ((d = readdir(dp))) n++;
        printf("Total entries: %d\n", n);
    } else printf("Usage: list f dir | list n dir\n");
    closedir(dp);
}

int main() {
    char in[100], *a[10];
    while (1) {
        printf("myshell$ ");
        if (!fgets(in, sizeof(in), stdin)) break;
        if (!(a[0] = strtok(in, " \t\n"))) continue;
        int i = 0; while ((a[++i] = strtok(NULL, " \t\n")));
        if (!strcmp(a[0], "exit")) break;
        else if (!strcmp(a[0], "list")) {
            if (a[1] && a[2]) listCmd(a[1], a[2]);
            else printf("Usage: list f dir | list n dir\n");
        } else if (fork() == 0) {
            execvp(a[0], a); perror("cmd"); exit(1);
        } else wait(NULL);
    }
}
