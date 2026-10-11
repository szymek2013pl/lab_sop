#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <getopt.h>

#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

void usage(char *pname) {
    
    fprintf(stderr, "USAGE:%s -n Name -p OCTAL -s SIZE\n", pname);
    exit(EXIT_FAILURE);

}

void make_file(char* name, ssize_t size, mode_t perms, int percent) {

    FILE* f;
    umask(~perms & 0777);
    
    if ((f = fopen(name, "w+")) == NULL) {

        ERR("fopen");

    }

    int i;
    char c;
    int ret;

    for (i = 0; i < size; i++) {

        /*
        if ((ret = fseek(f, 0, SEEK_END)) == -1) {

            ERR("fseek");

        }
        */
        
        if (rand() % 100 < percent) {

            c = 'A' + (rand() % 26);

        }

        else {

            c = 0;

        }

        fprintf(f, "%c", c);

    }

    if (fclose(f)) {

        ERR("fclose");

    }

}

int main(int argc, char** argv) {

    int opt;
    char* name = NULL;
    mode_t perm = -1;
    int size = -1;

    while((opt = getopt(argc, argv, "n:p:s:")) != -1) {

        if (opt == 'n') {

            name = optarg;

        }

        else if (opt == 'p') {

            perm = strtol(optarg, NULL, 8);

        }

        else if (opt == 's') {

            size = strtol(optarg, NULL, 10);
        }

        else {

            usage(argv[0]);

        }

    }

    if (name == NULL || perm == (mode_t)-1 || size == -1) {

        usage(argv[0]);

    }

    if (unlink(name) == -1 && errno != ENOENT) {

        ERR("unlink");

    }

    srand(time(NULL));

    make_file(name, size, perm, 10);
    return EXIT_SUCCESS;

} 
