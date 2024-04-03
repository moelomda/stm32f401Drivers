#include "std_types.h"
#include "GPIO.h"

#define LCD_CLEAR_DISPLAY                       0x01  // Clear display and return to home position
#define LCD_RETURN_HOME                         0x02  // Return cursor and display to home position
#define LCD_DISPLAY_CURSOR_BLINK_ALL_OFF        0x08  // Turn off display, cursor, and blinking
#define ENTRY_MODE_INC_SHIFT_OFF                0x06  // Set entry mode: increment cursor, no display shift (Normal Mode)
#define LCD_ENTRY_MODE_DEC_SHIFT_ON             0x05  // Set entry mode: decrement cursor, with display shift

#define LCD_TASK_PERIODICTY                     1
#define LCD_ENTRY_MODE_INC_SHIFT_ON             0x07  // Set entry mode: increment cursor, with display shift
#define LCD_DISPLAY_CURSOR_BLINK_ALL_OFF        0x08  // Turn off display, cursor, and blinking
#define LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF     0x0C  // Turn on display without cursor and blinking
#define LCD_DISPLAY_ON_CURSOR_OFF_BLINK_ON      0x0D  // Turn on display without cursor and with blinking
#define LCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF      0x0E  // Turn on display with cursor and without blinking
#define LCD_DISPLAY_CURSOR_BLINK_ALL_ON         0x0F  // Turn on display with cursor and blinking
#define LCD_CURSOR_SHIFT_LEFT                   0x10  // Shift cursor position to the left
#define LCD_CURSOR_SHIFT_RIGHT                  0x14  // Shift cursor position to the right
#define LCD_DISPLAY_SHIFT_LEFT                  0x18  // Shift entire display to the left, cursor follows
#define LCD_DISPLAY_SHIFT_RIGHT                 0x1C  // Shift entire display to the right, cursor follows
#define LCD_4BIT_MODE                           0x28  // Set 4-bit data mode
#define LCD_8BIT_MODE                           0x38  // Set 8-bit data mode
#define LCD_CGRAM_START_ADDRESS                 0x40  // Set CGRAM (Character Generator RAM) start address
#define LCD_DDRAM_START_ADDRESS                 0x80  // Set DDRAM (Display Data RAM) start address
typedef struct
{
	GpioPinCfg_t LCD_StrRsReg;
	GpioPinCfg_t LCD_StrEnReg;
	GpioPinCfg_t LCD_StrDataReg[8];
} LCD_Str_t;


void LCD_Init();

void LCD_GetStatus(u8 *LCD_Status);

void LCD_ClearDisplay();


void LCD_WriteString(const char *Copy_AddStr);


void LCD_SetCursor(u8 Copy_u8Row, u8 Copy_u8Col);
