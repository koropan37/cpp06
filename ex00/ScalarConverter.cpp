#include "ScalarConverter.hpp"
#include <limits>
#include <sstream>
#include <cerrno>
#include <cstdlib>
#include <climits>
#include <iomanip>

const char* ScalarConverter::ConvertException::what() const throw() {
    return "Invalid input";
}

static bool isDoubleStr(const std::string& str) {
    if (str == "nan" || str == "+nan" || str == "-nan" ||
        str == "inf" || str == "+inf" || str == "-inf")
        return true;
    return false;
}

static bool isFlatStr(const std::string& str) {
    if (str == "nanf" || str == "+nanf" || str == "-nanf" ||
        str == "inff" || str == "+inff" || str == "-inff")
        return true;
    return false;
}

// static_cast ... コンパイル時に行う
// 暗黙的な変換がある場合や、予測可能な変換のときに使う
// char -> int, float -> double は安全な拡大変換(情報が失われないことが多い)
// int → char、double → float、float → int などは情報が失われる可能性がある
//（切り捨て・オーバーフロー・実装依存の結果）

void ScalarConverter::convert(const std::string& str) {
    switch (validateType(str)) {
        case CHAR: {
            printChar(static_cast<char>(str[0]));
            printInt(static_cast<char>(str[0]));
            printFloat(static_cast<char>(str[0]));
            printDouble(static_cast<char>(str[0]));
            break;
        }
        case INT: {
            std::istringstream iss(str);
            int i = 0;
            iss >> i;

            // char
            if (i < 0 || i > 127)
                std::cout << "char: impossible" << std::endl;
            else
                printChar(static_cast<char>(i));
            printInt(i);
            printFloat(static_cast<float>(i));
            printDouble(static_cast<double>(i));
            break;
        }
        case FLOAT: {
            std::string tmp(str.substr(0, str.size() - 1));
            std::stringstream iss(tmp);
            float f = 0.0f;
            iss >> f;

            //char
            if (isFlatStr(str) || f < 0.0f || f > 127.0f)
                std::cout << "char: impossible" << std::endl;
            else
                printChar(static_cast<char>(f));
            // int
            if (isFlatStr(str) ||
                f < static_cast<float>(std::numeric_limits<int>::min()) ||
                f > static_cast<float>(std::numeric_limits<int>::max()))
                std::cout << "int: impossible" << std::endl;
            else
                printInt(static_cast<int>(f));
            if (isFlatStr(str)) {
                std::cout << "float: " << str << std::endl;
                std::cout << "double: " << str.substr(0, str.size() - 1)
                << std::endl;
            }
            else {
                printFloat(f);
                printDouble(static_cast<double>(f));
            }
            break;
        }
        case DOUBLE: {
            std::stringstream iss(str);
            double d = 0.0;
            iss >> d;

            // char
            if (isDoubleStr(str) || d < 0.0 || d > 127.0)
                std::cout << "char: impossible" << std::endl;
            else
                printChar(static_cast<char>(d));
            // int
            if (isDoubleStr(str) ||
                d < static_cast<double>(std::numeric_limits<int>::min()) ||
                d > static_cast<double>(std::numeric_limits<int>::max()))
                std::cout << "int: impossible" << std::endl;
            else
                printInt(static_cast<int>(d));
            // float
            if (isDoubleStr(str))
                std::cout << "float: " << str << "f" << std::endl;
            else if  (d > static_cast<double>(std::numeric_limits<float>::max()) ||
                      d < -static_cast<double>(std::numeric_limits<float>::max()))
                std::cout << "float: impossible" << std::endl;
            else
                printFloat(static_cast<float>(d));
            if (isDoubleStr(str))
                std::cout << "double: " << str << std::endl;
            else
                printDouble(d);
        break;
        }
        case NOTHING: throw ConvertException();
    }


}

Type ScalarConverter::validateType(const std::string& str) {
    if (str.empty())
        return NOTHING;

    if (isDoubleStr(str))
        return DOUBLE;
    if (isFlatStr(str))
        return FLOAT;

    if (canConvertChar(str))
        return CHAR;
    if (canConvertInt(str))
        return INT;
    if (canConvertFloat(str))
        return FLOAT;
    if(canConvertDouble(str))
        return DOUBLE;
    return NOTHING;
}

bool ScalarConverter::canConvertChar(const std::string& str) {
    if (str.size() == 1 &&
       !std::isdigit(static_cast<unsigned char>(str[0])))
        return true;
    return false;
}

bool ScalarConverter::canConvertInt(const std::string& str) {
    // try {
    //     size_t idx = 0;
    //     long v = std::stol(str, &idx); //stol()はc++11だが、コンパイルできる？
    //     if (idx != str.size())
    //         return false;
    //     if (v < static_cast<long>(std::numeric_limits<int>::min()) ||
    //         v > static_cast<long>(std::numeric_limits<int>::max()))
    //         return false;
    //     return true;
    // } catch (const std::invalid_argument&) {
    //     return false;
    // } catch (const std::out_of_range&) {
    //     return false;
    // }
    errno = 0;
    char* end = NULL;
    const char* s = str.c_str();
    long v = std::strtol(s, &end, 10);
    if (end == s || // 変換不可能
        *end != '\0'|| // 余分な文字
        errno == ERANGE || //overflow
        v < static_cast<long>(std::numeric_limits<int>::min()) ||
        v > static_cast<long>(std::numeric_limits<int>::max()))
        return false;
    return true;

}

bool ScalarConverter::canConvertFloat(const std::string& str) {
    if (str[str.size() - 1] != 'f')
        return false;
    std::string tmp = str.substr(0, str.size() - 1);
    errno = 0;
    char* end = NULL;
    const char* s = tmp.c_str();
    double d = std::strtod(s, &end);
    if (end == s ||
        *end != '\0'||
        errno == ERANGE ||
        d > static_cast<double>(std::numeric_limits<float>::max()) ||
        d < -static_cast<double>(std::numeric_limits<float>::max()))
        return false;
    return true;

}

bool ScalarConverter::canConvertDouble(const std::string& str) {
    errno = 0;
    char* end = NULL;
    const char* s = str.c_str();
    double d = std::strtod(s, &end);
    if (end == s ||
        *end != '\0'||
        errno == ERANGE)
        return false;
    (void)d;
    return true;
}

void ScalarConverter::printChar(char c) {
    if (std::isprint(static_cast<unsigned char>(c)))
      std::cout << "char: '" << c << "'" << std::endl;
     else
      std::cout << "char: Non displayable" << std::endl;
}

void ScalarConverter::printInt(int i) {
    std::cout << "int: " << i << std::endl;
}

void ScalarConverter::printFloat(float f) {
    std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f"
              << std::endl;
}
// setprecision(1) で小数点以下1桁まで表示

void ScalarConverter::printDouble(double d) {
    std::cout << "double: " << std::fixed << std::setprecision(1) << d
              << std::endl;
}
