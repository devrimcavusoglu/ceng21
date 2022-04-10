#ifndef BUNDLE_H
#define BUNDLE_H

#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utility>
#include <vector>


class ProcessBundle {
public:
    std::string name;
    std::vector<std::string> commands;
    
    ProcessBundle(std::string bundle_name) {
        name = bundle_name;
    }

    // Add a command to the process bundle.
    void addCommand(std::string &cmd);

    int count() const;

    std::vector<std::string> getCommands();

    // Executes the bundle with the given commands.
    // https://stackoverflow.com/questions/762200/how-to-capture-output-of-execvp
    void execute(char* in, char *out);

    /*
    * Returns a tuple of process_id capturing execvp out
    * to STDIN
    */
    pid_t subprocess(std::string &cmd, int *fds);

    std::string readFromFD(int fd);
};


#endif //BUNDLE_H