# The Ont Programming Language.

The Ont Programming Language is not in itself a programming language. It is a bit like herb sutter's cppfront/cpp2 in that it converts the code into c++ and you then run that c++ code. But herb sutter's cppfront is a much more high level language, and he is trying to make c++ 100X safer, this repository is just a different kind of syntax to c++. With it you enter your line of code and then pass it to the `parse` function, which then turns that line of code into c++ code, you will then have to compile that code given to you.

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
    a_class() {}
}
```
Simple right? Well no, with the braces you have to put the brace keyword before, but I will soon change that so that it is just `}`. We could in fact just use '}' at this current stage but the problem with that is, that the code won't come out formatted, you will have to format it yourself. Also this code is actually incorrect, becuase we need some way of putting a `;` at the end of the last brace for `a_class`.But apart from the braces and the semicolon, it looks fine! The constructor is just the same, because the ont parser doesn't even parse it because there is no key word in that, so it is shipped straight off to the `dotcppfile`! And that it for objects(for the moment, things might be added later on)!

### Functions

With functions, the syntax is a bit complicated, well, for a bit of it anyway. So to define a function that takes no arguements we have to use the `funcdef` keyword inorder to tell the parser that we are going to make a FUNCtionDEFinition. So after the `funcdef` keyword we put the function_name as we would normally. So far the syntax is `funcdef` then `function_name`. So then if it is a function taking no arguements, we do this strange syntax: (*: _). Which will oviously need to be fixed, I don't know why I chose to use the syntax(maybe it was easier to parse?). So then if you want to have a function taking no arguements you follow that syntax, here is an example using this:
```C++
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
and the generated code will be:                                                                                              COMPILES: FALSE
```C++
auto a_function(int first, auto) second)
{
}
```
Notice that it doesn't work becuase there is an extra bracket there, but that should be resolved shortly. And that is it for functions!
