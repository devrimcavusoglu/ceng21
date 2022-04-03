#ifndef BCB_H
#define BCB_H

#include "bundle.h"


class BundleControlBlock {
public:
    BundleControlBlock() {}

    // Add a command to the process bundle.
    void add(ProcessBundle pb);

    std::vector<ProcessBundle*> all();

private:
    std::vector<ProcessBundle*> bundles;
};

#endif //BCB_H
