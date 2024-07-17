//ls命令，目前只实现ls 和 ls -l
#include"shell.h"

// 打印文件信息的函数
void print_file_info(const char *name, const struct stat *file_stat) {  //ls -l func
    
    printf("%c", S_ISDIR(file_stat->st_mode) ? 'd' : '-');// 文件类型
    printf("%c", (file_stat->st_mode & S_IRUSR) ? 'r' : '-');// 用户权限
    printf("%c", (file_stat->st_mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (file_stat->st_mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (file_stat->st_mode & S_IRGRP) ? 'r' : '-');// 组权限
    printf("%c", (file_stat->st_mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (file_stat->st_mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (file_stat->st_mode & S_IROTH) ? 'r' : '-');// 其他用户权限
    printf("%c", (file_stat->st_mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (file_stat->st_mode & S_IXOTH) ? 'x' : '-');
    printf(" %hu", file_stat->st_nlink);

    struct passwd *pw = getpwuid(file_stat->st_uid);
    struct group *gr = getgrgid(file_stat->st_gid);
    printf(" %s %s", pw->pw_name, gr->gr_name);// 获取并打印文件的所有者和组

    printf(" %5lld", file_stat->st_size);// 打印文件大小

    char timebuf[80];
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&file_stat->st_mtime));
    printf(" %s %s\n", timebuf, name);// 打印文件的最后修改时间
}

void ls(char **argv) {

    int detailed = 0;
    if (argv[1] && argv[1][0] == '-') {
        if (strchr(argv[1], 'l')) {
            detailed = 1;
        }
    }

    struct dirent *entry;
    DIR *dp = opendir(".");

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_name[0] == '.') continue;  // skip hidden files
        if (detailed) {
            struct stat file_stat;
            if (stat(entry->d_name, &file_stat) == -1) {
                perror("stat");
                continue;
            }
            print_file_info(entry->d_name, &file_stat);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dp);
}
