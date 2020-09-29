#include <iostream>

/* 使用const常量替换#define 宏变量
 *      常量指针：如果常量是一个指针，并且放在头文件中来方便别的地方使用，这个时候就需要将该指针值设置成常量，来避免该指针值被修改。
 *          格式：type* const name;
 *      指针常量：如果我们不想让常量指向的值被修改，那么就可以这样做：
 *          const type* name;
 *          或者：type const *name;
 *      有时候，我们想让这个指针的值和指针指向的值均不能被修改，这个时候我们可以使用两个const来声明常量：
 *          const type* const name;
 */

// not #define PI = 3.1415926;
const float PI = 3.1415926;
const char *WebServer = "127.0.0.1";
char* const Client = "localhost";
const char* const AppName = "perfer const inline to define";


/* 使用enum来实现在类中初始化static成员变量
 *      对于一个类的非成员常量（非const成员），并且该成员还是static静态成员变量的时候，该变量的声明必须在类的外面；
 *      对于一个类的成员常量（const成员），如果我们使用static修饰该变量，那么该变量是允许在类内部初始化的。
 */
class A{
public:
    // static int SIZE = 1;     // error: Non-const static data member must be initialized out of line

    enum {SIZE=5};
    int nums[SIZE];             // 使用enum来实现类似成员常量初始化功能

    static const int SIZE2 = 1; // static成员常量可以在类中初始化
};

void study_cls_static_var(){
    std::cout << A::SIZE << std::endl;          // 5
    std::cout << A::SIZE2 << std::endl;         // 1
}


/* 使用inline替换宏函数
 *
 */

template<typename T>
inline T& max(const T t1, const T t2) {
    return t1 > t2? t1: t2;
}


int main() {
    study_cls_static_var();
    return 0;
}
