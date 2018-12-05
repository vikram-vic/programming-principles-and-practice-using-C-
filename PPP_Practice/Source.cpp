/*#include "std_lib_facilities.h"
#include <iterator>

class token
{
private: 
	char type;
	double val;

public:
	token(char c) : type(c)
	{}

	token(char c, double val) : type(c), val(val)
	{}

	char getType()
	{
		return type;
	}

	int getVal()
	{
		return val;
	}
};

int main()
{
	cout << "Greetings, program!" << endl;
	
	throw runtime_error("abc");
	
	cin.get();
	auto a = 0;
	std::cout << "Expression: ";
	while (cin >> a)
	{
		


	}
	token t1('8', 5);
	token t2('+');
	token t3('8', 2);

	vector<token>tok;
	tok.push_back(t1);
	tok.push_back(t2);
	tok.push_back(t3);

	double res = 0;

	std::cout << "Size: " << tok.size() << std::endl;

	for (int i = 0; i < tok.size(); ++i)
	{
		if (tok.at(i).getType() == '+')
		{
			std::cout << tok.at(i - 1).getVal() << " + " << tok.at(i + 1).getVal() << " = ";
			res = tok.at(i - 1).getVal() + tok.at(i + 1).getVal();
		}

	}

	std::cout << res << std::endl;
	
	return 0;
	
}*/



// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//
//
//
//This file is known as calculator02buggy.cpp
//
//I have inserted 5 errors that should cause this not to compile
//I have inserted 3 logic errors that should cause the program to give wrong results
//
//First try to find an remove the bugs without looking in the book.
//If that gets tedious, compare the code to that in the book (or posted source code)
//
//Happy hunting!

#include "std_lib_facilities.h"

//------------------------------------------------------------------------------

class Token{
public:
	char kind;        // what kind of token
	double value;     // for numbers: a value 
	Token(char ch)    // make a Token from a char
		:kind(ch), value(0) { }
	Token(char ch, double val)     // make a Token from a char and a double
		:kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream 
{
private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()

public:
	Token_stream();   // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void putback(Token t);    // put a Token back
};

Token_stream ts;        // provides get() and putback()

//------------------------------------------------------------------------------


// The constructor just sets full to indicate that the buffer is empty.
Token_stream::Token_stream()  
	:full(false), buffer(0)   // no Token in buffer
{}
//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer = t;       // copy t to buffer
	full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
	if (full) {       // do we already have a Token ready?
					  // remove token from buffer
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
	case ';':    // for "print"

	case 'q':    // for "quit"
	
	case '(': case ')': case '+': case '-': case '*': case '/':
		return Token(ch);        // let each character represent itself
	
	case '.':
	
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '9':
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;              // read a floating-point number
		return Token('8', val);   // let '8' represent "a number"
	}
	default:
		error("Bad token");
	}
}

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------


double primary()                // deal with numbers and parentheses
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':    // handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
			return d;
	}
	case '8':            // we use '8' to represent a number
		return t.value;  // return the number's value
	default:
		error("primary expected");
		return NULL;
	}
}

//------------------------------------------------------------------------------


double term()                  // deal with *, /, and %
{
	double left = primary();
	Token t = ts.get();        // get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);     // put t back into the token stream
			return left;
		}
	}
}

//------------------------------------------------------------------------------


double expression()             // deal with + and -
{
	double left = term();      // read and evaluate a Term
	Token t = ts.get();        // get the next token from token stream

	while (true) 
	{
		switch (t.kind) {
		case '+':
			left += term();    // evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left += term();    // evaluate Term and subtract
			t = ts.get();
			break;
		default:
			ts.putback(t);     // put t back into the token stream
			return left;       // finally: no more + or -: return the answer
		}
	}
}

//------------------------------------------------------------------------------

int main()
try
{
	double val;
	while (cin) 
	{
		Token t = ts.get();

		if (t.kind == 'q') break; // 'q' for quit
		if (t.kind == ';')        // ';' for "print now"
			cout << "=" << val << '\n';
		else
			ts.putback(t);
		val = expression();
	}
	keep_window_open();
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}

//------------------------------------------------------------------------------                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               