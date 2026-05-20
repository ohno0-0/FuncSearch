// src/PathManager.cpp
#include "PathManager.h"
#include <QDir>
#include <QDirIterator>

PathManager& PathManager::instance() {
    static PathManager pm;
    return pm;
}

void PathManager::addPath(const QString& path) {
    if (!m_paths.contains(path)) {
        m_paths.append(path);
    }
}

void PathManager::removePath(const QString& path) {
    m_paths.removeAll(path);
}

QStringList PathManager::getPaths() const {
    return m_paths;
}

void PathManager::refreshFiles() {
    m_files.clear();
    for (const QString& path : m_paths) {
        QDir dir(path);
        if (dir.exists()) {
            // 递归查找所有 txt 文件
            QStringList filters;
            filters << "*.txt";
            QDirIterator it(dir.absolutePath(), filters, QDir::Files, QDirIterator::Subdirectories);
            while (it.hasNext()) {
                m_files.append(it.next());
            }
        }
    }
}

QStringList PathManager::getFileList() const {
    return m_files;
}

