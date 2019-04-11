#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>
#include "tracetable.h"

namespace Ui {
class ResultWindow;
}

class ResultWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ResultWindow(QWidget *parent = nullptr, ull start_value = 1, ull final_value = 1);
    ~ResultWindow();
    void ResultReset(unsigned long long result);

private slots:
    void on_ShowTable_clicked();

private:
    ull start, final;
    Ui::ResultWindow *ui;
    TraceTable *tb;

};

#endif // RESULTWINDOW_H
