#include "LCD.h"
#define LCD_INIT_STATE                0
#define LCD_OPERATION_STATE           1
#define LCD_OFF_STATE                 2
#define INIT_PWR_ON_STATE             0
#define INIT_FUN_SET_STATE            1
#define INIT_DIS_ONOFF_CLR_STATE      2
#define INIT_DIS_CLR_STATE            3
#define INIT_END_STATE                4
#define INIT_ENTRY_MODE_STATE         5
#define USER_RQ_BUSY                  1
#define USER_RQ_RDY                   0
#define USER_REQ_TYP_SET_CURS         0
#define USER_REQ_TYP_WRITE_STR        1
#define USER_REQ_TYP_WRITE_COMM       2
#define USER_REQ_TYP_NO_REQ           3
#define SCHED_PERODICITY_MS           1

#define ROW1   1
#define ROW2   2
u8 LCD_STATE ;
u8 LCD_LatchedEn = 0;
u8 Time_mS = 0;
extern LCD_Str_t LCD_config ;
struct {
 u8 State ;
 u8 Type ;
 u16 Command;
}UserReq_t;
struct {
  const char *Str;
  u8 len;
  u8 pos;
}Write_Req;
struct {
  u8 Row;
  u8 Col;
}Cursor_Pos;
static void LCD_WriteCharData(u8 Copy_Data);
static void LCD_WriteCommandProc();
static void LCD_WriteStringProc();
static void LCD_HelperWriteCommand(u8 Command);
static void LCD_SetCursorProc();
static void LCD_Operation();
//static void LCD_SendEnableSignal();
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
	if((UserReq_t.State == USER_RQ_RDY) && ( LCD_STATE == LCD_OPERATION_STATE))
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
void LCD_WriteString(const char *Copy_AddStr, u8 len)
{
	if(UserReq_t.State == USER_RQ_RDY && LCD_STATE == LCD_OPERATION_STATE)
		{
		UserReq_t.State= USER_RQ_BUSY;
		UserReq_t.Type= USER_REQ_TYP_WRITE_STR;
		Write_Req.Str = Copy_AddStr;
		Write_Req.len = len ;
		Write_Req.pos = 0;
		}
}

void LCD_GetStatus(u8 *LCD_Status)
{
	*LCD_Status = LCD_STATE;
}

static void LCD_InitSm()
{
     static u8 InitState = INIT_PWR_ON_STATE ;
     Time_mS +=LCD_TASK_PERIODICTY;
    switch (InitState)
    {
    case INIT_PWR_ON_STATE :
    	if( Time_mS  >= 30)
    	{
    		InitState=INIT_FUN_SET_STATE;
    		Time_mS=0;
        }
    break;
    case INIT_FUN_SET_STATE :
    	if(Time_mS >= 2)
    	{
          LCD_HelperWriteCommand(LCD_8BIT_MODE);
    	}
      	if(LCD_LatchedEn)
       	{
       	   InitState=INIT_DIS_ONOFF_CLR_STATE;
       	   Time_mS=0;
        }
    break;
    case INIT_DIS_ONOFF_CLR_STATE :
    	  if(Time_mS >= 2)
    	  {
    		LCD_HelperWriteCommand(LCD_DISPLAY_CURSOR_BLINK_ALL_ON);
    	   if(LCD_LatchedEn){
    		 InitState=INIT_DIS_CLR_STATE;
    		 Time_mS=0;
    	    }
    	  }
    break;
    case INIT_DIS_CLR_STATE :
    	 if(Time_mS >= 2)
    	 {
    	   LCD_HelperWriteCommand(LCD_CLEAR_DISPLAY);
    	   if(LCD_LatchedEn){
    		   Time_mS=0;
        	   InitState=INIT_ENTRY_MODE_STATE;
        	}
    	 }
    break;
    case INIT_ENTRY_MODE_STATE :
        if(Time_mS >= 2 )
           {
           LCD_HelperWriteCommand(ENTRY_MODE_INC_SHIFT_OFF);
            if(LCD_LatchedEn){
              InitState=INIT_END_STATE;
               Time_mS=0;
               }
           }
          break;
    case INIT_END_STATE :
    	LCD_STATE = LCD_OPERATION_STATE;
    	UserReq_t.State= USER_RQ_RDY;
    	 Time_mS=0;
    	//initstate
    break;
   }
}
void LCD_Runabble(void)
{
    switch (LCD_STATE)
    {
    case LCD_INIT_STATE:
    	 LCD_InitSm();
        break;

    case LCD_OPERATION_STATE:
        LCD_Operation();
        break;

    case LCD_OFF_STATE:
        break;

    default:
        break;
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
	LCD_WriteCommandProc(UserReq_t.Command);

}

static void LCD_WriteStringProc()
{
 LCD_WriteCharData(Write_Req.Str[Write_Req.pos]);
}

static void LCD_WriteCommandProc()
{
	    LCD_LatchedEn = 0 ;
	    if(Time_mS == 1)
		{
		for (u8 i = 0 ; i < 8 ; i++)
		{
		 GPIO_SetPinValue((LCD_config.LCD_StrDataReg[i].GPIO_Port),(LCD_config.LCD_StrDataReg[i].GPIO_Pin) , (UserReq_t.Command >> i) & (u8) 0x01 );
		}
		GPIO_SetPinValue((LCD_config.LCD_StrRsReg.GPIO_Port), (LCD_config.LCD_StrRsReg.GPIO_Pin) , LOGIC_LOW ) ;
		GPIO_SetPinValue(LCD_config.LCD_StrEnReg.GPIO_Port,LCD_config.LCD_StrEnReg.GPIO_Pin,LOGIC_HIGH);
		}
	    else if(Time_mS > 1)
		{
	    LCD_LatchedEn = 1;
		GPIO_SetPinValue(LCD_config.LCD_StrEnReg.GPIO_Port,LCD_config.LCD_StrEnReg.GPIO_Pin,LOGIC_LOW);
/**/
		}
}

static void LCD_HelperWriteCommand(u8 Command)
{
	LCD_LatchedEn = 0 ;
    if(Time_mS == 2)
	{
	for (u8 i = 0 ; i < 8 ; i++)
	{
	 GPIO_SetPinValue((LCD_config.LCD_StrDataReg[i].GPIO_Port),(LCD_config.LCD_StrDataReg[i].GPIO_Pin) , (Command >> i) & (u8) 0x01 );
	}
	GPIO_SetPinValue((LCD_config.LCD_StrRsReg.GPIO_Port), (LCD_config.LCD_StrRsReg.GPIO_Pin) , LOGIC_LOW ) ;
	GPIO_SetPinValue(LCD_config.LCD_StrEnReg.GPIO_Port,LCD_config.LCD_StrEnReg.GPIO_Pin,LOGIC_HIGH);
	}
    else if(Time_mS > 2)
	{
    LCD_LatchedEn = 1;
	GPIO_SetPinValue(LCD_config.LCD_StrEnReg.GPIO_Port,LCD_config.LCD_StrEnReg.GPIO_Pin,LOGIC_LOW);
	}
}
static void LCD_WriteCharData(u8 Copy_Data)
{
	 if (Time_mS%2)
	{
	 for (u8 i = 0 ; i < 8 ; i++)
	 {
	   GPIO_SetPinValue(LCD_config.LCD_StrDataReg[i].GPIO_Port , LCD_config.LCD_StrDataReg[i].GPIO_Pin , (Copy_Data >> i) & (u8) 0x01);
	 }
	 GPIO_SetPinValue(LCD_config.LCD_StrRsReg.GPIO_Port,LCD_config.LCD_StrRsReg.GPIO_Pin , LOGIC_HIGH) ;
	 GPIO_SetPinValue(LCD_config.LCD_StrEnReg.GPIO_Port,LCD_config.LCD_StrEnReg.GPIO_Pin,LOGIC_HIGH);
	}
	else
	{
		GPIO_SetPinValue(LCD_config.LCD_StrEnReg.GPIO_Port,LCD_config.LCD_StrEnReg.GPIO_Pin,LOGIC_LOW);
		++(Write_Req.pos);
		--(Write_Req.len);
	}
}

 static void LCD_Operation(void)
{
    Time_mS += SCHED_PERODICITY_MS;

    switch (UserReq_t.Type)
    {
    case USER_REQ_TYP_WRITE_STR:
        if (Write_Req.len)
        {
        	LCD_WriteStringProc();
        }
        else
        {
           UserReq_t.State = USER_RQ_RDY;
           UserReq_t.Type  = USER_REQ_TYP_NO_REQ;
        	 Write_Req.len=0;
        	 Write_Req.pos=0;
             Time_mS = 0;
        }
        break;

    case USER_REQ_TYP_SET_CURS:
        if (Time_mS == 1)
        {
        	LCD_SetCursorProc();
        }
        else if (Time_mS == 2)
        {
        	LCD_SetCursorProc();
        	UserReq_t.State = USER_RQ_RDY;
        	UserReq_t.Type  = USER_REQ_TYP_NO_REQ;
            Time_mS = 0;
        }
        break;

    case USER_REQ_TYP_WRITE_COMM:
        if (Time_mS == 1)
        {
        	LCD_WriteCommandProc();
        }
        else if (Time_mS == 2)
        {
        	LCD_WriteCommandProc();
        }
        else if (Time_mS == 4)
        {
        	UserReq_t.State = USER_RQ_RDY;
            Time_mS = 0;
            UserReq_t.Type  = USER_REQ_TYP_NO_REQ;
        }
        break;

    default:
    Time_mS = 0;
        break;
    }

}
