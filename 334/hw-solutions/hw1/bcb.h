#ifndef BCB_H
#define BCB_H

#include "bundle.h"

class BundleControlBlock {
public:
    std::vector<ProcessBundle*> bundles;
    
    BundleControlBlock() {}

    // Add a bundle to the control block.
    void add(ProcessBundle *pb) {
        bundles.push_back(pb);
    }

    ProcessBundle *get(char *name) {
        for (int i = 0; i < this->count(); i++) {
            if (this->bundles[i]->name == name) {
                return bundles[i];
            }
        }
    }

    bool exists(std::string bundle_name) {
        for (int i = 0; i < this->count(); i++) {
            if (this->bundles[i]->name == bundle_name)
                return true;
        }
        return false;
    }

    int count() const {
        return bundles.size();
    }

    std::vector<ProcessBundle*> all() {
        return bundles;
    }
};

#endif //BCB_H