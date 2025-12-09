#ifndef SCALARCONCERTER_HPP_
#define SCALARCONCERTER_HPP_

#include <string>
#include <iostream>

enum Type {
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    NOTHING
};

class ScalarConverter {
 private:
    ScalarConverter();                    
    ScalarConverter(const ScalarConverter&); 
    ScalarConverter& operator=(const ScalarConverter&);
    ~ScalarConverter();
    //privateに宣言して実装しないことでインスタンス化を防止

 public:
    static void convert(const std::string& str);

    class ConvertException : public std::exception {
     public:
        virtual const char* what() const throw();
    };
 
 private:
    static bool canConvertChar(const std::string& str);
    static bool canConvertInt(const std::string& str);
    static bool canConvertFloat(const std::string& str);
    static bool canConvertDouble(const std::string& str);
    
    static void printChar(char c);
    static void printInt(int i);
    static void printFloat(float f);
    static void printDouble(double d);
    static Type validateType(const std::string& str);
};

#endif
