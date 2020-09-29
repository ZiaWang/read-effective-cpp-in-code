#include <iostream>
#include <list>
using namespace std;

/*  在使用对象之前，先将对象初始化。
 *      1. 不要依赖编译器帮助我们默认设置初值，我们应该始终确保自己将对象初始化了。
 *          - 原因是因为，有时候编译器并不会帮助我们设置初值，或者说初值是一个随机的值，这样对我们的程序来说存在隐患，影响整体开发效率（因
 *            为这种情况会导致不可预知的行为）。
 *      2. 对于内置的无成员的类型（比如int、char、double、float等），我们需要手动初始化。
 *         对于其他有成员的类型，我们要确保每一个构造函数都能够将对象的每一个成员变量都初始化。
 *
 *  初始化（initialization）与赋值（assignment）：
 *      c++中，对象的初始化是发生在调用对象的构造函数之前完成的。也就是说，在构造函数内部，对成员变量的赋值操作都是赋值，而不是初始化。
 *      比如：
 *          PhoneBook::PhoneBook(int id, const string& name, const list<PhoneNum>& phones) {
 *              // 一些对这些成员操作，实际上都是"赋值操作"，而非对成员变量的初始化。
 *              m_id = id;      // 对于内置类型来说，赋值操作的成本跟初始化是一样的
 *              m_name = name;       // 对于非内置类型来说，赋值操作的成本较高
 *              m_phones = phones;
 *          }
 *
 *      原因：
 *          对上面构造函数，当我们实例化一个PhoneBook对象的时候，实际上会先调用每一个成员变量的默认构造函数，然后再调用成员变量的拷贝赋值函数
 *          来赋值。很显然，第一步调用成员变量的默认构造函数是无意义且浪费资源的。
 *      解决方案：
 *          使用成员变量的初始化列表可以避免上面的问题，使用初始化列表之后，就会只调用一次成员变量的拷贝构造函数来实现初始化。
 *
 *  使用初始化列表的另一个好处就是可以让我们避免忘记初始化某个成员变量，而导致成员变量的值不确定（使用初值）
 *
 *  综上，为了避免在对象初始化之前过早地使用它们，需要：
 *      1. 手工初始化内置型non-member对象
 *      2. 使用初始化列表初始化成员
 *      3. TODO: 在“初始化次序不确定性”情况下，为免除“跨编译单元之初始化次序”问题，请以local static对象替换non-localstatic对象。(还需要在理解下)
 *
 */
class PhoneNum{};

class PhoneBook{
public:
    PhoneBook(int id, const string& name, const list<PhoneNum>& phones);
private:

    // 初始化的顺序与声明的顺序保持一致，因此PhoneBook成员变量的初始化顺序就是m_id、m_name、m_phones
    // 即使构造函数中的初始化列表不是这个顺序，也仍然会根据声明的顺序来初始化。
    int m_id;
    string m_name;
    list<PhoneNum> m_phones;
};

//PhoneBook::PhoneBook(int id, const string& name, const list<PhoneNum>& phones) {
//    // 一些对这些成员操作，实际上都是"赋值操作"，而非对成员变量的初始化。
//    m_id = id;      // 对于内置类型来说，赋值操作的成本很低，也可以这样做
//    m_name = name;       // 对于
//    m_phones = phones;
//}

PhoneBook::PhoneBook(int id, const string &name, const list<PhoneNum> &phones)
    :m_id(id),          // 这个时候，就是直接调用成员变量的拷贝构造函数来实例化这几个成员变量。
     m_name(name),
     m_phones(phones)
{}


int main() {
    return 0;
}
