// -----------------------------------------------------------
// inspirit_strip_llvm_ir: removes lines from an llvm IR file
#include <string>
#include <fstream>
#include <boost/filesystem/operations.hpp>
using namespace std;
// -----------------
int main(int argc, char** argv)
{
	if(argc == 1)
	{
		puts("No input files");
		return EXIT_SUCCESS;
	}
	puts(argv[0]);
	ifstream input;
}
