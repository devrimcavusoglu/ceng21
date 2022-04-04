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
    void addCommand(std::string &cmd) {
        commands.push_back(cmd);
    }

    int count() const {
        return commands.size();
    }

    std::vector<std::string> getCommands() {
        return commands;
    }

    // Executes the bundle with the given commands.
    void execute() {
    }
};


class BundleControlBlock {
public:
    std::vector<ProcessBundle*> bundles;
    
    BundleControlBlock() {}

    // Add a bundle to the control block.
    void add(ProcessBundle *pb) {
        bundles.push_back(pb);
    }

    int count() const {
        return bundles.size();
    }

    std::vector<ProcessBundle*> all() {
        return bundles;
    }
};

#endif //BUNDLE_H
