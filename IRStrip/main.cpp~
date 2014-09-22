// -----------------------------------------------------------
// inspirit_strip_llvm_ir: removes lines from an llvm IR file
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
//#include <boost/filesystem/operations.hpp>
using namespace std;
// -----------------
int main(int argc, char** argv)
{
	// command line input starts at the index 1
	// index 0 is the executable name
	if(argc == 1)
	{
		puts("No input files");
		return EXIT_SUCCESS;
	}
	bool overwriting = false;
	if(argc == 3)
	{
		string keep_arg = argv[2];
		if(keep_arg == "-overwrite")
			overwriting = true;
	}
	string filename = argv[1];
	string outputfile = filename+"stripped";
	ifstream input(filename.c_str());
	ofstream output(outputfile.c_str());
	// ---------------------
	while(!input.eof())
	{
		string token;
		input >> token;
		if(token != "define")
		{
			getline(input, token);
		}
		else
		{
			input >> token; input >> token; // get to the actual piece containing the name
			// read in the functions 'name' only, and write it to a temporary file
			int name_start = token.find_first_of("@")+1;
			int name_end = token.find_first_of("(")-1;
			string name = token.substr(name_start, name_end);
			output << name << endl;
		}
	}
	input.close();
	output.close();
	if(overwriting)
	{
		// if not windows, do unix commands
		// to be implemented someday
		string cmd = "mv ./";
		cmd += outputfile + " ./" + filename;
		system(cmd.c_str());
		cmd = "rm "; cmd+=outputfile;
		system(cmd.c_str());
	}
}
