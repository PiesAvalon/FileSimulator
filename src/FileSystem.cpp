#include "FileSystem.h"

FileSystem::FileSystem(const string& username, const uint64_t& inode)
    : root(new Directory("", username, inode, nullptr)), cur(root), username(username) {
    // no change
    users.insert(username);
}

// Navigation
bool FileSystem::changeDir(const uint64_t& inode) {
    // TODO: Change current directory using inode directly, return true if change successfully, otherwise false
    // note 1: check if the inode exists in children [or parent] and if target is directory
    // note 2: update current directory pointer
    if(cur->getParent() != nullptr && cur->getParent()->getInode() == inode){
        cur = dynamic_cast<Directory*>(cur->getParent());
        return true;
    }
    auto target = cur->getChild(inode);
    if(target && target->getType() == "directory"){
        cur = dynamic_cast<Directory*>(target);
        return true;
    }
    return false;
    // fprintf(stderr, "Error: FileSystem::changeDir() is not implemented yet!\n");
    // assert(0);  
    // return false;
}

// File operation "local"
File* FileSystem::createFile(const string& name) {
    // TODO: Create a new file in current directory, return File* if create successfully, otherwise nullptr
    // note 1: check if name already exists
    // note 2: generate new inode via InodeFactory, and update config_table
    for(auto item : cur->getAll()){
        if(item->getName() == name){
            return nullptr;
        }
    }
    InodeFactory i;
    auto inode = i.generateInode();
    File* file = new File(name, "file", username, inode, cur);
    string path = cur->getPath() + name;
    cur->add(file);
    // std::cout << path << std::endl;
    config_table[path] = inode;
    return file;

    // fprintf(stderr, "Error: FileSystem::createFile() is not implemented yet!\n");
    // assert(0);  
    // return nullptr;
}

bool FileSystem::deleteFile(const string& name, const string& user){
    // TODO: Delete file with given inode from current directory, return true if delete successfully, otherwise false
    // note 1: check if the inode exists and if target is a file, and check permission via user and file owner
    // note 2: update config_table
    auto iter = config_table.find(cur->getPath() + name);
    if(iter == config_table.end()){
        return false;
    }
    bool success = cur->remove(iter->second);
    if(!success){
        return false;
    }
    config_table.erase(iter);
    return true;
    // fprintf(stderr, "Error: FileSystem::deleteFile() is not implemented yet!\n");
    // assert(0);  
    // return false;
}

// Dir operation "local"
Directory* FileSystem::createDir(const string& name) {
    // TODO: Create a new directory in current directory, return Directory* if create successfully, otherwise nullptr
    // note 1: check if name already exists
    // note 2: generate new inode via InodeFactory, and update config_table
    for(auto item : cur->getAll()){
        if(item->getName() == name){
            return nullptr;
        }
    }
    InodeFactory i;
    auto inode = i.generateInode();
    Directory* d = new Directory(name, username, inode, cur);
    std::cout << "the path of the created dir is: " << d->getPath() << std::endl;
    config_table[d->getPath()] = inode;
    cur->add(d);
    return d;

    fprintf(stderr, "Error: FileSystem::createDir() is not implemented yet!\n");
    assert(0);  
    return nullptr;
}

bool FileSystem::deleteDir(const string& name,const string& user, bool recursive){
    // TODO: Delete directory with given name from current directory, return true if delete target successfully, otherwise false 
    // note 1: if recursive is true, delete all contents and their config_table entries, and check permission via user and directory owner
    // note 2: if recursive is false, only delete if empty
    auto iter = config_table.find(cur->getPath() + name + "/");
    if(iter == config_table.end()){
        return false;
    }
    auto success = cur->removeDir(iter->second);
    if(!success){
        return success;
    }
    config_table.erase(iter);
    return true;
    // fprintf(stderr, "Error: FileSystem::deleteDir() is not implemented yet!\n");
    // assert(0);  
    // return false;
}

// File and Dir operation "Global"
uint64_t FileSystem::search(const string& name, const string& type) {
    // TODO: Search name in config_table, return inode if found in config_table, 0 if not found
    // note 1: try to find relative path (current path + name) in config_table
    // note 2: try to find absolute path (from root) in config_table first
    string relative = cur->getPath() + name;
    for(auto item : config_table){
        if(item.first == name || item.first == relative){
            return item.second;
        }
    }
    return 0;
    // fprintf(stderr, "Error: FileSystem::search() is not implemented yet!\n");
    // assert(0);  
    // return 0;
}

// Getters
string FileSystem::getCurrentPath() const{
    // TODO: Get the full path of current directory
    // note 1: combine path from root to current directory
    // note 2: handle special case when at root
    if(!cur->getParent()){
        return "/";
    }
    return cur->getPath();

    // fprintf(stderr, "Error: FileSystem::getCurrentPath() is not implemented yet!\n");
    // assert(0);  
    // return "";
}

string FileSystem::getUserName() const {
    // TODO: Get current username
    return username;
    // fprintf(stderr, "Error: FileSystem::getUserName() is not implemented yet!\n");
    // assert(0);  
    // return "";
}

// Setters
bool FileSystem::setUser(const string& username) {
    // TODO: Set new User to use FileSystem
    // note 1: check if the user is in set of users
    // note 2: update current user
    auto iter = users.find(username);
    if(iter == users.end()){
        return false;
    }
    FileSystem::username = username;
    return true;
    // fprintf(stderr, "Error: FileSystem::setUser() is not implemented yet!\n");
    // assert(0);  
    // return false;
}

bool FileSystem::setCurrentDir(Directory* newDir){
    // TODO: Set new current dir in FileSystem, return true if set successfully, otherwise false
    cur = newDir;
    return true;
    // fprintf(stderr, "Error: FileSystem::setCurrentDir() is not implemented yet!\n");
    // assert(0);  
    // return false;
}

// User management methods
bool FileSystem::hasUser(const string& username) const {
    // TODO: Check if user exists in users set, returns true if username exists, otherwise false
    auto iter = users.find(username);
    return !(iter == users.end());
    // fprintf(stderr, "Error: FileSystem::hasUser() is not implemented yet!\n");
    // assert(0);  
    // return false;
}

bool FileSystem::registerUser(const string& username) {
    // TODO： Check if user exists in users set, return true if register successfully, otherwise false
    users.insert(username);
    return true;
    // fprintf(stderr, "Error: FileSystem::registerUser() is not implemented yet!\n");
    // assert(0);  
    // return false;
}

// helper function
FileObj* FileSystem::resolvePath(const string& path) {
    // TODO: resolve path, you can use strtok() in c library or istringstream with getline() in c++
    // return target of FileObj* if resolve successfully, otherwise nullptr

    // std::istringstream iss(path);
    // string name;
    // auto newCur = root;
    // while(getline(iss, name, '/')){
    //     if(!this->changeDir(search(name, "directory"))){
    //         return nullptr;
    //     }
    // }
    // cur = newCur;
    // return cur;

    //assume path is name of file
    std::cout << "start resolving path" << std::endl;
    if(path.find('/') == string::npos){
        string full_path = cur->getPath() + path + "/";
        std::cout << "the full path is: " << full_path << std::endl;
        for(auto item : config_table){
            std::cout << "the item is: " << item.first << std::endl;
        }
        auto filePtr = cur->getChild(config_table[full_path]);
        return filePtr;
    }
    return nullptr;

    // fprintf(stderr, "Error: FileSystem::resolvePath() is not implemented yet!\n");
    // assert(0);  
    // return nullptr;
}