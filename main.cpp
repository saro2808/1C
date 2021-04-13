#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


struct Item {
    std::string str;
    bool used;
};

std::vector<std::vector<Item>> book;
std::vector<Item> used;

int str_intersect(std::string s1, std::string s2) {
    int i = 0;
    for (; ; ++i) {
        if (s1[i] != s2[i]) {
            return i;
        }
    }
}

bool str_compare(std::string s1, std::string s2) {
    int intersection = str_intersect(s1, s2);
    if (intersection == s1.length() - 1 && intersection == s2.length() - 1) {
        return true;
    }
    return false;
}

int get_index(int elem, std::vector<int> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (elem == vec[i]) {
            return i;
        }
    }
    return -1;
}

int get_kth_index(std::vector<int> vec, int k) {
    std::vector<int> old_vec = vec;
    std::sort(vec.begin(), vec.end());
    int ret = get_index(vec[vec.size() - k - 1], old_vec);
    return ret;
}

void func(int lim1, int lim2, int *index, int k) {
    for (int i = 0; i < lim1 && *index < lim2; ++index) {
        if (!book[k][i].used) {
            used.push_back(book[k][i]);
        }
        ++i;
    }
}

int main() {
    int sem_count;
    std::cin >> sem_count;
    int max_level;
    std::cin >> max_level;
    std::vector<int> current_level_course_count(max_level);
    //std::vector<int> used_in_current_level_count;
    int used_count = 0;
    // read table
    std::string s;
    for (int i = 0; i <= max_level; ++i) {
        std::cout << "How many courses are available for " << i << " - ";
        std::cin >> current_level_course_count[i];
        for (int j = 0; j < current_level_course_count[i]; ++j) {
            std::cin >> s;
            book[i].push_back({s, false});
        }
    }

    // priorities of level 2
    std::cout << "Input your list of priorities of level 2 courses";
    //std::vector<Item> priority_vector(current_level_course_count[2]);
    std::vector<int> priority_vector(current_level_course_count[2]);
    int priority;
    for (int i = 0; i < current_level_course_count[2]; ++i) {
        std::cin >> priority;
        priority_vector.push_back(priority);
    }

    // selected three courses of level 3
    std::string selected_courses_3[3];
    for (int i = 0; i < 3; ++i) {
        std::cin >> selected_courses_3[i];
    }
    std::string selected_course_5;
    // and one of level 5
    std::cin >> selected_course_5;

    // minimum number of courses for each semester
    int minimum_number;
    std::cin >> minimum_number;

    int minimum_courses = minimum_number * sem_count;

    // dependencies of selected courses of level 3
    for (int i = 0; i < 3; ++i) {
        std::string course_name = selected_courses_3[i];
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < current_level_course_count[k]; ++j) {
                if (str_compare(book[k][j].str, course_name)) {
                    book[k][j].used = true;
                    used.push_back(book[k][j]);
                    //++used_in_current_level_count[k];
                    ++used_count;
                }
            }
        }
    }

    for (int k = 0; k < 5; ++k) {
        for (int j = 0; j < current_level_course_count[k]; ++j) {
            if (str_compare(book[k][j].str, selected_course_5)) {
                book[k][j].used = true;
                used.push_back(book[k][j]);
                //++used_in_current_level_count[k];
                ++used_count;
            }
        }
    }

    int index = 0;
    for (int k = 0; k < 2; ++k) {
        func(current_level_course_count[k], minimum_courses - used_count, &index, k);
    }

    for (int i = 0; i < current_level_course_count[2] && index < minimum_courses - used_count; ++index) {
        int max_index = get_kth_index(priority_vector, i);
        if (!book[2][max_index].used) {
            used.push_back(book[2][max_index]);
        }
        ++i;
    }

    for (int k = 3; k < max_level; ++k) {
        func(current_level_course_count[k], minimum_courses - used_count, &index, k);
    }

    int ind = 0;
    for (auto str : used) {
        std::cout << "Course " << ind << " " << str.str << std::endl;
    }

    return 0;
}
