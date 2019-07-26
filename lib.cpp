
#include "lib.h"

#include <cassert>

namespace my_lib {
	
std::vector<std::string> split(const std::string &str, char d)
{
  std::vector<std::string> r;

  std::string::size_type start = 0;
  std::string::size_type stop = str.find_first_of(d);
  while ( stop != std::string::npos ) {
    r.push_back(str.substr(start, stop - start));

    start = stop + 1;
    stop = str.find_first_of(d, start);
  }
  r.push_back(str.substr(start));
  return r;
}

std::vector<int> filter(const ip_pool_t& ip_pool, const std::string& s1, 
  const std::string&s2)
{
  std::vector<int> indexes;
  for ( ip_pool_t::size_type index = 0; index < ip_pool.size(); index++ ) {
    const ip_t& ip = ip_pool[index];     assert(ip.size() == 4);
    if ( ip[0] == s1 ) {
      if ( s2.empty() ) {
        indexes.push_back(index);
      } else if ( ip[1] == s2) {
        indexes.push_back(index);
      }
    }
  }
  return indexes;
}

std::vector<int> filter_any(const ip_pool_t& ip_pool, const std::string& str)
{
  std::vector<int> indexes;
  for ( ip_pool_t::size_type index = 0; index < ip_pool.size(); index++ ) {
    const ip_t& ip = ip_pool[index];     assert(ip.size() == 4);
    auto it = std::find(ip.cbegin(), ip.cend(), str);
    if ( it != ip.cend() )
      indexes.push_back(index);
  }
  return indexes;
}

}