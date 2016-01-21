#include <vector>
#include <map>
#include <iostream>
#include <obi/util/show.hpp>
#include <obi/meta/if_all_any.hpp>

int main(int argc, const char *argv[]) {
    // pull in operator
    using obi::util::operator<<;


    std::cout << std::boolalpha
              << obi::meta::if_all<true,true>() << std::endl
              << obi::meta::if_all_t<true,true>::value << std::endl
              << obi::meta::if_all_v<true,true,false> << std::endl

              << obi::meta::if_any<true,true>() << std::endl
              << obi::meta::if_any_t<false,false>::value << std::endl
              << obi::meta::if_any_v<true,false,true> << std::endl

              << std::endl;
    return 0;
}
