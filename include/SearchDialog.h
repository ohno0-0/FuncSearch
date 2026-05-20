// include/SearchDialog.h
#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include "FuncSearchEngine.h"

class SearchDialog : public QDialog {
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr);

private slots:
    void onSearchTriggered();
    void onItemClicked(QListWidgetItem* item);

private:
    QLineEdit* m_searchEdit;
    QListWidget* m_listWidget;
    QTextEdit* m_descEdit;
};

#endif // SEARCHDIALOG_H

