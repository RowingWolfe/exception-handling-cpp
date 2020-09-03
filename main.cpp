#include <iostream>

//Oh HELL no!
//using namespace std;

template<typename T>
T sum(T x, T y){
    if(typeid (x) == typeid (char) || typeid (y) == typeid (char) )
        throw "Can not sum characters, fool.";

    return x+y;
}

int main()
{
    std::cout << "Yo, Dickhead!" << '\n';

    //Some error handling stuff because it's important.
    //Handling from the caller to make future maint easier. Though there likely will be none here
    //Still, better to follow best practice regardless.
    try {
        int i = sum(4,32);
        std::cout << "Sum of 4 + 32: " << i << '\n';
        int c = sum('x','y');
        std::cout << "x + y = " << c << '\n'; //Will be skipped, thanks to error handling.
    }  catch (char const* err) {
        std::cerr << "ERR: " << err << '\n';
    }
    return 0;
}
