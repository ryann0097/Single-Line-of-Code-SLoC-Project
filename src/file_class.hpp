#ifndef FILE_HPP_
#define FILE_HPP_

#include <iostream>

/** A struct declaration.
 * The struct "FileInfo" carries relevant files' relevants informations,
 * as their name, type, types of lines and the sum of them.
*/

typedef struct FileInfo{
	
	/** Two strings values.
	 * "fileName" is the name of the file that we're opening.
	 * "fileType" is the type of the file that we're extracting.
	*/

	std::string fileName;
	std::string fileType;

	/** Multiple short values.
	 * These values are quantifiers for comment, blank and code lines,
	 * carrying the sum of them all too.
	*/

	short commentLines;
	short blankLines;
	short codeLines;
	short allLines;

} FileInfo;

#endif