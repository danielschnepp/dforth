#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PILE 256
#define MAX_TEXTE 256

enum code_retour {
	CODE_CONTINUE,
	CODE_MANQUE_ARG,
	CODE_TROP_NOMBRES,
	CODE_FIN,
	CODE_ERREUR,
};

char texte [MAX_TEXTE] = { 0 };
int nb_caracteres = 0;
int nb_element = 0;	
int nb_element2 = 0;	
float pile[MAX_PILE] = { 0 };
float pile2[MAX_PILE] = { 0 };

char caracteres[MAX_PILE];

int lecture(){
	
	int nombre = 0;	

        memset(caracteres,0,MAX_PILE);

	nombre = scanf("%s",&caracteres);

	return nombre;
}

int affichage(){
	int i;

	printf("\n");
	for (i = nb_element;i > 0;i--){
		printf("# %f\n",pile[i-1]);
	}
	return 0;
}

int affichage_texte(){
	int i;

	printf("%s\n", texte);
	return CODE_CONTINUE;
}

float pop() {
	float f = pile[nb_element-1];
	pile[nb_element-1] = 0;
	nb_element --;
	return f;
}

void push(float f) {
	nb_element ++;
	pile[nb_element-1] = f;
}

float pop2() {
	float f = pile2[nb_element2-1];
	pile2[nb_element2-1] = 0;
	nb_element2 --;
	return f;
}

void push2(float f) {
	nb_element2 ++;
	pile2[nb_element2-1] = f;
}



enum code_retour rentre_pile(){

		int i;

		if (lecture() == EOF) {
			return 0;
		}

		if (!strcmp(caracteres, ".")){
			if (nb_element > 0) {				
				float f = pop();
				printf("%f", f); 
				printf("\n"); 
			}
		} else if (!strcmp(caracteres, ".\"")){
        		memset(texte,0,MAX_TEXTE);
			lecture();
			while(strcmp(caracteres, "\"")) {
				strcat(texte, caracteres);
				lecture();
			}
			affichage_texte();

		} else if (!strcmp(caracteres, "+")) {
			if (nb_element < 2){
				return CODE_MANQUE_ARG;
			} else {
				float a = pop();
				float b = pop();
				float c = a + b;
				push(c);
			}
		} else if (!strcmp(caracteres, "-")){
			if (nb_element < 2){
				return CODE_MANQUE_ARG;
			} else {
				float a = pop();
				float b = pop();
				float c = a - b;
				push(c);
			}
		} else if (!strcmp(caracteres, "*")){
			if (nb_element < 2){
				return CODE_MANQUE_ARG;
		   	} else {
				float a = pop();
				float b = pop();
				float c = a * b;
				push(c);
			}
		} else if (!strcmp(caracteres, "/")){
 			if (nb_element < 2){
				return CODE_MANQUE_ARG;
			} else {
				float a = pop();
				float b = pop();
				float c = a / b;
				push(c);
			}
		} else if (!strcmp(caracteres, "drop")){
			if (nb_element < 1){
				return CODE_MANQUE_ARG;
			} else {
				pop(); 
			}
		} else if (!strcmp(caracteres, "dup")){
			if (nb_element < 1){
				return CODE_MANQUE_ARG;
			} else {
				float f = pop(); 
				push(f); 
				push(f); 
			}
		} else if (!strcmp(caracteres, "roll")){
			if (nb_element < 1){
				return CODE_CONTINUE;
			} else {
				int i = 0;
				float a = pop();

				int nb_elements_initial = nb_element;
				for (i = 0; i < nb_elements_initial; i++) {
					float f = pop();
					push2(f);
				}
				push(a);
				for (i = 0; i < nb_elements_initial; i++) {
					float f = pop2();
					push(f);
				}
			}
		} else if (!strcmp(caracteres, "swap")){
			if (nb_element < 2){
				return CODE_CONTINUE;
			} else {
				float a = pop();
				float b = pop();
				push(a);
				push(b);
			}
		} else if (!strcmp(caracteres, "nroll")){
			int n = pop();
			if (nb_element < 3){
				return CODE_CONTINUE;
			} else if (n > nb_element){
				push(n);
				return CODE_MANQUE_ARG;
			} else {
				int i = 0;
				float a = pop();

				for (i = 0; i < n; i++) {
					float f = pop();
					push2(f);
				}
				push(a);
				for (i = 0; i < n; i++) {
					float f = pop2();
					push(f);
				}
			}
		} else if (!strcmp(caracteres, "ndup")){
			if (nb_element < 1){
				return CODE_MANQUE_ARG;
			} else {
				int n = pop();
				int i = 0;
				float a;

				if (nb_element <= n){
					push(n);
					return CODE_MANQUE_ARG;
				}
				for (i = 0;i < n;i++){
					float f = pop();
					push2(f);
				}
				a = pop();

				for (i = 0;i < n;i++){
					float f = pop2();
					push(f);
				}
				
				push(a);
			}
		} else if (!strcmp(caracteres, "nswap")){
			if (nb_element < 2){
				return CODE_MANQUE_ARG;
			} else {
				int n = pop();
				int i = 0;
				float a;
				float b = pop();

				if(nb_element <= n){
					push(n);
					return CODE_MANQUE_ARG;
				}
				for (i = 0;i < n;i++){
					float f = pop();
					push2(f);
				}
				a = pop();
				push(b);
				for (i = 0;i < n;i++){
					float f = pop2();
					push(f);
				}
				push(a);
			}

		} else if (!strcmp(caracteres, "purge")){
			while (nb_element){
				pop();
			}
		} else if (!strcmp(caracteres, "exit")){
			return CODE_FIN;
		} else {
			if (nb_element >= MAX_PILE){
				return CODE_TROP_NOMBRES;
			} else {
				float f;
				sscanf(caracteres, "%f", &f);
				push(f);
			}
		}
	return CODE_CONTINUE;
}

int main(){
	enum code_retour q = CODE_CONTINUE;

	while((q != CODE_FIN) && (q != CODE_ERREUR)){
		q = rentre_pile();
		switch (q){
			case CODE_CONTINUE : affichage();
				   break;

			case CODE_MANQUE_ARG : printf("\n Erreur : manque d'argument pour effectuer l'opération !!! \n  \n");
				   break;

			case CODE_TROP_NOMBRES : printf("\n Erreur : trop de nombres sur le pile !!! \n \n");
				   break;

			case CODE_FIN: printf("\n Fin du programme, arrêt en cours \n \n");
				   break;

			case CODE_ERREUR:
			default: printf("\n Erreur du programme : arrêt en cours \n \n");
				  affichage();
				  q = 5;
				  break;

		}
	}
	return 0;
}
