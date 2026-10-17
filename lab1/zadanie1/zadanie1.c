#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

void usage(char *pname) {
    
    fprintf(stderr, "USAGE:%s -p PATH -o FILE\n", pname);
    exit(EXIT_FAILURE);

}

void scan_directory(const char* dir_path, FILE* fp) {

    DIR* dir;
    struct dirent* dp;
    
    if ((dir = opendir(dir_path)) == NULL) {

        perror("opendir");
        return;

    }

    fprintf(fp, "SCIEZKA:\n %s\n", dir_path);

    errno = 0; // - wazne!!!

    fprintf(fp, "LISTA PLIKOW: \n");

    while ((dp = readdir(dir)) != NULL) {
        
        struct stat f_buf;

        if (strcmp(dp->d_name, "..") && strcmp(dp->d_name, ".") && strcmp(dp->d_name, "zadanie1")) {

            char p[1024] = "";

            strcat(p, dir_path);
            strcat(p, "/");
            strcat(p, dp->d_name);

            int ret;

            if ((ret = stat(p, &f_buf)) == -1) {

                ERR("stat");

            }

            fprintf(fp, "%s %ld\n", dp->d_name, (long)f_buf.st_size);

        } 
        
        errno = 0;

    }

    if (errno != 0) {

        ERR("readir");

    }

    closedir(dir);

}

int main(int argc, char** argv) {

    FILE* fp = stdout;
    int opt;
    char* arr[argc];
    int index = 0;
    char* file_name = NULL;

    while ((opt = getopt(argc, argv, "p:o:")) != -1) {

        switch(opt) {

            case 'p':

                arr[index++] = optarg;
                break;

            case 'o':

                if (file_name != NULL) {

                    usage(argv[0]);

                }
  
                file_name = optarg;
                break;

            case '?':
                default:
                    usage(argv[0]);

        }

    }

    if (optind < argc) {

        usage(argv[0]);

    }

    if (file_name != NULL) {

        if ((fp = fopen(file_name, "w")) == NULL) {

            ERR("fopen");

        }

    }
    
    if (index > 0) {

        int i;
        for (i = 0; i < index; i++) {

            scan_directory(arr[i], fp);

        }

    }

    else {

        scan_directory(".", fp);

    }

    if (fp != stdout) {

        fclose(fp);

    }
    
    return EXIT_SUCCESS;

}
