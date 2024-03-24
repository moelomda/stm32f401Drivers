#include "LCD.h"
#define LCD_INIT_STATE                0
#define LCD_OPERATION_STATE           1
#define LCD_OFF_STATE                 2
#define INIT_PWR_ON_STATE             0
#define INIT_FUN_SET_STATE            1
#define INIT_DIS_ONOFF_CLR_STATE      2
#define INIT_DIS_CLR_STATE            3
#define INIT_END_STATE                4
#define USER_RQ_BUSY                 0
#define USER_RQ_RDY                  1
#define USER_REQ_TYP_SET_CURS        0
#define USER_REQ_TYP_WRITE_STR       1
#define USER_REQ_TYP_WRITE_COMM      2

#define ROW1   1
#define ROW2   2
u8 LCD_STATE ;
u8 LCD_LatchedEn = 0;
extern LCD_Str_t LCD_config ;
struct {
 const u8 *s;
 u8 State ;
 u8 Type ;
 u8 Command;
}UserReq_t;
struct {
  u8 Row;
  u8 Col;
  u8 *Str;
}Write_Req;
struct {
  u8 Row;
  u8 Col;
}Cursor_Pos;
static void LCD_WriteCharData(u8 Copy_u8Data);
static void LCD_WriteCommandProc();
static void LCD_WriteStringProc();
static void LCD_HelperWriteCommand(u8 Command);
static void LCD_SetCursorProc();
static void LCD_SendEnableSignal();
void LCD_Init()
{
	GPIO_Init(&LCD_config.LCD_StrRsReg);
	GPIO_Init(&LCD_config.LCD_StrEnReg);
	for (int j = 0; j < 8; j++)
	{
		GPIO_Init(&LCD_config.LCD_StrDataReg[j]);
    }
	LCD_STATE = LCD_INIT_STATE;
}
void LCD_SetCursor(u8 Copy_u8Row, u8 Copy_u8Col)
{
	if(UserReq_t.State == USER_RQ_RDY && LCD_STATE == LCD_OPERATION_STATE)
	{
    UserReq_t.State= USER_RQ_BUSY;
    UserReq_t.Type = USER_REQ_TYP_SET_CURS;
    Cursor_Pos.Row = Copy_u8Row;
    Cursor_Pos.Col = Copy_u8Col;
	}
}
void LCD_WriteCommand(u8 Copy_u8Command)
{
   if(UserReq_t.State == USER_RQ_RDY && LCD_STATE == LCD_OPERATION_STATE)
	{
	UserReq_t.State= USER_RQ_BUSY;
	UserReq_t.Type = USER_REQ_TYP_WRITE_COMM;
	UserReq_t.Command = Copy_u8Command ;
	}
}
void LCD_WriteStringPos(u8 Copy_u8Row, u8 Copy_u8Col, u8 *Copy_AddStr)
{
	if(UserReq_t.State == USER_RQ_RDY && LCD_STATE == LCD_OPERATION_STATE)
	{
	UserReq_t.State= USER_RQ_BUSY;
	UserReq_t.Type= USER_REQ_TYP_WRITE_STR;
	Write_Req.Row = Copy_u8Row ;
	Write_Req.Col = Copy_u8Col;
	Write_Req.Str = Copy_AddStr;
	}
}
void LCD_GetStatus(u8 *LCD_Status)
{
	*LCD_Status = LCD_STATE;
}
static void LCD_InitSm()
{
    static u8 InitState = INIT_PWR_ON_STATE ;
    static u8 Counter = 0 ;
    Counter++;
    switch (InitState)
    {
    case INIT_PWR_ON_STATE :
    	if(Counter >= 32)
    	{
    		LCD_HelperWriteCommand(LCD_8BIT_MODE);
    		if(LCD_LatchedEn){
    			InitState=INIT_FUN_SET_STATE;
    		    Counter=0;
    		}
    	}
    break;
    case INIT_FUN_SET_STATE :
        if(Counter >= 1)
        {
           LCD_HelperWriteCommand(LCD_DISPLAY_CURSOR_BLINK_ALL_ON);
       	if(LCD_LatchedEn){
       	   InitState=INIT_DIS_ONOFF_CLR_STATE;
       	   Counter=0;
       	  }
        }
    break;
    case INIT_DIS_ONOFF_CLR_STATE :
    	  if(Counter >= 1)
    	  {
    	   LCD_HelperWriteCommand(LCD_CLEAR_DISPLAY);
    	   if(LCD_LatchedEn){
    		 InitState=INIT_DIS_CLR_STATE;
    	     Counter=0;
    	    }
    	  }
    break;
    case INIT_DIS_CLR_STATE :
    	 if(Counter >= 2)
    	 {
    	   LCD_HelperWriteCommand(LCD_CLEAR_DISPLAY);
    	   if(LCD_LatchedEn){
        	  Counter=0;
        	  InitState=INIT_END_STATE;
        	}
    	 }
    break;
    case INIT_END_STATE :
    	LCD_STATE = LCD_OPERATION_STATE;
    break;
   }
}
static void LCD_WriteCharData(u8 Copy_u8Data)
{
	 GPIO_SetPinValue(LCD_config.LCD_StrRsReg.GPIO_Port,LCD_config.LCD_StrRsReg.GPIO_Pin , LOGIC_HIGH) ;
	 for (u8 i = 0 ; i < 8 ; i++)
	 {
	   GPIO_SetPinValue(LCD_config.LCD_StrDataReg[i].GPIO_Port , LCD_config.LCD_StrDataReg[i].GPIO_Pin , (Copy_u8Data >> i) & (u8) 0x01);
	 }
}
static void LCD_SetCursorProc()
{
	(Cursor_Pos.Col)--;
	switch (Cursor_Pos.Row)
		{
		case ROW1:
	        UserReq_t.Command = 0x80 + Cursor_Pos.Col ;
				break;

		case ROW2:
			UserReq_t.Command = 0xC0 + Cursor_Pos.Col ;
		       break;
		}
	LCD_WriteCommandProc();
}
static void LCD_WriteStringProc()
{
	LCD_SetCursor(Write_Req.Row, Write_Req.Col);
	while (*(Write_Req.Str))
	{
		LCD_WriteCharData(*(Write_Req.Str));
		(Write_Req.Str)++;
	}
}
static void LCD_WriteCommandProc()
{
	GPIO_SetPinValue((LCD_config.LCD_StrRsReg.GPIO_Port), (LCD_config.LCD_StrRsReg.GPIO_Port) , LOGIC_LOW ) ;
	 for (u8 i = 0 ; i < 8 ; i++)
	  {
		 GPIO_SetPinValue((LCD_config.LCD_StrDataReg[i].GPIO_Port),(LCD_config.LCD_StrDataReg[i].GPIO_Pin) , (UserReq_t.Command >> i) & (u8) 0x01 );
	  }
}
static void LCD_SendEnableSignal()
{
	static u8 En_Counter = 0 ;
	GPIO_SetPinValue(LCD_config.LCD_StrEnReg.GPIO_Port,LCD_config.LCD_StrEnReg.GPIO_Pin,LOGIC_HIGH);
	if(En_Counter++ == 1)
	{
	GPIO_SetPinValue(LCD_config.LCD_StrEnReg.GPIO_Port,LCD_config.LCD_StrEnReg.GPIO_Pin,LOGIC_LOW);
	LCD_LatchedEn = 1 ;
	En_Counter = 0;
    }
}
static void LCD_HelperWriteCommand(u8 Command)
{
	GPIO_SetPinValue((LCD_config.LCD_StrRsReg.GPIO_Port), (LCD_config.LCD_StrRsReg.GPIO_Pin) , LOGIC_LOW ) ;
	for (u8 i = 0 ; i < 8 ; i++)
	{
	 GPIO_SetPinValue((LCD_config.LCD_StrDataReg[i].GPIO_Port),(LCD_config.LCD_StrDataReg[i].GPIO_Pin) , (Command >> i) & (u8) 0x01 );
	}
	LCD_SendEnableSignal();
}
void LCD_Runabble()
{
	if(LCD_STATE == LCD_INIT_STATE)
	{
		LCD_InitSm();
	}
	else if (LCD_STATE == LCD_OPERATION_STATE )
	{
      if(UserReq_t.State == USER_RQ_BUSY)
      {
       switch (UserReq_t.Type)
       {
       case USER_REQ_TYP_SET_CURS :
    	   LCD_SetCursorProc();
    	   LCD_SendEnableSignal();
    	 	if(LCD_LatchedEn)
    	 	{
    	      UserReq_t.State = USER_RQ_RDY;
    	    }
    	   break;
       case USER_REQ_TYP_WRITE_STR:
    	   LCD_WriteStringProc();
           LCD_SendEnableSignal();
       	   if(LCD_LatchedEn)
          	{
       	     UserReq_t.State = USER_RQ_RDY;
         	}
           break;
       case USER_REQ_TYP_WRITE_COMM:
    	   LCD_WriteCommandProc();
    	   LCD_SendEnableSignal();
       	   if(LCD_LatchedEn)
          	{
       	     UserReq_t.State = USER_RQ_RDY;
         	}
           break;
       }
     }
	}
	else
	{

	}
}
