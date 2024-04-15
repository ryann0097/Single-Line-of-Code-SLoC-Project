#ifndef PROCESSOR_HPP_
#define PROCESSOR_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include "file_class.hpp"
#include "functions.hpp"
#include <cctype>

std::string trim(const std::string& string);
bool isStringLever(std::string string, short i, bool currentState);
short fileTypeExtractor(std::string &archiveName);

/*
 * @brief slocProcessor.
 * 
 * @param_ archiveName = A string that contains the archive's name that will be opened.
 * 
 * @return The return will be the a struct that contains the archive's informations.
*/

FileInfo slocProcessor (std::string archiveName){

	FileInfo fileToBeReturned;

	fileToBeReturned.fileName = archiveName;
	fileToBeReturned.fileType =  (fileTypeExtractor(archiveName) == 1) ? "C" : "C++";

	std::ifstream archiveToBeOpened(archiveName);
	if(!archiveToBeOpened.is_open()){std::cerr << "Error: the inserted archive cannot be read.\n" << std::endl; /*mudar*/exit;}

	std::string lineOfCode;
	bool isBlock = false, isLine = false, isString = false;
	short blankLines = 0, commentLines = 0, codeLines = 0;

	while(std::getline(archiveToBeOpened, lineOfCode)){

		short inlineCommentLines = 0, inlineCodeLines = 0;
		lineOfCode = trim(lineOfCode);
		
		/** A two conditional "if" command block.
		 * Doesn't have a character by character processment.
		 * In-line first characters processment.
		*/

		if(lineOfCode.empty()){blankLines++; continue;}
		if(!isString && (lineOfCode[0] == '/' && lineOfCode[1] == '/')){commentLines++; continue;}
		
		else{

			/** A for loop.
			* It is useful for in-line text/code character-by-character processment.
			*/

			for(int i = 0; i < lineOfCode.size(); i++){

				/** An "if-else if", "for" embeded, command block.
				* It tests the cases to comments, strings, lines of codes and the closening
				* of comment blocks.
				*/

				if(lineOfCode[i] == '/' && !isString){
					if(lineOfCode[i+1] == '*' && !isLine){
						isBlock = true;
						if(inlineCommentLines == 0){inlineCommentLines++;}
					}
					else if(lineOfCode[i+1] == '/' && !isBlock){
						isLine = true;
						if(inlineCommentLines == 0){inlineCommentLines++;}
					}
				}

				else if(lineOfCode[i] == '"' && !isLine && !isBlock){
					isString = isStringLever(lineOfCode, i, isString);
					if(inlineCodeLines == 0){inlineCodeLines++;}
				}

				else if(!isBlock && !isLine){
					if(inlineCodeLines == 0){
						inlineCodeLines++;
					}
				}

				else if(lineOfCode[i] == '*' && !isString){
					if(lineOfCode[i+1] == '/' && isLine == false){
						isBlock = false;
						if(inlineCommentLines == 0){inlineCommentLines++;}
					}
				}
			}
			isLine = false;
		}

		/* Final conditional.
		 * It verifies if the "isBlock" variable's value it's true to continue the counter
		 * of the comment-block lines counting. 
		*/
		
		if((isBlock && !isLine) && inlineCommentLines == 0){inlineCommentLines++;}
		commentLines += inlineCommentLines;
		codeLines += inlineCodeLines;
	}

	fileToBeReturned.commentLines = commentLines;
	fileToBeReturned.blankLines = blankLines;
	fileToBeReturned.codeLines = codeLines;
	fileToBeReturned.allLines = commentLines + blankLines + codeLines;
	
	archiveToBeOpened.close();

	return fileToBeReturned;
}

#endif