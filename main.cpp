
#include "lib.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <tuple>


my_lib::ip_pool_t get_ip_pool()
{
  my_lib::ip_pool_t ip_pool;
  for ( std::string line; std::getline(std::cin, line);) {
    my_lib::ip_t v = my_lib::split(line, '\t');
    ip_pool.push_back(my_lib::split(v.at(0), '.'));
  }
  return ip_pool;
}

void print_ip(const my_lib::ip_t &ip)
{
  for ( auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part ) {
    if ( ip_part != ip.cbegin() )
      std::cout << ".";
    std::cout << *ip_part;
  }
  std::cout << std::endl;
}

void print_ip_pool(const my_lib::ip_pool_t& ip_pool)
{
  std::for_each(ip_pool.cbegin(), ip_pool.cend(), print_ip);    
}

void print_ip_pool(const my_lib::ip_pool_t& ip_pool, const std::vector<int> &indexes)
{
  for ( int index : indexes ) {
    print_ip(ip_pool[index]);
  }
}

int main(int argc, char const *argv[])
{
  try {
    auto ip_pool = get_ip_pool();

    // TODO reverse lexicographically sort
    std::sort(ip_pool.begin(), ip_pool.end(),
      [] (const my_lib::ip_t& lhs, const my_lib::ip_t& rhs) {
      assert(lhs.size() == rhs.size());
      auto mk_tuple = [] (const my_lib::ip_t& ip) {
        assert(ip.size() == 4);
        return std::make_tuple(std::stoi(ip[0]), std::stoi(ip[1]), 
                               std::stoi(ip[2]), std::stoi(ip[3]));
      };
      return mk_tuple(lhs) > mk_tuple(rhs);
    });

    print_ip_pool(ip_pool);

    // 222.173.235.246
    // 222.130.177.64
    // 222.82.198.61
    // ...
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    // TODO filter by first byte and output
    // ip = filter(1)
    print_ip_pool(ip_pool, my_lib::filter(ip_pool, std::string("1")));

    // 1.231.69.33
    // 1.87.203.225
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    // TODO filter by first and second bytes and output
    // ip = filter(46, 70)
    print_ip_pool(ip_pool, my_lib::filter(ip_pool, std::string("46"), std::string("70")));

    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76

    // TODO filter by any byte and output
    // ip = filter_any(46)
    print_ip_pool(ip_pool, my_lib::filter_any(ip_pool, std::string("46")));

    // 186.204.34.46
    // 186.46.222.194
    // 185.46.87.231
    // 185.46.86.132
    // 185.46.86.131
    // 185.46.86.131
    // 185.46.86.22
    // 185.46.85.204
    // 185.46.85.78
    // 68.46.218.208
    // 46.251.197.23
    // 46.223.254.56
    // 46.223.254.56
    // 46.182.19.219
    // 46.161.63.66
    // 46.161.61.51
    // 46.161.60.92
    // 46.161.60.35
    // 46.161.58.202
    // 46.161.56.241
    // 46.161.56.203
    // 46.161.56.174
    // 46.161.56.106
    // 46.161.56.106
    // 46.101.163.119
    // 46.101.127.145
    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76
    // 46.55.46.98
    // 46.49.43.85
    // 39.46.86.85
    // 5.189.203.46
  } catch ( const std::exception &e ) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
