#include "resultwindow.h"
#include "ui_resultwindow.h"

extern std::vector<ull> trace;

ResultWindow::ResultWindow(QWidget *parent, ull start_value, ull final_value) :
    QDialog(parent),
    ui(new Ui::ResultWindow)
{
    ui->setupUi(this);

    start = start_value;
    final = final_value;
}

ResultWindow::~ResultWindow()
{
    delete ui;
}

void ResultWindow::ResultReset(unsigned long long result)
{
    ui->ResultField->setText(QString::number(result));
}

void ResultWindow::on_ShowTable_clicked()
{
    tb = new TraceTable(this, ((static_cast<int> (final)) - (static_cast<int> (start)) + 1), start, final);
    tb->show();
}
