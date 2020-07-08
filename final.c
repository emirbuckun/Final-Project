#include <stdio.h>

struct student
{
    unsigned int student_num;
    char name[20];
    char surname[20];
    int visa_result;
    int final_result;
    int homework1_result;
    int homework2_result;
    float end_grade;
};

struct student students[100];
int student_count = 0;

int get_num();
int get_info_manuel();
int search_student();

int main(int argc, char *argv[])
{
    int choice = get_num(), a, b;

    // If choice is 1, do the following (ADDING STUDENT) -nonparametric-
    if (choice == 1 & argc != 2)
    {
        a = get_info_manuel();

        if (a == 0)
            return main(argc, argv);
    }

    // If choice is 1, do the following (ADDING STUDENT) -parametric-
    if (choice == 1 & argc == 2)
    {
        char menu[1];
        int i = 0;

        FILE* student_list = fopen(argv[1], "r");
        while (!feof(student_list))
        {
            fscanf(student_list, "%u %s %s %i %i %i %i\n", &students[i].student_num, students[i].name, students[i].surname,
            &students[i].visa_result, &students[i].final_result, &students[i].homework1_result, &students[i].homework2_result);

            students[i].end_grade = ((students[i].visa_result * 0.25) + (students[i].final_result * 0.40)
                                    + (students[i].homework1_result * 0.15) + (students[i].homework2_result * 0.20));
            i++;
            student_count++;
        }

        fclose(student_list);

        printf("\nPress the 'M' button to return to the main menu...\n");
        scanf("%s", menu);

        if (menu[0] == 77 || menu[0] == 109)
            return main(argc, argv);
    }

    // If choice is 2, do the following (STUDENT SEARCH)
    if (choice == 2)
    {
        b = search_student();

        if (b == 0)
            return main(argc, argv);
    }

    // If choice is 3, do the following (PRINT REPORT)
    if (choice == 3)
    {
        float visa_average = 0, final_average = 0, homework1_average = 0, homework2_average = 0, end_grade_average = 0;
        int visa_sum = 0, final_sum = 0, homework1_sum = 0, homework2_sum = 0, end_grade_sum = 0;

        for (int i = 0; i < student_count; i++)
        {
            visa_sum = visa_sum + students[i].visa_result;
            final_sum = final_sum + students[i].final_result;
            homework1_sum = homework1_sum + students[i].homework1_result;
            homework2_sum = homework2_sum + students[i].homework2_result;
            end_grade_sum = end_grade_sum + students[i].end_grade;
        }

        visa_average = visa_sum / student_count;
        final_average = final_sum / student_count;
        homework1_average = homework1_sum / student_count;
        homework2_average = homework2_sum / student_count;
        end_grade_average =  end_grade_sum / student_count;

        FILE* file = fopen("CourseReport.txt", "w");

        fprintf(file, "Total Number of Students = %i\n\n", student_count);
        fprintf(file, "Visa Average = %.1f\n"
                    "Final Average = %.1f\n"
                    "Homework1 Average = %.1f\n"
                    "Homework2 Average = %.1f\n"
                    "End of Semester Average = %.1f",
                    visa_average, final_average, homework1_average, homework2_average, end_grade_average);

        fclose(file);
        return 0;
    }
}

// Get user choice
int get_num()
{
    int num = 0;
    printf("\n");
    puts("      MENU        ");
    puts("__________________");
    puts("1) ADDING STUDENT");
    puts("2) STUDENT SEARCH (BY NUMBER)");
    puts("3) PRINT REPORT");
    printf("\n>> ");
    scanf("%i", &num);
    printf("\n");
    return num;
}

// Add student info manuely
int get_info_manuel()
{
    char menu[1];
    printf("ENTER THE STUDENT INFORMATION\n\n");
    printf("STUDENT NUMBER: ");
    scanf("%i", &students[student_count].student_num);
    printf("NAME: ");
    scanf("%s", students[student_count].name);
    printf("SURNAME: ");
    scanf("%s", students[student_count].surname);
    printf("VISA RESULT: ");
    scanf("%i", &students[student_count].visa_result);
    printf("FINAL RESULT: ");
    scanf("%i", &students[student_count].final_result);
    printf("HOMEWORK1 RESULT: ");
    scanf("%i", &students[student_count].homework1_result);
    printf("HOMEWORK2 RESULT: ");
    scanf("%i", &students[student_count].homework2_result);

    students[student_count].end_grade = ((students[student_count].visa_result * 0.25) + (students[student_count].final_result * 0.40)
                                        + (students[student_count].homework1_result * 0.15) + (students[student_count].homework2_result * 0.20));

    printf("END OF SEMESTER GRADE: %.1f\n", students[student_count].end_grade);
    printf("\nPress the 'M' button to return to the main menu...\n");
    scanf("%s", menu);
    student_count++;

    if (menu[0] == 77 || menu[0] == 109)
        return 0;
    return 1;
}

// Find student data with student number and print these data
int search_student()
{
    char menu[1];
    int found = 1;
    int student_num;
    printf("\nENTER THE STUDENT NUMBER TO BE SEARCHED: ");
    scanf("%u", &student_num);

    for (int i = 0; i < student_count; i++)
    {
        if (student_num == students[i].student_num)
        {
            printf("\nSTUDENT NUMBER: %u", students[i].student_num);
            printf("\nNAME: %s", students[i].name);
            printf("\nSURNAME: %s", students[i].surname);
            printf("\nVISA RESULT: %i", students[i].visa_result);
            printf("\nFINAL RESULT: %i", students[i].final_result);
            printf("\nHOMEWORK1 RESULT: %i", students[i].homework1_result);
            printf("\nHOMEWORK2 RESULT: %i", students[i].homework2_result);
            printf("\nEND OF SEMESTER GRADE: %.1f", students[i].end_grade);
            found = 0;
        }
    }

    // If student found (0), ask for returning to menu
    if (found == 0)
    {
        printf("\nPress the 'M' button to return to the main menu...\n");
        scanf("%s", menu);

        if (menu[0] == 77 || menu[0] == 109)
            return 0;
        return 1;
    }

    // If student couldn't find (1), print 'kayıt bulunamadı' and ask for returning to menu
    printf("\nNO RECORDS FOUND!\n");
    printf("\nPress the 'M' button to return to the main menu...\n");
    scanf("%s", menu);

    if (menu[0] == 77 || menu[0] == 109)
       return 0;
    return 1;
}