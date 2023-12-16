#include "tinyexpr.h"
#include <stdio.h>

unsigned int D0 = 0;
unsigned int D1 = 0;
unsigned int D2 = 0;
unsigned int D3 = 0;
unsigned int D4 = 0;
unsigned int D5 = 0;
unsigned int D6 = 0;
unsigned int D7 = 0;

unsigned int A0 = 0;
unsigned int A1 = 0;
unsigned int A2 = 0;
unsigned int A3 = 0;
unsigned int A4 = 0;
unsigned int A5 = 0;
unsigned int A6 = 0;
unsigned int A7 = 0;

unsigned int addr_val(int in_addr)
{
	if (in_addr == 0x0)
	{
		return 0x100 + A0;
	}

    return 0x0;
}

int main(int argc, char *argv[])
{
    te_variable vars[] = { {"d0.b", &D0}, {"d1.w", &D1}, {"a0", &A0}, {"addr_val", addr_val, TE_FUNCTION1} };

    const char *c = "(d0.b == 0x0 && d1.w != 0xFF) || addr_val(0) > 0x100";
    // const char *c = "addr_val(0) > 0x100";
    // const char *c = "d0.b == 0x100";
    te_expr* expr = te_compile(c, true, vars, 4, NULL);
    if (expr != NULL)
    {
        te_print(expr);
        {
            const bool r = te_logic_eval(expr);
            printf("Result:\n\t%i\n", r);
        }
        {
            D0 = 0x100;
            A0 = 0x1;
            const bool r2 = te_logic_eval(expr);
            printf("Result:\n\t%i\n", r2);
        }
        {
            A0 = 0x0;
            const bool r2 = te_logic_eval(expr);
            printf("Result:\n\t%i\n", r2);
        }

        te_free(expr);
    }
    return 0;
}
