#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include <stdlib.h>

struct Expense
{
    char description[100];
    char category[50];
    float amount;
    char date[50];
};

void add_expense(struct Expense **expenses, int *count, int *capacity);
void view_expenses(struct Expense *expenses, int count);
void save_expenses(struct Expense *expenses, int count);
void monthly_summary(struct Expense *expenses, int count);
void get_current_datetime(char *buffer, int size);

int main()
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);

    struct Expense *expenses = NULL;
    int highlight = 0;
    int choice = 0;

    int expense_count = 0;
    int capacity = 2;

    expenses = malloc(capacity * sizeof(struct Expense));

    char *options[] = {
        "1. Add Expenses",
        "2. View Expense", 
        "3. Save", 
        "4. View Monthly Summary", 
        "5. Exit"};
    
    while(1)
    {
        box(stdscr, 0, 0);
        mvprintw(1, 2, "Expense Tracker! 💰");

        for(int i = 0; i < 5; i++)
        {
            if(i == highlight)
            {
                attron(A_REVERSE);
                mvprintw(3 + i, 2, "%s", options[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(3 + i, 2, "%s", options[i]);
            }
        }

        refresh();
        choice = getch();

        if (choice == KEY_UP)
        {
            highlight--;
            if(highlight < 0) highlight = 0;
        }
        else if(choice == KEY_DOWN)
        {
            highlight++;
            if (highlight > 4) highlight = 3;
        }
        else if(choice == '\n' || choice == '\r')
        {
            if(highlight == 0)
            {
                clear();
                add_expense(&expenses, &expense_count, &capacity);
                clear();
            }
            if(highlight == 1)
            {
                clear();
                view_expenses(expenses, expense_count);
                clear();
            }
            if(highlight == 2)
            {
                clear();
                save_expenses(expenses, expense_count);
                clear();
            }
            if(highlight == 3)
            {
                clear();
                monthly_summary(expenses, expense_count);
                clear();
            }
            if(highlight == 4)
            {
                break;
            }
        }
    }   
    endwin();
    printf("goodBye!!\n");
    return 0;
}

void add_expense(struct Expense **expenses, int *count, int *capacity)
{
    if(*count == *capacity)
    {
        *capacity *= 2;

        struct Expense *temp = realloc(*expenses, *capacity * sizeof(struct Expense));
        if(temp == NULL)
        {
            printf("Memory allction faild\n");
            return;
        }
        *expenses = temp;
    }

    echo();
    curs_set(1);

    char description[100];
    char category[100];
    float amount;

    mvprintw(2, 2, "Enter the category: ");
    getstr(category);

    mvprintw(3, 2, "Enter the description: ");
    getstr(description);

    mvprintw(4, 2, "Enter the amount: ");
    scanw("%f", &amount);

    noecho();
    curs_set(0);

    strcpy((*expenses)[*count].category, category);
    strcpy((*expenses)[*count].description, description);
    (*expenses)[*count].amount = amount;

    get_current_datetime((*expenses)[*count].date, 50);
    
    (*count)++;
    
    mvprintw(6, 2, "Expense added!");
    refresh();
    getch();

}

void get_current_datetime(char *buffer, int size)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

void view_expenses(struct Expense *expenses, int count)
{
    box(stdscr, 0, 0);
    mvprintw(1, 2, "View Expense");
    mvprintw(2, 2, "=================");
    int row = 4;

    if(count == 0)
    {
        mvprintw(4, 2, "There is no Expense add yet");
    }

    else
    {
        for(int i = 0; i < count; i++)
        {
            mvprintw(row, 2, "Category: %s", expenses[i].category);
            row++;
            mvprintw(row, 2, "Description: %s", expenses[i].description);
            row++;
            mvprintw(row, 2, "Spent: $%.2f", expenses[i].amount);
            row++;
            mvprintw(row, 2, "Date: %s", expenses[i].date);
            row++;
            mvprintw(row, 2, "=========================");
            row++;
        }
    }
    
    mvprintw(row + 2, 2, "Press any key to return...");
    refresh();
    getch();
}

void save_expenses(struct Expense *expenses, int count)
{
    FILE *file = fopen("save_expenses.txt", "w");

    if(count == 0) return;

    for(int i = 0; i < count; i++)
    {
        fprintf(file, "====================================\n");
        fprintf(file, "Expense #%d\n", i + 1);
        fprintf(file, "====================================\n");
        fprintf(file, "Description: %s\n", expenses[i].description);
        fprintf(file, "Category: %s\n", expenses[i].category);
        fprintf(file, "Amount: %.2f\n", expenses[i].amount);
        fprintf(file, "Date: %s\n", expenses[i].date);
        fprintf(file, "====================================\n");
    }
    
    fclose(file);
    mvprintw(10, 2, "✅ %d expenses saved!", count);
    refresh();
    getch();
}

void monthly_summary(struct Expense *expenses, int count)
{
    box(stdscr, 0, 0);
    mvprintw(1, 2, "Monthly Summary");
    mvprintw(2, 2, "====================================");
    
    if(count == 0) return;
    
    float total_spending = 0.0f;
    
    for (int i = 0; i < count; i++)
    {
        total_spending += expenses[i].amount;
    }
    
    float average = total_spending / count;
    
    mvprintw(4, 2, "Total expenses: %d", count);
    mvprintw(5, 2, "Total spending: $%.2f", total_spending);
    mvprintw(6, 2, "Average per expense: $%.2f", average);
    
    mvprintw(8, 2, "Press any key to return...");
    refresh();
    getch();
}
