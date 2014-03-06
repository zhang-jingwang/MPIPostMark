#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <plfs.h>

int PLFS_open(void **fd, const char *filename, int flags) {
    plfs_error_t rv;
    rv = plfs_open((Plfs_fd **)fd, filename, flags, getpid(), 0644, NULL);
    return(plfs_error_to_errno(rv));
}

int PLFS_read(void *fd, void *buf, off_t offset, size_t len) {
    ssize_t got;
    plfs_error_t rv;
    got = 0;
    rv = plfs_read(fd, buf, len, offset, &got);
    if (rv == PLFS_SUCCESS) {
        return(got);
    }
    return(plfs_error_to_errno(rv));
}

int PLFS_write(void *fd, void *buf, off_t offset, size_t len) {
    plfs_error_t rv;
    ssize_t did;
    pid_t pid = getpid();
    did = 0;
    rv = plfs_write(fd, buf, len, offset, pid, &did);
    if (rv == PLFS_SUCCESS) {
        return(did);
    }
    return(plfs_error_to_errno(rv));
}

int PLFS_close(void **fd) {
    int refs;
    //    ret = plfs_sync((Plfs_fd *)*fd);
    //    if (ret) printf("Sync error! %s.", strerror(errno));
    (void)plfs_close((Plfs_fd *)*fd, getpid(), 0, 
                     O_CREAT | O_RDWR, NULL, &refs);
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
