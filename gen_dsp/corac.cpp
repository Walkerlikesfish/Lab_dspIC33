#include <math.h>
#include <iostream>
#include <fstream>
#define M_PI 3.1415926535897932384626
#define K1 0.6072529350088812561694

int main(int argc, char **argv)
{
    int i;
    int bits = 32; // number of bits 
    int mul = (1<<(bits-2));
    
    FILE *FP;
    FP = fopen("cosh.h","w");
    
    int n = bits; // number of elements. 
    int c;

    fprintf("//Cordic in %d bit signed fixed point math\n", bits);
    fprintf("//Function is valid for arguments in range -pi/2 -- pi/2\n");
    fprintf("//for values pi/2--pi: value = half_pi-(theta-half_pi) and similarly for values -pi---pi/2\n");
    fprintf("//\n");
    fprintf("// 1.0 = %d\n", mul);
    fprintf("// 1/k = 0.6072529350088812561694\n");
    fprintf("// pi = 3.1415926535897932384626\n");

    fprintf("//Constants\n");
    fprintf("#define cordic_1K 0x%08X\n", (int)(mul*K1));
    fprintf("#define half_pi 0x%08X\n", (int)(mul*(M_PI/2)));
    fprintf("#define MUL %f\n", (double)mul);
    fprintf("#define CORDIC_NTAB %d\n", n);
    
    fprintf("int cordic_ctab [] = {");
    for(i=0;i<n;i++)
    {
        c = (atan(pow(2, -i)) * mul);
        fprintf("0x%08X, ", c);
    }
    fprintf("};\n\n");

    //Print the cordic function
    fprintf("void cordic(int theta, int *s, int *c, int n)\n{\n  int k, d, tx, ty, tz;\n");
    fprintf("  int x=cordic_1K,y=0,z=theta;\n  n = (n>CORDIC_NTAB) ? CORDIC_NTAB : n;\n");
    fprintf("  for (k=0; k<n; ++k)\n  {\n    d = z>>%d;\n", (bits-1));
    fprintf("    //get sign. for other architectures, you might want to use the more portable version\n");
    fprintf("    //d = z>=0 ? 0 : -1;\n    tx = x - (((y>>k) ^ d) - d);\n    ty = y + (((x>>k) ^ d) - d);\n");
    fprintf("    tz = z - ((cordic_ctab[k] ^ d) - d);\n    x = tx; y = ty; z = tz;\n  }  \n *c = x; *s = y;\n}\n");
    
}