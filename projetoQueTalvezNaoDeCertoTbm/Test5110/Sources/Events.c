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

extern int blue; //recebemos a varíavel blue para passarmos
				// os valores numericos lidos para o programa principal
extern char buffer[20]; // variável externa para salvarmos a string lida
extern int flag_leitura;  //flag para comunicarmos se a mensagem foi lida
int cnt = 0;  // contador para iterarmos dentro do buffer
char bufferAux[20];  // buffer auxliliar que recebe string diretamente do 
					// bluetooth, só depois de processada a string, passamos
					// seu valor para a variavel buffer, que se comunica com 
					// o programa principal
					
int flag_ReadNumber = 0;  //flag para sabermos se a mensagem continha
						// valores numericos


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
int j =0;


	

	AS1_RecvChar(&val); //função para ler a string do bluetooth
	int i = 0;
	
	
	if (val == '*'){
		  //se um * é lido significa que é o final da mensagem lida
		  // e que podemos passar o valor do buffer auxiliar para o programa principal
		
		  cnt = 0;
		 
		  
		  
		  if (flag_ReadNumber == 1){  
			// se um número foi lido, convertemos essa string
			// para int
			  blue = atoi(bufferAux);
			  flag_ReadNumber = 0;
			  
		  }
		  
		  else{
			  // se não foi lido um numero,
			  // passamos o bufferAux para a variável buffer, 
			  // que se comunica com o programa principal
		  strcpy(buffer, bufferAux);
		  
		  
		  }
		  
		  for (i=0;i<=19;i++){
			 // limpamos o vetor bufferAux para evitar futuros problemas com 
			 // as nova strings escritas
			  bufferAux[i]=0;
		  }
		  
		  flag_leitura = 1; // setamos a flag_leitura para um e entrarmos nas funçÕes 
							// do programa
		  flag_ReadNumber = 0;
	
		 
	  }
	
	else if (val != '\n' && val != '\f' && val != '\r' ){
		// enquanto * não é lido, vamos salvando o valor do bluetooth
		// no bufferAux
		
		 bufferAux[cnt]=val;
		 cnt++;
		 flag_leitura = 0;


							
		
			
			if ( (strcmp(bufferAux, "VEL") == 0 || strcmp(bufferAux, "ANO") == 0)   || \
			(strcmp(bufferAux, "DIA") == 0 || strcmp(bufferAux, "MES") == 0) || \
			strcmp(bufferAux, "HORA") == 0 || strcmp(bufferAux, "SEM") == 0|| strcmp(bufferAux, "MIN") == 0||\
			strcmp(bufferAux, "SEG") == 0){
				
				// se na string temos um dos valores acima,
				// temos um valor numerico passado
		 
			
			
				strcpy(buffer, bufferAux);
				// copiamos a parte já copiada para  o buffer, pois esta parte da mensagem
				// não será convertida para int, portanto é preciso salvar a parte não númerica primeiro
				
				  for (i=0;i<=2;i++){

						  bufferAux[i]=0;  // limpamos a parte já utilizada do buffer auxiliar
				  }
				  
				cnt = 0;
				flag_ReadNumber = 1;  // avisamos que existe váriavel numerica no mensagem do bluetooth por esta flag
			
			
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
