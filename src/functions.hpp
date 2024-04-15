#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP
#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <iomanip>
#include <sstream>

/**
 * @brief Prints a summary line for a FileInfo object.
 * 
 * This function prints a summary line for a FileInfo object, displaying
 * the file name, file type, number of comment, blank, and code lines,
 * as well as the percentage of each line type relative to the total lines.
 * 
 * @param fileInfo A FileInfo object containing information about the file.
 */

void printLine(const FileInfo& fileInfo) {
    std::stringstream archiveResumePrinter;
    
    double commentPercent = (static_cast<double>(fileInfo.commentLines)/fileInfo.allLines)*100;
    double blankPercent = (static_cast<double>(fileInfo.blankLines)/fileInfo.allLines)*100;
    double codePercent = (static_cast<double>(fileInfo.codeLines)/fileInfo.allLines)*100;

    std::stringstream comment; 
    comment << fileInfo.commentLines << "(" << std::fixed << std::setprecision(1) << commentPercent << "%)";
    std::stringstream blank; 
    blank << fileInfo.blankLines << "(" << std::fixed << std::setprecision(1) << blankPercent << "%)";
    std::stringstream code;
    code << fileInfo.codeLines << "(" << std::fixed << std::setprecision(1) << codePercent << "%)";

    archiveResumePrinter << std::left << std::setw(20) << fileInfo.fileName << std::setw(15) << fileInfo.fileType << std::setw(15) << comment.str() << std::setw(15) << blank.str() << std::setw(15) << code.str() << std::setw(15) << fileInfo.allLines;
    std::cout << archiveResumePrinter.str() << std::endl;
}


/**
 * @brief trim
 * 
 * @param string = Line to be "trimmed".
 * 
 * @return A "trimmed" string.
*/

std::string trim(const std::string& string) {
    std::string trimmedString = string;
    
    size_t start = trimmedString.find_first_not_of(" \t");
    if(start != std::string::npos) {trimmedString = trimmedString.substr(start);} 
    else {trimmedString.clear(); return trimmedString;}

    size_t end = trimmedString.find_last_not_of(" \t");
    if(end != std::string::npos){trimmedString = trimmedString.substr(0, end + 1);}

    return trimmedString;
}

/**
 * @brief stringLever.
 *
 * @param string = Line to be received
 * @param i = Index where we are with the string
 * @param currentState = Boolean state indicating the current verification.
 * 
 * @return The return value should be the opposite state of the current boolean.
*/


bool isStringLever(std::string string, short i, bool currentState){
	if(i - 1 >= 0 && string[i-1] == '\\'){
		/*Se isso for uma barra incluida numa string para colocar aspas, ignore.*/
		return currentState;
	}
	else{
		return !currentState;
	}
}

/**
 * @brief Determines the type of file based on its extension.
 * 
 * This function examines the extension of the given archive name to determine its type.
 * Supported file types are:
 *   - C++ source files (.cpp)
 *   - C++ header files (.hpp)
 *   - C source files (.c)
 *   - C header files (.h)
 * 
 * @param archiveName The name of the archive file.
 * @return An integer representing the file type:
 *   - 1 for C source files or C header files.
 *   - 2 for C++ source files or C++ header files.
 */

short fileTypeExtractor(std::string &archiveName){
    if(archiveName.size() >= 4){
        if(archiveName.substr(archiveName.size() - 4) == ".cpp"){return 2;}
        else if(archiveName.substr(archiveName.size() - 4) == ".hpp"){return 2;}
    }
    else if(archiveName.size() >= 2){
        if(archiveName.substr(archiveName.size() - 2) == ".c"){return 1;}
        else if(archiveName.substr(archiveName.size() - 2) == ".h"){return 1;}
    }
}

/**
 * @brief Opens a directory and retrieves a list of C/C++ archives.
 * 
 * This function opens the specified directory and retrieves a list of C/C++ archive files 
 * (source code or header files). It filters out other types of files using the `fileTypeExtractor`
 * function.
 * 
 * @param directoryName The name of the directory to open.
 * @return A vector containing the names of C/C++ archive files found in the directory.
 */

std::vector<std::string> directoryOpening (const std::string& directoryName) {
    std::vector<std::string> cppArchives;
    DIR* dirp = opendir(directoryName.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        std::string archiveName = dp->d_name;
        if (fileTypeExtractor(archiveName) == 1 || fileTypeExtractor(archiveName) == 2) {
            cppArchives.push_back(archiveName);
        }
    }
    closedir(dirp);
    return cppArchives;
}

// keeping agility and security, ha!
/*first of all, dear reader, i'm so sorry for messing up wit ur vision. i tried to generalize it, but, at the end
 * i couldn't do it cleaner. so, so sorry. my perdon.
*/

/**
 * 
 * @brief All sorting functions sorts, in a ascending order, FileInfo structs based on a specific attribute.
 *        We have "sortingFileName" and "sortingFileType" comparing the two first characters
 *        of the struct's strings. 
 *        And we have "sortingCommentLines", "sortingAllLines", "sortingCodeLines"
 *        and "sortingBlankLines" too. Comparing the "short" attributes of the struct.
 * 
 * @param a The first FileInfo object to compare.
 * @param b The second FileInfo object to compare.
 * @return True if a comes before b, false otherwise.
 * 
 */

bool sortingFileName(const FileInfo &a, const FileInfo &b){return a.fileName.substr(0,2) < b.fileName.substr(0,2);}
bool sortingFileType(const FileInfo &a, const FileInfo &b){return a.fileType.substr(0,2) < b.fileType.substr(0,2);}
bool sortingCommentLines(const FileInfo &a, const FileInfo &b){return a.commentLines < b.commentLines;}
bool sortingAllLines(const FileInfo &a, const FileInfo &b){return a.allLines < b.allLines;}
bool sortingCodeLines(const FileInfo &a, const FileInfo &b){return a.codeLines < b.codeLines;}
bool sortingBlankLines(const FileInfo &a, const FileInfo &b){return a.blankLines < b.blankLines;}

/**
 * 
 * @brief All reverse sorting functions sorts, in a descending order, FileInfo structs based on a specific attribute.
 *        We have "sortingFileName" and "sortingFileType" comparing the two first characters
 *        of the struct's strings. 
 *        And we have "sortingCommentLines", "sortingAllLines", "sortingCodeLines"
 *        and "sortingBlankLines" too. Comparing the "short" attributes of the struct.
 * 
 * @param a The first FileInfo object to compare.
 * @param b The second FileInfo object to compare.
 * @return True if a comes before b, false otherwise.
 * 
 */

bool reverseSortingFileName(const FileInfo &a, const FileInfo &b){return a.fileName.substr(0, 2) > b.fileName.substr(0, 2);}
bool reverseSortingFileType(const FileInfo &a, const FileInfo &b){return a.fileType.substr(0, 2) > b.fileType.substr(0, 2);}
bool reverseSortingCommentLines(const FileInfo &a, const FileInfo &b){return a.commentLines > b.commentLines;}
bool reverseSortingAllLines(const FileInfo &a, const FileInfo &b){return a.allLines > b.allLines;}
bool reverseSortingCodeLines(const FileInfo &a, const FileInfo &b){return a.codeLines > b.codeLines;}
bool reverseSortingBlankLines(const FileInfo &a, const FileInfo &b){return a.blankLines > b.blankLines;}


#endif