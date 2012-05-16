all: postmark

postmark: postmark-1_5.c libc_io.h posix_io.h plfs_io.h
	mpicc -D_FILE_OFFSET_BITS=64 -o postmark postmark-1_5.c -lpthread -lplfs
