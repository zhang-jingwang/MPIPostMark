all: postmark

postmark: postmark-1_5.c libc_io.h posix_io.h plfs_io.h
	mpicc -o postmark postmark-1_5.c -lpthread -lplfs
