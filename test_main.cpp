// test_main.cpp
#include <QApplication>
#include <QTextCodec>
#include "SearchDialog.h"
#include "PathManager.h"
#include "FuncSearchEngine.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

     // ===== 新增：设置 Qt 全局默认编码为 UTF-8 =====
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    // ==========================================

    // 1. 配置路径管理器
    // 获取可执行文件所在目录
    QString appDir = QCoreApplication::applicationDirPath();
    QString txtPath = appDir + "/resource/FuncFiles";

    PathManager::instance().addPath(txtPath); 

    // 2. 引擎加载数据库
    FuncSearchEngine::instance().loadDatabase();

    // 3. 弹出搜索引擎对话框
    SearchDialog dialog;
    dialog.exec();

    return 0;
}

