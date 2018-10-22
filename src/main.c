
#include "error/error.h"

int main(int argc, char** argv) {

	assert_w_msg(0 == 1, Die Mathematik funktioniert noch);
	char* t = "hallo";

	return 0;
}
