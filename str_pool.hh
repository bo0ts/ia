#ifndef _STR_POOL_HH__
#define _STR_POOL_HH__

#include <map>
#include <string>

class str_pool {
public:
  typedef std::map<std::string, unsigned long> pool;
  typedef pool::const_iterator const_iterator;
  pool::const_iterator insert(const std::string& x) {
    std::pair<const_iterator, bool> it = pool_.insert(std::make_pair(x, 0UL));
    return it.first;
  }

  void seal() {
    unsigned long i = 0UL;
    for(auto it = pool_.begin(); it != pool_.end(); ++it) {
      it->second = i;
      ++i;
    }
  }
private:
  pool pool_;
};

class str_proxy {
  str_pool::const_iterator it;
public:
  str_proxy(const std::string& x, str_pool& pool) : it(pool.insert(x)) {}

  bool operator<(const str_proxy& rhs) const {
    return it->second < rhs.it->second;
  }

  bool operator>(const str_proxy& rhs) const {
    return it->second > rhs.it->second;
  }

  bool operator==(const str_proxy& rhs) const {
    return it->second == rhs.it->second;
  }

  bool operator!=(const str_proxy& rhs) const {
    return it->second != rhs.it->second;
  }

  friend std::ostream& operator<<(std::ostream& os, const str_proxy& rhs) {
    os << rhs.it->first;
    return os;
  }
};


#endif //header guard
