#include "fs.h"

#include <filesystem>
#include <fstream>
#include <iostream>

/**
 * Constructs a FileReader object with the given directory name.
 *
 * @param dirname The name of the directory to be read. This has to be absolute
 *
 * @throws None
 */
FileReader::FileReader(const std::string &dirname) {
  if (!std::filesystem::is_directory(dirname)) {
    std::cerr << "Directory " << dirname << " does not exist" << std::endl;
    exit(EXIT_FAILURE);
  }

  this->dirname = dirname;
  load_dir();
}

/**
 * Iterates through the directory specified by 'dirname', adds regular files to
 * the 'files' vector.
 *
 * @param None
 *
 * @return None
 *
 * @throws None
 */
void FileReader::load_dir() {
  for (const auto &entry : std::filesystem::directory_iterator(dirname)) {
    if (std::filesystem::is_regular_file(entry.path())) {
      File file;
      file.name = entry.path().filename().string();
      file.path = entry.path().string();
      file.extension = entry.path().extension().string();
      files.push_back(file);
    }
  }
}

/**
 * Retrieves a file from the list of files. If the file is not found, it
 * searches for the file in the directory and adds it to the list. If the file
 * does not exist, it prints an error message and exits the program.
 *
 * @param filename The name of the file to retrieve.
 *
 * @return The file object corresponding to the filename.
 *
 * @throws None
 */
File FileReader::get(const std::string &filename) {
  // check if file is present in files
  for (const auto &file : files) {
    if (file.name == filename) {
      return file;
    }
  }
  // if not exists, search in dirname and add to files
  File file;
  file.name = filename;
  file.path = dirname + "/" + filename;
  file.extension = filename.substr(filename.find_last_of(".") + 1);
  // check if file exists
  if (!std::filesystem::exists(file.path)) {
    std::cerr << "File " << file.path << " does not exist" << std::endl;
    exit(EXIT_FAILURE);
  }

  files.push_back(file);
  return file;
}

/**
 * Reads the contents of a file specified by the filename into a string.
 *
 * @param filename The name of the file to read.
 *
 * @return A string containing the contents of the file.
 *
 * @throws None
 */
std::string FileReader::read_to_str(const std::string &filename) {
  return read_to_str(get(filename));
}

/**
 * Reads the contents of the file specified by the File object into a string.
 *
 * @param file The File object representing the file to read.
 *
 * @return A string containing the contents of the file.
 *
 * @throws None
 */
std::string FileReader::read_to_str(const File &file) {
  std::string str;

  std::ifstream in(file.path);
  in.seekg(0, std::ios::end);
  str.reserve(in.tellg());
  in.seekg(0, std::ios::beg);
  str.assign((std::istreambuf_iterator<char>(in)),
             std::istreambuf_iterator<char>());

  in.close();
  return str;
}