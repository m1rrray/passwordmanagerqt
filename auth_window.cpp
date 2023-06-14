#include "auth_window.h"
#include "ui_auth_window.h"

Auth_Window::Auth_Window(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Auth_Window)
{
    ui->setupUi(this);
}

Auth_Window::~Auth_Window()
{
    delete ui;
}

void Auth_Window::on_login_textEdited(const QString &arg1)
{
    // Слот вызывается при изменении текста поля логина
    // Обновляет значение переменной m_username
    Auth_Window::m_username = arg1;
}

void Auth_Window::on_pass_textEdited(const QString &arg1)
{
    // Слот вызывается при изменении текста поля пароля
    // Обновляет значение переменной m_userpass
    Auth_Window::m_userpass = arg1;
}

void Auth_Window::on_authbutton_clicked()
{
    // Слот вызывается при нажатии кнопки аутентификации
    // Имитирует сигнал login_button_clicked
    emit login_button_clicked();
}

void Auth_Window::on_regbutton_clicked()
{
    // Слот вызывается при нажатии кнопки регистрации
    // Имитирует сигнал register_button_clicked
    emit register_button_clicked();
}

QString Auth_Window::getLogin()
{
    // Возвращает текущее значение логина
    return Auth_Window::m_username;
}

QString Auth_Window::getPass()
{
    // Возвращает текущее значение пароля
    return Auth_Window::m_userpass;
}

void Auth_Window::clearFields()
{
    // Очищает поля логина и пароля
    ui->login->clear();
    ui->pass->clear();
}
