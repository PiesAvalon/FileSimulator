```cpp
//tests for File.h
int main() {
    
    // Basic construction test
    File* f1 = new File("notes", "file", "alice", 1001, nullptr);
    assert(f1->getName() == "notes");
    assert(f1->getOwner() == "alice");
    assert(f1->getInode() == 1001);
    assert(f1->getParent() == nullptr);
    std::cout << "1/8 tests passed" << std::endl;
    
    // Test initial empty state
    assert(f1->read().empty());
    assert(f1->getContent().empty());
    std::cout << "2/8 tests passed" << std::endl;

    // Basic write/read test
    assert(f1->write("Sample content"));
    assert(f1->read() == "Sample content");
    assert(f1->getContent() == "Sample content");
    std::cout << "3/8 tests passed" << std::endl;

    // Overwrite content
    assert(f1->write("New content"));
    assert(f1->read() == "New content");
    std::cout << "4/8 tests passed" << std::endl;

    // Empty write test
    assert(f1->write(""));
    assert(f1->read().empty());
    std::cout << "5/8 tests passed" << std::endl;

    // Multiple file test
    File* f2 = new File("data", "file", "bob", 1002, nullptr);
    assert(f2->write("atest")); 
    assert(f2->getContent().size() == 5);
    std::cout << "6/8 tests passed" << std::endl;

    // Parent independence test
    assert(f1->getParent() == nullptr);
    assert(f2->getParent() == nullptr);
    std::cout << "7/8 tests passed" << std::endl;

    // Display smoke tests
    f1->display();
    f2->display();
    std::cout << "8/8 tests passed" << std::endl;
    std::cout << "all tests passed" << std::endl;
    
    // Cleanup
    delete f1;
    delete f2;
    
    return 0;
}
```


```cpp
//tests for Directory.h
int main() {
    // Create root directory (parent is nullptr)
    Directory* root = new Directory("root", "admin", 1, nullptr);

    // Test empty state
    assert(root->isEmpty());
    assert(root->getCount() == 0);
    assert(root->getAll().empty());
    std::cout << "1/11 tests passed" << std::endl;

    // Create child objects
    FileObj* file1 = new File("file1", "file", "user", 100, root); // Assuming Directory can be used as file
    FileObj* dir1 = new Directory("dir1", "user", 101, root);
    std::cout << "2/11 tests passed" << std::endl;

    // Test adding children
    assert(root->add(file1));
    assert(root->getCount() == 1);
    assert(!root->isEmpty());
    assert(root->getChild(100) == file1);

    assert(root->add(dir1));
    assert(root->getCount() == 2);
    assert(root->getChild(101) == dir1);
    std::cout << "3/11 tests passed" << std::endl;

    // Test adding duplicate inode
    FileObj* duplicate = new Directory("duplicate", "user", 100, root);
    assert(!root->add(duplicate));  // Should fail
    delete duplicate;
    std::cout << "4/11 tests passed" << std::endl;

    // Test getAll
    auto all = root->getAll();
    assert(all.size() == 2);
    assert((all[0] == file1 || all[1] == file1));
    std::cout << "5/11 tests passed" << std::endl;

    // Test remove file
    assert(root->remove(100));
    assert(root->getCount() == 1);
    assert(root->getChild(100) == nullptr);
    std::cout << "6/11 tests passed" << std::endl;

    // Test remove non-existent inode
    assert(!root->remove(999));
    std::cout << "7/11 tests passed" << std::endl;

    // Test remove directory
    assert(root->removeDir(101));
    assert(root->isEmpty());
    std::cout << "8/11 tests passed" << std::endl;

    // Add nested structure
    Directory* subdir = new Directory("subdir", "user", 200, root);
    assert(root->add(subdir));
    FileObj* subfile = new Directory("subfile", "user", 201, subdir);
    assert(subdir->add(subfile));
    std::cout << "9/11 tests passed" << std::endl;

    // Test recursive deletion
    assert(root->removeDir(200));
    assert(root->isEmpty());
    std::cout << "10/11 tests passed" << std::endl;

    // Test display methods
    root->display();
    root->add(new Directory("test", "user", 300, root));
    root->display();
    std::cout << "11/11 tests passed" << std::endl;
    std::cout << "all tests passed" << std::endl;

    // Cleanup
    delete root;
    return 0;
}
```