#include <array>
#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <vector>

/// Verifica se o nome passado como argumento de fato corresponde a um diretório.
bool directory_exist(const std::string &target) {
  bool exists{ false };
  DIR *p_dir;
  p_dir = opendir(target.c_str());
  exists = (p_dir != nullptr);
  closedir(p_dir);
  return exists;
}

/// Verifica se o nome pasado como argumento de fato corresponde a um arquivo existente.
bool file_exists(const std::string &filename) {
  bool exists{ false };
  std::fstream fs{ filename };
  exists = fs.is_open();
  fs.close();
  return exists;
}

/*!
 * Verifica se o nome do arquivo fornecido com argumento
 * corresponde a alguns dos tipos de arquivos aceitos
 * pelo sloc.
 */
bool is_source_code(const std::string &filename) {
  std::array extensions{ ".cpp", ".c", ".h", ".hpp" };

  for (const auto &e : extensions) {
    auto result = filename.find(e);
    if (result != std::string::npos) {
      // Se entrar aqui é porque achou a substring correspondente
      // a uma das extensões suportadas.
      // TODO
      // Precisa ter certeza que a extensao é mesmo .cpp APENAS!
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  dirent *p_dirent;
  DIR *p_dir;

  // List of files to process.
  std::vector<std::string> src_list;

  // Ensure correct argument count.
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <dirname>\n";
    return EXIT_FAILURE;
  }

  // Ensure we can open directory.
  p_dir = opendir(argv[1]);
  if (p_dir == nullptr) {
    std::cout << "Cannot open directory '" << argv[1] << "'\n";
    return 1;
  }

  // Process each entry.
  while ((p_dirent = readdir(p_dir)) != nullptr) {
    std::string target{ p_dirent->d_name };
    if (target == ".") {
      continue;
    }
    if (target == "..") {
      continue;
    }
    if (is_source_code(target)) {
      std::cout << "Adding source file: " << target << "\n";
      src_list.push_back(target);  // Saving file name for later processing.
    } else {                       // It's a directory.
      std::cout << "Found a non source file or directory: " << target << "\n";
      // // TODO: Get list of files inside this directory
      // src_list = find_files(src_list, target);
    }
  }

  // Close directory and exit.
  closedir(p_dir);
  return EXIT_SUCCESS;
}
