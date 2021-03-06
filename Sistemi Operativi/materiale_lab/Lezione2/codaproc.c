// codaproc.cpp : Defines the entry point for the console application.
//Costruire una liste concatenate che rappresenti la lista dei processi 
//(IP,blocco iniziale della memoria, blocco finale,link al processo successivo) 
// modalit� First fit
#include <stdio.h>
#include <malloc.h>

typedef struct PROC_CODA
{unsigned long IP;
 unsigned long BIni;
 unsigned long BEnd;
 PROC_CODA *next;
} proc_coda;


void Inserisci(proc_coda *prc,unsigned long mem,unsigned long pid);
void Elimina(proc_coda *prc);
void visualizza(proc_coda *prc);

int main(int argc, char* argv[])
{proc_coda *prcod;
 unsigned long mem;
 unsigned long pid=1;
 printf("dai la quantit� di memoria disponibile :");
 scanf("%d",&mem);
 prcod=(proc_coda *)malloc(sizeof(PROC_CODA));
 prcod->IP=0;prcod->BIni=0;prcod->BEnd=mem-1;prcod->next=NULL;
 char scelta[2];
 do{
	 do{printf("Per inserire  un processo nella lista : I\nPer eliminare il processo dalla lista : E\nPer Uscire                            : s\nScelta:");
        scanf("%s",scelta);
		if( (scelta[0]!='I') && (scelta[0]!='E') && (scelta[0]!='s')) 
			printf("Scelta non consentita\n\n");
		}while( (scelta[0]!='I') && (scelta[0]!='E') && (scelta[0]!='s'));    	
     if(scelta[0]=='I') Inserisci(prcod,mem,pid++);
     if(scelta[0]=='E') Elimina(prcod);
 }while(scelta[0]!='s');
 return 0;

}

void Inserisci(proc_coda *prc,unsigned long mem,unsigned long pid)
{unsigned long BEnd;
 unsigned long Lungh;
 char trovato=0;
 proc_coda *P_prc,*P1_prc;
 printf("Dai la memoria occupata dal Processo:");scanf("%d",&Lungh);
 if( (Lungh>mem)) 
	printf("Lunghezza Blocco di memoria non consentito!!!!\n");
 else
 { P_prc=prc;//[0,0,300]->NULL Lungh=30
   while((P_prc!=NULL)&& (trovato==0))
   {if((P_prc->IP==0)&&((P_prc->BEnd-P_prc->BIni+1)>=Lungh))
     trovato=1;
   else 
	 P_prc=P_prc->next;
   }
  if(trovato==1)
  {P_prc->IP=pid;//[1,0,300]->NULL
   BEnd=P_prc->BIni+Lungh-1;//BEnd=0+30-1=29
   if((P_prc->BEnd-BEnd)>0)  
    {P1_prc=(proc_coda *)malloc(sizeof(PROC_CODA));
     P1_prc->IP=0;//[1,0,300]->NULL [0,x,y]->z
	 P1_prc->next=P_prc->next;//[1,0,300]->NULL [0,x,y]->NULL
     P_prc->next=P1_prc;//[1,0,300]->[0,x,y]->NULL
	 P1_prc->BIni=BEnd+1;//[1,0,300]->[0,30,y]->NULL
	 P1_prc->BEnd=P_prc->BEnd;//[1,0,300]->[0,30,300]->NULL
     P_prc->BEnd=BEnd;//[1,0,29]->[0,30,300]->NULL
    }
   
  }
  else
   printf("Lunghezza Blocco di memoria non consentito!!!!\n");
 }
 visualizza(prc);  
}


void Elimina(proc_coda *prc)
{unsigned long ip;
 printf("Dai IP del Processo da Elimanare:");scanf("%d",&ip);
 proc_coda *P_prc,*P_Prec_prc,*P_Next_prc;
 P_prc=prc;P_Prec_prc=NULL;
 char trovato=0;
 while( (P_prc!=NULL)&&(trovato==0))
	{if(ip==P_prc->IP) trovato=1;
	 else {P_Prec_prc=P_prc;P_prc=P_prc->next;}
	}
 if(trovato)
    {P_prc->IP=0;
	 if(P_prc->next!=NULL)  // non sono l'ultimo
	  {if(P_prc->next->IP==0) //il prossimo � un buco 
		  {P_prc->BEnd=P_prc->next->BEnd;
		   P_Next_prc=P_prc->next;
		   P_prc->next=P_Next_prc->next;
		   free(P_prc->next);
		  }
	  }
	 if(P_Prec_prc!=NULL)//non sono il primo 
	  {if(P_Prec_prc->IP==0)//il precedente � un buco
	    {P_Prec_prc->BEnd=P_prc->BEnd;
	     P_Prec_prc->next=P_prc->next;
		 free(P_prc);
	    }
      }
	}//if trovato
 else
	printf("Processo non Trovato\n");
 visualizza(prc);
}

void visualizza(proc_coda *prc)
{proc_coda *P_prc;
 P_prc=prc;
 while(P_prc!=NULL)
 {printf("[%d|%d|%d]->",P_prc->IP,P_prc->BIni,P_prc->BEnd);
  P_prc=P_prc->next;
 }
 printf("NULL\n");
}