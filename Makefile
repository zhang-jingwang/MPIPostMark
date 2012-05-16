all: postmark

postmark: postmark-1_5.c libc_io.h posix_io.h plfs_io.h
	gcc -o postmark postmark-1_5.c -lpthread -lplfs