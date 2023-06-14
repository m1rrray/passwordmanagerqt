#include "newpasswordform.h"
#include "ui_newpasswordform.h"

newpasswordform::newpasswordform(MainWindow* mainWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newpasswordform),
    m_mainWindow(mainWindow)
{
    ui->setupUi(this);
}

newpasswordform::~newpasswordform()
{
    delete ui;
}

void newpasswordform::on_addnewpassword_clicked()
{
    // Обработчик нажатия кнопки "Добавить пароль"

    // Получение значения полей ввода
    QString username = ui->username->text();
    QString password = ui->password->text();

    // Вызов функции для добавления пароля в таблицу
    bool success = m_mainWindow->addPasswordToTable(m_mainWindow->getCurrentUsername(), username, password);

    if (success) {
        // Пароль успешно добавлен
        qDebug() << "Password added to table: " << username << " " << password;
        // Можно добавить дополнительную логику здесь, например, обновление списка паролей пользователя
    } else {
        // Возникла ошибка при добавлении пароля
        qDebug() << "Failed to add password to table: " << username << " " << password;
    }

    // Закрытие окна после добавления пароля
    close();
}

