/**
 * Copyright (c) @UG-SEP. All right reserved
 * Licensed under MIT
 *
 * @brief contact_help.cpp
 *
 * This file contain contact help features
 */
#include "contact_help.h"
#include "ui_contact_help.h"

Contact_Help::Contact_Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contact_Help)
{
    ui->setupUi(this);
}

Contact_Help::~Contact_Help()
{
    delete ui;
}
