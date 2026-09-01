# 💰 Expense Tracker

A simple expense tracker written in C with ncurses GUI.

## ✨ Features

- ✅ Add expenses (description, category, amount)
- ✅ Auto-capture date and time
- ✅ View all expenses
- ✅ Monthly summary
- ✅ Total spending calculation
- ✅ Average per expense
- ✅ Save to file
- ✅ ncurses GUI with arrow key navigation

## 🚀 How to Compile

```bash
gcc -Wall -Wextra -o expense_tracker main.c -lncurses
```
## 🏃 How to Run
```bash
./expense_tracker
```
## 📁 File Format

Expenses are saved in save_expenses.txt:
```text
====================================
Expense #1
====================================
Description: Grocery shopping
Category: Food
Amount: $25.50
Date: 2026-09-01 14:30:25
====================================
```
