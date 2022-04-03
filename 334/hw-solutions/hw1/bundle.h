#ifndef BUNDLE_H
#define BUNDLE_H

#include <vector>


class ProcessBundle {
public:
    std::string name;
    ProcessBundle(std::string bundle_name) {
        name = bundle_name;
    }

    // Add a command to the process bundle.
    void addCommand(std::string cmd);

    std::vector<char> getCommands();

    // Executes the bundle with the given commands.
    void execute();

private:
    std::vector<char> commands;

};

#endif //BUNDLE_H
