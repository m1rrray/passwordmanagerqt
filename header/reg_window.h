/**
 * @file reg_window.h
 *
 * @brief This file contains the declaration of the Reg_window class.
 */

#ifndef REG_WINDOW_H
#define REG_WINDOW_H

#include <QDialog>

namespace Ui {
class Reg_window;
}

/**
 * @class Reg_window
 *
 * @brief The Reg_window class represents the registration window.
 */
class Reg_window : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a Reg_window object.
     *
     * @param parent The parent QDialog.
     */
    explicit Reg_window(QDialog *parent = nullptr);

    /**
     * @brief Destroys the Reg_window object.
     */
    ~Reg_window();

    /**
     * @brief Returns the entered name.
     *
     * @return The entered name.
     */
    QString getName();

    /**
     * @brief Returns the entered password.
     *
     * @return The entered password.
     */
    QString getPass();

    /**
     * @brief Checks if the entered password matches the confirmation password.
     *
     * @return True if the passwords match, false otherwise.
     */
    bool checkPass();

signals:
    /**
     * @brief Signal emitted when the register button is clicked.
     */
    void register_button_clicked2();

private slots:
    /**
     * @brief Slot called when the authenticate button is clicked.
     */
    void on_authbutton_2_clicked();

    /**
     * @brief Slot called when the login text is edited.
     *
     * @param arg1 The edited text.
     */
    void on_login_2_textEdited(const QString &arg1);

    /**
     * @brief Slot called when the password text is edited.
     *
     * @param arg1 The edited text.
     */
    void on_pass_3_textEdited(const QString &arg1);

    /**
     * @brief Slot called when the confirmation text is edited.
     *
     * @param arg1 The edited text.
     */
    void on_confirmation_textEdited(const QString &arg1);

private:
    Ui::Reg_window *ui; /**< The user interface object. */
    QString m_userName; /**< The entered username. */
    QString m_userPass; /**< The entered password. */
    QString m_confirmation; /**< The entered confirmation password. */
};

#endif // REG_WINDOW_H
