#include "ClientInterface.h"

ClientInterface::ClientInterface(const string& username, FileSystem* filesystem)
    : filesystem(filesystem), username(username) {
    // no change
}

std::vector<string> ClientInterface::parseCommand(const string& cmdLine) {
    // TODO: Parse command line into vector of arguments, returns vector of parsed arguments
    // note 1: split by whitespace, you can use strtok() in c or istringstream in c++ to get tokens
    // note 2: handle quote string in two bounds for per token
    std::vector<string> v;
    std::istringstream iss(cmdLine);
    string token;
    while(iss >> token){
        v.push_back(token);//note 2 is NOT implemented!
    }
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
    }

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
    return filesystem->createFile(name);//note 1 is NOT implemented!
    // fprintf(stderr, "Error: ClientInterface::createFile() is not implemented yet!\n");
    // assert(0);
    // return false;
}

bool ClientInterface::deleteFile(const string& name) {
    // TODO: Delete file with given name, returns true if file deleted successfully
    // note 1: use filesystem to delete file
    return filesystem->deleteFile(name, username);

    // fprintf(stderr, "Error: ClientInterface::deleteFile() is not implemented yet!\n");
    // assert(0);
    // return false;
}

string ClientInterface::readFile(const string& name) {
    // TODO: Read content from file with given name, returns file content as string
    // note 1: search file by name
    // note 2: cast to File type and read content
    auto file = dynamic_cast<File*>(filesystem->resolvePath(name));
    file->display();
    

    fprintf(stderr, "Error: ClientInterface::readFile() is not implemented yet!\n");
    assert(0);
    return "";
}

bool ClientInterface::writeFile(const string& name, const string& data) {
    // TODO: Write data to file with given name, returns true if write successful
    // note 1: search file by name
    // note 2: process quoted strings
    // note 3: cast to File type and write content

    fprintf(stderr, "Error: ClientInterface::writeFile() is not implemented yet!\n");
    assert(0);
    return false;
}

bool ClientInterface::createDir(const string& name) {
    // TODO: Create new directory with given name, returns true if directory created successfully
    // note 1: use filesystem to create directory

    fprintf(stderr, "Error: ClientInterface::createDir() is not implemented yet!\n");
    assert(0);
    return false;
}

bool ClientInterface::deleteDir(const string& name, bool recursive) {
    // TODO: Delete directory with given name, returns true if directory deleted successfully
    // note 1: use filesystem to delete directory with recursive flag

    fprintf(stderr, "Error: ClientInterface::deleteDir() is not implemented yet!\n");
    assert(0);
    return false;
}

bool ClientInterface::changeDir(const string& path) {
    // TODO: Change current directory to given path, returns true if directory changed successfully
    // note 1: resolve path to get target directory
    // note 2: validate target is directory type to set

    fprintf(stderr, "Error: ClientInterface::changeDir() is not implemented yet!\n");
    assert(0);
    return false;
}

void ClientInterface::listCurrentDir() {
    // TODO: List all contents in current directory, no return value
    // note 1: print each child's name in current directory per line

    fprintf(stderr, "Error: ClientInterface::listCurrentDir() is not implemented yet!\n");
    assert(0);
}

string ClientInterface::getCurrentPath() const {
    // TODO: Get current working directory path, returns current path as string
    // note 1: use filesystem to get current path

    fprintf(stderr, "Error: ClientInterface::getCurrentPath() is not implemented yet!\n");
    assert(0);
    return "";
}

string ClientInterface::search(const string& name, const string& type) {
    // TODO: Search file or directory by name, returns formatted result string
    // note 1: use filesystem to search by name

    fprintf(stderr, "Error: ClientInterface::search() is not implemented yet!\n");
    assert(0);
    return "";
}
