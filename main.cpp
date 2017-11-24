#include <dirent.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/stat.h>
#include <iomanip>

static void search(const char *filename, const char *basepath = ".", const char *filepath = ".") {
    DIR *dirpont;
    struct dirent *dp;

    if ((dirpont = opendir(filepath)) == nullptr)
        return perror("No such file or directory.");

    do {
        if ((dp = readdir(dirpont)) != nullptr) {
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
                continue;
            if (strcmp(dp->d_name, filename) == 0) {
                struct stat information;
                char path[1000];
                memset(path, 0, sizeof(path));
                strcat(path, filepath);
                strcat(path, "/");
                strcat(path, dp->d_name);
                stat(path, &information);

                std::cout << std::setfill(' ') << std::setw(20) << std::left << dp->d_name;
                std::cout << std::setfill(' ') << std::setw(25) << std::left << information.st_size;
                std::cout << std::setfill(' ') << std::setw(25) << std::left << information.st_blocks * 512;
                std::cout << std::setfill(' ') << std::setw(25) << std::left << information.st_blocks;
                std::cout << std::setfill(' ') << std::setw(25) << std::left << information.st_blksize << std::endl;

                closedir(dirpont);
                return;
            }
        }
    } while (dp != nullptr);

    closedir(dirpont);
}

int main(int argc, char *argv[]) {
    std::cout << std::setfill(' ') << std::setw(20) << std::left << "Name";
    std::cout << std::setfill(' ') << std::setw(25) << std::left << "Size";
    std::cout << std::setfill(' ') << std::setw(25) << std::left << "Disk Size";
    std::cout << std::setfill(' ') << std::setw(25) << std::left << "Block Numbers";
    std::cout << std::setfill(' ') << std::setw(25) << std::left << "Block Size" << std::endl;

    for (int i = 1; i < argc; i++)
        search(argv[i]);

    return 0;
}