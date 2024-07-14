#include <string>
#include <vector>

struct File {
  std::string name;
  std::string path;
  std::string extension;

  bool operator==(const File &other) const { return this->path == other.path; }
};

class FileReader {
 public:
  // FileReader();
  FileReader(const std::string &dirname);

  File get(const std::string &filename);
  std::string read_to_str(const std::string &filename);
  std::string read_to_str(const File &file);
  void load_dir();

  File not_found{
      .name = "not_found",
      .path = "/not_found",
      .extension = "html",
  };
  std::string not_found_file() {
    return "File " + this->not_found.path + " does not exist";
  }

  std::string dirname;
  std::vector<File> files;
};