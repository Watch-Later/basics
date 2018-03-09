#include <gtest/gtest.h>
#include <obi/meta/is_one_of.hpp>

using namespace std;
using namespace obi::meta;

TEST(meta_is_one_of, is_one_of){
    ASSERT_TRUE((is_one_of_v<int,double,float,int>));
    ASSERT_TRUE((is_one_of_v<int,double,int,float>));
    ASSERT_FALSE((is_one_of_v<int,double,float>));
    ASSERT_FALSE((is_one_of_v<int>));
}
