#include<stdio.h>  
#include<stdlib.h>  
#include<time.h>  
#include<math.h>
#include <string.h>
  
typedef struct  
{  
	int naipe;  
	int face;  
} carta;

typedef struct  
{  
	int indice;  
	carta card;  
} busca; 

void menu(int completo);
void embaralha(carta baralho[], carta baralhoOriginal[]);  
void escreve_baralho(carta baralho[], int nro);  
void zera(carta vet[], int nro);
void distribui_baralho(carta baralho[], carta mao1[], carta mao2[], char nome[], int nro);
int pontuacao_total(carta total[], int nro);
void adiciona_ao_total(carta total[], carta soma[], int nro);
int jogada_pessoa(carta baralho[],carta mao[], carta total[], char nome[]);
int jogada_computador(carta baralho[], carta mao[], carta total[]);
int verificaFimJogo(carta baralho[]);
void FimDoJogo(carta mao1[], carta mao2[], int pontuacao1, int pontuacao2, char nome[]);
  
main()  
{  
	carta baralho[52], baralhoOriginal[52], mao1[26], mao2[26], totalMao1[26], totalMao2[26];  
	char nome[20];
	int op;
	int completo = 1;
	int jogou = 0;
	int jogando = 0;
	int sai = 0;
	int pontuacaoMao1 = 0;
	int pontuacaoMao2 = 0;

	while(!sai)
	{
		menu(completo);
		fflush(stdin);
		scanf("%d", &op);

		switch(op)
		{
			case 1: printf("Digite do nome do jogador:\n");
				fflush(stdin);
				scanf("%s", &nome);
				printf("\n\n");
				zera(baralho, 52);
				zera(baralhoOriginal, 52);
				zera(mao1, 26);
				zera(mao2, 26);
				zera(totalMao1, 26);
				zera(totalMao2, 26);
				pontuacaoMao1 = 0;
				pontuacaoMao2 = 0;
				embaralha(baralho, baralhoOriginal);		
				distribui_baralho(baralho, mao1, mao2, nome, 3);
				completo = 0;
				jogando = 1;
				break;

			case 2: sai = 1;
				break;

			default: printf("Opcao invalida:\n");
		}

		while(jogando)
		{
			menu(completo);
			fflush(stdin);
			scanf("%d", &op);
			switch(op)
			{
				case 1:  
                        pontuacaoMao2 = pontuacaoMao2 + jogada_pessoa(baralho, mao2, totalMao2, nome);
						printf("Voce possui %d pontos\n", pontuacaoMao2);
						pontuacaoMao1 = pontuacaoMao1 + jogada_computador(baralho, mao1, totalMao1);
						printf("O computador possui %d pontos\n", pontuacaoMao1);
						if(verificaFimJogo(baralho))
						{
							FimDoJogo(mao1, mao2, pontuacaoMao1, pontuacaoMao2, nome);
							jogando = 0;
							completo = 1;
						}
						break;

				case 2: printf("Sua Mao:\n");
						escreve_baralho(mao2, 26);
						break;

				case 3: 
						printf("Mao do Computador:\n");
						escreve_baralho(mao1, 26);
						break;

				case 4: 
						printf("Cartas no Baralho Atual:\n");
						escreve_baralho(baralho, 52);
						break;

				case 5: 
						printf("Baralho:\n");
						escreve_baralho(baralhoOriginal, 52);
						break;

				case 6: printf("Voce possui %d pontos\n", pontuacaoMao2);
						printf("O Computador possui %d pontos\n", pontuacaoMao1);
						break;
						
				case 7: printf("Voce possuia %d pontos\n", pontuacaoMao2);
						printf("O Computador possuia %d pontos\n", pontuacaoMao1);
						FimDoJogo(mao1, mao2, pontuacaoMao1, pontuacaoMao2, nome);
						jogando = 0;
						completo = 1;
						break;

				case 8: printf("Baralho de Pontos do Jogador %s:\n", nome); 
						escreve_baralho(totalMao2, 26);
						break;

				case 9:
						printf("Baralho de Pontos do Computador:\n");
						escreve_baralho(totalMao1, 26);
						break;

				default: printf("Opcao invalida:\n");
			}
		}
	}
}

void menu(int completo)
{
	printf("\n\t\t\t\t   ~~~##########JOGO DO 15##########~~~\n");
	if(completo)
	{
		printf("\t\t\t\t#\t 1 - Inicia Jogo\t\t#\n");
		printf("\t\t\t\t#\t 2 - Sai do programa\t\t#");
	}
	else
	{
		printf("\t\t\t\t#\t 1 - Joga\t\t\t#\n");
		printf("\t\t\t\t#\t 2 - Ver Mao\t\t\t#\n");
		printf("\t\t\t\t#\t 3 - Ver Mao do Computador\t#\n");
		printf("\t\t\t\t#\t 4 - Ver baralho Atual\t\t#\n");
		printf("\t\t\t\t#\t 5 - Ver baralho Original\t#\n");
		printf("\t\t\t\t#\t 6 - Pontuacao Atual\t\t#\n");
		printf("\t\t\t\t#\t 7 - Fim do jogo\t\t#");
	}
	printf("\n\t\t\t\t   ~~~##############################~~~\n");
	printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
}
  
void embaralha(carta baralho[], carta baralhoOriginal[])  
{  
	int i, n, f;  
	srand(time(NULL));  
  
	zera(baralho, 52);
	zera(baralhoOriginal, 52);
  
	for(n = 1; n <= 4; n++)  
	{  
		for(f = 1; f <= 13; f++)  
		{  
			i = rand() % 52;  
			while(baralho[i].face != 0 )  
			{  
				i = rand() % 52;  
			}  
			baralho[i].naipe = n;  
			baralho[i].face = f;  
		}  
	}

	for(i = 0; i < 52; i++)  
	{    
		baralhoOriginal[i] = baralho[i];
	} 
}  
  
void escreve_baralho(carta baralho[], int nro)  
{  
	int i;  
  
	for(i = 0; i < nro; i++)  
	{
		if(baralho[i].face != 0)
		{
			if(baralho[i].naipe == 1)
			{
				printf("%d de ouros\n", baralho[i].face);
			}
			else if(baralho[i].naipe == 2)
			{
				printf("%d de copas\n", baralho[i].face);
			}
			else if(baralho[i].naipe == 3)
			{
				printf("%d de paus\n", baralho[i].face);
			}
			else if(baralho[i].naipe == 4)
			{
				printf("%d de espadas\n", baralho[i].face);
			}
		}
	}  
}  
  
void zera(carta vet[], int nro)  
{  
	int i;  

	for(i = 0; i < nro; i++)
	{
		vet[i].naipe = 0;  
		vet[i].face = 0; 
	}
}

void distribui_baralho(carta baralho[], carta mao1[], carta mao2[], char nome[], int nro)
{
	int i, j, index;

	zera(mao1, 26);
	zera(mao2, 26);
	
	for(i = 0; i < (nro*2); i++)
	{
		if(i % 2 == 0)
		{	
			mao2[i/2] = baralho[i];
			
			if(baralho[i].naipe == 1)
				printf("%s recebe %d de ouros\n", nome, baralho[i].face);
			else if(baralho[i].naipe == 2)
				printf("%s recebe %d de copas\n", nome, baralho[i].face);
			else if(baralho[i].naipe == 3)
				printf("%s recebe %d de paus\n", nome, baralho[i].face);
			else if(baralho[i].naipe == 4)
				printf("%s recebe %d de espadas\n", nome, baralho[i].face);
				
			baralho[i].face = 0;
			baralho[i].naipe = 0;
		}
		else
		{
			mao1[i/2] = baralho[i];
				
			baralho[i].face = 0;
			baralho[i].naipe = 0;
		}
	}
}

int pontuacao_total(carta total[], int nro)
{
	int i;
	int soma = 0;

	for(i = 0; i < nro; i++)
	{
		soma = soma + total[i].face;
	}
	
	return soma;
}

void adiciona_ao_total(carta total[], carta soma[], int nro)
{
	int i, j;
	int colocou = 0;
	for(i = 0; i < nro; i++)
	{
		j = 0;
		colocou = 0;
		if(soma[i].face != 0)
		{
			while((!colocou) && (j < nro))
			{
				if(total[j].face == 0)
				{
					total[j] = soma[i];
					colocou = 1;
				}
				j++;
			}			
		}
	}
}

int jogada_pessoa(carta baralho[],carta mao[], carta total[], char nome[])
{
	int i, j, k, l, x, op, index, colocou;
	int soma = 0;
	int comprou = 0;
	int naipeDiferente = 0;
	int somou = 0;
	int somando = 0;
	int pontuou = 0;
	int acabouMao = 1;
	static int pontuacao = 0;
	carta somar[26];

	zera(somar, 26);

	i=0;
    while((!comprou) && (i < 26))
    {
		if(mao[i].face == 0)
        {
            j = 0;
            while((!comprou) && (j < 52))
            {
                if(baralho[j].face != 0)
                {
                    mao[i] = baralho[j];
					baralho[j].face = 0;
                    
                    comprou = 1;
                    printf("Voce comprou");
                    switch (mao[i].naipe)
                    {
                        case 1: printf(" %d de ouros\n", mao[i].face);
                                break;
                        case 2: printf(" %d de copas\n",mao[i].face);
                                break;
                        case 3: printf(" %d de paus\n", mao[i].face);
								break;
                        case 4: printf(" %d de espadas\n", mao[i].face);
                                break;
                        default: printf("Opcao invalida!\n"); 
                    }
                }
                j++;
            }
            if(!comprou)
            {
            	printf("Nao existem mais cartas no baralho!\n");
            	comprou = 1;
            }
        }
        i++;
    }
    
    for(i = 0; i < 26; i++) 
    {
   		if(mao[i].face != 0)
        {
			soma = soma + mao[i].face;
		}
	}

	if(soma > 15)
	{
		printf("%s, indique quais cartas deseja somar:\n", nome);
	}
	else
	{
		printf("%s, voce nao pode somar nesta rodada.\n", nome);
		getchar();
		if(pontuou)
		{
			return pontuacao;
		}
		else
			return 0;
	}

	soma = 0;
	while(1)
	{
        printf("\nEscolha uma opcao para somar seus pontos:\n");
		for(i = 0; i < 26; i++)
		{
			index = i + 1;
			if((soma) && ((mao[i].face != 0) && ((mao[i].face != somar[i].face) && (mao[i].naipe != somar[i].naipe))))
			{
				switch (mao[i].naipe)
                {
                    case 1: printf("%d - %d de ouros\n",index, mao[i].face);
                            break;
                    case 2: printf("%d - %d de copas\n",index, mao[i].face);
                            break;
                    case 3: printf("%d - %d de paus\n",index, mao[i].face);
                            break;
                    case 4: printf("%d - %d de espadas\n",index, mao[i].face);
                            break;
                    default: printf("Opcao invalida!\n"); 
                }
            }
			else if((mao[i].face != 0) && (mao[i].face != somar[i].face) && (mao[i].naipe != somar[i].naipe))
            {
                switch (mao[i].naipe)
                {
                    case 1: printf("%d - %d de ouros\n",index, mao[i].face);
                            break;
                    case 2: printf("%d - %d de copas\n",index, mao[i].face);
                            break;
                    case 3: printf("%d - %d de paus\n",index, mao[i].face);
                            break;
                    case 4: printf("%d - %d de espadas\n",index, mao[i].face);
                            break;
                    default: printf("Opcao invalida!\n");
                }
            }
        }
		printf("0 - Passa a vez\n");

		fflush(stdin);		        
		scanf("%d", &op);
		if(op == 0)
		{
			if(pontuou)
			{
				return pontuacao;
			}
			else
				return 0;
		}
		op = op - 1;

		if(mao[op].face == 0)
		{
			printf("%d eh uma opcao invalida.\n", op);
		}
		else
		{
			soma = soma + mao[op].face;
			somar[op] = mao[op];
			mao[op].face = 0;

			printf("Sua soma eh %d.\n", soma);

			if(soma == 15)
			{
				soma = 0;
				pontuou = 0;
				somou = 1;
				
				for(i = 0; i < 26; i++)
				{
					if(!pontuou)
					{
						if(somar[i].face == 13)
						{
							for(j = i+1; j < 26; j++)
							{
								if((somar[j].face == 1) && (!pontuou))
								{
									pontuacao = 150;
									pontuou = 1;
								}
							}
						}

						if(somar[i].face == 5)
						{
							for(j = i+1; j < 26; j++)
							{
								if((somar[j].face == 5) && (!pontuou))
								{
									pontuacao = 120;
									pontuou = 1;
								}
							}
						}
					}
					
					if(!pontuou)
					{
						if(somar[i].face != 0)
						{
							for(j = i+1; j < 26; j++)
							{
                                  
                                  if ((somar[i].naipe != somar[j].naipe) &&  (somar[j].face != 0)) {         
                                     naipeDiferente = 1;                                                                                                                                                    
                                  }
                             }
                         if (naipeDiferente != 1){                         
                           pontuacao = 100;
         				   pontuou = 1;
                         }
                             
                        }																
					}
					
					if(!pontuou)
					{
						if(mao[i].face != 0)
						{
							acabouMao = 0;
						}
						else
						{
							acabouMao = 1;
						}
					}
				}
		
				if(acabouMao)
				{
					pontuacao = 50;
					pontuou = 1;
				}
				
				printf("Voce somou 15!\n");
				adiciona_ao_total(total, somar, 26);				
			}
			else if(soma < 15)
			{
				printf("Voce ainda nao somou 15 pontos.\n");
			}
			else if(soma > 15)
			{
				printf("O valor somado ultrapassa os 15! Inicie a jogada novamente.\n");

				for(i = 0; i < 26; i++) 
				{
					j = 0;
					colocou = 0;
					if(somar[i].face != 0)
					{
						while((!colocou) && (j < 26))
						{
							if(mao[j].face == 0)
							{
								mao[j] = somar[i];
								colocou = 1;
							}
							j++;
						}			
					}
				}
				zera(somar, 26);
				soma = 0;
				pontuacao = 0;
				pontuou = 0;
			}
		}
	}
}

int jogada_computador(carta baralho[], carta mao[], carta total[])
{
	int i, j, k, l, x, op, index;
	int cartaNroAux[4];
	int nroCartas = 2;
	int soma = 0;
    int comprou = 0;
	int somou = 0;
	int sai = 0;
	int naipeDiferente = 0;
	int vaicomprar = 0;
	int somando = 0;
	int pontuou = 0;
	int acabouMao = 1;
	static int pontuacao = 0;
	carta somar[26];
	busca buscaCarta[5];

	zera(somar, 26);
	
	i=0;
    while((!comprou) && (i < 26))
    {
		if(mao[i].face == 0)
        {
            j = 0;
            while((!comprou) && (j < 52))
            {
                if(baralho[j].face != 0)
                {
                    mao[i] = baralho[j];
					baralho[j].face = 0;
                    
                    comprou = 1;
                    printf("O computador comprou uma carta.\n");
                }
                j++;
            }
            if(!comprou)
            {
            	printf("Nao existem mais cartas no baralho!\n");
            	comprou = 1;
            }
        }
        i++;
    }

	for(i = 0; i < 26; i++)
    {
        if(mao[i].face != 0)
        {
			soma = soma + mao[i].face;
		}
	}

	if(soma >= 15)
	{
		soma = 0;
		pontuacao = 0;
		while(1)
		{
			somou = 0;
			for(i = 0; i < 5; i++)
			{
				buscaCarta[i].indice = 0;
				buscaCarta[i].card.face = 0;
				buscaCarta[i].card.naipe = 0;
			}
			switch(nroCartas)
			{
				case 2:
					for(i = 0; i < 26; i++)
					{
						if((mao[i].face != 0) && (!somou))
						{
							buscaCarta[0].indice = i;
							buscaCarta[0].card = mao[i];
							cartaNroAux[0] = 15 - buscaCarta[0].card.face;
						
							for(j = 0; j < 26; j++)
							{
								if((mao[j].face == cartaNroAux[0]) && (!somou))
								{
									buscaCarta[1].indice = j;
									buscaCarta[1].card = mao[j];
									somou = 1;
								}
							}
						}
					}

					if(!somou)
					{
						nroCartas = 3;
						for(i = 0; i < 5; i++)
						{
							cartaNroAux[i] = 0;
						}
					}	
					break;

					case 3:
						for(i = 0; i < 26; i++)
						{
							if((mao[i].face != 0) && (!somou))
							{
								buscaCarta[0].indice = i;
								buscaCarta[0].card = mao[i];
								cartaNroAux[0] = 15 - buscaCarta[0].card.face;
					
								for(j = i+1; j < 26; j++)
								{
									if((mao[j].face != 0) && (!somou))
									{
										buscaCarta[1].indice = j;
										buscaCarta[1].card = mao[j];
										cartaNroAux[1] = cartaNroAux[0] - buscaCarta[1].card.face;
									
										for(k = j+1; k < 26; k++)
										{
											if((mao[k].face == cartaNroAux[1]) && (!somou))
											{
												buscaCarta[2].indice = k;
												buscaCarta[2].card = mao[k];
												somou = 1;
											}
										}
									}
								}
							}
						}

						if(!somou)
						{
							nroCartas = 4;
							for(i = 0; i < 5; i++)
							{
								cartaNroAux[i] = 0;
							}
						}
						break;
						
					case 4:
						for(i = 0; i < 26; i++)
						{
							if((mao[i].face != 0) && (!somou))
							{
								buscaCarta[0].indice = i;
								buscaCarta[0].card = mao[i];
								cartaNroAux[0] = 15 - buscaCarta[0].card.face;
					
								for(j = i+1; j < 26; j++)
								{
									if((mao[j].face != 0) && (!somou))
									{
										buscaCarta[1].indice = j;
										buscaCarta[1].card = mao[j];
										cartaNroAux[1] = cartaNroAux[0] - buscaCarta[1].card.face;
									
										for(k = j+1; k < 26; k++)
										{
											if((mao[k].face != 0) && (!somou))
											{
												buscaCarta[2].indice = k;
												buscaCarta[2].card = mao[k];
												cartaNroAux[2] = cartaNroAux[0] - buscaCarta[2].card.face;
									
												for(l = k+1; l < 26; l++)
												{
													if((mao[l].face == cartaNroAux[2]) && (!somou))
													{
														buscaCarta[3].indice = l;
														buscaCarta[3].card = mao[l];
														somou = 1;
													}
												}
											}
										}
									}
								}
							}
						}

						if(!somou)
						{
							nroCartas = 0;
							for(i = 0; i < 5; i++)
							{
								cartaNroAux[i] = 0;
							}
						}
						break;
				
					default: if(pontuou)
							{
								return pontuacao;
							}
							else
								return 0;
							break;
			}

			if(somou)
			{
				pontuou = 0;
				for(i = 0; i < nroCartas; i++)
				{
					somar[i] = buscaCarta[i].card;
					mao[buscaCarta[i].indice].face = 0;

					if(!pontuou)
					{
						if(buscaCarta[i].card.face == 13)
						{
							for(j = i+1; j < nroCartas; j++)
							{
								if((buscaCarta[j].card.face == 1) && (!pontuou))
								{
									pontuacao = 150;
									pontuou = 1;
								}
							}
						}

						if(buscaCarta[i].card.face == 5)
						{
							for(j = i+1; j < nroCartas; j++)
							{
								if((buscaCarta[j].card.face == 5) && (!pontuou))
								{
									pontuacao = 120;
									pontuou = 1;
								}
							}
						}
					}
				}
				
				if(!pontuou)
				{
					
							for(j = 1; j < 26; j++)
							{
                                  
                                  if ((buscaCarta[0].card.naipe != buscaCarta[j].card.naipe) &&  (buscaCarta[j].card.face != 0)) {         
                                     naipeDiferente = 1;                                                                                                                                                    
                                  }
                             }
                         if (naipeDiferente != 1){                         
                           pontuacao = 100;
         				   pontuou = 1;
                         }
                             
				}
				
				if(!pontuou)
				{
					for(i = 0; i < 26; i++)
					{
						if(mao[i].face != 0)
						{
							acabouMao = 0;
						}
						else
						{
							acabouMao = 1;
						}
					}
			
					if(acabouMao)
					{
						pontuacao = 50;
						pontuou = 1;
					}
				}

				printf("O computador somou 15!\n");
				adiciona_ao_total(total, somar, 26);
			}
		}
    }	
	else
	{
		if(pontuou)
		{
			return pontuacao;
		}
		else
			return 0;
	}
}

int verificaFimJogo(carta baralho[])
{
	int i;
	int acabou = 0;
	
	for(i = 0; i < 52; i++)
	{
		if(baralho[i].face == 0)
		{
			acabou = 1;
		}
		else
		{
			return 0;
		}
	}
	
	return acabou;
}

void FimDoJogo(carta mao1[], carta mao2[], int pontuacao1, int pontuacao2, char nome[])
{
	FILE * File;
	char buffer [100];
	int i;

    printf("\tFIM DA PARTIDA!\n\n");
    
	File = fopen ("Resultados.txt" , "a");
	if (File == NULL) perror ("Erro ao abrir o arquivo");
	
	fprintf(File, "FIM DA PARTIDA\n\n");
	
	fprintf(File, "%s acabou o jogo com %d pontos e com as cartas na mao:\n", nome, pontuacao2);
	
	for(i = 0; i < 26; i++)
	{
		if(mao2[i].face != 0)
		{
			switch (mao2[i].naipe)
            {
                case 1: fprintf(File, "%d de ouros\n", mao2[i].face);
                        break;
                case 2: fprintf(File, "%d de copas\n", mao2[i].face);
                        break;
                case 3: fprintf(File, "%d de paus\n", mao2[i].face);
                        break;
                case 4: fprintf(File, "%d de espadas\n", mao2[i].face);
                        break;
                default: printf("Opcao invalida!\n"); 
            }
		}
	}
	
	fprintf(File, "\nO computador acabou o jogo com %d pontos e com as cartas na mao:\n", pontuacao1);
	
	for(i = 0; i < 26; i++)
	{
		if(mao1[i].face != 0)
		{
			switch (mao1[i].naipe)
            {
                case 1: fprintf(File, "%d de ouros\n", mao1[i].face);
                        break;
                case 2: fprintf(File, "%d de copas\n", mao1[i].face);
                        break;
                case 3: fprintf(File, "%d de paus\n", mao1[i].face);
                        break;
                case 4: fprintf(File, "%d de espadas\n", mao1[i].face);
                        break;
                default: printf("Opcao invalida!\n"); 
            }
		}
	}
	
	if(pontuacao1 < pontuacao2)
	{
		fprintf(File, "%s ganhou o jogo!\n", nome);
	}
	else if (pontuacao1 > pontuacao2)
	{
		fprintf(File, "O computador ganhou o jogo!\n");
	}
	else if (pontuacao1 == pontuacao2)
	{
		fprintf(File, "O jogo empatou!\n");
	}
	
	fprintf(File, "\n\n\n");

	fclose (File);
}

