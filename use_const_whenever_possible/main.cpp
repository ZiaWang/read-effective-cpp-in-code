#include <iostream>
#include <vector>
using namespace std;

/* 尽可能的使用const
 *      const的作用是让我们指定一个不可以被修改的对象。
 *
 * STL迭代器与const
 *      迭代器实际上可以看作一个T*指针，当我们声明const T*的时候，实际上是声明该指针是一个常量，也就是说这个指针不能被修改，因此这个迭代器不
 *      能再去指向其他内存，但是该迭代器指向的内存中的数据是仍然可以修改的。
 *      如果我们想让迭代器指向的值不能被修改，那么就需要使用std::vector<T>::const_iter
 *
 * 注意：
 *      1. const常量必须在声明的时候就初始化，常量的初始化方式任意，这也影响了执行常量初始化的时间。
 */

void use_const_with_stl(){
    vector<int> nums = {1, 2, 3, 4};

    // 迭代器不能被修改，但是指向的值可以修改
    const vector<int>::iterator _end = nums.end() - 1;
    cout << *_end << endl;      // 4

    *_end += 1;
    cout << *_end << endl;      // 5

    // ++_end;                     // error: Cannot increment value of type 'const vector<int>::iterator' (aka 'const __wrap_iter<int *>')

    // 迭代器可以被修改，但是值不能被修改
    vector<int>::const_iterator _start = nums.cbegin();
    cout << *_start << endl;

    // (*_start)++;                // error: Cannot assign to return value because function 'operator*' returns a const value
    // *_start += 1                // error: Cannot assign to return value because function 'operator*' returns a const value

    _start++;       // 现在指向了第二个元素
    cout << *_start << endl;        // 2


    // 迭代器和值均不能被修改
    const auto _itor = nums.cbegin();
    // _itor++;            // error: Cannot increment value of type 'const std::__1::__wrap_iter<const int *>'
    // *_itor = 10;        // error: Cannot assign to return value because function 'operator*' returns a const value

}


/* const成员函数
 *      1. 两个成员函数如果只是"常量性"不同 ，是可以被重载的。
 *          即：func() const与func()是可以重载的。
 *      2. 如果我们想在常量性的成员函数中修改某个成员变量的值，那么我们需要在声明该变量的时候，使用mutable关键字。
 *         mutable关键字可以释放掉non-static成员变量的bitwise constness约束。
 *      3. 当 const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可避免代码重复。
 */


class TextBlock{
public:
    TextBlock(string text):m_text(text){};

    const char& operator[](size_t position)const{ return m_text[position]; }

    // char& operator[](size_t position){ return m_text[position]; };
    char& operator[](size_t position){
        return const_cast<char&>(
                    static_cast<const TextBlock&>(*this)[position]
                );
    }


private:
    string m_text;
};

int main() {

    TextBlock tb("Hello");
    tb[0];
    tb[0] = 's';           // 调用的是 char& operator[]

    const TextBlock ctb("Hello");
    ctb[0];                // 调用的是  const char& operator[]
    // ctb[0] = 's';       // error: Cannot assign to return value because function 'operator[]' returns a const value

    return 0;
}
