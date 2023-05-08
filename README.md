# The Ont Programming Language.

The Ont Programming Language is not in itself a programming language. It is a bit like herb sutter's cppfront/cpp2 in that it converts the code into c++ and you then run that c++ code. But herb sutter's cppfront is a much more high level language, and he is trying to make c++ 10X safer, this repository is just a different kind of syntax to c++. With it you enter your line of code and then pass it to the `parse` function, which then turns that line of code into c++ code, you will then have to compile that code given to you in the form of a `std::vector<std::string>` called `dotcppfile`.

Here is the general syntax:

### Objects

With objects, i have chosen to get rid of `class` and `struct` and replace them with `object`. Strictly speaking this is not an object, an object is an instance of this. I would be up for changing the name if there is enough demmand, or you could even make your own pull request! So to make a class in the ont programming language you have to use `object object_name` and then that is it. You cannot have a brace on the same line. So an example definition of one of these objects would be like this:
```C++
object a_class
brace {
a_class() {} // constructor
brace }
```
and the generated code will be:                                                                                         COMPILES: FALSE
```C++
struct a_class
{
    a_class() {} // constructor
}
```
Simple right? Well no, with the braces you have to put the brace keyword before, but I will soon change that so that it is just `}`. We could in fact just use '}' at this current stage but the problem with that is, that the code won't come out formatted, you will have to format it yourself. Also this code is actually incorrect, becuase we need some way of putting a `;` at the end of the last brace for `a_class`.But apart from the braces and the semicolon, it looks fine! The constructor is just the same, because the ont parser doesn't even parse it because there is no key word in that, so it is shipped straight off to the `dotcppfile`! And that it for objects(for the moment, things might be added later on)!

### Functions

With functions, the syntax is a bit complicated, well, for a bit of it anyway. So to define a function that takes no arguements we have to use the `funcdef` keyword inorder to tell the parser that we are going to make a FUNCtionDEFinition. So after the `funcdef` keyword we put the function_name as we would normally. So far the syntax is `funcdef` then `function_name`. So then if it is a function taking no arguements, we do this strange syntax: (*: _). Which will oviously need to be fixed, I don't know why I chose to use the syntax(maybe it was easier to parse?). So then if you want to have a function taking no arguements you follow that syntax, here is an example using this:
```
funcdef a_function(*: _)
brace {
brace }
```
and the generated code will be:                                                                                           COMPILES: TRUE
```C++
auto a_function()
{
}
```
So that is functions taking no arguements done! So now it is time for the arguements taking one or more arguements! So now the syntax is simple, it is just like you would find in other languages like Rust. With parameters being taken in with the following syntax: `variable_name: type`, bear in mind you can pass auto as the type. So the syntax is like as before with the function taking no args for the most part. So you start of with `funcdefmore`, `funcdefmore` not `funcdef`. So then after that you give the function name, for instance `function_name`. Then you have the bracket '(' and then the syntax as shown before `variable_name: type` and then the closing bracket: ')'. Please note that you cannot use `funcdef` and `funcdefmore` interchangibly, but that might change in the future. So an example use of using a functoin with multiple arguements is like this:
```C++
funcdefmore a_function(first: int, second: auto)
brace {
brace }
```
and the generated code will be:                                                                                              COMPILES: TRUE
```C++
auto a_function(int first, auto) second)
{
}
```
Notice that it doesn't work becuase there is an extra bracket there, but that should be resolved shortly. And that is it for functions! Now I will tell you how to call functions!
So the syntax is again quite strange. You start with the `function_call` keyword, notice that every line, if you want it to get parsed by the ont compiler, has to have a keyword starting on it. So after the `function_call` keyword you will need a space, ` `, and then the function name, for instance `a_function`. Then you will need to use the angle brackets, `<>` then followed by a `!`. Notice that at the moment you cannot call a function taking arguements, well you can but I will come back to that, because the parser looks for `<>` with nothing inside of it. So you can call those functions just usein the normal c++ function call syntax: `functionname()` becuase there is no keyword the ont compiler will know to parse so it will just spit out what it was passed in. Here is an example usage:

```C++
funcdef function(*: _)
brace {
brace }
funcdef main(*: _)
brace {
function_call function<>!;
brace }
```
So, the generated code would be:                                                                                           COMPILES: TRUE
```C++
auto function()
{
}
int main()
{
    function();
}
```

### Namespaces

So there are two topics in this section, first creating namespaces and second using namespaces. I will cover creating namespaces first. So to create a namespace you have got to use the `body` keyword and then the namespace name. It is really quite simple. So here is an example use case:
```C++
body a_namespace
brace {
brace }
```
and the generated code will be:                                                                                                   COMPILES: TRUE
```C++
namespace a_namespace
{
}
```
Really simple isn't it. I didn't think `namespace` was a great name, so I chose body, the reason that I chose body was that a body has lots of features and a `namespace` has a lot of features.
Now I will move onto using namespaces. To use namespaces you have got to use the `apply` keyword, I chose this name becuase when you use a namespace you apply it to variables. So you do `apply` and then the name of the namespace. Here is an example usage:
```C++
apply a_namespace;
```
and the generated code will be:                                                                                                         COMPILES: TRUE
```C++
using namespace a_namespace;
```
It is nice isn't it with the simple naming. I will now be moving onto variables.

### Variables
With declaring variables in the ont programming language you have to use the keyword `vardef` a bit like you would have to do in JavaScript except the naming is different. In JavaScript it is `var` and in ont it is `vardef`. The syntax is a bit funny, you have to do `vardef` then the name of the variable, then `{` then the value, then the `}`. The reason I made the syntax like this is because one of the core guidlines states that you should prefer braced initialization becuase first of all if you haven't put anything in the brace initializer, the variable will get defailt constructred. So here is an example use case:
```C++
funcdef main(*: _)
brace {
var x = 42;
brace }
```
so the generated would be:                                                                                                               COMPILES: TRUE
```C++
auto main()
{
    auto x = 42;
}
```
So, really quite simple isn't it! Also notice that the code it formatted. That is one of the reasons for using `brace {` instead of `{`. Now I will move onto including header files! With variables you can also use the new `make_instance` keyword which will automatically default construct, call `type{}`, so that you don't have to worry about the type not being initialized! Here is an example use case:
```C++
funcdef main(*: _)
brace {
make_instance int i;
brace} 
```
So the generated code will be:
```C++
auto main()
{
    int i{};
}
```
This is good because we can forget about remembering to default construct types using that!

### Header Files

In the ont programming language you have got to use the `use` keyword and then it has to be followed by a space and a `~` character and then the name of the header file to include. So here is how you have to use it `use ~headerfilename~`. Here is an example use case:
```
use ~inputoutput~
use ~str~
use ~vector~
use ~iomanip~
```
So, the generated code will be:                                                                     COMPILES: TRUE
```C++
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
```
Pretty simple isn't it? I have made some header files have different names like: `inputoutput` for `iostream` and `str` for `string`. But you can still use `iostream` and `string` if you want to.
