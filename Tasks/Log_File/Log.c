#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include "log.h"

char File_Name[100] = {0};
Log_Output_Type_t Output_Type = 0;
log_level_t min_log_level = LOG_LEVEL_DEBUG; // Global variable to store the minimum log level

static void formatMessage(char *LogMessage, const char *message)
{
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    sprintf((char *)LogMessage, "[%s] %s\n", timestamp, message);
}

Log_Error_t LogFile_Name(const char *name)
{
    strcpy(File_Name, name);
    return Log_OK;
}

Log_Error_t Output_Type_Select(Log_Output_Type_t Type)
{
    Output_Type = Type;
    return Log_OK;
}

Log_Error_t Output_message(log_level_t level, const char *message)
{
    Log_Error_t returnStatus = Log_OK;

    char logMessage[150];
    formatMessage(logMessage, message);

    if (level >= min_log_level)
    {
        if (Output_Type & Console)
        {
            printf(logMessage);
        }

        if (Output_Type & Log_File)
        {
            FILE *file = fopen(File_Name, "a+");

            if (file != NULL)
            {
                fprintf(file, "%s", logMessage);
            }
            else
            {
                returnStatus = Log_NOk;
            }
            fclose(file);
        }
    }

    return returnStatus;
}

Log_Error_t Output_message_varadidic(log_level_t level, const char *message, ...)
{
    char logMessage[150];

    va_list args;
    va_start(args, message);
    vsprintf(logMessage, message, args);
    va_end(args);

    return Output_message(level, logMessage);
}LOGGER_OK;

