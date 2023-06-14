#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Создание и установка переводчика для локализации пользовательского интерфейса
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "PasswordManagerInCreator_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // Создание экземпляра главного окна и отображение его содержимого
    MainWindow w;
    w.display();

    // Запуск основного цикла приложения
    return a.exec();
}

