#include "reg_window.h"
#include "ui_reg_window.h"

Reg_window::Reg_window(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Reg_window)
{
    ui->setupUi(this);
}

Reg_window::~Reg_window()
{
    delete ui;
}

void Reg_window::on_authbutton_2_clicked()
{
    // Обработчик нажатия кнопки "Зарегистрироваться"
    emit register_button_clicked2();
}

void Reg_window::on_login_2_textEdited(const QString &arg1)
{
    // Слот вызывается при изменении текста поля ввода имени пользователя
    // Обновление значения переменной m_userName
    Reg_window::m_userName = arg1;
}

void Reg_window::on_pass_3_textEdited(const QString &arg1)
{
    // Слот вызывается при изменении текста поля ввода пароля
    // Обновление значения переменной m_userPass
    Reg_window::m_userPass = arg1;
}

void Reg_window::on_confirmation_textEdited(const QString &arg1)
{
    // Слот вызывается при изменении текста поля ввода подтверждения пароля
    // Обновление значения переменной m_confirmation
    Reg_window::m_confirmation = arg1;
}

QString Reg_window::getName()
{
    // Получение значения имени пользователя
    return m_userName;
}

QString Reg_window::getPass()
{
    // Получение значения пароля
    return m_userPass;
}

bool Reg_window::checkPass()
{
    // Проверка совпадения пароля и подтверждения пароля
    return (m_confirmation == m_userPass);
}
