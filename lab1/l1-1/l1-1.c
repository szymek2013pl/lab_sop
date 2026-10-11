#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

void go_dir() {

    DIR* dir;
    struct dirent* dp;
    struct stat buf;

    int files = 0;
    int links = 0;
    int catalogs = 0;
    int others = 0;

    if ((dir = opendir(".")) == NULL) {

        ERR("opendir");

    }

    errno = 0;

    while ((dp = readdir(dir)) != NULL) {

        if (lstat(dp->d_name, &buf) == 0) {

            if (S_ISREG(buf.st_mode)) { 

                files++;

            }

            else if (S_ISDIR(buf.st_mode)) {

                catalogs++;

            }

            else if (S_ISLNK(buf.st_mode)) {

                links++;

            }

            else {

                others++;

            }

        }

        else {

            ERR("lstat");

        }

        errno = 0;

    }

    if (errno != 0) {

        ERR("readdir");

    }

    if (closedir(dir)) {

        ERR("closedir");

    }

    printf("Files: %d, Dirs: %d, Links: %d, Others: %d\n", files, catalogs, links, others);

}

int main(int argc, char** argv) {

    go_dir();
    return EXIT_SUCCESS;

}
