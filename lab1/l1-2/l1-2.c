#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

void go_dir() {

    DIR* dir;
    struct dirent* dr;
    struct stat bufstat;

    int files = 0;
    int links = 0;
    int directories = 0;
    int others = 0;
    
    if ((dir = opendir(".")) == NULL) {

        ERR("readdir");

    }

    errno = 0;

    while ((dr = readdir(dir)) != NULL) {

        if (lstat(dr->d_name, &bufstat) == 0) {

            if (S_ISREG(bufstat.st_mode)) { files++; }
            else if (S_ISDIR(bufstat.st_mode)) { directories++; }
            else if (S_ISLNK(bufstat.st_mode)) { links++; }
            else { others++; }

        }
        
        errno = 0;

    }

    if (errno != 0) {

        ERR("readdir");

    }

    if (closedir(dir)) {

        ERR("closedir");

    }

    printf("files: %d, directories: %d, links: %d, others: %d\n", files, directories, links, others);

}

int main(int argc, char** argv) {

    char buf[1024];
    int i;

    if (getcwd(buf, 1024) == NULL) {

        ERR("getcwd");

    }

    for (i = 1; i < argc; i++) {

        if (chdir(argv[i]) == -1) {

            ERR("chdir");

        }
        
        printf("%s\n", argv[i]);
        go_dir();

        if (chdir(buf) == -1) {

            ERR("chdir");

        }

    }
    
    return EXIT_SUCCESS;

}
