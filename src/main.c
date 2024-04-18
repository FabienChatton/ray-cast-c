#include "ncusrsIhm.h"
#include "gameCtrl.h"
#include <setjmp.h>
#include <stdlib.h>

extern jmp_buf bufJmp;

int main()
{
	if (setjmp(bufJmp) == 0)
	{
		testGame();
	}
	else
	{
		fprintf(stderr, "fail to launche game. Exit now");
		exit(1);
	}
	disposeIhm();
	return 0;
}