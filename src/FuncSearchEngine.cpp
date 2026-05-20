// src/FuncSearchEngine.cpp
#include "FuncSearchEngine.h"
#include "PathManager.h"
#include <QFile>
#include <QTextStream> // 确保包含此头文件
#include <QFileInfo>
#include <QTextCodec>  // <-- 新增此头文件
#include <algorithm>
#include <QDebug>

FuncSearchEngine& FuncSearchEngine::instance() {
    static FuncSearchEngine engine;
    return engine;
}

void FuncSearchEngine::loadDatabase() {
    m_database.clear();
    PathManager::instance().refreshFiles();
    QStringList files = PathManager::instance().getFileList();

    for (const QString& filePath : files) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            // ===== 新增：强制指定流使用 UTF-8 解码 =====
            in.setCodec("UTF-8"); 
            // ==========================================

            QString content = in.readAll();
            file.close();

            QFileInfo info(filePath);
            SearchResult res;
            res.title = info.baseName(); // 文件名作为功能名
            res.filePath = filePath;
            res.content = content;
            res.score = 0;
            m_database.append(res);
        }
    }
}

QList<SearchResult> FuncSearchEngine::search(const QString& query) {
    QList<SearchResult> results;
    
    if (query.isEmpty()) {
        // 如果搜索词为空，返回所有功能列表
        results = m_database;
        for (auto& res : results) res.score = 0;
         qDebug()<< "搜索词为空!";
        return results;
    }

    qDebug()<< "搜索开始!";
    for (const SearchResult& res : m_database) {
        // 对标题和内容分别打分，标题权重更高
        int titleScore = calculateScore(query, res.title) * 3;
        int contentScore = calculateScore(query, res.content);
        int totalScore = titleScore + contentScore;

        if (totalScore > 0) {
            SearchResult matchedRes = res;
            matchedRes.score = totalScore;
            results.append(matchedRes);
        }
    }

    // 按得分降序排序
    std::sort(results.begin(), results.end(), [](const SearchResult& a, const SearchResult& b) {
        return a.score > b.score;
    });

    return results;
}

int FuncSearchEngine::calculateScore(const QString& query, const QString& target) const {
    int score = 0;
    int queryIdx = 0;
    int lastMatchIdx = -2;

    for (int i = 0; i < target.length() && queryIdx < query.length(); ++i) {
        if (query[queryIdx].toLower() == target[i].toLower()) {
            // 基础分
            score += 10;

            // 连续性加分 (紧挨着匹配得分更高)
            if (i == lastMatchIdx + 1) {
                score += 20;
            }

            // 边界加分 (单词首字母或符号后匹配得分更高)
            if (i == 0 || target[i-1].isSpace() || target[i-1].isPunct()) {
                score += 15;
            }

            lastMatchIdx = i;
            queryIdx++;
        }
    }

    // 必须完整匹配所有查询字符才算模糊匹配成功
    return (queryIdx == query.length()) ? score : 0;
}

