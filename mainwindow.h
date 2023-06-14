/**
 * @file mainwindow.h
 *
 * @brief This file contains the declaration of the MainWindow class.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QtSql/QtSql>
#include "auth_window.h"
#include "reg_window.h"
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 *
 * @brief The MainWindow class represents the main window of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a MainWindow object.
     *
     * @param parent The parent QWidget.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroys the MainWindow object.
     */
    ~MainWindow();

    /**
     * @brief Displays the main window only if authentication is successful.
     */
    void display();

    /**
     * @brief Establishes a connection to the database.
     *
     * @return True if the connection is successful, false otherwise.
     */
    bool connectDB();

    /**
     * @brief Retrieves the current username.
     *
     * @return The current username.
     */
    QString getCurrentUsername() const;

    /**
     * @brief Adds a password to the "passwords" table in the database.
     *
     * @param name     The name of the user.
     * @param username The username.
     * @param password The password.
     * @return True if the password is successfully added, false otherwise.
     */
    bool addPasswordToTable(const QString& name, const QString& username, const QString& password);

    /**
     * @brief Updates the password list displayed in the main window.
     */
    void updatePasswordList();

private:
    Ui::MainWindow *ui_Main; /**< The user interface object. */
    Auth_Window ui_Auth; /**< The instance of the authentication window. */
    Reg_window ui_Reg; /**< The instance of the registration window. */
    QString m_username; /**< The current username. */
    QString m_userpass; /**< The current user password. */
    QString db_input; /**< The input string for database queries. */
    QSqlDatabase mw_db; /**< The database connection object. */

    QPoint m_dragPosition;

    int user_counter; /**< The counter for user records. */
    bool m_loginSuccesfull; /**< Flag indicating successful login. */

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    /**
     * @brief Slot for authorizing the user.
     */
    void authorizeUser();

    /**
     * @brief Slot for showing the registration window.
     */
    void registerWindowShow();

    /**
     * @brief Slot for registering a new user.
     */
    void registerUser();

    /**
     * @brief Slot for handling the "Add New Password" button click.
     */
    void on_addnewpass_clicked();

    /**
     * @brief Slot for handling the "Logout" button click.
     */
    void on_logout_clicked();

    /**
     * @brief Slot for handling the "Delete Password" button click.
     */
    void on_delpass_clicked();
};

#endif // MAINWINDOW_H
