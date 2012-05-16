#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int POSIX_open(void **fd, const char *filename, int flags) {
    *fd = malloc(sizeof(int));
    if (!*fd) return -1;
    *((int *)*fd) = open(filename, flags, 0644);
    if (*((int *)*fd) >= 0) return 0;
    fprintf(stderr, "Error opening file:%s: %s.\n", filename, strerror(errno));
    free(*fd);
    *fd = NULL;
    return -1;
}

int POSIX_read(void *fd, void *buf, off_t offset, size_t len) {
    int pfd = *((int *)fd);
    read(pfd, buf, len);
    return 0;
}

int POSIX_write(void *fd, void *buf, off_t offset, size_t len) {
    int pfd = *((int *)fd);
    write(pfd, buf, len);
    return 0;
}

int POSIX_close(void **fd) {
    int pfd = *((int *)*fd);
    close(pfd);
    free(*fd);
    *fd = NULL;
}

int POSIX_remove(const char *filename) {
    int ret;
    ret = remove(filename);
    if (ret) {fprintf(stderr, "Error delete file:%s.", strerror(errno));}
    return ret;
}

int POSIX_mkdir(const char *dirname) {
    return mkdir(dirname, 0700);
}

int POSIX_rmdir(const char *dirname) {
    return rmdir(dirname);
}
