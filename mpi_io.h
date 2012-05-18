#include <mpi.h>
#include <assert.h>

int MPI_open(void **fd, const char *filename, int flags) {
    int mpi_open_mode = 0;
    *fd = malloc(sizeof(MPI_File));
    assert(*fd != NULL);
    if (flags & O_RDONLY) mpi_open_mode |= MPI_MODE_RDONLY;
    if (flags & O_RDWR) mpi_open_mode |= MPI_MODE_RDWR;
    if (flags & O_WRONLY) mpi_open_mode |= MPI_MODE_WRONLY;
    if (flags & O_CREAT) mpi_open_mode |= MPI_MODE_CREATE;
    if (flags & O_APPEND) mpi_open_mode |= MPI_MODE_APPEND;
    return MPI_File_open(MPI_COMM_SELF, (char *)filename, mpi_open_mode, MPI_INFO_NULL, *fd);
}

int MPI_read(void *fd, void *buf, off_t offset, size_t len) {
    MPI_File *fh = (MPI_File *)fd;
    MPI_Status status;
    MPI_File_read_at(*fh, offset, buf, len, MPI_CHAR, &status);
    return 0;
}

int MPI_write(void *fd, void *buf, off_t offset, size_t len) {
    MPI_File *fh = (MPI_File *)fd;
    MPI_Status status;
    MPI_File_write_at(*fh, offset, buf, len, MPI_CHAR, &status);
    return 0;
}

int MPI_close(void **fd) {
    MPI_File *fh = (MPI_File *)*fd;
    MPI_File_close(fh);
    free(*fd);
    *fd = NULL;
    return 0;
}

int MPI_remove(const char *filename) {
    MPI_File_delete((char *)filename, MPI_INFO_NULL);
    return 0;
}

int MPI_mkdir(const char *dirname) {
    const char *realname = dirname;

    if (!strncmp(dirname, "plfs:", 5)) realname += 5;
    if (realname == dirname)
        return mkdir(realname, 0700);
    return plfs_mkdir(realname, 0700);
}

int MPI_rmdir(const char *dirname) {
    const char *realname = dirname;

    if (!strncmp(dirname, "plfs:", 5)) realname += 5;
    if (realname == dirname)
        return rmdir(realname);
    return plfs_rmdir(realname);
}
