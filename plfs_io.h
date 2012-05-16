#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <plfs.h>

int PLFS_open(void **fd, const char *filename, int flags) {
    return plfs_open((Plfs_fd **)fd, filename, flags, getpid(), 0644, NULL);
}

int PLFS_read(void *fd, void *buf, off_t offset, size_t len) {
    return plfs_read(fd, buf, len, offset);
}

int PLFS_write(void *fd, void *buf, off_t offset, size_t len) {
    pid_t pid = getpid();
    return plfs_write(fd, buf, len, offset, pid);
}

int PLFS_close(void **fd) {
    int ret;
    //    ret = plfs_sync((Plfs_fd *)*fd);
    //    if (ret) printf("Sync error! %s.", strerror(errno));
    plfs_close((Plfs_fd *)*fd, getpid(), 0, O_CREAT | O_RDWR, NULL);
    *fd = NULL;
    return 0;
}

int PLFS_remove(const char *filename) {
    return plfs_unlink(filename);
}

int PLFS_mkdir(const char *dirname) {
    return plfs_mkdir(dirname, 0700);
}

int PLFS_rmdir(const char *dirname) {
    return plfs_rmdir(dirname);
}
