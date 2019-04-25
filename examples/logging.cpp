// Copyright - xxxx-2019 - Jan Christoph Uhde <Jan@UhdeJC.com>
#include <vector>
#include <map>
#include <iostream>

#ifndef _WIN32
#include <obi/util/logging.hpp>

int main(/*int argc, const char *argv[]*/) {
    {
        using namespace obi::util::logging;
        configuration::function = false;
    }
    OBI_LOG_TOPIC(error, network) << "packages lost";
    OBI_LOG(fatal) << "General Excoption";
#else
int main(/*int argc, const char *argv[]*/) {
#endif
    return 0;
}

