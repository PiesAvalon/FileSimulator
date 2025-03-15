#include "Directory.h"

Directory::Directory(const string& name, const string& owner, const uint64_t& inode, FileObj* parent)
    :FileObj(name, (parent ? parent->getPath() + name + "/" : "/"), "directory", owner, inode, parent){ 
    // TODO: finish construction function like File class
    // fprintf(stderr, "Error: Directory::Directory() is not implemented yet!\n");
    // assert(0);
}

// add, remove
bool Directory::add(FileObj* child) {
    // TODO: add a FileObj to current Directory, return true if add successfully, otherwise false
    // note 1: you can't add a nullptr 
    // note 2: set child's parent pointer
    children[child->getInode()] = child;
    child->setParent(this);
    // fprintf(stderr, "Error: Directory::add() is not implemented yet!\n");
    // assert(0);
    return true;
}

bool Directory::remove(uint64_t inode) {
    // TODO: Remove child object by inode, return true if remove successfully, otherwise false
    // note 1: free memory if child object need to be removed
    // note 2: only remove files, not directories (use removeDir for directories)
    auto iter = children.find(inode);
    // std::cout << "removing" << std::endl;
    if(iter == children.end()){
        // std::cout << "remove file failed" << std::endl;
        return false;
    }
    if(iter->second->getType() != "file"){
        return false;
    }
    // std::cout << "the removal is valid" << std::endl;
    delete iter->second;
    children.erase(iter);
    return true;
    // fprintf(stderr, "Error: Directory::remove() is not implemented yet!\n");
    // assert(0);  
    // return true;
}

bool Directory::removeDir(uint64_t inode){
    // TODO: Remove directory object by inode, return true if remove successfully, otherwise false
    // note 1: free memory of the directory and all its children recursively
    // note 2: return false if inode not in current directory or target is not a directory
    // note 3: use dynamic_cast to safely convert FileObj* to Directory*
    // note 4: recursively remove all children before removing the directory itself
    auto iter = children.find(inode);
    if(iter == children.end()){
        return false;
    }
    if(iter->second->getType() != "directory"){
        return false;
    }
    for(auto item : children){
        if(item.second->getType() == "file"){
            remove(item.first);
        }
        else if(item.second->getType() == "directory"){
            dynamic_cast<Directory*>(item.second)->removeDir((dynamic_cast<Directory*>(item.second)->getInode()));
        }
    }
    delete iter->second;
    children.erase(iter);
    return true;
    // fprintf(stderr, "Error: Directory::removeDir() is not implemented yet!\n");
    // assert(0);  
    // return true;
}

// Getters
FileObj* Directory::getChild(uint64_t inode) {
    // TODO: Get child object by inode if found, otherwise nullptr
    auto iter = children.find(inode);
    if(iter == children.end()){
        return nullptr;
    }
    else{
        return iter->second;
    }
    // fprintf(stderr, "Error: Directory::getChild() is not implemented yet!\n");
    // assert(0);  
    // return nullptr;
}

std::vector<FileObj*> Directory::getAll() const {
    // TODO: Get all child objects in vector, may be empty
    std::vector<FileObj*> v;
    for(auto item : children){
        v.push_back(item.second);
    }
    return v;
    // fprintf(stderr, "Error: Directory::getAll() is not implemented yet!\n");
    // assert(0);  
    // return std::vector<FileObj*>();
}

size_t Directory::getCount() const {
    // TODO: Get number of children
    return children.size();
    // fprintf(stderr, "Error: Directory::getCount() is not implemented yet!\n");
    // assert(0);  
    // return 0;
}

// helper function
bool Directory::isEmpty() const {
    // TODO: return true if directory is empty, otherwise flase
    return children.empty();
    // fprintf(stderr, "Error: Directory::isEmpty() is not implemented yet!\n");
    // assert(0);  
    // return false;
}

// helper function
void Directory::display() const {
    std::cout << "[Directory: " << getName() << "]" << std::endl;
    for (const auto& pair : this->children) {
        std::cout << "- " << pair.second->getType() << ": " 
                 << pair.second->getName() << " with owner: " << pair.second->getOwner() << std::endl;
    }
}