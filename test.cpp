#define BOOST_TEST_MODULE test_filter

#include <boost/test/unit_test.hpp>
#include "lib.h"


static my_lib::ip_pool_t ip_pool = {

  {"10","5","79","165"},
  {"10","5","79","166"},
  {"10","5","79","167"},
  {"10","5","79","168"},
  {"10","5","79","169"},
  {"10","5","79","170"},
  {"10","5","79","171"},

  {"192","168","79","171"},
  {"192","168","79","172"},

  {"192","168","80","171"},
};


BOOST_AUTO_TEST_SUITE(test_lib)

BOOST_AUTO_TEST_CASE(test_split)
{
  BOOST_CHECK(my_lib::split("", '.')      == my_lib::ip_t({""}));
  BOOST_CHECK(my_lib::split("11", '.')    == my_lib::ip_t({"11"}));
  BOOST_CHECK(my_lib::split("..", '.')    == my_lib::ip_t({"", "", ""}));
  BOOST_CHECK(my_lib::split(".11", '.')   == my_lib::ip_t({"", "11"}));
  BOOST_CHECK(my_lib::split("11.", '.')   == my_lib::ip_t({"11", ""}));
  BOOST_CHECK(my_lib::split("11.22", '.') == my_lib::ip_t({"11", "22"}));

  BOOST_CHECK(my_lib::split("10.5.79.165", '.')    == my_lib::ip_t({"10", "5", "79", "165"}));
  BOOST_CHECK(my_lib::split("192.198.80.171", '.') == my_lib::ip_t({"192", "168", "80", "171"}));

  BOOST_CHECK(my_lib::split("10.5.79.165\t192.198.80.171", '\t') == my_lib::ip_t({"10.5.79.165", "192.198.80.171"}));
}

BOOST_AUTO_TEST_CASE(test_filter)
{
  BOOST_CHECK(my_lib::filter(ip_pool, "10")  == std::vector<int>({0, 1, 2, 3, 4, 5, 6}));
  BOOST_CHECK(my_lib::filter(ip_pool, "192") == std::vector<int>({7, 8, 9}));
}

BOOST_AUTO_TEST_CASE(test_filter_any)
{
  BOOST_CHECK(my_lib::filter(ip_pool, "171") == std::vector<int>({6, 7, 9}));
  BOOST_CHECK(my_lib::filter(ip_pool, "80")  == std::vector<int>({9}));
}

BOOST_AUTO_TEST_SUITE_END()