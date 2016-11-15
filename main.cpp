#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <iterator>

using coord = std::pair<int,int>;

namespace std {
  std::ostream & operator<<(std::ostream & os, const coord & p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
  }
}

class solution {
public:
  bool isInterleave(const std::string & s1, const std::string & s2, const std::string & s3) {
    std::vector<std::vector<coord>> paths = getPath(s1, s2, s3, std::vector<coord>{std::make_pair(-1,-1)});
    for (auto path : paths) {
      std::copy(path.begin(), path.end(), std::ostream_iterator<coord>(std::cout, " "));
      std::cout << std::endl;
    }
    return !paths.empty();
  }

private:
  std::vector<std::vector<coord>> getPath(const std::string & s1, const std::string & s2, const std::string & s3, const std::vector<coord> & curr) {
    std::vector<std::vector<coord>> result;
    if (curr.size() == s3.size()+1)
      result.push_back(curr);
    else {
      // std::cout << "current path:\n";
      // std::copy(curr.begin(), curr.end(), std::ostream_iterator<coord>(std::cout, " "));
      // std::cout << std::endl;
      auto next = getNext(s1, s2, s3, curr);
      // std::cout << "next:\n";
      // std::copy(next.begin(), next.end(), std::ostream_iterator<coord>(std::cout, " "));
      // std::cout << std::endl;
      for (auto nx : next) {
	auto cpy = curr;
	cpy.push_back(nx);
	auto temp = getPath(s1, s2, s3, cpy);
	for (auto tmp : temp)
	  result.push_back(tmp);
      }
    }
    return result;
  }

  std::vector<coord> getNext(const std::string & s1, const std::string &s2, const std::string & s3, const std::vector<coord> & curr) {
    std::vector<coord> next;
    coord p = curr.back();
    if (p.first < int(s1.size()-1) && s3[curr.size()-1] == s1[p.first+1])
      next.push_back(std::make_pair(p.first+1, p.second));
    if (p.second < int(s2.size()-1) && s3[curr.size()-1] == s2[p.second+1])
      next.push_back(std::make_pair(p.first, p.second+1));
    return next;
  }
};

int main() {
  std::string s1{"aabcc"}, s2{"dbbca"}, s3{"aadbbcbcac"};


  solution soln;
  bool interleave = soln.isInterleave(s1,s2,s3);
  std::cout << s3 << (interleave ? " is " : " is NOT ") << "formed by the interleaving of " << s1 << " and " << s2 << std::endl;
}
