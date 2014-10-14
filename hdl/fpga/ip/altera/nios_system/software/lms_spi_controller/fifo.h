
#ifndef fifo_H
#define fifo_H

#include "system.h"
#include <stdint.h>
#include <stdlib.h>

extern void debug(const char* s);

// MUCH faster modulus if mod is power of 2
inline int32_t modpow2(int32_t i, int32_t mod){
	return i & (mod-1);
}

typedef struct fifo {
	uint32_t first;
	uint32_t last;
	uint32_t capacity;
	uint32_t count;
	uint8_t* base;
} fifo;

// MUST BE POWER OF 2 FOR FAST MODULO
fifo fifo_new(uint8_t* buffer, uint32_t capacity){
	uint8_t* base = buffer;
	fifo us = {0};
	if(base){
		us.capacity = capacity;
		us.first = 0;
		us.last = 0;
		us.count = 0;
		us.base = base;
	}
	else{
		//could not allocate...
		debug("[fifo] Could not allocate!");
	}
	return us;
};
uint32_t fifo_size(fifo* uf){
	return uf->count;
};
void 	fifo_enqueue(fifo* us, uint8_t b){
	if(us->base == 0){
		return;
	}


	if(us->count == us->capacity){
		// full, increase first
		us->count--;
		us->first++;
	}
	us->last = modpow2(us->last, us->capacity);
	us->first = modpow2(us->first, us->capacity);


	us->base[us->last] = b;
	us->count++;

	us->last++;
};
uint8_t fifo_empty(fifo* us){
	return us->count == 0;
}

uint8_t fifo_dequeue(fifo* us){
	if(us->base == 0){
		debug("[fifo] dequeue() of null buffer.");
		return 0;
	}

	if(fifo_empty(us)){
		debug("[fifo] dequeue() of empty buffer.");
		return 0;
	}

	us->first = modpow2(us->first, us->capacity);
	uint8_t b = us->base[us->first++];
	us->count--;

	return b;
};
void fifo_delete(fifo* us){
	if(us->base != 0){
		free(us->base);
	}
	us->first = 0;
	us->last = 0;
	us->count = 0;
	us->capacity = 0;
};




/*  -- rename to main() and run on ideone.com C99 strict
void fifo_test(){
	fifo f = fifo_new(malloc(10), 10);
	int i;
	for(i = 0; i < f.capacity; i++){
		fifo_enqueue( &f, (uint8_t)i );
	}

	//demonstrates over capacity reset
	fifo_enqueue( &f, 15 );
	fifo_enqueue( &f, 16 );
	fifo_enqueue( &f, 17 );
	fifo_enqueue( &f, 18 );


	//will display...
	// initial size: 10
	// 4,5,6,7,8,9,15,16,17,18
	printf("initial size: %d\n",fifo_size(&f));
	while( fifo_size(&f)){
		int s = fifo_size(&f);
		int ff = f.first;
		int l = f.last;
		printf("(%d,%d,%d) -> (%d,%d,%d)  %d\n",s,ff,l,fifo_size(&f), f.first, f.last, fifo_dequeue(&f) );
	}

	fifo_enqueue( &f, 20 );
	fifo_enqueue( &f, 21 );
	fifo_enqueue( &f, 22 );
	fifo_enqueue( &f, 23 );


	//will display...
	// "initial size: 4"
	// 20,21,22,23
	printf("initial size: %d\n",fifo_size(&f));
	while( fifo_size(&f)){
		int s = fifo_size(&f);
		int ff = f.first;
		int l = f.last;
		printf("(%d,%d,%d) -> (%d,%d,%d)  %d\n",s,ff,l,fifo_size(&f), f.first, f.last, fifo_dequeue(&f) );
	}

	// will output
	// initial size: 10
	// 80,81,82,83,84,85,86,87,88,89
	for(i = 50; i < 50+f.capacity*4; i++){
		fifo_enqueue( &f, i );
	}
	printf("initial size: %d\n",fifo_size(&f));
	while( fifo_size(&f)){
		int s = fifo_size(&f);
		int ff = f.first;
		int l = f.last;
		printf("(%d,%d,%d) -> (%d,%d,%d)  %d\n",s,ff,l,fifo_size(&f), f.first, f.last, fifo_dequeue(&f) );
	}


	fifo_delete(&f);
}
*/


#endif
