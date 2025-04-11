#include "File.h"

File::File(const string& name, const string& type, const string& owner, const uint64_t& inode, FileObj* parent)
    :FileObj(name, (parent ? parent->getPath() + name + "/" : "/"), type, owner, inode, parent), content("") {
}

// read and write
string File::read() const {
    // TODO: return file content
    // note 1: you can choose to printf content into stdout in this function or not (Optional)
    std::cout << content << std::endl;
    return content;
    // fprintf(stderr, "Error: File::read() is not implemented yet!\n");
    // assert(0);
    // return "";
}

// bool File::write(const string &data) { 
//     //TODO: write data into file content, return true if write successfully, otherwise false
//     // note 1: replace "\\n" into new line "\n"
//     // for example, when you wrote "Hello PA-1\n" in command line, data will be "Hello PA-1\\n"
//     content = data;// content.append(data); **NOT sure about this**
//     return true;
// }

bool File::write(const string &data) {
    string processedData;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i] == '\\' && i+1 < data.size() && data[i+1] == 'n') {
            processedData += '\n';   
            ++i;                     
        } else {
            processedData += data[i];
        }
    }
    content = processedData;         
    return true;
}

string File::getContent() const {
    // TODO: retun file content
    return content;
    // fprintf(stderr, "Error: File::getContent() is not implemented yet!\n");
    // assert(0);  
    // return "";
}

// helper function
void File::display() const {
    std::cout << "[File: " << getName() << "] Size: " << content.length() << " bytes" << std::endl;
}
