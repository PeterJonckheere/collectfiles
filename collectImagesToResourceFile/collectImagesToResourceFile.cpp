// collectfiles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include  <windows.h>

#include <string>

#include <vector>

#include <iostream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <sstream>   
namespace fs = std::filesystem;


#include <queue>


using namespace std;

/*
const char *text =
"This text is pretty long, but will be "
"concatenated into just a single string. "
"The disadvantage is that you have to quote "
"each part, and newlines must be literal as "
"usual.";*/
const char *stdtext =
"<?xml version =   '1.0' ?>\n"
"<resources>\n";
string startPath = "testmap";

/*
class Main
{
	// Iterative function to traverse the given directory in Java using BFS
	public static void main(String[] args)
	{
		// Root directory
		String rootDir = "/var/www/html";

		// maintain a queue to store files and directories
		Queue<File> queue = new LinkedList<>();

		// add root directory to the queue
		queue.add(new File(rootDir));

		// loop until queue is empty - all files and directories present
		// inside the root directory are processed
		while (!queue.isEmpty())
		{
			// get next file/directory from the queue
			File current = queue.poll();

			// get list of all files and directories in 'current'
			File[] listOfFilesAndDirectory = current.listFiles();

			// listFiles() returns non-null array if 'current' denotes a dir
			if (listOfFilesAndDirectory != null)
			{
				// iterate over the names of the files and directories in
				// the current directory
				for (File file : listOfFilesAndDirectory)
				{
					// if file denotes a directory
					if (file.isDirectory()) {
						queue.add(file);
					}
					// if file denotes a file, print it
					else {
						System.out.println(file);
					}
				}
			}
		}
	}
}


*/

void BFSDirectoryTravers(const fs::path& pathToScan) {
	
	queue<fs::directory_entry> FileQueue;
	FileQueue.push(fs::directory_entry(pathToScan));
	int level = 0;
	bool areThereFiles = false;
	std::stringstream buffer; 
	while (!FileQueue.empty())
	{

		areThereFiles = false;
		buffer.str(std::string());
		fs::directory_entry current = FileQueue.front();
		FileQueue.pop();
		if (current.exists()) {
			buffer << "<set path =" << '"' << current.path().string() << '"' << "/>" << '\n';
			buffer << "<atlas>" << '\n';
			for (const auto& entry : fs::directory_iterator(current)) {
				const auto filenameStr = entry.path().filename().string();
				if (entry.is_directory()) {
					
					FileQueue.push(fs::directory_entry(entry));
				}
				else if (entry.is_regular_file()   && entry.path().extension().string() == ".png" ) {
					areThereFiles = true;
					buffer << " <image id = " << '"' << current.path().filename().string() << "_" << entry.path().stem().string() << '"';

					buffer << " file= " << '"' << filenameStr << '"' << "/>" << "\n";
				}



			}// for
			buffer << "</atlas>" << '\n';
			if (areThereFiles)  std::cout << buffer.str();


		}// if exists



	} // function

}
// <image id = "arms_p_arm_idle" file = "p_arm_idle.png" / >
void DisplayDirectoryTree(const fs::path& pathToScan, int level = 0) {
	for (const auto& entry : fs::directory_iterator(pathToScan)) {
		const auto filenameStr = entry.path().filename().string();
		if (entry.is_directory()) {
			std::cout << std::setw(level * 3) << "<set path =" << '"' << startPath << "/" << filenameStr << '"' << "/>" << '\n';
			std::cout << "<atlas>" << '\n';
			//std::cout << std::setw(level * 3) << "" << filenameStr << '\n';
			DisplayDirectoryTree(entry, level + 1);
			std::cout << "</atlas>" << '\n';

		}
		else if (entry.is_regular_file() && level > -1 && entry.path().extension().string() == ".png") {
			std::cout << std::setw(level * 3) << " <image id = " << '"' << pathToScan.string() << "_" << entry.path().stem().string() << '"';

			std::cout << " file= " << '"' << filenameStr << '"' << "/>" << "\n";




		}
		else if (level > -1);

		//std::cout << std::setw(level * 3) << "" << " [?]" << filenameStr << '\n';
	}
}

/*
void BFSDirectoryTravers(const fs::path& pathToScan) {
	
	queue<fs::directory_entry> FileQueue;
	FileQueue.push(fs::directory_entry(pathToScan));
	int level = 0;
	while (!FileQueue.empty())
	{


		fs::directory_entry current = FileQueue.front();
		FileQueue.pop();
		if (current.exists()) {
			std::cout << "<set path =" << '"' << current.path().string() << '"' << "/>" << '\n';
			std::cout << "<atlas>" << '\n';
			for (const auto& entry : fs::directory_iterator(current)) {
				const auto filenameStr = entry.path().filename().string();
				if (entry.is_directory()) {
					
					FileQueue.push(fs::directory_entry(entry));
				}
				else if (entry.is_regular_file()   && entry.path().extension().string() == ".png" ) {
					std::cout << " <image id = " << '"' << current.path().filename().string() << "_" << entry.path().stem().string() << '"';

					std::cout << " file= " << '"' << filenameStr << '"' << "/>" << "\n";
				}



			}// for
			std::cout << "</atlas>" << '\n';


		}// if exists



	} // function

}
*/




vector<string> get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);

			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}


int main(int argc, char** argv)
{
	vector<string> res;
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	//path_buffer = s.c_str();
	//string startPath = "testmap";
	auto pad = fs::current_path();
	string sss = pad.filename().string();
	startPath = sss;
	//auto fff= std::filesystem::path(".\\");
	std::cout << stdtext << "\n";
	//std::cout << "<set path =" << '"' << startPath << '"' << "/ >" << '\n';
	//DisplayDirectoryTree("");
	std::string folder;
	if (argc > 1) folder = argv[1]; else folder = "";
	BFSDirectoryTravers(folder);
	std::cout << "</resources>";


	/*
		res = get_all_files_names_within_folder(argv[1]);

		ofstream myfile;

		myfile.open(string(argv[1]) + ".txt");
		for (vector<string>::iterator it = res.begin(); it != res.end(); ++it) {
			_splitpath((*it).c_str(), drive, dir, fname, ext);


			//myfile << *it << "\n";


			myfile << "<image id= " << '"' << string(argv[1]) << "_" << fname << '"' << " file =" << '"' << fname << ext << '"' << "/>" << "\n";
		}
	*/

	return 0;


}

//<image file = "foot.png" / >









// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
