#include <stdio.h>
#include "log.h"

int main() {
    // Set log file name
    Log_Error_t fileResult = LogFile_Name("logfile.txt");
    if (fileResult != Log_OK) {
        printf("Error setting log file name\n");
        return 1;
    }

    // Select log output type
    Log_Error_t outputResult = Output_Type_Select(Console | Log_File);
    if (outputResult != Log_OK) {
        printf("Error selecting log output type\n");
        return 1;
    }

    // Output log messages with different levels
    Output_message(LOG_LEVEL_DEBUG, "This is a debug message");
    Output_message(LOG_LEVEL_INFO, "This is an info message");
    Output_message(LOG_LEVEL_WARNING, "This is a warning message");
    Output_message(LOG_LEVEL_ERROR, "This is an error message");
    Output_message(LOG_LEVEL_CRITICAL, "This is a critical message");

    // Output log messages with variable arguments
    Output_message_varadidic(LOG_LEVEL_INFO, "File '%s' not found", "example.txt");
    Output_message_varadidic(LOG_LEVEL_ERROR, "Failed to allocate memory for %d bytes", 1024);

    return 0;
}
