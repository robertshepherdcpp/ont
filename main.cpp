#include<string>
#include<iostream>
#include<vector>

/*
* The syntax:
* 
* A function call:
* 
* function_call function_name<>!;
* 
* A class:
* 
* object class_name
* 
* A brace:
* 
* brace {
* 
* Include file
* 
* use ~filename~
* 
* Make a functoin(no args)
* 
* funcdef function_name(*: _)
* 
* MAke a function(as many args)
* 
* funcdef more(var: int, vartwo: double)
*/

std::vector<std::string> dotcppfile{};

struct first {};
struct last {};
int indent = 0;
bool using_namespace_std = false;

namespace corresponding
{
	std::string use = "#include";
	std::string inputoutput = "<iostream>";
	std::string str = "<string>";
	std::string vector = "<vector>";
	std::string output = "std::cout ";
	std::string oppositetrailing = "<<";
}

auto get_first_keyword(std::string str_)
{
	int j = 0;
	for (auto i : str_)
	{
		if (i == ' ')
		{
			break;
		}
		// incrememt the index count.
		j++;
	}


	// so that we don't overlow.
	if (j > str_.size())
	{
		j = 0;
	}

	// so now we have the index of the one past the last element of the key word.
	// so we just now need to get the string out of that.

	std::string keyword = str_.substr(0, j);

	// so now we can just return the key word.
	// we will not check if is a keyword first though.
	// we will leave that to the user that called it.

	return keyword;

}

auto is_keyword(std::string s)
{
	if (s == "use")
	{
		return true;
	}
	else if (s == "funcdef")
	{
		return true;
	}
	else if (s == "brace")
	{
		return true;
	}
	else if (s == "output")
	{
		return true;
	}
	else if (s == "object")
	{
		return true;
	}
	else if (s == "funcdefmore")
	{
		return true;
	}
	else if (s == "function_call")
	{
		return true;
	}
	else if (s == "apply")
	{
		return true;
	}
	else if (s == "body")
	{
		return true;
	}
	else if (s == "vardef")
	{
		return true;
	}
	else if (s == "type_arg")
	{
		return true;
	}
	else if(s == "vardef_comp")
	{
		return true;
	}
	else if (s == "pattern_match")
	{
		return true;
	}
	else if (s == "make_instance")
	{
		return true;
	}
	else if (s == "funcdef_trailing")
	{
		return true;
	}
	else if(s == "comment")
	{
		return true;
	}
    else if(s == "input")
    {
        return true;
    }
    else if(s == "loop")
    {
        return true;
    }
		// FIXME: Add more key words and then the base case for something that isn't a keyword
		// like a compiler error message.

		return false;
}

struct exception
{
	std::string message{};

	auto what() { return message; }
};

template<char c>
auto has(std::string str_, first)
{
	if (str_[0] == c)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<char c>
auto has(std::string str_)
{
	for (auto _ : str_)
	{
		if (_ == c)
			return true;

	}
    return false;
}

template<char c>
auto has(std::string str_, last)
{
	auto x = str_[str_.size() - 1];
	if (x == c)
	{
		return true;
	}
	else
	{
		return false;
	}
}

auto amount_str(int num)
{
	std::string s_{};
	for (int i = 0; i < num; i++)
	{
		s_ += " ";
	}
	return s_;
}

auto amount_str(char c, int num)
{
	std::string s_{};
	for (int i = 0; i < num; i++)
	{
		s_ += std::to_string(c);
	}
}

auto get_str_var(std::string var_expr)
{
	// So the user will pass in something like this variable_name: type, 
	std::string my_var_expr{var_expr};
	std::string final{};
	std::string name{};
	std::string type{};
	bool second_time = false;
	int index_for_last_name{};
	bool last_var_reached = false;
	while (last_var_reached == false)
	{
		for (int i = 0; i < my_var_expr.size(); i++)
		{
			if (my_var_expr[i] == ':')
			{
				index_for_last_name = i;
				break;
			}
			else if (my_var_expr[i] == ')')
			{
				index_for_last_name = i;
				last_var_reached = true;
				break;
			}
		}
		if (has<':'>(name) == true)
		{
			name = my_var_expr.substr(0, index_for_last_name - 1);
		}
		else
		{
			name = my_var_expr.substr(0, index_for_last_name);
		}
		name = my_var_expr.substr(0, index_for_last_name);

		// Change all above my_var_expr to just var_expr
	
		// so the name will be variable_name
		if (second_time == true)
		{
			my_var_expr = my_var_expr.substr(index_for_last_name + 2, my_var_expr.size());
		}
		else
		{
			my_var_expr = my_var_expr.substr(index_for_last_name + 2, my_var_expr.size());
		}
		// so now what we have left is the type, ....
		std::string token{};
		int last_index_of_type{};
		for (int i = 0; i < my_var_expr.size(); i++)
		{
			if (my_var_expr[i] == ',')
			{
				token = ",";
				last_index_of_type = i;
				break;
			}
			else if (my_var_expr[i] == ')')
			{
				token = ")";
				last_index_of_type = i;
				break;
			}
		}
		if (has<':'>(type) == true)
		{
			type = my_var_expr.substr(1, last_index_of_type);
		}
		else
		{
			type = my_var_expr.substr(0, last_index_of_type);
		}
		type += " ";
		final += (type + name + token);
		my_var_expr = my_var_expr.substr(last_index_of_type + 1, my_var_expr.size());
		if (token == ")")
		{
			break;
		}

		name = {};
		type = {};
		second_time = true;
	}
	return final;
}

auto parse(std::string str_)
{
	auto possible_keyword = get_first_keyword(str_);
	bool b = is_keyword(possible_keyword);
	if (!b)
	{
		//throw exception{ "Error: '" + possible_keyword + "' is not a keyword." };
		if (possible_keyword == "\n")
		{
			dotcppfile.push_back("\n");
		}
		if(str_ == "}")
		   {
		   std::string current_indent = amount_str(indent - 4);
		   dotcppfile.push_back(current_indent + str_);
		}
		else if(str_ == "{")
		{
			std::string current_indent = amount_str(indent);
			dotcppfile.push_back(current_indent + str_);
		}
		else
		{	
		std::string current_indent = amount_str(indent);
		dotcppfile.push_back(current_indent + str_);
		}
	}
	else
	{
		// A valid keyword has been entered, so we are going to use it, and get the rest of the
		// expression.

		if (possible_keyword == "use")
		{
			// It will be five because use: 3 + space:\/ 1 + current_character: 1
			std::string next_expression = str_.substr(4, str_.size()); // substring from j to the end of the string.
			bool a = has < '~' >(next_expression, first{}) && has<'~'>(next_expression, last{});
			bool b = (next_expression[0] == '~') && (next_expression[next_expression.size() - 1] == '~');
			if (!a && !b)
			{
				throw exception{ "Error: Missing '~' before and/or after the include file." };
			}
			else
			{
				// The user has entered the right syntax, so we carry on:
				if (next_expression == "~inputoutput~")
				{
					std::string current_indent = amount_str(indent);
					dotcppfile.push_back(current_indent + corresponding::use + corresponding::inputoutput);
				}
				if (next_expression == "~str~")
				{
					std::string current_indent = amount_str(indent);
					dotcppfile.push_back(current_indent + corresponding::use + corresponding::str);
				}
				if (next_expression == "~vector~")
				{
					std::string current_indent = amount_str(indent);
					dotcppfile.push_back(current_indent + corresponding::use + corresponding::vector);
				}
			}
		} // if possible_keyword == "use"
		else if (possible_keyword == "comment")
		{
			std::string current_string_o = amount_str(indent);
			current_string_o += "//";
			current_string_o += str_.substr(8, str_.size());
			dotcppfile.push_back(current_string_o);
			
		} // else if possible_keyword == "comment"
		else if (possible_keyword == "funcdef")
		{
			// Needs implementing.
			// so with funcdef we will need to put it before every function definition like this:
			// funcdef function_name(a: int) -> int
			std::string current_string_o = amount_str(indent);
			current_string_o += "[[nodiscard]] ";
			std::string next_expression = str_.substr(8, str_.size()); // substring from j to the end of the string.
			current_string_o += "auto ";
			std::string function_name{};
			int IndexOfFindingFunctionName = 0;
			for (int i = 0; i < next_expression.size(); i++)
			{
				if (next_expression[i] == '(')
				{
					function_name = next_expression.substr(0, i);
					IndexOfFindingFunctionName = i;
				}
			}
			current_string_o += function_name;
			current_string_o += "(";
			if (next_expression[IndexOfFindingFunctionName + 1] == '*')
			{
				// so this is the synatax for a void function:
				// funcdef function_name(*: _)

				if (next_expression.substr((IndexOfFindingFunctionName + 4), next_expression.size()) == "void")
				{
					next_expression = next_expression.substr(IndexOfFindingFunctionName + 9, next_expression.size());
				}
				else if (next_expression.substr((IndexOfFindingFunctionName + 4), next_expression.size()) == "_")
				{
					next_expression = next_expression.substr(IndexOfFindingFunctionName + 6);
				}
				current_string_o += ")";
				if (function_name == "main" || function_name == " main" || function_name == "main ")
				{
					current_string_o += " -> int";
				}
			}
			else
			{
				// we have got a variable with a name. A variable will have the following syntax:
				// var: _  or var: auto

				int index_of_start_name = IndexOfFindingFunctionName;
				int name_final_index = 0;
				std::string current_str_to_deal = next_expression.substr(index_of_start_name, next_expression.size());
				// for(int i = 0; i < curren)
				for (int i = 0; i < current_str_to_deal.size(); i++)
				{
					if (current_str_to_deal[i] == ':')
					{
						name_final_index = i;
					}
				}
				std::string name = current_str_to_deal.substr(1, name_final_index - 1);
				if (current_str_to_deal.substr(name_final_index, name_final_index + 2) == " _")
				{
					std::string s = "auto " + name;
					current_string_o += s;
				}
				else
				{
					// we have got to find the name of the type so we will just find the next ',' or ')' character
					int last_type_index = 0;

					for (int i = name_final_index; i < current_str_to_deal.size(); i++)
					{
						if (current_str_to_deal[i] == ')')
						{
							last_type_index = i - 1;
						}
					}
					std::string type{};
					type = current_str_to_deal.substr(name_final_index + 2, last_type_index - 1);
					bool has_brace = false;
					for (int i = 0; i < type.size(); i++)
					{
						if (type[i] == '(' || type[i] == ')')
						{
							has_brace = true;
						}
					}

					bool has_brace_two = false;
					for (int i = 0; i < type.size(); i++)
					{
						if (name[i] == '(' || name[i] == ')')
						{
							has_brace = true;
						}
					}
					if (has_brace)
					{
						type = type.substr(0, type.size() - 1);
					}
					else if (!has_brace)
					{
						type = type.substr(0, type.size());
					}
					if (has_brace_two)
					{
						name = name.substr(0, name.size() - 1);
					}
					else if (!has_brace)
					{
						name = name.substr(0, name.size());
					}
					std::string s{ type + " " + name + ")" };
					current_string_o += s;
				}
			}
			dotcppfile.push_back(current_string_o);
		} // else if(possible_keyword == "funcdef")
        else if (possible_keyword == "loop")
        {
            // the syntax will be loop i to n
            //                    loop i to n
            std::string waiting{amount_str(indent)};
            waiting.append("for(int ");
            std::string rest = str_.substr(5, str_.size());
            // find the integer i.
            for(int i = 0; i < rest.size(); i++) {
                if(i < rest.size() - 2 && rest[i] == 't' && rest[i+1] == 'o' && i >= 2)
                {
                    // so this is index of the position.
                    // so we know where to is. well just assume its an integer
                    std::string variable_name{rest.substr(0, i - 1)};
                    waiting.append(variable_name);
                    waiting.append(" = 0; ");
                    waiting.append(variable_name);
                    waiting.append(" < ");
                    // here we need to find the variable name of n
                    waiting.append(rest.substr(i + 3, rest.size()));
                    waiting.append("; ");
                    waiting.append(variable_name);
                    waiting.append("++)");
                    
                }
            }
            dotcppfile.push_back(waiting);
        }
		else if (possible_keyword == "funcdef_trailing")
		{
		std::string waiting{amount_str(indent)};
	        waiting += "[[nodiscard]] ";
		std::string rest = str_.substr(17, str_.size());
		int first_bracket_index = 0;
		// so now all we have is the function_name(*: _) -> void
		int last_function_index = 0;
		for (int i = 0; i < rest.size(); i++)
		{
			if (rest[i] == ')')
			{
				last_function_index = i;
				break;
			}
			if (rest[i] == '(')
			{
				first_bracket_index = i;
			}
		}
		std::string name = rest.substr(0, first_bracket_index);
		waiting += ("auto " + name + "(");
		// name is now function_name.
		int index_last_bracket = 0;
		for (int i = 0; i < rest.size(); i++)
		{
			if (rest[i] == ')')
			{
				index_last_bracket = i;
				break;
			}
		}
		if ((last_function_index - first_bracket_index) > 4)
		{
			// so we have a variable.
			// we will get the variable by doing rest.substr(first_bracket_index, last_function_index)

			std::string variable{rest.substr(first_bracket_index, last_function_index)};
			for (int i = 0; i < variable.size(); i++)
			{
				if (variable[i] == '-')
				{
					// variable = variable.substr(0, static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1);
					variable = variable.substr(0, i - 1);
					break;
				}
			}
			std::string name{};
			//std::string type{};
			// so to get the name we will do a loop looking for ':' and then get a substr out of rest with indexes.
			int last_index_colon = 0;
		    for (int i = 0; i < variable.size(); i++)
			{
				if (variable[i] == ':')
				{
					last_index_colon = i;
					break;
				}
			}
			name = variable.substr(1, last_index_colon - 1);
			std::string type = variable.substr(last_index_colon + 2, (variable.size() - 4));
			std::string type_two{};
			//for(int i = 0; i < type.size())
			for (int i = 0; i < type.size(); i++)
			{
				if (type[i] != ')')
				{
					type_two.push_back(type[i]);
				}
			}
			waiting += (type.substr(0, type.size() - 1) + " " + name + ")");
			std::string trailing{rest.substr(last_function_index + 1, rest.size())};
			waiting += trailing;
		}
		else
		{
			// we have a function taking no parameters.
			//for (int i = 0; i < rest.size(); i++)
			//{
			//	if(rest[i] == '>')
			//}

			//waiting += ")";

			// we will just append whatever we have left onto the string that is waiting.
			std::string rest_trailing = rest.substr(index_last_bracket, rest.size());
			waiting += rest_trailing;

		}
		dotcppfile.push_back(waiting);
		} // else if(possible_keyword == "funcdef_trailing")
		else if (possible_keyword == "object")
		{
			std::string current_string_o = amount_str(indent);
			std::string bit_after_object = str_.substr(6, str_.size());
			// so we know have OBJECTNAME
			current_string_o += "struct";
			// we are going to have all things public by default.
			std::string object_name = bit_after_object;
			current_string_o += object_name;
			dotcppfile.push_back(current_string_o);
			// well there is an error here, we need the semicolon on the end brace
		}
		else if (possible_keyword == "brace")
		{
			std::string next_expression = str_.substr(6, str_.size()); // substring from j to the end of the string.
			if (next_expression == "{")
			{
				std::string current_indent = amount_str(indent);
				indent += 4;
				dotcppfile.push_back(current_indent + next_expression);
			}
			else if (next_expression == "}")
			{
				indent -= 4;
				std::string current_indent = amount_str(indent);
				dotcppfile.push_back(current_indent + next_expression);
			}
			else
			{
				// else the user has used an invalid key word and will now have to
				// catch an exception or just abort the program.
				if (next_expression[0] == '}')
				{
					indent -= 4;
				}
				else
				{
					indent += 4;
				}
				dotcppfile.push_back(amount_str(indent) + next_expression);
				//throw exception{ "You have used the brace keyword in a wrong context" };
			}
		} // else if(possible_keyword == "brace"
		else if (possible_keyword == "output")
		{
			std::string next_expression = str_.substr(7, str_.size());
			if (next_expression.find("<-") != -1)
			{
				// so we are doing output <- something;
				for (int i = 0; i < next_expression.size(); i++)
				{
					if (next_expression[i] == '<' && next_expression[i + 1] == '-')
					{
						std::string current_indent = amount_str(indent);
						std::string output_thing = next_expression.substr(next_expression.find("<-") + 3, next_expression.size());
						std::string output_s{};
						if (using_namespace_std)
						{
							output_s = "cout ";
						}
						else
						{
							output_s = corresponding::output;
						}
						dotcppfile.push_back(current_indent + output_s + corresponding::oppositetrailing + " " + output_thing);
					}
				}
			}
		} // else if(possible_key_word == "output")
		else if (possible_keyword == "funcdefmore")
		{
			// we are now parsing multiple parameters use the keyword funcdefmore.
			// the syntax will look like this:
			// funcdefmore function_name(first: int, second: char, third: bool, ...)
			std::string cppfile_waiting = amount_str(indent);
			cppfile_waiting += "[[nodiscard]] ";
			std::string rest_of_function = str_.substr(11, str_.size());
			cppfile_waiting += "auto";
			int last_index_of_name = 0;
			for (int i = 0; i < rest_of_function.size(); i++)
			{
				if (rest_of_function[i] == '(')
				{
					last_index_of_name = i;
					break;
				}
			}
			bool last_parameter_reached = false;
			std::string name = rest_of_function.substr(0, last_index_of_name);
			cppfile_waiting += name;
			cppfile_waiting += "(";
			std::string parameters = rest_of_function.substr(last_index_of_name + 1, rest_of_function.size() - 1);
			int last_reached_index = 0;

			cppfile_waiting += get_str_var(parameters);

			while (/*last_parameter_reached == */false)
			{
				// so now we just have variablename: type, variablename2: type, variablename3: type etc.
				// we will parse then one by one and then either delegate to another function, or in a while loop
				int index_of_variable_name = 0;
				for (int i = last_reached_index + 2; i < parameters.size(); i++)
				{
					if (parameters[i] == ',')
					{
						index_of_variable_name = i;
						break;
					}
					if (parameters[i] == ')')
					{
						index_of_variable_name = i - 1;
						last_parameter_reached = true;
						break;
					}
				}
				// so now we have the last index of the variable, for instance it could be:
				// s: int
				std::string variable{};
				if (last_parameter_reached == true)
				{
					variable = parameters.substr(last_reached_index + 2, index_of_variable_name - 3);
				}
				if (last_parameter_reached == false)
				{
					variable = parameters.substr(last_reached_index, index_of_variable_name);
				}
				last_reached_index = index_of_variable_name;
				// int temporary_index = index_of_variable_name
				// now assign this at the end.
				std::string name{};
				std::string type{};
				int last_name_index = 0;
				for (int i = 0; i < variable.size(); i++)
				{
					if (variable[i] == ':')
					{
						last_name_index = i;
						break;
					}
				}
				name = variable.substr(0, last_name_index);
				if (last_parameter_reached == false)
				{
					type = variable.substr(last_name_index + 2, variable.size());
				}
				else if (last_parameter_reached == true)
				{
					type = variable.substr(last_name_index + 2, variable.size() - 1);
				}
				last_name_index -= 1;

				cppfile_waiting += (type + " " + name);
				if (last_parameter_reached == true)
				{
					//cppfile_waiting.substr(0, cppfile_waiting.size() - 3);
					cppfile_waiting += ")";
				}
				else
				{
					cppfile_waiting += ", ";
				}
			} // while(last_parameter_reached == false)
			dotcppfile.push_back(cppfile_waiting);
		} // else if(possible_keyword == "funcdefmore")
		else if (possible_keyword == "function_call")
		{
			// this is the syntax for a function call:
			// function_name function_name<parameters>!;
			std::string cpp_file_waiting = amount_str(indent);
			std::string rest_of_function_call = str_.substr(14, str_.size());
			int end_index_function_name = 0;
			for (int i = 0; i < rest_of_function_call.size(); i++)
			{
				if (rest_of_function_call[i] == '<')
				{
					end_index_function_name = i;
					break;
				}
			}
			std::string function_name = rest_of_function_call.substr(0, end_index_function_name);
			cpp_file_waiting += function_name;
			std::string rest_func = rest_of_function_call.substr(end_index_function_name, rest_of_function_call.size());
			if (rest_func[0] == '<' && rest_func[1] == '>' && rest_func[2] == '!' && rest_func[3] == ';')
			{
				cpp_file_waiting += "();";
			}

			dotcppfile.push_back(cpp_file_waiting);
		} // else if(possible_keyword == "function_call
		else if (possible_keyword == "apply")
		{
			std::string cpp_file_waiting = amount_str(indent);
			cpp_file_waiting += "using namespace ";
			std::string namespace_name = str_.substr(6, str_.size());
			if (namespace_name == "standard" || namespace_name == "standard;")
			{
				namespace_name = "std;";
			}
			//namespace_name += ";";
			cpp_file_waiting += namespace_name;
			if (namespace_name == "std")
			{
				using_namespace_std = true;
			}
			dotcppfile.push_back(cpp_file_waiting);
		}
		else if (possible_keyword == "body")
		{
			// a body is a namespace.
			std::string namespace_name = str_.substr(5, str_.size());
			std::string cpp_waiting = amount_str(indent);
			cpp_waiting += ("namespace " + namespace_name);
			dotcppfile.push_back(cpp_waiting);
		}
		else if (possible_keyword == "vardef")
		{
			// so we are making a variable, it is really simple.
			std::string to_add_cpp = amount_str(indent);
			to_add_cpp += "auto ";
			std::string name_of_var{};
			int index_of_var_name_last{};
			for (int i = 7; i < str_.size(); i++)
			{
				if (str_[i] == '{')
				{
					index_of_var_name_last = i;
				}
			}
			std::string rest = str_.substr(7, str_.size());
			index_of_var_name_last -= 7;
			std::string var_name = rest.substr(0, index_of_var_name_last);
			to_add_cpp += var_name;
			std::string value = rest.substr(index_of_var_name_last, rest.size());
			to_add_cpp += value;
			dotcppfile.push_back(to_add_cpp);
		} // else if(possible_keyword == "vardef")
		else if (possible_keyword == "vardef_comp")
		{
			// so we are making a variable, it is really simple.
			std::string to_add_cpp = amount_str(indent);
			to_add_cpp += "constexpr ";
			to_add_cpp += "auto ";
			std::string name_of_var{};
			int index_of_var_name_last{};
			for (int i = 7; i < str_.size(); i++)
			{
				if (str_[i] == '{')
				{
					index_of_var_name_last = i;
				}
			}
			std::string rest = str_.substr(7, str_.size());
			index_of_var_name_last -= 7;
			std::string var_name = rest.substr(0, index_of_var_name_last);
			to_add_cpp += var_name;
			std::string value = rest.substr(index_of_var_name_last, rest.size());
			to_add_cpp += value;
			dotcppfile.push_back(to_add_cpp);
		} // else if(possible_keyword == "vardef")
		else if (possible_keyword == "type_arg")
		{
			std::string to_add_cpp{ amount_str(indent) };
			to_add_cpp += "template";
			std::string curr{ str_.substr(9, str_.size()) };
			if (curr[0] != '<')
			{
				throw exception{ "Expected a '<' after `type_arg`" };
			}
			if (curr[curr.size() - 1] != '>')
			{
				throw exception{ "Expected a '>' after " + curr.substr(1, curr.size() - 1) };
			}
			std::string rest = curr.substr(1, curr.size() - 1);
			to_add_cpp += ("<" + rest);
			dotcppfile.push_back(to_add_cpp);
		} // else if(possible_keyword == "type_arg")
		else if (possible_keyword == "pattern_match")
		{
			std::string rest{};
			rest += str_.substr(14, str_.size());
			int last_type_index = 0;
			for (int i = 0; i < rest.size(); i++)
			{
				if (rest[i] == ' ')
				{
					last_type_index = i;
					break;
				}
			}
			std::string typeone = rest.substr(0, last_type_index);
			std::string typetwo{};
			rest = rest.substr(last_type_index + 1, rest.size());
			last_type_index = 0;
			if (rest[0] == 'i' && rest[1] == 's')
			{
				rest = rest.substr(3, rest.size());
				for (int i = 0; i < rest.size(); i++)
				{
					if (rest[i] == ';')
					{
						last_type_index = i;
						break;
					}
				}
				typetwo = rest.substr(0, last_type_index);
			}
			std::string string_file_to_add{};
			string_file_to_add += ("bool " + typeone + "Is" + typetwo + " = " + "std::is_same_v<" + typeone + ", " + typetwo + ">;");
			dotcppfile.push_back((amount_str(indent) + string_file_to_add));
			std::vector<std::string> dotcpptwo{ "#include<type_traits>" };
			for (int i = 0; i < dotcppfile.size() + 1; i++)
			{
				dotcpptwo.push_back(" ");
			}
			// dotcpptwo += dotcppfile;
			for (int i = 0; i < dotcppfile.size(); i++)
			{
				dotcpptwo[i + 1] = dotcppfile[i];
			}
			dotcppfile = dotcpptwo;
		} // else if(possible_keyword == "pattern_match"
		else if (possible_keyword == "make_instance")
		{
			// So with this we want an object that is default constructable, we don't have to call the default constructor it is
			// already defaulted. So the syntax will look like this:
			std::string rest = str_.substr(14, str_.size());
			int index_for_type = 0;
			for (int i = 0; i < str_.size(); i++)
			{
				if (rest[i] == ' ')
				{
					index_for_type = i;
					break;
				}
			}
			std::string type{ rest.substr(0, index_for_type) };
			rest = rest.substr(index_for_type + 1, rest.size());
			std::string name{ rest.substr(0, rest.size() - 1) }; // - 1 to remove semicolon.
			std::string to_add_cpp{ type + " " + name + "{};" };
			dotcppfile.push_back(to_add_cpp);
		}
        else if(possible_keyword == "input")
        {
            std::string next_expression = str_.substr(6, str_.size());
			if (next_expression.find("->") != -1)
			{
				// so we are doing output <- something;
				for (int i = 0; i < next_expression.size(); i++)
				{
					if (next_expression[i] == '-' && next_expression[i + 1] == '>')
					{
						std::string current_indent = amount_str(indent);
						std::string output_thing = next_expression.substr(next_expression.find("->") + 3, next_expression.size());
						std::string output_s{};
						if (using_namespace_std)
						{
							output_s = "cin ";
						}
						else
						{
							output_s = "std::cin";
						}
						dotcppfile.push_back(current_indent + output_s + " >>" + " " + output_thing);
					}
				}
			}
        }
	}
}

auto get_input()
{
	std::string s{};
	int j = 1;
	while (s != "End")
	{
		std::cout << "|" << j << "|    ";
		std::getline(std::cin, s);
		parse(s);
		j++;
	}
	std::cout << "\n";
}

int main()
{
    parse("#include<iostream>");
    parse("int main()");
    parse("{");
    parse("output <- \"Hello World\";");
    parse("int x = 42;");
    parse("input -> xyz;");
    parse("output <- xyz;");
    parse("}");
    parse("funcdef_trailing function_name(a: int) -> float");
	parse("make_instance int c;");
	parse("pattern_match int is double;");
	parse("use ~inputoutput~");
	parse("use ~str~");
	parse("use ~vector~");
	parse("int main()");
	parse("brace {");
	parse("output <- 42;");
	parse("brace }");
	parse("funcdef function_name(type: int)");
	parse("brace {");
	parse("brace }");
	parse("funcdef function_name(avariablename: bool");
	parse("brace {");
	parse("brace }");
	parse("struct a_struct");
	parse("brace {");
	parse("funcdef function(parameter: int)");
	parse("brace {");
	parse("output <- 42;");
	parse("brace }");
	parse("brace }");
	parse("funcdef function_definition(*: _)");
	parse("brace {");
	parse("output <- 'c';");
	parse("brace }");
	parse("object object_name");
	parse("brace {");
	parse("brace }");
	parse("funcdef main(*: _)");
	parse("brace {");
	parse("brace {");
	parse("function_call function_definition<>!;");
	parse("brace }");
	parse("brace }");
	parse("funcdefmore function_name(first: bool, second: int)");
	parse("brace {");
	parse("brace }");
	parse("funcdefmore function_name(first: bool, second: int, third: char, fourth: bool)");
	parse("brace {");
	parse("brace }");
    parse("loop n to 10");
    parse("brace {");
    parse("brace }");
	// parse("funcdefmore function_name(var_int: int, var_char: char)");

	int j = 1;
	for (auto _ : dotcppfile)
	{
        std::cout << _ << "\n";

	}
}
