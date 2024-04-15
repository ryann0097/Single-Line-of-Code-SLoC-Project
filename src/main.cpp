#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include "file_class.hpp"
#include "slocProcessor.hpp"
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){

/*--------------------------------------------------------------------------------------------------------------*/
    
    std::ostringstream Header;

    std::string line = "\n-----------------------------------------------------------------------------------------\n";
    std::string slocArt = R"(
                             ___ _    ___   ___       _ 
                            / __| |  / _ \ / __| __ _/ |
                            \__ \ |_| (_) | (__  \ V / |
                            |___/____\___/ \___|(_)_/|_|
                                  
    )";

    Header << line << slocArt << "              Welcome to slocpp, version 1.0,(c) 2024 Selan, DIMAp" << "\n" <<line;

    std::string slocHeader = Header.str(); 

/*--------------------------------------------------------------------------------------------------------------*/
    std::cout << slocHeader;

    char sortOrder = 's', sortMode = 'f';   
    std::string caminhoRecebido; 

    std::string helpMessage = "\nUsage: sloc files/directory [options]\nOptions:\n-h/--help       Display this information.\n-s f/t/c/b/s/a  Sort table in ascending order by(f)ilename,(t) filetype,\n(c)omments,(b)lank lines,(s)loc, or(a)ll. Default is to show\nfiles in ordem of appearance.\n-S f/t/c/b/s/a  Same as above, but in descending order.\n";

    try{
        if(argc == 1){
            std::cerr << helpMessage << std::endl;
            return 1;
        }

        if(argc == 2){
            caminhoRecebido = argv[1];
            struct stat fileInfo;

            if(caminhoRecebido == "--help" || caminhoRecebido == "-h"){std::cout << helpMessage << std::endl;exit;}
            else if(stat(caminhoRecebido.c_str(), &fileInfo) != 0){throw std::runtime_error("\n[Error]:\n Unfortunately, I couldn't obtaining information about the file or directory.");}
            else if(S_ISDIR(fileInfo.st_mode)){std::cerr << "\n[Error]:\nSorting order field missing. Here goes a tip:\n" << helpMessage << std::endl;return 1;}
            else{
                std::string caminhoRecebido = argv[1];
                struct stat fileInfo;
                if(stat(caminhoRecebido.c_str(), &fileInfo) != 0){
                    throw std::runtime_error("\n[Error]:\n Unfortunately, I couldn't obtaining information about the file or directory.");
                }
                else{
                    std::cout << "\nFiles processed: 1\n" << std::endl;
                    FileInfo fileReceiver = slocProcessor(caminhoRecebido);
                    std::cout << "-----------------------------------------------------------------------------------------\n" << "Filename            Language        Comments        Blank           Code            All\n" << "-----------------------------------------------------------------------------------------\n";
                    printLine(fileReceiver);
                }
            }
        }

        else if(argc == 3){
            caminhoRecebido = argv[1];
            struct stat fileInfo;
            
            if(stat(caminhoRecebido.c_str(),&fileInfo) != 0){throw std::runtime_error("\n[Error]:\n Unfortunately, I couldn't obtaining information about the file or directory.");}
            if(!S_ISDIR(fileInfo.st_mode)){std::cerr << "\n[Error]:\nThe path that you insert isn't a directory." << helpMessage << std::endl; return 1;}

            else{
                if(std::strcmp(argv[2], "-S") == 0 || std::strcmp(argv[2], "-s") == 0){std::cerr << "\n[Tip]:\nUh... I guess you're missing the sort field, lil bro/sis. Try it:\n" << helpMessage << std::endl;}
                else{std::cerr << "\n[Tip]:\nwhoa, whoa, lil bro/sis! That's invalid usage!\nTry it:" << helpMessage << std::endl;}
            }
        }

        else if(argc == 4){
            caminhoRecebido = argv[1];
            struct stat fileInfo;
            
            if(stat(caminhoRecebido.c_str(), &fileInfo) != 0){throw std::runtime_error("\n[Error]:\n Unfortunately, I couldn't obtaining information about the file or directory.");}
            
            if(!S_ISDIR(fileInfo.st_mode)){std::cerr << "\n[Tip]:\nwhoa, whoa, lil bro/sis! That's invalid usage!\nTry it:" << helpMessage << std::endl; exit;}

            else{
                if(std::strcmp(argv[2], "-s") == 0){

                    sortOrder = 's';
                    switch(argv[3][0]){
                    case 'f':
                        sortMode = 'f'; break;
                    case 't':
                        sortMode = 't'; break;
                    case 'c':
                        sortMode = 'c'; break;
                    case 'b':
                        sortMode = 'b'; break;
                    case 's': 
                        sortMode = 's'; break;
                    case 'a':
                        sortMode = 'a'; break;
                    default:
                        std::cerr << "\n[Tip]:\nwhoa, whoa, lil bro/sis! That's invalid sort mode!\n" << helpMessage << std::endl;
                        return 1;
                    }
                }
                else if(std::strcmp(argv[2], "-S") == 0){

                    sortOrder = 'S';
                    switch(argv[3][0]){
                    case 'f':
                        sortMode = 'f'; break;
                    case 't':
                        sortMode = 't'; break;
                    case 'c':
                        sortMode = 'c'; break;
                    case 'b':
                        sortMode = 'b'; break;
                    case 's': 
                        sortMode = 's'; break;
                    case 'a':
                        sortMode = 'a'; break;
                    default:
                        std::cerr << "\n[Tip]:\n whoa, whoa, lil bro/sis! That's invalid sort mode!\n" << helpMessage << std::endl;
                        return 1;
                    }
                }
            }

            std::vector<std::string> Archives = directoryOpening(caminhoRecebido);
            std::vector<FileInfo>readArchives;
            if(Archives.empty()){std::cout << "\n[Error]:\nOh no! We couldn't find \".c /.h\" or \".cpp/.hpp\" archives. So sorry." << std::endl;} 
            else{
                for(const auto& arquivo : Archives){
                    FileInfo arquivoAtual = slocProcessor(arquivo);
                    readArchives.push_back(arquivoAtual);
                }
            }

            if(sortOrder == 's'){
                if(sortMode == 'f'){std::sort(readArchives.begin(), readArchives.end(), sortingFileName);} 
                else if(sortMode == 't'){std::sort(readArchives.begin(), readArchives.end(), sortingFileType);} 
                else if(sortMode == 'c'){std::sort(readArchives.begin(), readArchives.end(), sortingCommentLines);} 
                else if(sortMode == 'b'){std::sort(readArchives.begin(), readArchives.end(), sortingBlankLines);} 
                else if(sortMode == 's'){std::sort(readArchives.begin(), readArchives.end(), sortingCodeLines);} 
                else if(sortMode == 'a'){std::sort(readArchives.begin(), readArchives.end(), sortingAllLines);}

            }
            else if(sortOrder == 'S'){
                if(sortMode == 'f'){std::sort(readArchives.begin(), readArchives.end(), reverseSortingFileName);} 
                else if(sortMode == 't'){std::sort(readArchives.begin(), readArchives.end(), reverseSortingFileType);} 
                else if(sortMode == 'c'){std::sort(readArchives.begin(), readArchives.end(), reverseSortingCommentLines);} 
                else if(sortMode == 'b'){std::sort(readArchives.begin(), readArchives.end(), reverseSortingBlankLines);} 
                else if(sortMode == 's'){std::sort(readArchives.begin(), readArchives.end(), reverseSortingCodeLines);} 
                else if(sortMode == 'a'){std::sort(readArchives.begin(), readArchives.end(), reverseSortingAllLines);}
            }

            short totalComment = 0, totalBlank = 0, totalCode = 0;
            std::cout << "Files processed: " << readArchives.size() << std::endl;
            std::cout << "-----------------------------------------------------------------------------------------\n" << "Filename            Language        Comments        Blank           Code            All\n" << "-----------------------------------------------------------------------------------------\n";
            for(const auto& arquivo : readArchives){
                totalComment += arquivo.commentLines;
                totalBlank += arquivo.blankLines;
                totalCode += arquivo.codeLines;
                printLine(arquivo);
            }
            std::cout << "-----------------------------------------------------------------------------------------\n" << "SUM                                  " << totalComment << "             " << totalBlank << "              " << totalCode << "             " << totalBlank+totalCode+totalComment << std::endl;
            std::cout << "-----------------------------------------------------------------------------------------\n";

        }

        return 0;
    } catch(const std::exception& e){
        std::cerr << "WHOA! An error occurred: " << e.what() << std::endl;
        return 1;
    }
}
