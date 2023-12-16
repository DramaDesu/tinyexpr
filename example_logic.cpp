#include "tinyexpr.h"
#include <stdio.h>
#include <vector>

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

struct expr_guard_t
{
    expr_guard_t(const char* in_exp)
    {
        expr = te_compile(in_exp, true, nullptr, 0, nullptr);
    }

	expr_guard_t(const char* in_exp, const std::vector<te_variable>& in_vars)
	{
        expr = te_compile(in_exp, true, in_vars.data(), in_vars.size(), nullptr);
	}

    ~expr_guard_t()
	{
		te_free(expr);
	}

    bool is_valid() const
    {
	    return expr != nullptr;
    }

    void print() const
    {
		te_print(expr);
    }

    bool eval() const
	{
        if (expr == nullptr)
        {
	        return false;
        }
        return te_logic_eval(expr);
	}

    te_expr* expr = nullptr;
};

int main(int argc, char *argv[])
{
    const std::vector<te_variable> vars = { {"d0.b", &D0}, {"d1.w", &D1}, {"a0", &A0}, {"addr_val", addr_val, TE_FUNCTION1} };

    const char *c = "(d0.b == 0x0 && d1.w != 0xFF) || addr_val(0) > 0x100";

    const expr_guard_t expr_guard(c, vars);
    if (expr_guard.is_valid())
    {
        expr_guard.print();
        {
            printf("Result:\n\t%i\n", expr_guard.eval());
        }
        {
            D0 = 0x100;
            A0 = 0x1;
            printf("Result:\n\t%i\n", expr_guard.eval());
        }
        {
            A0 = 0x0;
            printf("Result:\n\t%i\n", expr_guard.eval());
        }
    }

    const char* c_ = "(d0.b == 0x0 && d1.w != 0xFF) || addr_val(0) > 0x100";

    return 0;
}
