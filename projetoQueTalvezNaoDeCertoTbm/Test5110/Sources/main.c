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
#include <string.h>
//strcat


#define EXAUSTOR Bit1_PutVal(0); Bit2_PutVal(1); PDC1_ClearLine(0); PDC1_WriteLineStr(1, "OK EXAUST");
#define VENTILADOR Bit1_PutVal(1); Bit2_PutVal(0); PDC1_ClearLine(0); PDC1_WriteLineStr(1, "OK VENT");
#define PARADO Bit1_PutVal(0); Bit2_PutVal(0);
//#define PARAMETROINC 
#define ESCREVEVEL itoa(blue,blueChar,10); PDC1_ClearLine(1);  strcat(blueChar, " %");  PDC1_WriteLineStr(2,blueChar);
#define ESCREVEVAL itoa(blue,blueChar,10); PDC1_ClearLine(1); PDC1_ClearLine(2);  PDC1_WriteLineStr(2,blueChar);
//#define INEX PDC1_ClearLine(1);PDC1_ClearLine(2); PDC1_WriteLineStr(2,"PAR�METRO INEXISTENTE"); PDC1_ClearLine(2);
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

void PARAMETROINC(void){
	 AS1_SendChar('P');WAIT1_Waitms(1);
	 AS1_SendChar('A');WAIT1_Waitms(1); 
	 AS1_SendChar('R');WAIT1_Waitms(1); 
	 AS1_SendChar('A');WAIT1_Waitms(1);
	 AS1_SendChar('M'); WAIT1_Waitms(1);
	 AS1_SendChar('E');WAIT1_Waitms(1);
	 AS1_SendChar('T');WAIT1_Waitms(1);
	 AS1_SendChar('R');WAIT1_Waitms(1);
	 AS1_SendChar('O'); WAIT1_Waitms(1);
	 AS1_SendChar(' '); WAIT1_Waitms(1);
	 AS1_SendChar('I');WAIT1_Waitms(1);
	 AS1_SendChar('N');WAIT1_Waitms(1);
	 AS1_SendChar('C');WAIT1_Waitms(1);
	 AS1_SendChar('O');WAIT1_Waitms(1);
	 AS1_SendChar('R');WAIT1_Waitms(1);
	 AS1_SendChar('R');WAIT1_Waitms(1);
	 AS1_SendChar('E');WAIT1_Waitms(1);
	 AS1_SendChar('T');WAIT1_Waitms(1);
	 AS1_SendChar('O');WAIT1_Waitms(1);
}

void INEX(void){
	 AS1_SendChar('P');WAIT1_Waitms(1);
	 AS1_SendChar('A');WAIT1_Waitms(1); 
	 AS1_SendChar('R');WAIT1_Waitms(1); 
	 AS1_SendChar('A');WAIT1_Waitms(1);
	 AS1_SendChar('M'); WAIT1_Waitms(1);
	 AS1_SendChar('E');WAIT1_Waitms(1);
	 AS1_SendChar('T');WAIT1_Waitms(1);
	 AS1_SendChar('R');WAIT1_Waitms(1);
	 AS1_SendChar('O'); WAIT1_Waitms(1);
	 AS1_SendChar(' '); WAIT1_Waitms(1);
	 AS1_SendChar('I');WAIT1_Waitms(1);
	 AS1_SendChar('N');WAIT1_Waitms(1);
	 AS1_SendChar('E');WAIT1_Waitms(1);
	 AS1_SendChar('X');WAIT1_Waitms(1);
	 AS1_SendChar('I');WAIT1_Waitms(1);
	 AS1_SendChar('S');WAIT1_Waitms(1);
	 AS1_SendChar('T');WAIT1_Waitms(1);
	 AS1_SendChar('E');WAIT1_Waitms(1);
	 AS1_SendChar('N');WAIT1_Waitms(1);
	 AS1_SendChar('T');WAIT1_Waitms(1);
	 AS1_SendChar('E');WAIT1_Waitms(1);
}


void setSpeed(int blue)

{
	int speed=0;
	speed = 100-blue;
	PWM1_SetDutyMS(speed);

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
int flag_comando_feito=0;

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
   /* For example: for(;;) { } */
 
  
  PDC1_SetContrast(63);
  
  
  
  for (;;){
	  
	 
	  
	  if (flag_leitura==1){
		 
		  
		  if(strcmp(buffer, "VENT") == 0){
			  
			
			  blue = lastBlue;
			  PARADO;
			  delay(7);
			  
			  setSpeed(blue);
			  VENTILADOR;
			  
			  PDC1_ClearLine(2);
		
			  ESCREVEVEL;
			 
			  flag_comando_feito=1;
			  flag_leitura = 0;
			  
			  	  	  }
		  
		  else if(strcmp(buffer, "EXAUST") == 0){
			
	
			 blue = lastBlue;
			 ESCREVEVEL;
			  PARADO;
			  delay(7);
			  setSpeed(blue);
			  EXAUSTOR;
			  
			  flag_comando_feito = 1;
			  flag_leitura = 0;
		  	  	  	  	  	  	  }
		  
		  else if(strcmp(buffer, "PARA") == 0){
			  
			 
			  PDC1_WriteLineStr(1, "OK PARA");
			  PDC1_ClearLine(1);
			  PARADO;
			  flag_comando_feito = 1;
			  flag_leitura = 0;
		  }
		  
		  
/////////////////////////////////////////////////////////////////	
		  
		  
		  else if (strcmp(buffer, "VEL") == 0){
				
			  if(blue == NULL) {
					INEX();
					
				}
			  
			  else if (blue<=100 && blue>=0){
				  
				  
				  lastBlue = blue;
				  setSpeed(blue);
				  ESCREVEVEL;
				  
			  }
			  
			  else  {PARAMETROINC();}
			  
			  flag_comando_feito = 1; 
			  flag_leitura = 0;
			  lastBlue = blue;
		  }
		  
		  
		  
		  else if (strcmp(buffer, "ANO") == 0){
			  
			  if(blue == NULL) {
					INEX();
				}
			  else if (blue<10000 && blue>=0){
				  
					ESCREVEVAL;
					PDC1_ClearLine(2);
					PDC1_WriteLineStr(3,"OK ANO");
				  
			  }
			  else  {PARAMETROINC();}
			  
			  
			  flag_comando_feito = 1;
			  flag_leitura = 0;
		  	  
		  }
		  
		  
		  else if (strcmp(buffer, "MES") == 0){
			 
			  if(blue == NULL) {
					INEX();
				}
			  
			  else if (blue<=12 && blue>=1){
				  
				  ESCREVEVAL;
					 PDC1_ClearLine(2);
					PDC1_WriteLineStr(3,"OK MES");
				  
			  }
			  else  {PARAMETROINC();}
			  flag_comando_feito = 1;
			  flag_leitura = 0;
		  }
		  
		  else if (strcmp(buffer, "DIA") == 0){
			 
			  if(blue == NULL) {
					INEX();
				}
			  
			  else if (blue<=31 && blue>=1){
				  
				  ESCREVEVAL;
					 PDC1_ClearLine(2);
					PDC1_WriteLineStr(3,"OK DIA");
				  
			  }
			  else  {PARAMETROINC();}
			  flag_comando_feito = 1;
			  flag_leitura = 0;
		  }
		  
		  else if (strcmp(buffer, "SEM") == 0){
			  if(blue == NULL) {
					INEX();
				}
			  else if (blue<8 && blue>=1){
				  
				  ESCREVEVAL;
					 PDC1_ClearLine(2);
					PDC1_WriteLineStr(3,"OK SEMANA");
				  
			  }
			  else  {PARAMETROINC();}
			  flag_comando_feito = 1;
			  flag_leitura = 0;
		  }
		  
		  else if (strcmp(buffer, "HORA") == 0){
			  
			  if(blue == NULL) {
					INEX();
				}
			  
			  else if (blue<25 && blue>=0){
				  
				  ESCREVEVAL;
					 PDC1_ClearLine(2);
					PDC1_WriteLineStr(3,"OK HORA");
				  
			  }
			  else  {PARAMETROINC();}
			  flag_comando_feito = 1;
			  flag_leitura = 0;
		  }
		  
		  else if (strcmp(buffer, "MIN") == 0){
			  
			  if(blue == NULL) {
					INEX();
				}
			  else if (blue<60 && blue>=0){
				  
				  ESCREVEVAL;
					 PDC1_ClearLine(2);
					PDC1_WriteLineStr(3,"OK MIN");
				  
			  }
			  else  {PARAMETROINC();}
			  flag_comando_feito = 1;
			  flag_leitura = 0;
		  }
		  
		 else if (strcmp(buffer, "SEG") == 0){
			  if(blue == NULL) {
					INEX();
				} 
			  else if (blue<61 && blue>=0){
				  
				  ESCREVEVAL;
					 PDC1_ClearLine(2);
					PDC1_WriteLineStr(3,"OK SEG");
				  
			  }
			  else  {PARAMETROINC();}
			  flag_comando_feito = 1;
			  flag_leitura = 0;
		  	  }
		  
		  else if (flag_comando_feito == 0){
			  AS1_SendChar('C');WAIT1_Waitms(1);
			  	 AS1_SendChar('O');WAIT1_Waitms(1); 
			  	 AS1_SendChar('M');WAIT1_Waitms(1); 
			  	 AS1_SendChar('A');WAIT1_Waitms(1);
			  	 AS1_SendChar('N'); WAIT1_Waitms(1);
			  	 AS1_SendChar('D');WAIT1_Waitms(1);
			  	 AS1_SendChar('O');WAIT1_Waitms(1);
			  	 AS1_SendChar(' ');WAIT1_Waitms(1);
			  	 AS1_SendChar('I'); WAIT1_Waitms(1);
			  	 AS1_SendChar('N'); WAIT1_Waitms(1);
			  	 AS1_SendChar('E');WAIT1_Waitms(1);
			  	 AS1_SendChar('X');WAIT1_Waitms(1);
			  	 AS1_SendChar('I');WAIT1_Waitms(1);
			  	 AS1_SendChar('S');WAIT1_Waitms(1);
			  	 AS1_SendChar('T');WAIT1_Waitms(1);
			  	 AS1_SendChar('E');WAIT1_Waitms(1);
			  	 AS1_SendChar('N');WAIT1_Waitms(1);
			  	 AS1_SendChar('T');WAIT1_Waitms(1);
			  	 AS1_SendChar('E');WAIT1_Waitms(1);

			  flag_leitura = 0;
			   }
		  

		  
		  delay(14);
		  PDC1_ClearLine(2);
		  
		  int i = 0;
		  
		  for (i=0;i<=19;i++){
			  
			  buffer[i] = 0;
			  
		  }
		  
	  }
	  
	  flag_comando_feito = 0;
	  
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
