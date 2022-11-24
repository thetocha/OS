#include <iostream>
#include <signal.h>
#include <cstring>

void killByID(int id){
    pid_t pid = id;
    kill(pid, SIGTERM);
}

pid_t getIDByName(char *name){
    char buf[512];
    char command[50];
    sprintf(command, "pidof -s %s", name);
    FILE *cmd_pipe = popen(command, "r");

    fgets(buf, 512, cmd_pipe);
    pid_t pid = strtoul(buf, NULL, 10);

    pclose( cmd_pipe );
    return pid;
}

void killByName(char *name){
    pid_t pid = getIDByName(name);
    killByID(pid);

}

int main(int argc, char *argv[]) {
    std::cout << "Hello, I'll kill you) " << std::endl;
    char* env = getenv("PROC_TO_KILL");
    killByName(env);
    return 0;
}
