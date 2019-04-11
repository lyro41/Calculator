#ifndef TRACETABLE_H
#define TRACETABLE_H

#include <QDialog>
#include <QStandardItemModel>
#include <vector>
#include <string>
#include <algorithm>

typedef unsigned long long ull;



extern void stoull_list(std::string field, std::vector<ull> &list);


extern void command_separate(std::string field, std::vector<ull> &add, std::vector<ull> &mult, std::vector<ull> &pow);


extern ull calculate(ull start, ull final, std::vector<ull> &exceptions, std::vector<ull> &checkpoints, std::vector<ull> &add, std::vector<ull> &mult);


extern int getColumnQuantity(ull &start, ull &final);



namespace Ui {
class TraceTable;
}

class TraceTable : public QDialog
{
    Q_OBJECT

public:
    explicit TraceTable(QWidget *parent = nullptr, int columns = 1, ull start = 1, ull final = 1);
    ~TraceTable();

private:
    Ui::TraceTable *ui;
    QStandardItemModel *model;
};

#endif // TRACETABLE_H
