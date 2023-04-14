gcc -Wall -Wextra process_b.c -o process_b && ./process_b
gcc -Wall -Wextra process_a.c -o process_a && ./process_a

# Use the kill command not the bash builtin kill
# enable -n kill will disable the bash builtin kill
# You can also use $(which kill) to run the kill command
# bash uses kill to kill manage the jobs (processes) it starts
kill --signal SIGINT -q 9999999 39384


# Sidebar 
# One quick way to determine whether the command 
# you are using is a bash built-in or not is to use 
# the command “command”.

$ command -V kill
kill is a shell builtin

$ command -V echo
echo is a shell builtin

$ command -V which
which is /usr/bin/which

# help lists all bash builtin commands
$ help
GNU bash, version 5.1.16(1)-release (x86_64-pc-linux-gnu)
These shell commands are defined internally.  Type `help' to see this list.
Type `help name' to find out more about the function `name'.

# You can use the env command to launch a command on the path
env kill --help
env kill -l

You can verify this by using strace to monitor system calls while running echo vs env echo:

$ strace -f -e trace=process bash -c 'echo hello'

$ strace -f -e trace=process bash -c 'env echo hello'

