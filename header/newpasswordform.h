/**
 * @file newpasswordform.h
 *
 * @brief This file contains the declaration of the newpasswordform class.
 */

#ifndef NEWPASSWORDFORM_H
#define NEWPASSWORDFORM_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class newpasswordform;
}

/**
 * @class newpasswordform
 *
 * @brief The newpasswordform class represents the form for adding a new password.
 */
class newpasswordform : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a newpasswordform object.
     *
     * @param mainWindow Pointer to the MainWindow object.
     * @param parent The parent QWidget.
     */
    explicit newpasswordform(MainWindow* mainWindow, QWidget *parent = nullptr);

    /**
     * @brief Destroys the newpasswordform object.
     */
    ~newpasswordform();

private slots:
    /**
     * @brief Slot called when the add new password button is clicked.
     */
    void on_addnewpassword_clicked();



private:
    Ui::newpasswordform *ui; /**< The user interface object. */
    MainWindow* m_mainWindow; /**< Pointer to the MainWindow object. */
};

#endif // NEWPASSWORDFORM_H
