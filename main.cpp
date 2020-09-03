#include <iostream>
#include <string>
#include <exception>

//Oh HELL no!
//using namespace std;


//While I COULD use std::runtime_error here I opted to write my own error handling just to
//Make sure I understand how it all works.

//In fact there's a lot of ways I could do this... https://en.cppreference.com/w/cpp/error/exception

//Let's use an exception class instead of a char const*
//You can also derive other forms of exceptions from this very exception.
//Very power. Much custom. Waow.
//However you need to pay close attention to the order of the catch blocks since Derived is-a Base.
//Catch Derived types before Base.
//I didn't ented this to be so long or I would have used a /**/ ... fuck. I could just change it but
//Then I couldn't shame myself for failure to think ahead and where would the fun be in that?
class MrException : public std::exception{
private:
    std::string m_err;
public:
    MrException(std::string err):
        m_err{err}{
        //Nothing to do here, really.
    }

    //Return the err as a c string.
    const char* getError() const { return m_err.c_str(); }
    //Using the built in exception handling from std::exception would look more like this...
    //And it's a better way of doing things.
    //But I'm just fucking around here.
    const char* what() const noexcept { return m_err.c_str(); }
};

//Inheritor of MrException. To prove a point.
class ExceptionJr : public MrException{

public:
    ExceptionJr(std::string err):
        MrException(err){

    }
    const char* getError() const {return "ExceptionJr has this under control... actually, not he doesn't. Shit's broken. Sorry about that."; }
};

//A template, since it could be a double or a long or who knows? I mean I guess you would know when you call it... But still.
template<typename T>
T sum(T x, T y){
    //We don't know how to add chars here. We could convert to char codes and add those I guess but let's not.
    if(typeid (x) == typeid (char) || typeid (y) == typeid (char) )
        throw ExceptionJr("Shit broke, man.");
        //throw MrException("Can't be adding characters like numbers here, homie.");
        //Old hat.
        //throw "Can not sum characters, fool.";

    return x+y;
}


int main()
{
    //Can use std::endl but I am a fan of the old C way and as far as I can tell it doesn't make much difference nowadays.
    //Correct me if I'm wrong though.
    std::cout << "Yo, Dickhead!" << '\n';

    //Some error handling stuff because it's important.
    //Handling from the caller to make future maint easier. Though there likely will be none here
    //Still, better to follow best practice regardless.
    try {
        int i = sum(4,32);
        std::cout << "Sum of 4 + 32: " << i << '\n';
        int c = sum('x','y');
        std::cout << "x + y = " << c << '\n'; //Will be skipped, thanks to error handling.
    }
    catch (ExceptionJr &err) {
        //MUST catch ExceptionJr first or it will default to the Base type (MrException)
        std::cerr << "ERR: " << err.getError() << '\n';
    }
    //Fall through to the rest if the first catch doesn't know how to handle the type.
    catch(const MrException &err){
        //Now we handle with our own data types and member functions. Much more power.
        std::cerr << "ERR: " << err.getError() << '\n';
    }
    catch(const std::exception &err){
        //A catch all for derived types based on std::exception.
        std::cerr << "An exception derived from std::exception has been thrown: " << err.what() << '\n';
    }
    catch(...){ //Catch all, for errors of unknown type. Often used to wrap main's code entirely which I guess I am mostly doing.
        std::cerr << "Well, I guess I didn't see that coming. You broke it in a way I did not expect. Good job. \n" <<
                     "Error: Type Unknown.";
    }
    return 0;
}
