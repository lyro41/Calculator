#include "mainwindow.h"
#include <QApplication>

std::vector<ull> trace(0);



void stoull_list(std::string field, std::vector<ull> &list)
{
    field += " ";
    while (field != "")
    {
        ull space = field.find(' ');
        list.push_back(stoull(field.substr(0, space)));
        field = field.substr(space + 1, field.length() - space - 1);
    }
    stable_sort(list.begin(), list.end());
}


void command_separate(std::string field, std::vector<ull> &add, std::vector<ull> &mult, std::vector<ull> &pow)
{
    field += " ";
    while (field != "")
    {
        ull space = field.find(' ');
        if (field[0] == '+') add.push_back(stoull(field.substr(1, space)));
        else if (field[0] == '*') mult.push_back(stoull(field.substr(1, space)));
        else if (field[0] == '^') pow.push_back(stoull(field.substr(1, space)));
        field = field.substr(space + 1, field.length() - space - 1);
    }
    stable_sort(add.begin(), add.end());
    stable_sort(mult.begin(), mult.end());
    stable_sort(pow.begin(), pow.end());
}


ull calculate(ull start, ull final, std::vector<ull> &exceptions, std::vector<ull> &checkpoints, std::vector<ull> &add, std::vector<ull> &mult)
{
    trace.resize(0);
    trace.resize(final + 1);
    trace[start] = 1;
    ull k = 0;
    ull min_it;
    if (add.size() == 0) min_it = start * mult[0];
    else if (mult.size() == 0) min_it = start + add[0];
    else min_it = std::min(start + add[0], start * mult[0]);
    if (checkpoints.size() == 0)
    {
        for (ull i = min_it; i <= final; ++i)
        {
            if (k < exceptions.size() && i == exceptions[k]) ++k;
            else
            {
                for (ull j = 0; j < add.size(); ++j) if (i >= add[j]) trace[i] += trace[i - add[j]];
                for (ull j = 0; j < mult.size(); ++j) if (i % mult[j] == 0) trace[i] += trace[i / mult[j]];
            }
        }
    }
    else
    {
        for (ull i = min_it; i <= checkpoints[0]; ++i)
        {
            if (k < exceptions.size() && i == exceptions[k]) ++k;
            else
            {
                for (ull j = 0; j < add.size(); ++j) if (i >= add[j]) trace[i] += trace[i - add[j]];
                for (ull j = 0; j < mult.size(); ++j) if (i % mult[j] == 0) trace[i] += trace[i / mult[j]];
            }
        }
        for (ull t = 0; t < checkpoints.size() - 1; ++t)
        {
            for (ull i = std::min(checkpoints[t] + add[0], checkpoints[t] * mult[0]); i <= checkpoints[t + 1]; ++i)
            {
                if (k < exceptions.size() && i == exceptions[k]) ++k;
                else
                {
                    for (ull j = 0; j < add.size(); ++j) if (i >= add[j] && i - add[j] >= checkpoints[t]) trace[i] += trace[i - add[j]];
                    for (ull j = 0; j < mult.size(); ++j) if (i % mult[j] == 0 && i / mult[j] >= checkpoints[t]) trace[i] += trace[i / mult[j]];
                }
            }
        }

        for (ull i = std::min(checkpoints[checkpoints.size() - 1] + add[0], checkpoints[checkpoints.size() - 1] * mult[0]); i <= final; ++i)
        {
            if (k < exceptions.size() && i == exceptions[k]) ++k;
            else
            {
                for (ull j = 0; j < add.size(); ++j) if (i >= add[j] && i - add[j] >= checkpoints[checkpoints.size() - 1]) trace[i] += trace[i - add[j]];
                for (ull j = 0; j < mult.size(); ++j) if (i % mult[j] == 0 && i / mult[j] >= checkpoints[checkpoints.size() - 1]) trace[i] += trace[i / mult[j]];
            }
        }
    }

    return trace[final];
}


int getColumnQuantity(ull &start, ull &final, std::vector<ull> &trace)
{
    int column = 0;
    for (ull i = start; i <= final; ++i) if (trace[i] != 0) ++column;
    return column;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
