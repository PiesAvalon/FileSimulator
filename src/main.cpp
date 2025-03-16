#include "ClientInterface.h"
#include "VFS.h"

int main() {
    VFS vfs;
    vfs.run();
    return 0;
    
}

// int main() {
//     // Initialize filesystem
//     FileSystem fs("admin", 1000);
//     assert(fs.getUserName() == "admin");
//     assert(fs.getRootDir() != nullptr);
//     assert(fs.getCurrentDir() == fs.getRootDir());

//     // Test user management
//     assert(fs.hasUser("admin"));
//     assert(!fs.hasUser("user1"));
//     assert(fs.registerUser("user1"));
//     assert(fs.hasUser("user1"));
//     assert(!fs.registerUser("user1")); // Duplicate registration

//     // Create directory structure
//     Directory* docs = fs.createDir("docs");
//     assert(docs != nullptr);
//     assert(fs.getCurrentDir()->getChild(docs->getInode()) == docs);
    
//     // Test file creation
//     File* notes = fs.createFile("notes.txt");
//     assert(notes != nullptr);
//     assert(notes->getOwner() == "admin");
//     assert(fs.getCurrentDir()->getChild(notes->getInode()) == notes);

//     // Test navigation
//     uint64_t docs_inode = docs->getInode();
//     assert(fs.changeDir(docs_inode));
//     assert(fs.getCurrentDir() == docs);
//     assert(fs.getCurrentPath().find("/docs") != string::npos);

//     // Create nested structure
//     File* secret = fs.createFile("secret.txt");
//     Directory* projects = fs.createDir("projects");
//     assert(fs.changeDir(projects->getInode()));
//     File* code = fs.createFile("main.cpp");
//     assert(fs.getCurrentPath().find("/docs/projects") != string::npos);

//     // Test search functionality
//     uint64_t found = fs.search("secret.txt", "file");
//     assert(found == secret->getInode());
//     found = fs.search("projects", "directory");
//     assert(found == projects->getInode());
//     found = fs.search("ghost.txt", "file");
//     assert(found == 0);

//     // Test file deletion
//     assert(fs.deleteFile("secret.txt", "admin")); // Valid owner
//     assert(!fs.deleteFile("ghost.txt", "admin")); // Non-existent file
//     assert(!fs.deleteFile("notes.txt", "user1")); // Wrong user

//     // Test directory deletion
//     fs.setCurrentDir(fs.getRootDir());
//     assert(!fs.deleteDir("docs", "user1")); // Unauthorized
//     assert(!fs.deleteDir("docs", "admin")); // Non-recursive delete of non-empty dir
//     assert(fs.deleteDir("docs", "admin", true)); // Recursive delete
//     assert(fs.getCurrentDir()->getChild(docs_inode) == nullptr);

//     // Test path resolution
//     fs.setCurrentDir(fs.getRootDir());
//     Directory* bin = fs.createDir("bin");
//     File* tool = fs.createFile("tool.exe");
//     assert(fs.changeDir(bin->getInode()));
//     assert(fs.getCurrentPath() == "/bin/");

//     // Test user switching
//     assert(!fs.setUser("hacker")); // Unknown user
//     assert(fs.setUser("user1"));
//     assert(fs.getUserName() == "user1");

//     // Test edge cases
//     File* invalid = fs.createFile(""); // Empty name
//     assert(invalid == nullptr);
//     assert(!fs.changeDir(999999)); // Invalid inode

//     // Test memory boundaries
//     for(int i = 0; i < 100; i++) {
//         assert(fs.createDir("dir_" + to_string(i)));
//     }
//     assert(fs.getCurrentDir()->getCount() == 100);

//     // Cleanup
//     assert(fs.deleteDir("bin", "user1", true));
//     return 0;
// }
