#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

string encrypt(int shift, string plainText) {
  string cipherText(plainText.length(), '\0');
  for (int i = 0; i < plainText.length(); i++) {
    cipherText[i] = static_cast<char>((plainText[i] + shift) % 128);
  }
  return cipherText;
}

string decrypt(int shift, string cipherText) {
  string plainText(cipherText.length(), '\0');
  for (int i = 0; i < plainText.length(); i++) {
    plainText[i] = static_cast<char>((cipherText[i] - shift) % 128);
  }
  return plainText;
}

void showUsage() {
  cout << "Usage: './caesar <option> <key shift>'" << endl;
  cout << "\t\tOptions: E/e = encrypt | D/d = decrypt" << endl;
  cout << "\t\tkey shift must be an integer" << endl;
}

int main(int argc, char **argv) {
  // No content given
  if (argc != 3) {
    showUsage();
    return 1;
  }

  // Grab option from input
  char option = argv[1][0];
  // Check for allowable values of option
  switch (option) {
    case 'e':
    case 'E':
    case 'd':
    case 'D':
      break;
    default:
      showUsage();
      return 0;
  }

  // Grab key shift from input, check for proper input
  int shift{0};
  try {
    shift = std::stoi(argv[2]);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Invalid key shift value provided: " << e.what() << endl;
    showUsage();
    return 0;
  } catch (const std::out_of_range &e) {
    std::cerr << "Invalid key shift value provided: " << e.what() << endl;
    showUsage();
    return 0;
  }

  // Read input text from standard input
  string inputText;
  getline(cin, inputText);

  string outputText(inputText.length(), '\0');
  if (option == 'e' || option == 'E') {
    outputText = encrypt(shift, inputText);
  } else if (option == 'd' || option == 'D') {
    outputText = decrypt(shift, inputText);
  }

  cout << outputText << endl;
  return 0;
}
