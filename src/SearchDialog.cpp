// src/SearchDialog.cpp
#include "SearchDialog.h"
#include <QSplitter>
#include <QDebug>

SearchDialog::SearchDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("搜索引擎");//Func Search Engine
    resize(600, 500);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // 搜索栏
    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("输入文本进行搜索(按 Enter 键进行 )...");//Input text to search(press Enter )...
    mainLayout->addWidget(m_searchEdit);

    // 上下分割器：上面是列表，下面是描述
    QSplitter* splitter = new QSplitter(Qt::Vertical, this);
    m_listWidget = new QListWidget(this);
    m_descEdit = new QTextEdit(this);
    m_descEdit->setReadOnly(true);
    splitter->addWidget(m_listWidget);
    splitter->addWidget(m_descEdit);
    mainLayout->addWidget(splitter);

    // 信号槽连接
    // 文本改变时实时搜索
    connect(m_searchEdit, &QLineEdit::textChanged, this, &SearchDialog::onSearchTriggered);    

    // 2. 列表项被点击时展示描述
    connect(m_listWidget, &QListWidget::itemClicked, this, &SearchDialog::onItemClicked);
}

void SearchDialog::onSearchTriggered() {
    QString query = m_searchEdit->text().trimmed();

    qDebug() << "输入的关键词是:" << query << " , 长度:" << query.length();

    QList<SearchResult> results = FuncSearchEngine::instance().search(query);

    m_listWidget->clear();
    m_descEdit->clear();

    for (const SearchResult& res : results) {
        QListWidgetItem* item = new QListWidgetItem(m_listWidget);
        item->setText(QString("%1 (Score: %2)").arg(res.title).arg(res.score));
        item->setData(Qt::UserRole, res.content); // 将内容存储在 UserRole 中
    }

    if (!results.isEmpty()) {
        m_listWidget->setCurrentRow(0);
        onItemClicked(m_listWidget->item(0));
    }
}

void SearchDialog::onItemClicked(QListWidgetItem* item) {
    if (item) {
        QString content = item->data(Qt::UserRole).toString();
        m_descEdit->setText(content);
    }
}

