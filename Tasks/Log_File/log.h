#ifndef LOG_H
#define LOG_H

#include <stdio.h>

// Enumeration for different types of log outputs
typedef enum {
    Console = 1,
    Log_File = 2
} Log_Output_Type_t;

// Enumeration for different log error types
typedef enum {
    Log_OK,
    Log_NOk
} Log_Error_t;

// Enumeration for logging levels
typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_CRITICAL
} log_level_t;

// Function to set the log file name
Log_Error_t LogFile_Name(const char *name);

// Function to select log output type
Log_Error_t Output_Type_Select(Log_Output_Type_t Type);

// Function to output a log message with specified log level
Log_Error_t Output_message(log_level_t level, const char *message);

// Function to output a log message with specified log level and variable arguments
Log_Error_t Output_message_varadidic(log_level_t level, const char *message, ...);

#endif /* LOG_H */
