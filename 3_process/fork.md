# fork.c
### ./fork
```
Start: PPID=2131 PID=2195
fork_ret=2196 The 1 times
    Parent process: PPID=2131 PID=2195
0 The 1 times
    Child process: PPID=2195 PID=2196
...
fork_ret=2196 The 10 times
    Parent process: PPID=2131 PID=2195
0 The 10 times
    Child process: PPID=2195 PID=2196
--------
--------
```

### pstree -p
```
bash(2131)───fork(2195)───fork(2196)
```


###./fork_2
```
2700 -fork-> 2701 - fork-> 2703
     \------------- fork-> 2702
```
###pstree -p
```
bash(2131)───fork(2700)─┬─fork(2701)───fork(2703)
                        └─fork(2702)
```