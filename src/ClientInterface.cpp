#include "ClientInterface.h"

ClientInterface::ClientInterface(const string& username, FileSystem* filesystem)
    : filesystem(filesystem), username(username) {
    // no change
}

std::vector<string> ClientInterface::parseCommand(const string& cmdLine) {
    // TODO: Parse command line into vector of arguments, returns vector of parsed arguments
    // note 1: split by whitespace, you can use strtok() in c or istringstream in c++ to get tokens
    // note 2: handle quote string in two bounds for per token
    if(cmdLine.empty()){
        return std::vector<string>();
    }
    std::vector<string> v;
    std::istringstream iss(cmdLine);
    string token;
    while(iss >> token){
        if(token[0] == '\"'){
            string temp;
            while(token[token.size()-1] != '\"'){
                temp += token + " ";
                iss >> token;
            }
            temp += token;
            temp = temp.substr(1, temp.size()-2);
            v.push_back(temp);
            continue;
        }
        v.push_back(token);//note 2 is NOT implemented!
    }

    //debug
    for(auto item : v){
        // std::cout << item << std::endl;
    }
    // filesystem->getCurrentDir()->display();
    return v;

    // fprintf(stderr, "Error: ClientInterface::parseCommand() is not implemented yet!\n");
    // assert(0);
    // return std::vector<string>();
}

bool ClientInterface::execueCommand(const std::vector<string>& cmd) {
    // TODO: Execute parsed command, returns true if command executed successfully
    // note 1: check first argument for command type
    // note 2: validate number of arguments
    // note 3: call corresponding operation method
    if(cmd.size() == 0){
        return true;
    }
    string program = cmd[0];
    if(program == "help"){
        showHelp();
        return true;
    }
    if(program == "create"){
        return createFile(cmd[1]);//only creates one file
    }
    if(program == "delete"){
        return deleteFile(cmd[1]);//only deletes one file
    }
    if(program == "read"){
        readFile(cmd[1]);
        return true;
    }
    if(program == "write"){
        return writeFile(cmd[1], cmd[2]);
    }
    if(program == "ls"){
        listCurrentDir();
        return true;
    }
    if(program == "mkdir"){
        return createDir(cmd[1]);
    }
    if(program == "rmdir"){
        if(cmd.size() == 3 && cmd[2] == "-r"){
            // std::cout << "recursive delete" << std::endl;
            return deleteDir(cmd[1], true);
        }
        else{
            // std::cout << "non-recursive delete" << std::endl;
            return deleteDir(cmd[1], false);
        }
    }
    if(program == "cd"){
        return changeDir(cmd[1]);
    }
    if(program == "pwd"){
        std::cout << getCurrentPath() << std::endl;
        return true;
    }
    if(program == "whoami"){
        std::cout << username << std::endl;
        return true;
    }
    if(program == "clear"){
        std::cout << "\033[2J\033[1;1H";
        return true;
    }
    if(program == "exit"){
        exit(0);
    }
    return true;
    // fprintf(stderr, "Error: ClientInterface::execueCommand() is not implemented yet!\n");
    // assert(0);
    // return false;
}

void ClientInterface::processCommand(const string& cmdLine) {
    // TODO: Process user input command line, no return value
    // note 1: parse command line
    // note 2: execute command
    // note 3: handle exceptions
    auto cmdVec = parseCommand(cmdLine);
    execueCommand(cmdVec);

    
    // fprintf(stderr, "Error: ClientInterface::processCommand() is not implemented yet!\n");
    // assert(0);
}

void ClientInterface::showHelp() const {
    // Show help message with all available commands and their usage, no return value
    std::cout << "Available commands:\n"
         << "  create <filename...>      - Create one or more new files\n"
         << "  delete <filename...>      - Delete one or more files\n"
         << "  read <filename...>        - Read content from one or more files\n"
         << "  write <filename> <text>   - Write text to file (supports '\\n' for newline)\n"
         << "  mkdir <dirname>           - Create a new directory\n"
         << "  rmdir [-r] <dirname>      - Remove directory (-r for recursive deletion)\n"
         << "  cd <path>                - Change directory (supports relative/absolute paths)\n"
         << "  ls                       - List current directory contents\n"
         << "  pwd                      - Show current working directory\n"
         << "  whoami                   - Show current user name\n"
         << "  clear                    - clear current command line\n"
         << "  help                     - Show this help message\n"
         << "  exit                     - Logout current user\n"
         << "  quit                     - Exit program\n" << std::endl;
}


bool ClientInterface::createFile(const string& name) {
    // TODO: Create new file with given name, returns true if file created successfully
    // note 1: validate file name
    // note 2: use filesystem to create file
    bool success = filesystem->createFile(name);
    if(success){
        std::cout << "File created successfully!" << std::endl;
    }
    else{
        std::cout << "File creation failed!" << std::endl;
    }
    return success;//note 1 is NOT implemented!
    // fprintf(stderr, "Error: ClientInterface::createFile() is not implemented yet!\n");
    // assert(0);
    // return false;
}

bool ClientInterface::deleteFile(const string& name) {
    // TODO: Delete file with given name, returns true if file deleted successfully
    // note 1: use filesystem to delete file
    auto success =  filesystem->deleteFile(name, username);
    if(success){
        std::cout << "File deleted successfully!" << std::endl;
    }
    else{
        std::cout << "File deletion failed!" << std::endl;
    }
    return success;

    // fprintf(stderr, "Error: ClientInterface::deleteFile() is not implemented yet!\n");
    // assert(0);
    // return false;
}

string ClientInterface::readFile(const string& name) {
    // TODO: Read content from file with given name, returns file content as string
    // note 1: search file by name
    // note 2: cast to File type and read content
    auto file = dynamic_cast<File*>(filesystem->resolvePath(name));
    // file->display();
    if(file){
        std::cout << file->getContent() << std::endl;
        return file->getContent();
    }
    std::cout << "File not found!" << std::endl;
    return "";
    
    // fprintf(stderr, "Error: ClientInterface::readFile() is not implemented yet!\n");
    // assert(0);
    // return "";
}

bool ClientInterface::writeFile(const string& name, const string& data) {
    // TODO: Write data to file with given name, returns true if write successful
    // note 1: search file by name
    // note 2: process quoted strings
    // note 3: cast to File type and write content
    auto file = dynamic_cast<File*>(filesystem->resolvePath(name));
    if(file){
        file->write(data);
        std::cout << "File written successfully!" << std::endl;
        return true;
    }
    return false;

    // fprintf(stderr, "Error: ClientInterface::writeFile() is not implemented yet!\n");
    // assert(0);
    // return false;
}

bool ClientInterface::createDir(const string& name) {
    // TODO: Create new directory with given name, returns true if directory created successfully
    // note 1: use filesystem to create directory
    bool success = filesystem->createDir(name);
    if(success){
        std::cout << "directory created!" << std::endl;
    }
    else{
        std::cout << "directory creation failed" << std::endl;
    }
    return success;
    // fprintf(stderr, "Error: ClientInterface::createDir() is not implemented yet!\n");
    // assert(0);
    // return false;
}

bool ClientInterface::deleteDir(const string& name, bool recursive) {
    // TODO: Delete directory with given name, returns true if directory deleted successfully
    // note 1: use filesystem to delete directory with recursive flag
    bool success = filesystem->deleteDir(name, username, recursive);
    if(success){
        std::cout << "directory deleted!" << std::endl;
    }
    else{
        std::cout << "deletion failed" << std::endl;
    }
    return success;

    // fprintf(stderr, "Error: ClientInterface::deleteDir() is not implemented yet!\n");
    // assert(0);
    // return false;
}

bool ClientInterface::changeDir(const string& path) {
    // TODO: Change current directory to given path, returns true if directory changed successfully
    // note 1: resolve path to get target directory
    // note 2: validate target is directory type to set
    if(path == ".."){
        auto parent = filesystem->getCurrentDir()->getParent();
        if(parent){
            std::cout << "parent directory: " << parent->getPath() << std::endl;
            return filesystem->setCurrentDir(dynamic_cast<Directory*>(parent));
        }
        else{
            std::cout << "no parent directory" << std::endl;
            return false;
        }
    }
    auto dir = filesystem->resolvePath(path + "/");
    if(!dir){
        std::cout << "directory not found" << std::endl;
        return false;
    }
    std::cout << dir->getPath() << std::endl;
    bool success = filesystem->setCurrentDir(dynamic_cast<Directory*>(dir));
    if(success){
        std::cout << "directory changed!" << std::endl;
    }
    else{
        std::cout << "directory change failed" << std::endl;
    }
    return success;
    // fprintf(stderr, "Error: ClientInterface::changeDir() is not implemented yet!\n");
    // assert(0);
    // return false;
}

void ClientInterface::listCurrentDir() {
    // TODO: List all contents in current directory, no return value
    // note 1: print each child's name in current directory per line
    filesystem->getCurrentDir()->display();
    // auto pwd =  filesystem->getCurrentDir();
    // for(auto item : pwd->getAll()){
    //     std::cout << item->getName() << std::endl;
    // }

    // fprintf(stderr, "Error: ClientInterface::listCurrentDir() is not implemented yet!\n");
    // assert(0);
}

string ClientInterface::getCurrentPath() const {
    // TODO: Get current working directory path, returns current path as string
    // note 1: use filesystem to get current path

    auto pwd =  filesystem->getCurrentDir();
    // std::cout << pwd->getPath() << std::endl;
    return pwd->getPath();
    // fprintf(stderr, "Error: ClientInterface::getCurrentPath() is not implemented yet!\n");
    // assert(0);
    // return "";
}

string ClientInterface::search(const string& name, const string& type) {
    // TODO: Search file or directory by name, returns formatted result string
    // note 1: use filesystem to search by name

    //this is not a fuctional module
    auto a = type;
    auto b = name;
    return "";

    // fprintf(stderr, "Error: ClientInterface::search() is not implemented yet!\n");
    // assert(0);
    // return "";
}
