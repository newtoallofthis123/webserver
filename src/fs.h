#include <string>
#include <vector>

struct File {
  std::string name;
  std::string path;
  std::string extension;
};

class FileReader {
 public:
  // FileReader();
  FileReader(const std::string &dirname);

  File get(const std::string &filename);
  std::string read_to_str(const std::string &filename);
  std::string read_to_str(const File &file);
  void load_dir();

  std::string dirname;
  std::vector<File> files;
};