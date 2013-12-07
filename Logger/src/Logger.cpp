/**
 * Logger (Singleton) Source
 * @description a Logger implementing the Singleton pattern
 * @author Denis Meyer
 * @website https://sites.google.com/site/calltopowersoftware/software
 * @version 1.0.0
 * @created 3/16/11
 * @file Logger.cpp
 */
#include "../include/Logger.h"

// static variables
Logger* Logger::m_instance = 0;
std::string Logger::m_prefix = "";
std::string Logger::m_postfix = "";
std::string Logger::m_separator = " ";
bool Logger::m_output = true;
bool Logger::m_endl = true;
std::ostream *Logger::m_stream = &std::cout;
unsigned int Logger::m_nrLogs = 0;
std::string lastError = "";

/*************************************************
 * public
 *************************************************/

// return the Logger instance
Logger* Logger::instance()
{
    if (!m_instance)
    {
        m_instance = new Logger;
    }
    
    return m_instance;
}

/*************************************************
 * helper
 *************************************************/

// print nr newlines
void Logger::newLine(const int nr) const
{
    if(m_output)
    {
        for(int i = 0; i < abs(nr); ++i)
        {
            *m_stream << std::endl;
        }
    }
}

// prints str times times
void Logger::printTimes(const int times, const std::string str, const bool separator) const
{
    if(m_output && (abs(times) > 0))
    {
        *m_stream << m_prefix;
        for(int i = 0; i < abs(times); ++i)
        {
            if((i != 0) && separator)
            {
                *m_stream << m_separator;
            }
            *m_stream << str;
        }
        *m_stream << m_postfix;
        if(m_endl)
        {
            *m_stream << std::endl;
        }
    }
}

/*************************************************
 * logging
 *************************************************/

// log a std::string
bool Logger::log(const std::string str) const
{
    return logX("s", str.c_str());
}

// log an int
bool Logger::log(const int i) const
{
    return logX("i", i);
}

// log a double
bool Logger::log(const double d) const
{
    return logX("d", d);
}

// log a double**
bool Logger::log(double **d, const int rows, const int cols) const
{
    if(m_output && d)
    {
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                try {
                    *m_stream << d[i][j] << m_separator;
                } catch (...) {
                    return false;
                }
            }
            if(m_endl)
            {
                *m_stream << std::endl;
            }
        }
        ++m_nrLogs;
        return true;
    }
    return false;
}

// log a variable number of arguments
int Logger::logX(const std::string szTypes, ...) const
{
    int i = 0;
    if(m_output)
    {
        va_list vl;
        va_start(vl, szTypes);
        for( ; szTypes[i] != '\0'; ++i)
        {
            if(i == 0)
            {
                *m_stream << m_prefix;
            } else
            {
                *m_stream << m_separator;
            }
            switch(szTypes[i])
            {
                case 'b':
                    m_currType.i = va_arg(vl, int);
                    *m_stream << ((m_currType.i == 0) ? "false" : "true");
                    break;
                case 'i':
                    m_currType.i = va_arg(vl, int);
                    *m_stream << m_currType.i;
                    break;
                case 'f':
                case 'd':
                    m_currType.f = va_arg(vl, double);
                    *m_stream << m_currType.f;
                    break;
                case 'c':
                    m_currType.c = va_arg(vl, int);
                    *m_stream << m_currType.c;
                    break;
                case 's':
                    m_currType.s = va_arg(vl, char *);
                    *m_stream << (m_currType.s != 0 ? std::string(m_currType.s) : "");
                    break;
                default:
                    break;
            }
        }
        if(i != 0)
        {
            *m_stream << m_postfix;
            if(m_endl)
            {
                *m_stream << std::endl;
            }
            ++m_nrLogs;
        }
    }
    return i;
}

/*************************************************
 * setter
 *************************************************/

// set a prefix
void Logger::setPrefix(const std::string prefix)
{
    m_prefix = prefix;
}

// set a postfix
void Logger::setPostfix(const std::string postfix)
{
    m_postfix = postfix;
}

// set a separator
void Logger::setSeparator(const std::string separator)
{
    m_separator = separator;
}

// set flag if output to stream
void Logger::setOutput(const bool output)
{
    m_output = output;
}

// set flag if endline after each log
void Logger::setEndline(const bool endline)
{
    m_endl = endline;
}

// set if output to stream
void Logger::setStream(std::ostream &stream)
{
    if (m_stream && (m_stream!=&std::cout))
    {
        delete(&m_stream);
    }
    m_stream = &stream;
}

/*************************************************
 * clearer/resetter
 *************************************************/

// reset the number of successful logs
void Logger::resetNrOfLogs()
{
    m_nrLogs = 0;
}

// clear the prefix
void Logger::clearPrefix()
{
    m_prefix = "";
}

// clear the postfix
void Logger::clearPostfix()
{
    m_postfix = "";
}

// reset the separator
void Logger::resetSeparator()
{
    m_separator = " ";
}

/*************************************************
 * getter
 *************************************************/

// return the successful number of logs
unsigned int Logger::getNrOfLogs() const
{
    return int(m_nrLogs);
}

// return the prefix
std::string Logger::getPrefix() const
{
    return std::string(m_prefix);
}

// return the postfix
std::string Logger::getPostfix() const
{
    return std::string(m_postfix);
}

// return the separator
std::string Logger::getSeparator() const
{
    return std::string(m_separator);
}

// return flag if output set
bool Logger::output() const
{
    return bool(m_output);
}

// return flag if endl after each log set
bool Logger::endl() const
{
    return bool(m_endl);
}

/*************************************************
 * private
 *************************************************/

// ctor
Logger::Logger()
{
}

// dtor
Logger::~Logger()
{
    if (m_stream && (m_stream!=&std::cout))
    {
        delete(&m_stream);
    }
}

// copy ctor
Logger::Logger(const Logger& l)
{
    // this cannot happen
}

// assignment operator
Logger& Logger::operator=(const Logger& l)
{
    // handle self assignment
    if (this == &l)
    {
        return *this;
    }
    // this cannot happen
    return *this;
}
