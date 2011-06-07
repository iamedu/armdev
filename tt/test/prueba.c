#define BASE	0x0
#define NULL 0

#include <stdarg.h>

typedef struct UARTInterface {
        int US_CR;
        int US_MR;
        int US_IER;
        int US_IDR;
        int US_IMR;
        int US_CSR;
        int US_RHR;
        int US_THR;
        int US_BRGR;
        int US_RTOR;
        int US_TTGR;
        int US_Reserved_1;
        int US_FIDI;
        int US_NER;
        int US_Reserved_2;
        int US_IF;
} UARTInterface;

typedef struct lista {
	char l;
        struct lista *siguiente;
} lista;

void *malloc(int);
lista *nodo(char);
void add(lista **, char);
void put_char(char c);
void print_num(int d, int b);
int printf(const char *format, ...);

static int var = 6;

int main() {
	UARTInterface *uart = (UARTInterface *)0xFFFB0000;
	int i;
	int *base = (int *)BASE;
	*base = 4;

	lista *principal = NULL;
	lista *tmp;
	uart->US_CR |= 0x40;
	
	for(i = 0; i < 10; i++)
		add(&principal, i);
	add(&principal,'\n');

	while(1) {
		tmp = principal;
		while(tmp != NULL){
			printf("Var estatica 0x%x:%d, Var lista:%d\n", 
				&var,
				var,
			        tmp->l);
			tmp = tmp->siguiente;
		}
	}
	return 0;
}

int printf(const char *format, ...) {
	va_list ap;
	char *fmt = (char *)format;
	int d;
	char c;
	char *s;

	va_start(ap, format);

	while(*fmt) {
		c = *fmt++;
		if(c != '%') {
			put_char(c);
			continue;
		}
		switch(*fmt++) {
			case 'd':
				d = va_arg(ap, int);
				print_num(d, 10);
				break;
			case 'x':
				d = va_arg(ap, int);
				print_num(d, 16);
				break;
			case 'c':
				d = va_arg(ap, int);
				put_char(d);
				break;
			case 's':
				s = va_arg(ap, char *);
				while(*s != '\0') {
					put_char(*s++);
				}
				break;
			case 'b':
				d = va_arg(ap, int);
				print_num(d, 2);
				break;
			case 'o':
				d = va_arg(ap, int);
				print_num(d, 8);
				break;
		}
	}

	va_end(ap);
	return 0;
}

void print_num(int d, int b) {
	//div_t res;
	int quot;
	int tmp;
	int rem;
	char c;
	int i;
	char buf[32];


	i = 0;

	if(d & 0x80000000) {
		put_char('-');
		d = ~d;
		d += 1;
	}

	quot = d;

	do {
		//res = div(res.quot, b);
		tmp = quot;
		quot = tmp / b;
		rem  = tmp % b;
		if(rem >= 10) {
			c = rem + 'a' - 10;
		} else {
			c = '0' + rem;
		}
		buf[i++] = c;
	} while(quot != 0);

	while(i > 0) {
		put_char(buf[--i]);
	}
}


void put_char(char c) {
	UARTInterface *uart = (UARTInterface *)0xFFFB0000;
	while((uart->US_IER & 0x2) == 0);
	uart->US_THR = c;
}

void *malloc(int num) {
	int *base = (int*)BASE;
	void *ptr = (void *)*base;
	*base += num;
	return ptr;
}

lista *nodo(char c) {
	lista *n = malloc(sizeof(lista));
	n->l = c;
	n->siguiente = NULL;
	return n;
}

void add(lista **principal, char c) {
	lista *tmp;
	tmp = *principal;
	if(*principal == NULL) {
		*principal = nodo(c);
	} else {
		while(tmp->siguiente != NULL) {
			tmp=tmp->siguiente;
		}
		tmp->siguiente = nodo(c);
	}
}

