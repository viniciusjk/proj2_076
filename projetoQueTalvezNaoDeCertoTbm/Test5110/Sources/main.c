/* ###################################################################
**     Filename    : main.c
**     Project     : Test5110
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-05-15, 19:18, # CodeGen: 54
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "SM1.h"
#include "MCUC1.h"
#include "WAIT1.h"
#include "PDC1.h"
#include "RESpin1.h"
#include "SCEpin1.h"
#include "D_Cpin1.h"
#include "LT.h"
#include "BitIoLdd1.h"
#include "PWM1.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "Bit1.h"
#include "BitIoLdd2.h"
#include "Bit2.h"
#include "BitIoLdd3.h"
#include "AS1.h"
#include "ASerialLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include <extras/extras_stdlib.h>


#define EXAUSTOR Bit1_PutVal(0); Bit2_PutVal(1); PDC1_ClearLine(0); PDC1_WriteLineStr(1, "OK EXAUST");
#define VENTILADOR Bit1_PutVal(1); Bit2_PutVal(0); PDC1_ClearLine(0); PDC1_WriteLineStr(1, "OK VENT");
#define PARADO Bit1_PutVal(0); Bit2_PutVal(0);
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

void setSpeed(int blue)

{
	
	int speed=0;
	speed = 100-blue;
	PWM1_SetDutyMS(speed);
	//itoa
	//PDC1_WriteLineStr(2, "0000");

}

void delay(int seconds){
	int j =0;
	seconds = seconds*480000;
	  while (j<=seconds){
		  j++;
	  	  }
	
}

char buffer[20];
int blue = 0;
int flag_leitura = 0;
int lastBlue = 0;
char blueChar[20];
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
   /* For example: for(;;) { } */
 /* 
  PDC1_WriteLineStr(1, "Hello World");
  PDC1_WriteLineStr(2, "from the");
  PDC1_WriteLineStr(3, "telefone do caio, vem de Zap");
  PDC1_WriteLineStr(4, "11 942332370!");
  PDC1_SetContrast(63);PDC1_ClearLine();
  */
  PDC1_SetContrast(63);
  
  
  EXAUSTOR;
  blue = 35;
  setSpeed(blue);
  
  for (;;){
	  
	
	  
	 
	  
	  if (flag_leitura==1){
		 
		  //setSpeed(blue);
		
		  //PDC1_ClearLine(1);
		  
		  if(strcmp(buffer, "VENT") == 0){
			  
			  blue =90;

			 
			  PARADO;

			  delay(7);
			  
		

			  VENTILADOR;
			  
			  PDC1_ClearLine(2);
			  itoa(blue,blueChar,10);
			  
			  PDC1_WriteLineStr(2,blueChar);
			  setSpeed(blue);
			  
			  }
		  else if(strcmp(buffer, "EXAUST") == 0){
			
			  blue = 100;
			  PDC1_ClearLine(2);
			  PDC1_WriteLineStr(2,itoa(blue,blueChar,10));
			 
			  PARADO;
			  delay(7);
			  EXAUSTOR;

			  setSpeed(blue);
		  }
		  
		  else if(strcmp(buffer, "PARA") == 0){
			  
			  lastBlue = blue;
			  PDC1_WriteLineStr(1, "OK PARA");
			  PARADO;
		  }
		  
		  else if (strcmp(buffer, "VEL") == 0){
			  
			  setSpeed(blue);
			  
			  
			  PDC1_ClearLine(2);
			  PDC1_WriteLineStr(2,itoa(blue,blueChar,10));
			  
		  }
		  
		  
		  int i = 0;
		  for (i=0;i<=19;i++){
			  buffer[i] = 0;
			  }
	  }
  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
