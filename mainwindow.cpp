#include "mainwindow.h"
#include "ui_mainwindow.h"

extern std::vector<ull> trace;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_CalculateButton_clicked()
{

    QString start = ui->StartValue->text();
    ull start_value = start.toULongLong();

    QString final = ui->FinalValue->text();
    ull final_value = final.toULongLong();

    std::vector<ull> toAdd_list(0);
    std::vector<ull> toMult_list(0);
    std::vector<ull> toPow_list(0);
    command_separate(ui->CommandList->text().toStdString(), toAdd_list, toMult_list, toPow_list);

    std::vector<ull> exceptions(0);
    if (ui->ExceptionSwitch->isChecked()) stoull_list(ui->ExceptionList->text().toStdString(), exceptions);

    std::vector<ull> checkpoints(0);
    if (ui->CheckpointSwitch->isChecked()) stoull_list(ui->CheckpointList->text().toStdString(), checkpoints);


    rw = new ResultWindow(this, start_value, final_value);
    rw->ResultReset(calculate(start_value, final_value, exceptions, checkpoints, toAdd_list, toMult_list));
    rw->show();
}
