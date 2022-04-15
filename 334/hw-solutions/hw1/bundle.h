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


typedef struct redirection_t {
    std::pair<int, int> stdin;
    std::pair<int, int> stdout;
} redirection_t;


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
    std::string execute(int fd_in, int fd_out, std::string &str_in);

    /* Creates a subprocess, executes the given command
    *  and returns a pair of int for (in, out) file descriptors.
    */
    redirection_t subprocess(std::string &cmd);

    std::string readFromFD(int fd);
};


#endif //BUNDLE_H