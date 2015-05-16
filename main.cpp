/*
  apt-add-repo by Andy "PyroAVR" Meyer
  A simple tool which allows installation of Ubuntu "PPA" repositories on Debian-derivative systems.
  Probably also works with any system that uses the Advanced Package Tool (APT).

  GPLv2 license or higher, this is open-source software, free forever, yada-yada-yada.  Don't steal it, don't make money from it, and if you decide to use it/modify it, please credit me. Andy "PyroAVR" Meyer.
  Enjoy!
*/
#define VERSION "1.0"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;
string repository;
string release = "trusty";
string arg1,arg2,arg3;
char response;
int xabort()	{				//Cannot replace abort() from cstdlib
	cout << "Exiting with no changes made to sources." << endl;
	exit(1);
}
int parse_opts(char *args)	{ 		//Take argument #1 and strip "ppa:" from it.
	string opts = args;	 		//Convert to a string first
	int pos = opts.find("ppa:");		//Locate the first instance of "ppa:"
	if (pos == string::npos)	{
		cout << "Could not find any instances of \"ppa:\"  Please try again." << endl;
		xabort();
	}
	repository = opts.substr(pos + 4);	//Get everything after "ppa:" ("ppa:" is 4 characters long, therefore we add four to eliminate it)
	return 0;
}
int main(int argc, char *argv[])	{
	//Not sure why this is necessary... Convert all chars to strings for comparisons later on, assuming that they actually have a value, otherwise don't assign anything, to prevent null-comparison errors.
	if (argv[1] != NULL) arg1 = argv[1];
	if (argv[2] != NULL) arg2 = argv[2];
	if (argv[3] != NULL) arg3 = argv[3];
	//Take care of special input cases
	if(argc == 1)	{	//Don't do anything if there isn't anything to do!
		cout << "Looks like you didn't enter anything.  Please enter a PPA address to be added to your sources." << endl;
		cout << "PPA looks like this: ppa:repo/software" << endl;
		cout << "To get help, type \'-h\' or \"--help\" at the commandline" << endl;
		xabort();
	}
	if(strcmp(arg1.c_str(),"--help") == 0 || strcmp(arg1.c_str(), "-h") == 0 || strcmp(arg1.c_str(), "help") == 0)	{ //Not sure why strcmp(char, char) is necessary either...
		cout << "add-apt-repository by Andy \"PyroAVR\" Meyer" << endl;
		cout << "Version: " << VERSION << endl;
		cout << "Usage: " << "apt-add-repository ppa:repo/software" << " [OPTIONS]" << endl;
		cout << "Command-Line Options:" << endl << "\t" << "-r:\t change the release to use" << endl;
		xabort();
	}
	if(arg1 == "-r")	{
		string tmp = argv[2];
		if (tmp.find("ppa:") != string::npos)	{
			cout << "Release change requested, however, no release was specified.  Assuming default." << endl;
			cout << "Arg 2:" << argv[2] << endl;
			parse_opts(argv[2]);		//These stay because of the type which parse_opts(char *) accepts
		}
		else	{
			release = tmp;
			cout <<"Argument 3: " << argv[3] << endl;
			parse_opts(argv[3]);
		}
	}
	if(arg2 == "-r")	{
		if (argv[3] != NULL) release = argv[3];
		parse_opts(argv[1]);
	}
	else	{
		parse_opts(argv[1]);
	}
	//Get the repository name from above after all error-cases have been checked for.  Repo name is returned from parse_opts(char*).
	string entry = "deb http://ppa.launchpad.net/";		//Set the first part of a ppa address
	entry += repository;					//Concatenate the repository we want
	entry += "/ubuntu ";					//Apparently PPAs were never made to leave the Ubuntu domain... Not anymore!
	entry += release;					//Specify what version you want, since we aren't on Ubuntu
	entry += " main";					//Always assume main for the distribution type.
	cout << "Adding PPA repository: " << entry << " ." << endl;
	cout << "Is this correct?[Y/N]" ;
	cin >> response;
	if (response == 'N') xabort();				//Confirm with the user.
	fstream sources;
	sources.open("/etc/apt/sources.list", fstream::out| fstream::app);	//Open the sources file for writing. Append, DO NOT overwrite.
	if (sources.fail())
	{
		sources.close();
		cout << "Could not open /etc/apt/sources.list for writing.  Are you root?" << endl;
		abort();
	}
	sources << entry;
	sources.close();
	cout <<  "Source added!" << endl << "Enjoy!" << endl;
	return 0;
}
