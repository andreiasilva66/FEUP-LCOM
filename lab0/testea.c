#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BIT(n) (1<<(n))

char *byte2bin(uint8_t n, char *binstr) 
{
    // one element per bit (0/1)
    uint8_t binary[8];

    int i = 0;
    for(i = 0; i < 8; i++) {
        binary[i] = n % 2;
        n = n / 2;
    }

    // printing binary array in reverse order
    for (int j = 7, k= 0; j >= 0; j--, k++)
        sprintf(binstr + k, "%d", binary[j]);
        
	return binstr;
}

void print_usage(char *name) {
	printf("Usage: %s <action> <byte> <bit no>\n", name);
	printf("\tWhere: <action> one of 'h'|'l'|'r'|'s'|'t'\n"
		"\t\t <byte> 8-bit integer in hexadecimal\n"
		"\t\t <bit no> of bit to operate on\n");
}



int main(int argc, char *argv[])
{
	char a =  argv[1];	// action: 'h', 'l', 'r', 's', 't'
	unsigned long n =  strtoul(argv[2],NULL,0); // value to convert must be smaller than 256
	int bit = atoi(argv[3]); // bit to operate on: must be between 0 an 7
    char binary[9]; // array for binary representation of n,
					//  remember that in C strings are terminated with a 0
 
	// Validate command line arguments

    if(argc != 4){
        print_usage("bitwise");
        EXIT_FAILURE;
    }

    a = *(argv[1]);

    if(!(a == 'h' || a == 't' || a == 's' || a == 'r' || a == 'l')){
        print_usage("bitwise");
        EXIT_FAILURE;
    }

    if( n > 255){
        print_usage("bitwise");
        EXIT_FAILURE;
    }

    if(  0 < bit && bit < 8)



    
	// Print to stdout the binary representation of n

    byte2bin(n,binary);

   

	
	// Do what the user asked and print the result
	/*  if(a == 'h'){

        if( n & bit != 0 ) byte2bin(1,binary);

        
        
    }

    else if (a == 'l'){
        
        if( n & bit == 0 ) byte2bin(1,binary);
        

    }

    else if(a == 's'){

       n |= BIT(bit);

    }

    else if(a == 'r'){

        n = (u_int8_t) ~(BIT(bit) | ~n); 

    }

    else if(a == 't'){

        u_int8_t tester = (u_int8_t) ~(BIT(bit) | ~n);

        if(tester ^ n != 0) n = tester;

        else n |= BIT(bit);}*/

    return 0;
}