/*PROYECTO. ESTRUCTURA DEL COMPUTADOR.*/
/*Elaborado por:
--------------------
*/

#include <stdio.h>
#include <stdlib.h>

	int matriz[10][5];
	unsigned long int vector[10];

void iniciarlizarvector(unsigned long int vector[10]){
	for(int x=0; x<10; x++)
		vector[x]=0;	
}
void inicializarmatriz(int matriz[10][5]){
	for(int x=0; x<10; x++)
		for(int y=0; y<5; y++)
			matriz[x][y]=0;	
}

int col3,numerocolumnaR;
void numerocolumna(){//ASSEMBLER
	/*Numero de entrada*/
	int numero=0,x=0,y=1;
	_asm{
		mov esi,0
		mov eax,col3
		mov ebx,4
		mul ebx
		add esi,eax
		lazo1:
		cmp x,10
		jge fin1
			cmp numero,0
			je fin2
				mov eax,y
				mov ebx,10
				mul ebx
				mov y,eax
			fin2:
			mov eax,[matriz+esi]
			mov ebx,y
			mul ebx
			mov ebx,numero
			add eax,ebx
			mov numero,eax
			add esi,20
			inc x
		jmp lazo1		
		fin1:
		mov eax,numero
		mov numerocolumnaR,eax
	}
}

int fil5,numerofilaR;
int numerofila(){//ASSEMBLER
	int numero=0,x,y=1,z=0,w;
	_asm{
		mov esi,0
		mov eax,fil5
		mov ebx,20
		mul ebx
		add esi,eax
		mov x,4
		add esi,16
		lazo1:
		cmp x,0
		jl fin1
			mov eax,[matriz+esi]
			mov ebx,z
			add eax,ebx
			mov w,eax
			cmp w,0
			jle fin2
				mov z,1
				cmp numero,0
				je fin3
					mov eax,y
					mov ebx,10
					mul ebx
					mov y,eax
				fin3:
				mov eax,[matriz+esi]
				mov ebx,y
				mul ebx
				mov ebx,numero
				add eax,ebx
				mov numero,eax
			fin2:
			sub esi,4
		dec x
		jmp lazo1
		fin1:
		mov eax,numero
		mov numerofilaR,eax
	}
}

void crearcolumna(int matriz[10][5], int col, unsigned long n){//ASSEMBLER
	/*Transforma cada número para llenar la matriz*/
	int x=0,y;
	unsigned long int z=n;
	_asm{		
		mov esi,0
		mov eax,col
		mov ebx,4
		mul ebx
		add esi,eax
		lazo:			
			cmp z,0
			jle fin
			mov eax,z
			mov ecx,10
			cdq
			div ecx
			mov z,eax
			mov y,edx
			mov eax,matriz
			mov ebx,y
			mov [eax+esi],ebx
			add esi,20
			jmp lazo
		fin:
	}
}
void crearvector(unsigned long int vector[10]){//Rutina#5 //ASSEMBLER
	int x;
	_asm{
		mov esi,0
		mov x,0
		lazo1:
		cmp x,10
		jge fin1
			mov eax,x
			mov fil5,eax
			call numerofila
			mov eax,vector
			mov ebx,numerofilaR
			mov [eax+esi],ebx
		add esi,4
		inc x
		jmp lazo1
		fin1:
	}
}

void insertardatos(int matriz[10][5], int *cant){ //Rutina#1
	printf("\nCantidad de numeros a registrar: ");
	scanf("%i",&(*cant));
	if (((*cant)>=2)&&((*cant)<=5))
		for (short x=1; x<=(*cant); x++){
			printf("Ingrese numero#%i :",x);
			unsigned long int n; scanf("%i",&n);
			crearcolumna(matriz,x-1,n);	
		}
	else 
		printf("\nPuede ingresar un maximo de 5 numeros y un minimo de 2\n\n");
	system("pause");
}

void mostrarmatriz(int matriz[10][5]){//Rutina#2
	system("cls");
	for(int x=0; x<10; x++){
		for(int y=0; y<5; y++){
			printf("\t %i",matriz[x][y]);
		}
		printf("\n");
	}
	printf("\n");
	system("pause");
}
void mostrarvector(unsigned long int vector[10]){//Rutina#6
	for(int x=0; x<10; x++)
		printf(" %i ",vector[x]);
	printf("\n");
	system("pause");
}

int fil1,col1,atrasxR; 
void atrasx(){//ASSEMBLER
	int x=col1-1,r=1,n=matriz[fil1][col1];
	_asm{
		cmp col1,0
		je fin1
			mov esi,0
			mov eax,fil1
			mov ebx,20
			mul ebx
			add esi,eax
			mov eax,x
			mov ebx,4
			mul ebx
			add esi,eax
			lazo2:
			cmp x,0
			jl fin2
				mov eax,n
				cmp eax,[matriz+esi]
				jne fin3
					mov r,0
				fin3:			
			sub esi,4
			dec x
			jmp lazo2
			fin2:
		fin1:	
		mov eax,r
		mov atrasxR,eax
	}
}

int fil2,cant2,numero2,repeticionesxR;
void repeticionesx(){//ASSEMBLER
	int rep=0,x=0;
	_asm{
		mov eax,fil2
		mov ebx,20
		mul ebx
		mov esi,eax
		lazo1:
		mov eax,x
		cmp eax, cant2
		jge fin1			
			mov ebx,numero2
			cmp [matriz+esi],ebx
			jne fin2
				inc rep
			fin2:
		add esi,4
		inc x
		jmp lazo1
		fin1:
		mov eax,rep
		mov repeticionesxR,eax
	}
}

int fil4,col4,cant4;
void posicionidentica(){//ASSEMBLER	
	char *msg1= "\nPosicion %i", *msg2="\nDigito coincidente: %i", *msg3="\nEntradas correpondientes: ", *linea="\n",*ent=" %i ";
	int x=col4,y,z,w,p;
	_asm{
		mov esi,0
		mov edi,0
		mov eax,fil4
		mov ebx,20
		mul ebx
		add esi,eax
		add edi,eax
		mov eax,col4
		mov ebx,4
		mul ebx
		add esi,eax
		lazo1:
		mov eax,x
		cmp eax,cant4
		jge fin1
			mov eax,fil4
			mov fil1,eax
			mov eax,x
			mov col1,eax
			call atrasx
			cmp atrasxR,0
			je fin2
				mov eax,fil4
				mov fil2,eax
				mov ebx,cant4
				mov cant2,ebx
				mov ecx,[matriz+esi]
				mov numero2,ecx				
				call repeticionesx
				mov eax,repeticionesxR
				mov y,eax
				cmp y,1
				jle fin3
					mov eax,fil4
					add eax,1
					push eax
					push msg1
					call printf
					pop msg1
					pop eax
					mov eax,[matriz+esi]
					push eax
					push msg2
					call printf
					pop msg2
					pop eax
					push msg3
					call printf
					pop msg3
					mov z,0
					mov w,0
					lazo2:
						mov eax,w
						cmp eax,y
						jg fin4
							mov eax,z
							cmp eax,cant4
							jge fin4
								mov eax,[matriz+esi]
								cmp eax,[matriz+edi]
								jne fin5
									mov eax,z
									mov col3,eax
									call numerocolumna
									mov eax,numerocolumnaR
									push eax
									push ent
									call printf
									pop ent
									pop eax
									inc w
								fin5:
								add edi,4
								inc z
						jmp lazo2
						fin4:
						push linea
						call printf
						pop linea			
				fin3:
			fin2:
		add esi,4
		inc x
		jmp lazo1
		fin1:	
	}
}

void mostrarposicionidentica(int matriz[10][5], int cant){//Rutina#3//ASSEMBLER
	int x,y,z,w;
	_asm{
		mov y,0
		mov esi,0
		lazo1:
		mov eax,y
		cmp eax,cant
		jge fin1
			mov z,0
			add esi,180
			mov x,9
			lazo2:			
			cmp x,0
			jl fin2
				mov eax,z
				mov ebx,matriz
				add eax,[ebx+esi]
				mov w,eax
				cmp w,0
				jle fin3
					mov z,1
					mov eax,x
					mov fil4,eax
					mov eax,y
					mov col4,eax
					mov eax,cant
					mov cant4,eax
					call posicionidentica
				fin3:
				sub esi,20
				dec x
			jmp lazo2
			fin2:
			add esi,4
			inc y
		jmp lazo1
		fin1:
	}
}

int fil6,col6,atrasyR;
void atrasy(){
	int r=1, x=fil6-1, n=matriz[fil6][col6];
	_asm{
		mov esi,0
		mov eax,col6
		mov ebx,4
		mul ebx
		add esi,eax
		mov eax,x
		mov ebx,20
		mul ebx
		add esi,eax
		lazo1:
		cmp x,0
		jl fin1
			mov eax,[matriz+esi]
			cmp n,eax
			jne fin2
				mov r,0
			fin2:
		sub esi,20
		dec x
		jmp lazo1
		fin1:
		mov eax,r
		mov atrasyR,eax
	}
}

int ent1,ent2,repeticionesyR;
void repeticionesy(){	
	int z,r,x,w,y;
	_asm{
		mov z,0
		mov r,0
		mov x,9
		mov esi,0		
		mov eax,ent1
		mov ebx,4
		mul ebx
		mov esi,eax
		add esi,180
		lazo1:
		cmp x,0
		jl fin1
			cmp [matriz+esi],0
			je fin2
				mov z,1
			fin2:
			cmp z,0
			je fin3
				mov w,0
				mov y,9
				mov edi,0
				mov eax,ent2
				mov ebx,4
				mul ebx
				mov edi,eax
				add edi,180
				lazo2:
				cmp y,0
				jl fin4
					cmp [matriz+edi],0
					je fin5
						mov w,1
					fin5:
					cmp w,0
					je fin6
						mov eax,[matriz+esi]
						cmp eax,[matriz+edi]
						jne fin7
							inc r
						fin7:
					fin6:
				sub edi,20
				dec y
				jmp lazo2
				fin4:				
			fin3:
		sub esi,20
		dec x
		jmp lazo1
		fin1:
		mov eax, r
		mov repeticionesyR,eax
	}
}

int col7,cant7;
void coincidencias(){
	char  *linea="\n", *msg1= "Entradas: %i y %i\n", *msg2="Coincidencias: %i\n", *msg3="Digitos:",*ent=" %i ";
	int x=col7+1,y,a,b,r,p,s,q;
	_asm{
		lazo1:
		mov eax,cant7
		cmp x,eax
		jge fin1
		mov eax,col7
		mov ent1,eax
		mov eax,x
		mov ent2,eax
		call repeticionesy
		mov eax, repeticionesyR
		mov y,eax
		cmp y,0
		jle fin2
			mov eax,col7
			mov col3,eax
			call numerocolumna
			mov eax, numerocolumnaR
			mov a,eax
			mov eax, x
			mov col3,eax
			call numerocolumna
			mov eax,numerocolumnaR
			mov b,eax
			push linea
			call printf
			pop linea
			push b
			push a
			push msg1
			call printf
			pop msg1
			pop a
			pop b
			push y
			push msg2
			call printf
			pop msg2
			pop y
			push msg3
			call printf
			pop msg3
			mov r,0
			mov p,9
			mov esi,0
			mov eax,col7
			mov ebx,4
			mul ebx
			mov esi,eax
			add esi,180
				lazo2:
				cmp p,0
				jl fin3
					cmp [matriz+esi],0
					je fin4
						mov r,1
					fin4:
					cmp r,0
					je fin5
						mov eax,p
						mov fil6,eax
						mov eax,col7
						mov col6,eax
						call atrasy
						cmp atrasyR,0
						je fin6
						mov s,0
						mov q,9
						mov edi,0
						mov eax,x
						mov ebx,4
						mul ebx
						mov edi,eax
						add edi,180
							lazo3:
							cmp q,0
							jl fin7
								cmp [matriz+edi],0
								je fin8
									mov s,1
								fin8:
								cmp s,0
								je fin9
									mov eax,q
									mov fil6,eax
									mov eax,x
									mov col6,eax
									call atrasy
									cmp atrasyR,0
									je fin10
									mov eax,[matriz+esi]
									cmp eax,[matriz+edi]
									jne fin10
										push eax
										push ent
										call printf
										pop ent
										pop eax
									fin10:
								fin9:
							sub edi,20
							dec q
							jmp lazo3
							fin7:
						fin6:
					fin5:
				sub esi,20
				dec p
				jmp lazo2
				fin3:
			push linea
			call printf
			pop linea
			fin2:
		inc x
		jmp lazo1
		fin1:
	}
}

void mostrarcoincidencias(int matriz[10][5], int cant){
	int x;
	_asm{
		mov x,0
		lazo1:
		mov eax,cant
		cmp x,eax
		jge fin1
			mov eax,x
			mov col7,eax
			mov eax,cant
			mov cant7,eax
			call coincidencias
		inc x
		jmp lazo1
		fin1:
	}
}

void menu(){
	int x=-1,cant=0;
	inicializarmatriz(matriz);
	iniciarlizarvector(vector);
	while(x){
		system("cls");
		printf("Menú principal\n");
		printf("--------------\n\n");
		printf("\t Opciones:\n");
		printf("\t ---------\n");
		printf("\t 1.Leer datos\n");
		printf("\t 2.Mostrar datos\n");
		printf("\t 3.Mostrar posiciones identicas de la matriz en la fila\n");
		printf("\t 4.Mostrar para cada numero sus coincidencias con las entradas\n");
		printf("\t 5.Crear el vector de enteros formados por filas\n");
		printf("\t 6.Mostrar el vector de enteros formados por filas\n");
		printf("\t 0.SALIR\n");
		scanf("%i",&x);
		if (x)
		switch(x){
			case 1:	inicializarmatriz(matriz);
					insertardatos(matriz,&cant);
					break;
			case 2: mostrarmatriz(matriz);
					break;
			case 3:	mostrarposicionidentica(matriz,cant);
					printf("\n");
					system("pause");
					break;
			case 4:	mostrarcoincidencias(matriz,cant);
					printf("\n");
					system("pause");
					break;
			case 5:	crearvector(vector);
					break;
			case 6:	mostrarvector(vector);
					break;	
		}
	}
}

void main(){
	menu();
	system("pause");
}

