#include <string>
#include <vector>

namespace my_lib {
	
using ip_t = std::vector<std::string>;
using ip_pool_t = std::vector<ip_t>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d);

std::vector<int> filter(const ip_pool_t& ip_pool, const std::string& s1, const std::string&s2 = std::string());

std::vector<int> filter_any(const ip_pool_t& ip_pool, const std::string& str);

}