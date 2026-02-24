#include<stdio.h>

enum DeptEnum {
    DEPT_NONE_SELECTED = 0,
    DEPT_ACCT = 1,
    DEPT_SALES = 2,
    DEPT_PLANT = 3,
    DEPT_SHIPPING = 4,
    DEPT_QC = 5
};




struct UserVO {
    const char *username;
    const char *first;
    const char *last;
    const char *email;
    const char *password;
    enum DeptEnum department;



    bool (*isValid)(const struct UserVO self, const char password);
    const char *(*givenName)(const struct UserVO self, char buffer, size_t buffer_size);
};



// const char *dept_to_string(enum DeptEnum dept);
const char *dept_to_string(const enum DeptEnum dept) {
        switch (dept) {
        case DEPT_NONE_SELECTED: return "--NONE_SELECTED--";
        case DEPT_ACCT: return "Accounting";
        case DEPT_SALES: return "Sales";
        case DEPT_PLANT: return "Plant";
        case DEPT_SHIPPING: return "Shipping";
        case DEPT_QC: return "Quality Control";
        default: return "Unknown";
    }
}

int main(){
    return 0;
}