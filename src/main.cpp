#include "ClientInterface.h"
#include "VFS.h"

int main() {
    // VFS vfs;
    // vfs.run();
    // return 0;
    File file("myFile", "File", "Pies", 10, nullptr);
    string i, j;
    std::cin >> i;
    file.write(i);
    file.read();
    std::cin >> j;
    file.write(j);
    std::cout << file.getContent();
}