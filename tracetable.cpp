#include "tracetable.h"
#include "ui_tracetable.h"

extern std::vector<ull> trace;

TraceTable::TraceTable(QWidget *parent, int columns, ull start, ull final) :
    QDialog(parent),
    ui(new Ui::TraceTable)
{
    ui->setupUi(this);

    model = new QStandardItemModel(1, columns, this);

    ui->table->setModel(model);

    QModelIndex index;

    for (ull i = start; i <= final; ++i)
    {
        model->setHeaderData(static_cast<int>(i - start), Qt::Horizontal, QString::number(i));

        index = model->index(0, static_cast<int>(i - start));
        model->setData(index, QString::number(trace[i]));
    }

    model->setHeaderData(0, Qt::Vertical, "result");

}

TraceTable::~TraceTable()
{
    delete ui;
}
