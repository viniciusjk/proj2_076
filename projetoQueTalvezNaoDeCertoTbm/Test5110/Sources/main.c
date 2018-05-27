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
/*Bibliotecas extras são chamadas, pois algumas funções extras são necessárias para manipulação de matrizes */

#define EXAUSTOR Bit1_PutVal(0); Bit2_PutVal(1); PDC1_ClearLine(0); PDC1_WriteLineStr(1, "OK EXAUST");
//função que seta o modo exaustor, os bits que contralam o sentido de roatação, e são escritas também as mensagens no visor
#define VENTILADOR Bit1_PutVal(1); Bit2_PutVal(0); PDC1_ClearLine(0); PDC1_WriteLineStr(1, "OK VENT");
//idem a função exaustor, mas com os valores dos bits de controle invertidos
#define PARADO Bit1_PutVal(0); Bit2_PutVal(0);
 //função para parar totalmente o motor, os bits zero são mandados. Nesta função não é escrita a mensagem
 // pois esta função é usada para outros propositos também
#define ESCREVEVEL itoa(blue,blueChar,10); PDC1_ClearLine(1);  strcat(blueChar, " %");  PDC1_WriteLineStr(2,blueChar);
//fução para escrever a velocidade atual no visor
#define ESCREVEVAL itoa(blue,blueChar,10); PDC1_ClearLine(1); PDC1_ClearLine(2);  PDC1_WriteLineStr(2,blueChar);
//função para escrever todos outros valores que não são velocidade no visor, como ano, dia, mês etc

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

void PARAMETROINC(void){
	
	//Função que exibe mensagem de erro, cada uma das letras tem que ser mandadas uma de cada vez
	// e a função wait foi necessária pois sem ela a função chegava fragmentada
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
	//idem a função PARAMETROINC
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
//função que define a velocidade do motor
{
	int speed=0;
	speed = 100-blue;
	PWM1_SetDutyMS(speed);

}



char buffer[20]; //variável que recebe a mensagem do bluetooth
int blue = 0; //variavel para os valores númericos lidos pelo bluetooth
int flag_leitura = 0;  //flag de leitura
int lastBlue = 0; //variável que recebe o ultimo valor de velocidade caso o motor seja parado
char blueChar[20];
int flag_comando_feito=0; //flag para ver se algum comando foi feito pelo programa

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
	  
	 
	  
	  if (flag_leitura==1){ //se existe leitura do bluetooth entramos neste loop
		 
		  
		  if(strcmp(buffer, "VENT") == 0){
			  //se VENT entra setamos o motor para o modo ventilador
			
			  blue = lastBlue;  // variavel de velocidade recebe o valor da ultima velocidade
			  PARADO; // paramos o motor
			  WAIT1_Waitms(10000); //esperamos 10 segundos para o motor parar totalmente
			  
			  setSpeed(blue);  // setamos a velocidade do motor
			  VENTILADOR;  //entramos no modo ventilador
			  
			  
		
			  ESCREVEVEL;  //chamamos a função para escrever a velocidade no visor
			 
			  flag_comando_feito=1;  //o comando foi feito setamos a flag para 1
			  flag_leitura = 0;  //voltamos a flag de leitura para 0
			  
			  	  	  }
		  
		  else if(strcmp(buffer, "EXAUST") == 0){
			
			//função para o exaustor, mesma lógica de do ventilador
	
			 blue = lastBlue;
			
			  PARADO;
			  WAIT1_Waitms(10000);
			  setSpeed(blue);
			  EXAUSTOR;
			   ESCREVEVEL;
			  flag_comando_feito = 1;
			  flag_leitura = 0;
		  	  	  	  	  	  	  }
		  
		  else if(strcmp(buffer, "PARA") == 0){
			  
			  //se PARA entramos na função de parar
			 
			 
			  PDC1_WriteLineStr(1, "OK PARA");  //escrevemos ok para no visor para indicar que 
												//entramos no modo parado do motor
			  PDC1_ClearLine(1);
			  PARADO;
			  flag_comando_feito = 1;
			  flag_leitura = 0;
		  }
		  
		  
/////////////////////////////////////////////////////////////////	

// A partir daqui são as funções que usam valores numéricos na leitura também
		  
		  
		  else if (strcmp(buffer, "VEL") == 0){
				
				//função para setar uma nova velocidade
			  
			  if(blue == NULL) 
				  //treste que checa se uma valor numerico foi passado
				/// para a variavel blue. Se não, exibimos a mensagem PARAMETRO INEXISTENTE
				//no visor do celular
					INEX();
					
				}
			  
			  else if (blue<=100 && blue>=0){
				  
				  //se a velocidade esta entre 0 e 100, mudamos a velocidade do motor
				  
				  lastBlue = blue; //salvamos a velocidade, para o caso de pararmos o motor
									//  e precisarmos fazer o motor voltar a rodar na mesma 
									// velocidade
				  setSpeed(blue);  //setamos a nova velocidade do motor
				  ESCREVEVEL;   //escrevemos o valor da velocidade no visor
				  
			  }
			  
			  else  {PARAMETROINC();}  //se  a velocidade está fora do range
										// exibimos a mensagem de PARAMETRO INCORRETO
			  
			  flag_comando_feito = 1; 
			  flag_leitura = 0;
			  lastBlue = blue;
		  }
		  
		  
		  
		  else if (strcmp(buffer, "ANO") == 0){
			  
			  // teste para setar o ano
			  
			  if(blue == NULL) { 
			  
			   //treste que checa se uma valor numerico foi passado
				/// para a variavel blue. Se não, exibimos a mensagem PARAMETRO INEXISTENTE
				//no visor do celular
				
					INEX();
				}
			  else if (blue<10000 && blue>=0){  //testamos se o range esta correto
				  
					ESCREVEVAL;
					PDC1_ClearLine(2);
					PDC1_WriteLineStr(3,"OK ANO");  //escrevemos no visor o ano setado
				  
			  }
			  else  {PARAMETROINC();}  // se nenhum dos casos anteriores, 
									// exibimos a mensagem de PARAMETRO INCORRETO
			  
			  
			  flag_comando_feito = 1;
			  flag_leitura = 0;
		  	  
		  }
		  
		  
		  else if (strcmp(buffer, "MES") == 0){
			  
			 // mesma lógica da função ANO,
			 //só mudamos o range de valores aceitáveis
			 
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
			  // mesma lógica da função ANO,
			 //só mudamos o range de valores aceitáveis
			 
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
			   // mesma lógica da função ANO,
			 //só mudamos o range de valores aceitáveis
			 
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
			   // mesma lógica da função ANO,
			 //só mudamos o range de valores aceitáveis
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
			   // mesma lógica da função ANO,
			 //só mudamos o range de valores aceitáveis
			  
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
			  // mesma lógica da função ANO,
			 //só mudamos o range de valores aceitáveis
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
			  
			 //se não entramos e nenhum dos comandos acima, o comando dado é
			 // inexistente
			 
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
		  

		   
		  WAIT1_Waitms(10000); // esperamos 10 segundos e limpamos a linha 2
		  PDC1_ClearLine(2);
		  
		  int i = 0;
		  
		  for (i=0;i<=19;i++){
			  
			  buffer[i] = 0;  //limpamos a váriavel buffer para ser usada novamente 
								// na proxima vez sem erros
			  
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
