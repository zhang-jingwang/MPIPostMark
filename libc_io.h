#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int LIBC_open(void **fd, const char *filename, int flags) {
    FILE *fp;
    int pfd;

    fp = fopen(filename, "w+");
    if (fp != NULL) {
        *fd = (void *)fp;
        return 0;
    }
#if 0
    pfd = open(filename, flags, 0644);
    if (pfd >= 0) {
        if (flags & O_WRONLY)
            fp = fdopen(pfd, "w");
        else
            fp = fdopen(pfd, "r");
        if (fp != NULL) {
            *fd = (void *)fp;
            return 0;
        }
        close(pfd);
    }
#endif
    fprintf(stderr, "Error opening file:%s: %s.\n", filename, strerror(errno));
    return -1;
}

int LIBC_read(void *fd, void *buf, off_t offset, size_t len) {
    FILE *fp = (FILE *)fd;
    fread(buf, len, 1, fp);
    return 0;
}

int LIBC_write(void *fd, void *buf, off_t offset, size_t len) {
    FILE *fp = (FILE *)fd;
    fwrite(buf, len, 1, fp);
    return 0;
}

int LIBC_close(void **fd) {
    FILE *fp = (FILE *)*fd;
    fclose(fp);
    *fd = NULL;
    return 0;
}

int LIBC_remove(const char *filename) {
    int ret;
    ret = remove(filename);
    if (ret) {fprintf(stderr, "Error delete file:%s.", strerror(errno));}
    return ret;
}

int LIBC_mkdir(const char *dirname) {
    return mkdir(dirname, 0700);
}

int LIBC_rmdir(const char *dirname) {
    return rmdir(dirname);
}
