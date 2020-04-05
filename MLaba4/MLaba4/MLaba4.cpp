#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>

struct Stack
{
	char info;	     // Информационная часть элемента, например int
	Stack* next;    // Адресная часть – указатель на следующий эле-мент 
	int priority;
} *begin;

Stack* inStack(Stack*, char, int);
Stack* outStack(Stack*, char*);
void rezult(char[], int);
int znak (char);
void del_All(Stack**);
void task(char []);



int main()
{
	setlocale(0, "rus");
	char formula[100];
	printf("Введите формулу:\n");
	gets_s(formula);
	task(formula);

	return 0;
}

Stack* inStack(Stack* p, char in, int prior)
{
	Stack* t = new Stack;			// Захватываем память для элемента
	t->info = in;			// Формируем информационную часть
	t->next = p;			// Формируем адресную часть
	t->priority = prior;
	return t;
}

Stack* outStack(Stack* p, char* out) 
{
	Stack* t = p;			// Устанавливаем указатель t на вершину p
	*out = p->info;
	p = p->next; 		// Переставляем вершину p на следующий
	delete t; 			// Удаляем бывшую вершину t
	return p; 			// Возвращаем новую вершину p
}


void task(char formula[])
{
	char otvet[100] = "";
	Stack* t;
	begin = NULL; 		                	// Стек операций пуст
	char ss, a;
	int len = strlen(formula), k, otv = 0, n = 0;
	for (k = 0; k <= len; k++) {
		ss = formula[k];
		if (ss == 32)
			continue;
		if (ss == '(') begin = inStack(begin, ss, 1);
		if (ss == ')') {
			// Выталкиваем из стека все знаки операций до открывающей скобки
			while ((begin->info) != '(') {
				begin = outStack(begin, &a);	// Считываем элемент из
				otvet[otv] = a;
				otv++;
			}
			begin = outStack(begin, &a);	// Удаляем из стека скобку «(»
		}
		// Букву (операнд) заносим в выходную строку
		if (ss >= 'a' && ss <= 'z')
		{
			otvet[otv] = ss;
			otv++;
			n++;
		}
		if (znak(ss)) {
			while (begin != NULL && begin->priority >= znak(ss)) {
				begin = outStack(begin, &a);
				otvet[otv] = a;
				otv++;
			}
			begin = inStack(begin, ss, znak(ss));
		}
	}
	while (begin != NULL) {
		begin = outStack(begin, &a);
		otvet[otv] = a;
		otv++;
	}
	puts(otvet);
	rezult(otvet, n);
}

void rezult(char otvet[], int n)
{
	double forms[500];
	for (int i = 0; i < n; i++)
	{
		printf("Переменная %c равна: ", 'a' + i);
		scanf("%lf", &forms[static_cast<int>('a'+ i)]);
	}
	char ch, ch1, ch2, chr = 'z' + 1;
	double op1, op2, rez = 0;
	for (int i = 0; i <= strlen(otvet); i++) {
		ch = otvet[i];
		if (!znak(ch)) begin = inStack(begin, ch, 0);
		else {
			begin = outStack(begin, &ch1);
			begin = outStack(begin, &ch2);
			op1 = forms[static_cast<int>(ch1)];
			op2 = forms[static_cast<int>(ch2)];
			switch (ch) {
			case '+': 	rez = op2 + op1;  		break;
			case '-': 	rez = op2 - op1;  		break;
			case '*': 	rez = op2 * op1;  		break;
			case '/': 	rez = op2 / op1;   		break;
			case '^': 	rez = pow(op2, op1); 	break;
			}
			forms[static_cast<int>(chr)] = rez;
			begin = inStack(begin, chr, 0);
			chr++;
		}
	}
	printf("%lf", rez);
}

int znak(char ss)
{
	switch (ss)
	{
		case '+': case '-':
			return 2; break;
		case '*': case '/':
			return 3; break;
		case '^':
			return 4; break;
		default:
			return 0;
	}
}