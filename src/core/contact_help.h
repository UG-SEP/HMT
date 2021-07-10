/**
 * Copyright (c) @UG-SEP. All right reserved
 * Licensed under MIT
 *
 * @brief contact_help.h
 *
 * This is a header file of contact_help.cpp
 */
#ifndef CONTACT_HELP_H
#define CONTACT_HELP_H

#include <QDialog>

namespace Ui {
class Contact_Help;
}

class Contact_Help : public QDialog
{
    Q_OBJECT

public:
    explicit Contact_Help(QWidget *parent = nullptr);
    ~Contact_Help();

private:
    Ui::Contact_Help *ui;
};

#endif // CONTACT_HELP_H
