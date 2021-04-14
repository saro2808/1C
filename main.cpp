#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

struct Course {
    std::string str;
    bool used;
};

std::vector<std::vector<Course>> courses_by_levels;
std::vector<Course> used;
std::unordered_set<std::string> courses_set = {};

int str_intersect(std::string str1, std::string str2) {
    int i = 0;
    for (; i < str1.size() && i < str2.size(); ++i) {
        if (str1[i] != str2[i]) {
            return i;
        }
    }
    return 0;
}

bool str_compare(std::string str1, std::string str2) {
    int intersection = str_intersect(str1, str2);
    if (intersection == str1.length() - 1 && intersection == str2.length() - 1) {
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
    return get_index(vec[vec.size() - k - 1], old_vec);
}

void func(int lim1, int lim2, int *index, int k) {
    for (int i = 0; i < lim1 && *index < lim2; ++index) {
        std::cout << "iter " << i << std::endl;
        if (!courses_by_levels[k][i].used) {
            courses_set.insert(courses_by_levels[k][i].str);
        }
        ++i;
    }
}

int main() {
    int sem_count;
    std::cout << "How many semesters there should be - ";
    std::cin >> sem_count;
    std::cout << std::endl;

    int level_count;
    std::cout << "How many levels there should be - ";
    std::cin >> level_count;
    std::cout << std::endl;

    std::vector<std::vector<Course>> temp_book(level_count);
    courses_by_levels = temp_book;

    std::vector<int> current_level_course_count(level_count);
    int used_count = 0; // used.size()

    // read table
    std::string s;
    for (int i = 0; i < level_count; ++i) {
        std::cout << "How many courses are available for level " << i << " - ";
        std::cin >> current_level_course_count[i];
        std::cout << "List them" << std::endl;
        for (int j = 0; j < current_level_course_count[i]; ++j) {
            std::cin >> s;
            courses_by_levels[i].push_back({s, false});
        }
    }

    // priorities of level 2
    std::cout << "Input your list of priorities of level 2 courses" << std::endl;
    std::vector<int> priority_vector(current_level_course_count[2]);
    int priority;
    for (int i = 0; i < current_level_course_count[2]; ++i) {
        std::cin >> priority;
        priority_vector.push_back(priority);
    }

    // selected three courses of level 3
    std::cout << "Input your selected 3 courses of level 3" << std::endl;
    std::string selected_courses_3[3];
    for (int i = 0; i < 3; ++i) {
        std::cin >> selected_courses_3[i];
    }
    std::cout << "Input your selected course of level 5" << std::endl;
    std::string selected_course_5;
    // and one of level 5
    std::cin >> selected_course_5;

    // minimum number of courses for each semester
    int minimum_number;
    std::cout << "What is the minimum number of courses each semester - ";
    std::cin >> minimum_number;

    int minimum_courses = minimum_number * sem_count;

    // dependencies of selected courses of level 3
    for (int i = 0; i < 3; ++i) {
        std::string course_name = selected_courses_3[i];
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < current_level_course_count[k]; ++j) {
                if (str_compare(courses_by_levels[k][j].str, course_name)
                && !courses_by_levels[k][j].used) {
                    courses_by_levels[k][j].used = true;
                    used.push_back(courses_by_levels[k][j]);
                    ++used_count;
                }
            }
        }
    }

    for (int k = 0; k < 5; ++k) {
        for (int j = 0; j < current_level_course_count[k]; ++j) {
            if (str_compare(courses_by_levels[k][j].str, selected_course_5)
                && !courses_by_levels[k][j].used) {
                courses_by_levels[k][j].used = true;
                used.push_back(courses_by_levels[k][j]);
                ++used_count;
            }
        }
    }

    int index = 0;
    for (int k = 0; k < 2; ++k) {
        func(current_level_course_count[k], minimum_courses - used_count, &index, k);
    }

    for (int i = 0; i < current_level_course_count[2] && index < minimum_courses - used_count; ++index) {
        int kth_max_index = get_kth_index(priority_vector, i);
        if (kth_max_index < current_level_course_count[2]
        && kth_max_index > -1
        && !courses_by_levels[2][kth_max_index].used) {
            courses_set.insert(courses_by_levels[2][kth_max_index].str);
        }
        ++i;
    }

    for (int k = 3; k < level_count; ++k) {
        func(current_level_course_count[k], minimum_courses - used_count, &index, k);
    }

    std::cout << "Needed courses:" << std::endl;
    int ind = 0;
    for (auto course : used) {
        std::cout << "Course " << ind << ": " << course.str << std::endl;
        ++ind;
    }
    for (auto course : courses_set) {
        std::cout << "Course " << ind << ": " << course << std::endl;
        ++ind;
    }
    std::cout << "Total of " << ind << " courses" << std::endl;

    return 0;
}
