#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "auth_window.h"
#include "reg_window.h"
#include <QtDebug>
#include "newpasswordform.h"
#include <QMouseEvent>

// Конструктор класса MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_Main(new Ui::MainWindow)
{
    // Инициализация переменных класса
    user_counter = 0;
    m_loginSuccesfull = false;

    // Установка соединений между сигналами и слотами
    connect(&ui_Auth, SIGNAL(login_button_clicked()), this, SLOT(authorizeUser()));
    connect(&ui_Auth, SIGNAL(destroyed()), this, SLOT(show()));
    connect(&ui_Auth, SIGNAL(register_button_clicked()), this, SLOT(registerWindowShow()));
    connect(&ui_Reg, SIGNAL(register_button_clicked2()), this, SLOT(registerUser()));
    connect(&ui_Reg, SIGNAL(destroyed()), &ui_Auth, SLOT(show()));

    // Подключение к базе данных
    if (!connectDB())
    {
        qDebug() << "Failed to connect DB";
    }

    // Установка флагов окна для фиксированного размера
    //    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    setFixedSize(800, 600);

    // Создание таблицы "userlist" в базе данных, если она не существует
    QSqlQuery query;
    db_input = "CREATE TABLE userlist ( "
               "number INTEGER PRIMARY KEY NOT NULL,"
               "name VARCHAR(20), "
               "pass VARCHAR(12), "
               "xpos INTEGER, "
               "ypos INTEGER, "
               "width INTEGER, "
               "length INTEGER );";

    if (!query.exec(db_input))
    {
        qDebug() << "Unable to create a table" << query.lastError();
    }

    // Создание таблицы "passwords" в базе данных, если она не существует
    QSqlQuery passwordsquery;
    QString db_output = "CREATE TABLE passwords ("
                        "name VARCHAR(20), "
                        "username VARCHAR(20), "
                        "password VARCHAR(12), "
                        "FOREIGN KEY (name) REFERENCES userlist(name)"
                        ")";
    passwordsquery.exec(db_output);

    // Вывод данных из таблицы "passwords" на консоль
    QSqlQuery query2;
    if (query2.exec("SELECT * FROM passwords"))
    {
        while (query2.next())
        {
            QString name = query2.value("name").toString();
            QString username = query2.value("username").toString();
            QString password = query2.value("password").toString();
            qDebug() << "Name:" << name << "Username:" << username << "Password:" << password;
        }
    }
    else
    {
        qDebug() << "Unable to retrieve data from passwords table:" << query2.lastError();
    }

    // Инициализация пользовательского интерфейса
    ui_Main->setupUi(this);
}

// Слот для авторизации пользователя
void MainWindow::authorizeUser()
{
    // Получение введенного логина и пароля из окна авторизации
    m_username = ui_Auth.getLogin();
    m_userpass = ui_Auth.getPass();

    QString str_t = " SELECT * "
                    " FROM userlist "
                    " WHERE name = '%1'";

    QString username = "";
    QString userpass = "";

    int xPos = 0;
    int yPos = 0;

    int width = 0;
    int length = 0;

    db_input = str_t.arg(m_username);

    QSqlQuery query;
    QSqlRecord rec;

    if (!query.exec(db_input))
    {
        qDebug() << "Unable to execute query - exiting" << query.lastError() << " : " << query.lastQuery();
    }
    rec = query.record();
    query.next();
    user_counter = query.value(rec.indexOf("number")).toInt();
    username = query.value(rec.indexOf("name")).toString();
    userpass = query.value(rec.indexOf("pass")).toString();

    // Проверка соответствия введенного логина и пароля
    if (m_username != username || m_userpass != userpass)
    {
        qDebug() << "Password missmatch" << username << " " << userpass;
        m_loginSuccesfull = false;
    }
    else
    {
        // Установка успешного входа в систему
        m_loginSuccesfull = true;
        xPos = query.value(rec.indexOf("xpos")).toInt();
        yPos = query.value(rec.indexOf("ypos")).toInt();
        width = query.value(rec.indexOf("width")).toInt();
        length = query.value(rec.indexOf("length")).toInt();
        ui_Auth.close();
        ui_Reg.close();
        this->setGeometry(xPos, yPos, width, length);
        this->show();
    }

    // Обновление списка паролей
    updatePasswordList();
}

// Слот для отображения окна регистрации
void MainWindow::registerWindowShow()
{
    ui_Auth.hide();
    ui_Reg.show();
}

// Слот для регистрации пользователя
void MainWindow::registerUser()
{
    if (ui_Reg.checkPass())
    {
        qDebug() << "lalalalallaa";
        QSqlQuery query;
        QSqlRecord rec;
        QString str_t = "SELECT COUNT(*) "
                        "FROM userlist;";
        db_input = str_t;
        if (!query.exec(db_input))
        {
            qDebug() << "Unable to get number " << query.lastError() << " : " << query.lastQuery();
            return;
        }
        else
        {
            query.next();
            rec = query.record();
            user_counter = rec.value(0).toInt();
            qDebug() << user_counter;
        }

        m_username = ui_Reg.getName();
        m_userpass = ui_Reg.getPass();
        user_counter++;

        // Вставка данных пользователя в таблицу "userlist"
        str_t = "INSERT INTO userlist(number, name, pass, xpos, ypos, width, length)"
                "VALUES(%1, '%2', '%3', %4, %5, %6, %7);";
        db_input = str_t.arg(user_counter)
                       .arg(m_username)
                       .arg(m_userpass)
                       .arg(0)
                       .arg(0)
                       .arg(800)
                       .arg(400);

        if (!query.exec(db_input))
        {
            qDebug() << "Unable to insert data" << query.lastError() << " : " << query.lastQuery();
        }
        else
        {
            ui_Reg.hide();
            ui_Auth.show();
        }
    }
    else
    {
        qDebug() << "Confirm password correctly";
    }
}

// Слот для отображения окна MainWindow
void MainWindow::display()
{
    ui_Auth.show();
}

// Деструктор класса MainWindow
MainWindow::~MainWindow()
{
    if (m_loginSuccesfull)
    {
        QString str_t = "UPDATE userlist "
                        "SET xpos = %2, ypos = %3, width = %4, length = %5 "
                        "WHERE name = '%1';";
        db_input = str_t.arg(m_username)
                       .arg(this->x())
                       .arg(this->y())
                       .arg(this->width())
                       .arg(this->height());
        QSqlQuery query;
        if (!query.exec(db_input))
        {
            qDebug() << "Unable to insert data" << query.lastError() << " : " << query.lastQuery();
        }
    }
    mw_db.removeDatabase("authorisation");
    qDebug() << "MainWindow Destroyed";
    delete ui_Main;
    exit(0);
}

// Функция для установки соединения с базой данных
bool MainWindow::connectDB()
{
    mw_db = QSqlDatabase::addDatabase("QSQLITE");
    mw_db.setDatabaseName("authorisation");
    if (!mw_db.open())
    {
        qDebug() << "Cannot open database: " << mw_db.lastError();
        return false;
    }
    return true;
}

// Функция для получения текущего имени пользователя
QString MainWindow::getCurrentUsername() const
{
    return m_username;
}

// Слот для добавления нового пароля
void MainWindow::on_addnewpass_clicked()
{
    newpasswordform* newPassWindow = new newpasswordform(this);
    newPassWindow->show();
}

// Функция для обновления списка паролей
void MainWindow::updatePasswordList()
{
    QString realusername = getCurrentUsername();

    QSqlQuery queryreal;
    QString db_input = "SELECT username, password FROM passwords WHERE name = :realusername";
    queryreal.prepare(db_input);
    queryreal.bindValue(":realusername", realusername);

    if (queryreal.exec())
    {
        ui_Main->listWidget->clear(); // Очистить список перед добавлением новых элементов
        while (queryreal.next())
        {
            QString realusername = queryreal.value("username").toString();
            QString password = queryreal.value("password").toString();
            QString itemText = QString("Username: %1, Password: %2").arg(realusername).arg(password);
            qDebug() << itemText;
            ui_Main->listWidget->addItem(itemText);
        }
    }
    else
    {
        qDebug() << "Unable to retrieve data from passwords table:" << queryreal.lastError();
    }
}

// Функция для добавления пароля в таблицу "passwords"
bool MainWindow::addPasswordToTable(const QString& name, const QString& username, const QString& password)
{
    QSqlQuery query;
    QString db_input = "INSERT INTO passwords (name, username, password) VALUES (:name, :username, :password)";
    query.prepare(db_input);
    query.bindValue(":name", name);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (query.exec())
    {
        updatePasswordList(); // Обновить список паролей после успешного добавления
        return true;
    }
    else
    {
        qDebug() << "Unable to add password to table:" << query.lastError();
        return false;
    }
}

// Слот для выхода из учетной записи
void MainWindow::on_logout_clicked()
{
    close();

    // Очистить поля формы авторизации (ui_Auth)
    ui_Auth.clearFields();

    // Открыть окно авторизации (AuthWindow)
    ui_Auth.show();
}

// Слот для удаления выбранного пароля из списка
void MainWindow::on_delpass_clicked()
{
    QListWidgetItem* selectedItem = ui_Main->listWidget->currentItem();
    if (selectedItem)
    {
        QString itemText = selectedItem->text();
        QRegularExpression regex("Username: (.*), Password: (.*)");
        QRegularExpressionMatch match = regex.match(itemText);
        if (match.hasMatch())
        {
            QString username = match.captured(1);
            QString password = match.captured(2);
            QString realusername = getCurrentUsername();

            QSqlQuery query;
            QString db_input = "DELETE FROM passwords WHERE name = :realusername AND username = :username AND password = :password";
            query.prepare(db_input);
            query.bindValue(":realusername", realusername);
            query.bindValue(":username", username);
            query.bindValue(":password", password);
            if (query.exec())
            {
                updatePasswordList(); // Обновить список паролей после успешного удаления
            }
            else
            {
                qDebug() << "Unable to delete password from table:" << query.lastError();
            }
        }
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Перехватываем событие нажатия кнопки мыши
    if (event->button() == Qt::LeftButton)
    {
        // Запоминаем начальные координаты нажатия
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Перехватываем событие перемещения мыши
    if (event->buttons() & Qt::LeftButton)
    {
        // Вычисляем новое положение окна на основе текущих координат мыши
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // Перехватываем событие отпускания кнопки мыши
    if (event->button() == Qt::LeftButton)
    {
        // Завершаем перемещение окна
        event->accept();
    }
}
