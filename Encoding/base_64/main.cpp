#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <streambuf>
#include <cstdlib>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

std::string base64_encode(const std::string& in) {
  BUF_MEM *bptr;
  BIO* b64 = BIO_new(BIO_f_base64());
  BIO* bio = BIO_new(BIO_s_mem());
  bio = BIO_push(b64, bio);
  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
  BIO_write(bio, in.c_str(), (int)in.size());
  BIO_flush(bio);
  BIO_get_mem_ptr(bio, &bptr);

  std::string out(bptr->data, bptr->length);
  BIO_free_all(bio);

  return out;
}


int main(int argc, char** argv)
{

    if (argc != 2)
    {
        std::cout << "You must give a file name as the argument to this program.\n" << std::endl;
        std::cout << "This program reads in a file from the disk and compresses\n"
             << "it in an in memory buffer and then converts that buffer \n"
             << "into base64 text.  The final step is to output to the screen\n"
             << "some C++ code that contains this base64 encoded text and can\n"
             << "decompress it back into its original form.\n" << std::endl;

        return EXIT_FAILURE;
    }

    // open the file the user specified on the command line
    std::ifstream fin(argv[1], std::ios::binary);
    if (!fin) {
        std::cout << "can't open file " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    std::string str((std::istreambuf_iterator<char>(fin)),
                     std::istreambuf_iterator<char>());

    std::cout << "init_string: \n" << str << std::endl;

    std::string encoded_string = base64_encode(str);
    std::cout << "encoded string: \n" << encoded_string;

    std::ofstream out("test.dec");
    out << encoded_string << "\n"; // \n -> otherwise the file is not created
}
