#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void _exit(int a) {while(1);}
void *_sbrk(int a) {}
int _write(int fd, const void *buf, size_t count) {}
int _close(int fd) {}
int _fstat(int fd, struct stat *buf) {}
int _isatty(int fd) {}
off_t _lseek(int fd, off_t offset, int whence) {}
ssize_t _read(int fd, void *buf, size_t count) {}

int _kill(int pid, int sig) { return -1; } // Not implemented
int _getpid(void) { return 1; } // Return a fictional PID
