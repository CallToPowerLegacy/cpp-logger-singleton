/**
 * Logger (Singleton) Header
 * @description a Logger implementing the Singleton pattern
 * @author Denis Meyer - CallToPower Software
 * @website https://sites.google.com/site/calltopowersoftware/software
 * @version 0.1.3.2
 * @created 3/16/11
 * @file Logger.h
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <stdarg.h>

/**
 * Logger Singleton
 */
class Logger
{
public:
    /**
     * returns the Logger instance
     * @return the Logger instance
     */
    static Logger* instance();
    
    /*************************************************
     * helper
     *************************************************/
    
    /**
     * prints nr newlines
     * @param nr number of newlines ot print
     */
    void newLine(const int nr = 1) const;
    
    /**
     * prints str times times
     * @param times number of times to print str
     * @param str str to print times times
     * @param separator flag if current separator should be used or not
     */
    void printTimes(const int times, const std::string str, const bool separator = false) const;
    
    /*************************************************
     * logging
     *************************************************/
    
    /**
     * logs a std::string
     * @param a std::string to log
     */
    bool log(const std::string str = "") const;
    
    /**
     * logs an int
     * @param an int
     */
    bool log(const int i) const;
    
    /**
     * logs a double
     * @param a double
     */
    bool log(const double d) const;
    
    /**
     * logs a double**
     * @param a double**
     */
    bool log(double **d, const int rows, const int cols) const;
    
    /**
     * logs a variable number of arguments
     * @param variable number of arguments to log
     *      - f or d:   float and double
     *      - c     :   char
     *      - s     :   string (char *)
     *      - i     :   integer
     *      - b     :   bool
     * @return number of arguments logged
     */
    int logX(const std::string szTypes = "", ...) const;
    
    /*************************************************
     * setter
     *************************************************/
    
    /**
     * sets a prefix
     * @param prefix to set before every log
     */
    void setPrefix(const std::string prefix = "");
    
    /**
     * sets a postfix
     * @param postfix to set after every log
     */
    void setPostfix(const std::string postfix = "");
    
    /**
     * sets a separator
     * @param separator to set between multiple arguments
     */
    void setSeparator(const std::string separator = " ");
    
    /**
     * sets flag if output to stream
     * @param flag if output to stream
     */
    void setOutput(const bool output = true);
    
    /**
     * sets flag if endline after each log
     * @param flag if endline after each log
     */
    void setEndline(const bool endline = true);
    
    /**
     * sets if output to stream
     * @param flag if output to stream
     */
    void setStream(std::ostream &stream = std::cout);
    
    /*************************************************
     * clearer/resetter
     *************************************************/
    
    /**
     * resets the number of successful logs
     */
    void resetNrOfLogs();
    
    /**
     * clears the prefix
     */
    void clearPrefix();
    
    /**
     * clears the postfix
     */
    void clearPostfix();
    
    /**
     * resets the separator
     */
    void resetSeparator();
    
    /*************************************************
     * getter
     *************************************************/
    
    /**
     * returns the successful number of logs
     * @return the successful number of logs
     */
    unsigned int getNrOfLogs() const;
    
    /**
     * returns the prefix
     * @return the prefix
     */
    std::string getPrefix() const;
    
    /**
     * returns the postfix
     * @return the postfix
     */
    std::string getPostfix() const;
    
    /**
     * returns the separator
     * @return the separator
     */
    std::string getSeparator() const;
    
    /**
     * returns a flag if output
     * @return true if output, false else
     */
    bool output() const;
    
    /**
     * returns a flag if endl after each log set
     * @return true if endl after each log set, false else
     */
    bool endl() const;
    
private:
    /**
     * default ctor
     */
    Logger();
    
    /**
     * copy ctor
     */
    Logger(const Logger& l);
    
    /**
     * dtor
     */
    ~Logger();
    
    /**
     * assignment operator
     */
    Logger& operator=(const Logger& l);
    
    // static variables
    static Logger *m_instance;
    static std::string m_prefix;
    static std::string m_postfix;
    static std::string m_separator;
    static bool m_output;
    static bool m_endl;
    static std::ostream *m_stream;
    static unsigned int m_nrLogs;
    
    // union for multiple argument logging
    mutable union currType_t
    {
        int i;
        float f;
        char c;
        char *s;
    } m_currType;
};

#endif // LOGGER_H
