/**
 * @file auth_window.h
 *
 * @brief This file contains the declaration of the Auth_Window class.
 */

#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H

#include <QDialog>

namespace Ui {
class Auth_Window;
}

/**
 * @class Auth_Window
 *
 * @brief The Auth_Window class represents the authentication window of the application.
 */
class Auth_Window : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs an Auth_Window object.
     *
     * @param parent The parent QDialog.
     */
    explicit Auth_Window(QDialog *parent = nullptr);

    /**
     * @brief Destroys the Auth_Window object.
     */
    ~Auth_Window();

    /**
     * @brief Retrieves the login entered by the user.
     *
     * @return The login entered by the user.
     */
    QString getLogin();

    /**
     * @brief Retrieves the password entered by the user.
     *
     * @return The password entered by the user.
     */
    QString getPass();

    /**
     * @brief Clears the login and password fields.
     */
    void clearFields();

signals:
    /**
     * @brief Signal emitted when the login button is clicked.
     */
    void login_button_clicked();

    /**
     * @brief Signal emitted when the register button is clicked.
     */
    void register_button_clicked();

private slots:
    /**
     * @brief Slot called when the login text is edited.
     *
     * @param arg1 The edited text.
     */
    void on_login_textEdited(const QString &arg1);

    /**
     * @brief Slot called when the password text is edited.
     *
     * @param arg1 The edited text.
     */
    void on_pass_textEdited(const QString &arg1);

    /**
     * @brief Slot called when the authentication button is clicked.
     */
    void on_authbutton_clicked();

    /**
     * @brief Slot called when the registration button is clicked.
     */
    void on_regbutton_clicked();


private:
    Ui::Auth_Window *ui; /**< The user interface object. */
    QString m_username; /**< The entered username. */
    QString m_userpass; /**< The entered user password. */
};

#endif // AUTH_WINDOW_H
