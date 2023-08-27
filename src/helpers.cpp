#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <sstream>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::vector;

namespace fs = std::filesystem;

void copyFile(const std::string &filename, const std::string &fromWhere,
              const std::string &toWhere) {
  std::string filepath_in_source = fromWhere + "/" + filename;
  std::string filepath_in_replica = toWhere + "/" + filename;

  try {
    // if (!fs::exists(filepath_in_replica)) {
    fs::copy_file(filepath_in_source, filepath_in_replica);
    cout << filename << " copied to " << toWhere << endl;
    // }
  } catch (const fs::filesystem_error &e) {
    cerr << e.what() << endl;
  }
}

void deleteFile(const std::string &filename, const std::string &fromWhere) {
  std::string path_to_file = fromWhere + "/" + filename;
  try {
    fs::remove(path_to_file);
    cout << filename << " deleted from " << fromWhere << endl;
  } catch (fs::filesystem_error &e) {
    cout << e.what() << endl;
  }
}

vector<std::string> makeVector(const std::string &directory_path) {
  vector<std::string> result;
  for (const auto &file : fs::directory_iterator(directory_path)) {
    result.push_back(file.path().filename().string());
  }
  return result;
}

void printStringVector(const vector<std::string> vec) {
  for (std::string v : vec) {
    cout << v << "   ";
  }
  cout << endl;
}

void printMapPairs(const std::map<std::string, std::string> myMap) {
  for (auto pair : myMap) {
    cout << pair.first << " : " << pair.second << endl;
  }
}

// std::string calculateMD5(const std::string &filename) {
//   std::ifstream file(filename, std::ios::binary);
//   if (!file) {
//     throw std::runtime_error("Failed to open file for reading.");
//   }

//   //   std::ifstream filetoprint(filename);
//   //   std::string line;
//   //   while (std::getline(file, line)) {
//   // cout << line << endl;
//   //   }

//   MD5_CTX md5ctx;
//   MD5_Init(&md5ctx);

//   char buffer[1024];
//   while (file.read(buffer, sizeof(buffer))) {
//     MD5_Update(&md5ctx, buffer, file.gcount());
//   }

//   unsigned char hash[MD5_DIGEST_LENGTH];
//   MD5_Final(hash, &md5ctx);

//   std::stringstream ss;
//   for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
//     ss << std::hex << std::setw(2) << std::setfill('0')
//        << static_cast<int>(hash[i]);
//   }

//   return ss.str();
// }

std::string calculateMD5(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Failed to open file for reading.");
  }

  EVP_MD_CTX *md5ctx = EVP_MD_CTX_new();
  if (!md5ctx) {
    throw std::runtime_error("Failed to create EVP context.");
  }

  EVP_MD_CTX_init(md5ctx);
  EVP_DigestInit_ex(md5ctx, EVP_md5(), nullptr);

  char buffer[1024];
  while (file.read(buffer, sizeof(buffer))) {
    EVP_DigestUpdate(md5ctx, buffer, file.gcount());
  }

  unsigned char hash[EVP_MAX_MD_SIZE];
  unsigned int hashLen;
  EVP_DigestFinal_ex(md5ctx, hash, &hashLen);

  EVP_MD_CTX_free(md5ctx);

  std::stringstream ss;
  for (unsigned int i = 0; i < hashLen; ++i) {
    ss << std::hex << std::setw(2) << std::setfill('0')
       << static_cast<int>(hash[i]);
  }

  return ss.str();
}

void makeMapWithHash(std::map<std::string, std::string> &mapWithHash,
                     const std::string &directory_path) {
  for (const auto &file : fs::directory_iterator(directory_path)) {
    std::string name_of_file = file.path().filename().string();
    std::string file_path = file.path().string();

    mapWithHash[name_of_file] = calculateMD5(file_path);
  }
}
