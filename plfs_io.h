#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <plfs.h>

int PLFS_open(void **fd, const char *filename, int flags) {
    return plfs_open((Plfs_fd **)fd, filename, flags, getpid(), 0644, NULL);
}

int PLFS_read(void *fd, void *buf, off_t offset, size_t len) {
    return plfs_read(fd, buf, len, offset);
}

int PLFS_write(void *fd, void *buf, off_t offset, size_t len) {
    return plfs_write(fd, buf, len, offset, getpid());
}

int PLFS_close(void **fd) {
    plfs_close((Plfs_fd *)*fd, getpid(), 0, O_CREAT | O_RDWR, NULL);
    *fd = NULL;
    return 0;
}

int PLFS_remove(const char *filename) {
    return plfs_unlink(filename);
}
