# Function lib and system call
1. gcc hello.c -o hello
2. ./hello
3. strace - trace system calls and signals
```
strace ./hello
execve("./hello", ["./hello"], 0x7fffa03586d0 /* 65 vars */) = 0
brk(NULL)                               = 0x556c789f5000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=139675, ...}) = 0
mmap(NULL, 139675, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fc699fcb000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260\34\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=2030544, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fc699fc9000
mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fc6999d6000
mprotect(0x7fc699bbd000, 2097152, PROT_NONE) = 0
mmap(0x7fc699dbd000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7fc699dbd000
mmap(0x7fc699dc3000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fc699dc3000
close(3)                                = 0
arch_prctl(ARCH_SET_FS, 0x7fc699fca4c0) = 0
mprotect(0x7fc699dbd000, 16384, PROT_READ) = 0
mprotect(0x556c78688000, 4096, PROT_READ) = 0
mprotect(0x7fc699fee000, 4096, PROT_READ) = 0
munmap(0x7fc699fcb000, 139675)          = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 2), ...}) = 0
brk(NULL)                               = 0x556c789f5000
brk(0x556c78a16000)                     = 0x556c78a16000
write(1, "Hello world\n", 12Hello world
)           = 12
exit_group(0)                           = ?
+++ exited with 0 +++
```
