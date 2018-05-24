/* ###################################################################
**     Filename    : Events.c
**     Project     : Test5110
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-05-15, 19:18, # CodeGen: 54
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         AS1_OnError  - void AS1_OnError(void);
**         AS1_OnRxChar - void AS1_OnRxChar(void);
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

extern int numValue;
extern char buffer[20];
extern int read_flag;
int contador = 0;
char buffer_interno[20];
int numero_lido_flag = 0;


#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */


/*
** ===================================================================
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void AS1_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnRxChar(void)
{
	

  /* Write your code here ... */
	byte val;


	

	AS1_RecvChar(&val);
	int i = 0;
	
	
	if (val == '*'){
		  
		
		  contador = 0;
		  
		  
		  if (numero_lido_flag == 1){
			  numValue = atoi(buffer_interno);
			  numero_lido_flag = 0;
			  
		  }
		  
		  else{
			  
		  strcpy(buffer, buffer_interno);
		  
		  
		  }
		  
		  for (i=0;i<20;i++){
			 
			  buffer_interno[i]=0;
		  }
		  
		  read_flag = 1;
		  numero_lido_flag = 0;
		 
	  }
	
	else if (val != '\n' && val != '\f' && val != '\r' ){
		
		 buffer_interno[contador]=val;
		 contador=contador+1;
		 read_flag = 0;


							
		
			
			if ( (strcmp(buffer_interno, "VEN") != 0 && strcmp(buffer_interno, "PAR") != 0)   && strcmp(buffer_interno, "EXA") != 0){
		 
			
				strcpy(buffer, buffer_interno);
				
				  for (i=0;i<3;i++){
						  buffer_interno[i]=0;
				  }
				  
				contador = 0;
				numero_lido_flag = 1;
			
			
		}
		 
	  }

}

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
