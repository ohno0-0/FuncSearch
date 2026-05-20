// include/PathManager.h
#ifndef PATHMANAGER_H
#define PATHMANAGER_H

#include <QString>
#include <QStringList>
#include <QDir>

class PathManager {
public:
    static PathManager& instance();

    // 添加搜索路径
    void addPath(const QString& path);
    // 移除搜索路径
    void removePath(const QString& path);
    // 获取所有管理的路径
    QStringList getPaths() const;
    // 扫描所有路径下的文本文件
    void refreshFiles();

    // 获取当前扫描到的所有文件路径
    QStringList getFileList() const;

private:
    PathManager() = default;
    QStringList m_paths;
    QStringList m_files;
};

#endif // PATHMANAGER_H

