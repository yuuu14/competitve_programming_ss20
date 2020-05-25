#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#define GETLINEFROM std::cin


//long long max_strength = 0;
//void dfs(int, unsigned long, std::vector<int>);
//void method1(int, unsigned long, std::vector<int>);

int main() {
    std::ifstream file("1.in");
    std::vector<std::vector<long>> matrix;
    
    // the way to split string with delimiter
    std::string s, delimiter = " ", num_in_char;
    size_t pos = 0;
    while (std::getline(GETLINEFROM, s)) {
        std::vector<long> line;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            num_in_char = s.substr(0, pos);
            line.push_back(std::stoi(num_in_char));
            s.erase(0, pos + delimiter.length());

        }
        num_in_char = s;
        line.push_back(std::stoi(num_in_char));
        matrix.push_back(line);
    }
    /*
    for (unsigned int i = 0; i < matrix.size(); ++i) {
        for (unsigned int j = 0; j < matrix[i].size(); ++j) {
            std::cout << std::setw(3) << std::right; 
            std::cout << matrix[i][j] << std::setw(3);
        }
        std::cout << std::endl;
    }
    */

    // 

    // dfs; prune when zero be choosed
    /*
    std::vector<int> usable, lines;
    for (unsigned i = 0; i < 11; ++i) {
        usable.push_back(i);
        lines.push_back(i);
    } 
    */
    
    auto start = std::chrono::high_resolution_clock::now();
    
    /*
    for (unsigned int i = 0; i < 11; ++i) {
        for (unsigned int j = 0; j < 11; ++j) {
            std::vector<int> usable_next(usable);
            usable_next.erase(usable_next.begin() + j);
            dfs((i+1) % 11, matrix[lines[i]][j], usable_next);
        }
    }
    */

    long long max_res = 0;
    std::vector<long> v;
    for (unsigned int i = 0; i < 11; ++i) v.push_back(i); 
    do {
        long long sum = 0;
        unsigned int i;
        for (i = 0; i < 11; ++i) sum += matrix[i][v[i]];
        if (sum > max_res) max_res = sum;
    } while (std::next_permutation(v.begin(), v.end()));
    
    //method1(0, 0, usable);

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);

    std::cout << max_res << std::endl;// << std::endl;
    //std::cout << "\nTime taken: " << duration.count() << " microseconds" << std::endl;
    //method1(0,0,usable);
    //std::cout << max_strength << std::endl;

    return 0;
}

/*
void dfs(int l, unsigned long cur_strength, std::vector<int> usable) {
    if (usable.size() == 1) {
        std::cout << cur_strength + matrix[l][usable[0]] << std::endl;
        max_strength = \
            matrix[l][usable[0]] && cur_strength + matrix[l][usable[0]] > max_strength?\
            cur_strength + matrix[l][usable[0]] : max_strength;
        return;
    }
    else {
        // find max in available
        int max = 0;
        std::vector<int> max_pos;

        for (unsigned int i = 0; i < usable.size(); ++i)
            if (matrix[l][usable[i]] > max) max = matrix[l][usable[i]];
        for (unsigned int i = 0; i < usable.size(); ++i)
            if (matrix[l][usable[i]] == max) max_pos.push_back(i);
        for (unsigned int i = 0; i < max_pos.size(); ++i) {
            if (matrix[l][usable[max_pos[i]]]) {
                std::vector<int> usable_next(usable);
                usable_next.erase(usable_next.begin() + max_pos[i]);        
                dfs((i+1) % 11, cur_strength+matrix[l][usable[max_pos[i]]], usable_next);
            }
            else return;
        }
    }
}

void method1(int i, unsigned long cur_strength, std::vector<int> usable) {
    if (usable.size() == 1) {
        //std::cout << cur_strength + matrix[i][usable[0]] << std::endl;
        max_strength = \
            matrix[i][usable[0]] && cur_strength + matrix[i][usable[0]] > max_strength?\
            cur_strength + matrix[i][usable[0]] : max_strength;
        //std::cout << max_strength << std::endl;
        return;
    }
    else {
        //for (unsigned int j = 0; j < usable.size(); ++j) std::cout << usable[j] << " ";
        //std::cout << std::endl;
        for (unsigned int j = 0; j < usable.size(); ++j) {
            if (matrix[i][usable[j]]) {
                std::vector<int> usable_next(usable);
                usable_next.erase(usable_next.begin() + j);        
                method1(i+1, cur_strength+matrix[i][usable[j]], usable_next);
            }
            else return;
        }
    }
}
*/