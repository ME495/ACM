# 构造函数
```
std::bitset<16> foo;
std::bitset<16> bar (0xfa2);
std::bitset<16> baz (std::string("0101111001"));
```
# 位运算操作
```
// bitset operators
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo (std::string("1001"));
  std::bitset<4> bar (std::string("0011"));

  std::cout << (foo^=bar) << '\n';       // 1010 (XOR,assign)
  std::cout << (foo&=bar) << '\n';       // 0010 (AND,assign)
  std::cout << (foo|=bar) << '\n';       // 0011 (OR,assign)

  std::cout << (foo<<=2) << '\n';        // 1100 (SHL,assign)
  std::cout << (foo>>=1) << '\n';        // 0110 (SHR,assign)

  std::cout << (~bar) << '\n';           // 1100 (NOT)
  std::cout << (bar<<1) << '\n';         // 0110 (SHL)
  std::cout << (bar>>1) << '\n';         // 0001 (SHR)

  std::cout << (foo==bar) << '\n';       // false (0110==0011)
  std::cout << (foo!=bar) << '\n';       // true  (0110!=0011)

  std::cout << (foo&bar) << '\n';        // 0010
  std::cout << (foo|bar) << '\n';        // 0111
  std::cout << (foo^bar) << '\n';        // 0101

  return 0;
}
```
# 数组下标取值
```
// bitset::operator[]
#include <iostream>       // std::cout
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo;

  foo[1]=1;             // 0010
  foo[2]=foo[1];        // 0110

  std::cout << "foo: " << foo << '\n';

  return 0;
}
```
# count()
```
// bitset::count
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<8> foo (std::string("10110011"));

  std::cout << foo << " has ";
  std::cout << foo.count() << " ones and ";
  std::cout << (foo.size()-foo.count()) << " zeros.\n";

  return 0;
}
```
Output:
```
10110011 has 5 ones and 3 zeros.
```
# size()
Return size
# test()
Return bit value
```
// bitset::test
#include <iostream>       // std::cout
#include <string>         // std::string
#include <cstddef>        // std::size_t
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<5> foo (std::string("01011"));

  std::cout << "foo contains:\n";
  std::cout << std::boolalpha;
  for (std::size_t i=0; i<foo.size(); ++i)
    std::cout << foo.test(i) << '\n';

  return 0;
}
```
Output:
```
foo contains:
true
true
false
true
false
```
# any()
Test if any bit is set
```
// bitset::any
#include <iostream>       // std::cin, std::cout
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<16> foo;

  std::cout << "Please, enter a binary number: ";
  std::cin >> foo;

  if (foo.any())
    std::cout << foo << " has " << foo.count() << " bits set.\n";
  else
    std::cout << foo << " has no bits set.\n";

  return 0;
}
```
Possible output:
```
Please, enter a binary number: 10110
0000000000010110 has 3 bits set.
```
# none()
Test if no bit is set
```
// bitset::none
#include <iostream>       // std::cin, std::cout
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<16> foo;

  std::cout << "Please, enter a binary number: ";
  std::cin >> foo;

  if (foo.none())
    std::cout << foo << " has no bits set.\n";
  else
    std::cout << foo << " has " << foo.count() << " bits set.\n";

  return 0;
}
```
Possible output:
```
Please, enter a binary number: 11010111
0000000011010111 has 6 bits set.
```
# all()
Test if all bits are set,c++11
```
// bitset::all
#include <iostream>       // std::cin, std::cout, std::boolalpha
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<8> foo;

  std::cout << "Please, enter an 8-bit binary number: ";
  std::cin >> foo;

  std::cout << std::boolalpha;
  std::cout << "all: " << foo.all() << '\n';
  std::cout << "any: " << foo.any() << '\n';
  std::cout << "none: " << foo.none() << '\n';

  return 0;
}
```
Possible output:
```
Please, enter an 8-bit binary number: 11111111
all: true
any: true
none: false
```
# set()
Set bits
```
// bitset::set
#include <iostream>       // std::cout
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo;

  std::cout << foo.set() << '\n';       // 1111
  std::cout << foo.set(2,0) << '\n';    // 1011
  std::cout << foo.set(2) << '\n';      // 1111

  return 0;
}
```
Output:
```
1111
1011
1111
```
# reset()
Reset bits
```
// bitset::reset
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo (std::string("1011"));

  std::cout << foo.reset(1) << '\n';    // 1001
  std::cout << foo.reset() << '\n';     // 0000

  return 0;
}
```
Output:
```
1001
0000
```
# flip()
Flip bits
```
// bitset::flip
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo (std::string("0001"));

  std::cout << foo.flip(2) << '\n';     // 0101
  std::cout << foo.flip() << '\n';      // 1010

  return 0;
}
```
Output:
```
0101
1010
```
# to_string()
Convert to string
```
// bitset::to_string
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> mybits;     // mybits: 0000
  mybits.set();              // mybits: 1111

  std::string mystring =
    mybits.to_string<char,std::string::traits_type,std::string::allocator_type>();

  std::cout << "mystring: " << mystring << '\n';

  return 0;
}
```
Output:
```
mystring: 1111
```
# to_ulong
Convert to unsigned long integer
```
// bitset::to_ulong
#include <iostream>       // std::cout
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo;     // foo: 0000
  foo.set();              // foo: 1111

  std::cout << foo << " as an integer is: " << foo.to_ulong() << '\n';

  return 0;
}
```
Output:
```
1111 as an integer is: 15
```
# to_ullong 
Convert to unsigned long long
```
// bitset::to_ullong
#include <iostream>       // std::cout
#include <bitset>         // std::bitset

int main ()
{
  std::bitset<4> foo;     // foo: 0000
  foo.set();              // foo: 1111

  std::cout << foo << " as an integer is: " << foo.to_ullong() << '\n';

  return 0;
}
```
Output:
```
1111 as an integer is: 15
```