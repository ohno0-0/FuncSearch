// include/FuncSearchEngine.h
#ifndef FUNCSEARCHENGINE_H
#define FUNCSEARCHENGINE_H

#include <QString>
#include <QList>
#include <QPair>

struct SearchResult {
    QString title;      // 文件名（功能名）
    QString filePath;   // 文件路径
    QString content;    // 功能描述内容
    int score;          // 匹配得分
};

class FuncSearchEngine {
public:
    static FuncSearchEngine& instance();

    // 加载资料库
    void loadDatabase();
    // 执行搜索
    QList<SearchResult> search(const QString& query);

private:
    FuncSearchEngine() = default;
    
    // 模糊匹配打分算法 (子序列匹配)
    int calculateScore(const QString& query, const QString& target) const;
    
    QList<SearchResult> m_database;
};

#endif // FUNCSEARCHENGINE_H

