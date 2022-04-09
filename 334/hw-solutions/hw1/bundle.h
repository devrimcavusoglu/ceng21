#ifndef BUNDLE_H
#define BUNDLE_H

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
    void execute(int in = -1, int out = -1);
};


#endif //BUNDLE_H