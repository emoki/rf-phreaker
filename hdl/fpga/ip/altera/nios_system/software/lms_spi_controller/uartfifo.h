
#ifndef uartfifo_H
#define uartfifo_H

#include "system.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct uartfifo {
	uint32_t first;
	uint32_t last;
	uint32_t capacity;
	uint8_t* base;
} uartfifo;

uartfifo uartfifo_new(uint32_t capacity){
	uint8_t* base = (uint8_t*)malloc( capacity );
	uartfifo us = {0,0,0,0};
	if(base){
		us.capacity = capacity;
		us.first = 0;
		us.last = 0;
		us.base = base;
	}
	else{
		//could not allocate...
	}
	return us;
};
void 	uartfifo_enqueue(uartfifo* us, uint8_t b){
	if(us->base == 0){
		return;
	}

	if(us->last >= us->capacity ){
		us->first = 0;
		us->last = 0;
	}
	us->base[us->last] = b;

	us->last++;
};
uint8_t uartfifo_empty(uartfifo* us){
	if(us->first == us->last){
		us->first = 0;
		us->last = 0;
		return 1;
	}
	return 0;
}
uint32_t uartfifo_size(uartfifo* uf){
	int32_t amt = (int32_t)(uf->last) - (int32_t)(uf->first);
	if(amt < 0){
		uf->first = 0;
		uf->last = 0;
		return 0;
	}
	return amt;
}
uint8_t uartfifo_dequeue(uartfifo* us){
	if(us->base == 0){
		return 0;
	}

	//
	uint8_t b = us->base[us->first++];
	if(uartfifo_empty(us)){
		us->first = 0;
		us->last = 0;
	}
	return b;
};
void uartfifo_delete(uartfifo* us){
	if(us->base != 0){
		free(us->base);
		us->first = 0;
		us->last = 0;
		us->capacity = 0;
	}
};





void uartfifo_test(){
	uartfifo f = uartfifo_new(10);
	int i;
	for(i = 0; i < f.capacity; i++){
		uartfifo_enqueue( &f, (uint8_t)i );
	}

	//demonstrates over capacity reset
	//uartfifo_enqueue( &f, 15 );


	//will display "0,1,2,3,4,5,6,7,8,9,"
	while(!uartfifo_empty(&f)){
		printf("%d,",uartfifo_dequeue(&f));
	}

	uartfifo_delete(&f);
}



#endif
