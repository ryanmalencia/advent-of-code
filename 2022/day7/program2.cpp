#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../../include/timing.h"

class Node {
public:
    Node(const std::string& name, int value, bool leaf) {
        Name = name;
        Value = value;
        Parent = nullptr;
        Leaf = leaf;
    };
    ~Node() {};

    void addChild(Node* child) {
        Children.push_back(child);
        child->Parent = this;
        Value += child->Value;
        Node* parent = this->Parent;
        while(parent != nullptr)
        {
            parent->Value += child->Value;
            parent = parent->Parent;
        }
    }

    Node* findChild(const std::string& name) {
        for(const auto& child : Children) {
            if(child->Name == name)
                return child;
        }
        return nullptr;
    }

    int sumDirectoriesLessThanOrEqualSize(Node* node, int size) {
        int sum = 0;
        for(const auto child : node->Children) { 
            if(child->Leaf)
                continue;
            else
            {
                int dirsize = child->Value;
                sum += dirsize <= size ? dirsize : 0;
                int subdirsize = sumDirectoriesLessThanOrEqualSize(child, size);
                sum += subdirsize;
            }
        }
        return sum;
    }

    void getAllDirectorySizes(Node* node, std::vector<int>& vals) {
        for(const auto child : node->Children) { 
            if(child->Leaf)
                continue;
            else
            {
                vals.push_back(child->Value);
                getAllDirectorySizes(child, vals);
            }
        }
    }
public:
    std::string Name;
    int Value;
    std::vector<Node*> Children;
    Node* Parent;
    bool Leaf;
};

int main()
{
    START_TIMER(main_timer);
    std::string line;
    std::string filename("input.txt");
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
        return EXIT_FAILURE;
    }

    std::getline(input_file, line);
    Node* root = new Node("/", 0, false);
    Node* current = root;
    
    std::getline(input_file, line);
    while(line.length() != 0)
    {
        if(line[0] == '$')
        {
            if(line[2] == 'c' && line[3] == 'd')
            {
                if(line[5] == '.' && line[6] == '.')
                    current = current->Parent;
                else
                {
                    line.erase(0, line.find(' ') + 1);
                    line.erase(0, line.find(' ') + 1);
                    if(current->findChild(line) == nullptr)
                    {
                        Node* node = new Node(line, 0, false); 
                        current->addChild(node);
                        current = node;
                    }
                    else 
                        current = current->findChild(line);

                    std::getline(input_file, line);
                    if(line.length() == 0) break;
                    if(line[0] == '$' && line[2] == 'l' && line[3] == 's')
                    {
                        
                        std::getline(input_file, line);
                        while(line.length() > 0 && line[0] != '$')
                        {
                            if(line[0] == 'd' && line[1] == 'i' && line[2] == 'r')
                            {
                                line.erase(0, line.find(' ') + 1);
                                current->addChild(new Node(line, 0, false));
                            }
                            else
                            {
                                int size = atoi(line.substr(0, line.find(' ')).c_str());
                                line.erase(0, line.find(' ') + 1);
                                current->addChild(new Node(line, size, true));
                            }
                            std::getline(input_file, line);
                        }
                        if(line[0] == '$')
                            continue;
                    }
                }
                std::getline(input_file, line);
            }
            else if(line[2] == 'l' && line[3] == 's')
            {
                std::getline(input_file, line);
                while(line.length() > 0 && line[0] != '$')
                {
                    if(line[0] == 'd' && line[1] == 'i' && line[2] == 'r')
                    {
                        line.erase(0, line.find(' ') + 1);
                        current->addChild(new Node(line, 0, false));
                    }
                    else
                    {
                        int size = atoi(line.substr(0, line.find(' ')).c_str());
                        line.erase(0, line.find(' ') + 1);
                        current->addChild(new Node(line, size, true));
                    }
                    std::getline(input_file, line);
                }
                if(line[0] == '$')
                    continue;
            }
        }
    }

    int directorySize = 70000000;
    int freespace = directorySize - root->Value;
    int freespacerequired = 30000000 - freespace;
    std::cout << "Free space required: " << freespacerequired << std::endl;
    std::vector<int> allsizes;
    root->getAllDirectorySizes(root, allsizes);
    std::sort(allsizes.begin(), allsizes.end(), std::greater<int>());
    for(int idx = 0; idx < allsizes.size(); ++idx)
    {
        int val = allsizes[idx];
        if(val < freespacerequired)
        {
            std::cout << allsizes[idx - 1] << std::endl;        
            break;
        }
    }
    
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    input_file.close();
    return EXIT_SUCCESS;
}