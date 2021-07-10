/**
 * Copyright (c) @UG-SEP. All right reserved
 * Licensed under MIT
 *
 * @brief mainwindow.h
 * This file is the header file of the mainwindow.cpp it contain the function declaration and some variables
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QCloseEvent>
#include "contact_help.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionFind_triggered();

    void on_actionSelect_All_triggered();

    void on_actionFind_Replace_triggered();

    void on_actionFind_Next_triggered();

    void on_actionFind_Previous_triggered();

    void on_actionTime_Date_triggered();

    void on_actionStatusbar_triggered();

    void on_actionTool_Bar_triggered();

    void on_actionText_Color_triggered();

    void on_actionBackground_Color_triggered();

    void on_actionLeft_triggered();

    void on_actionRight_triggered();

    void on_actionCenter_triggered();

    void on_actionJustify_triggered();

    void on_actionFont_triggered();

    void on_actionBackground_Color_2_triggered();

    void on_actionLower_Roman_triggered();

    void on_actionUpper_Roman_triggered();

    void on_actionDecimal_triggered();

    void on_actionLower_Alphabet_triggered();

    void on_actionUpperAlphabet_triggered();

    void on_actionDisc_triggered();

    void on_actionCircle_triggered();

    void on_actionSquare_triggered();

    void on_actionInsert_Table_triggered();

    void on_actionInsert_Image_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionmargin_triggered();

    void on_actionApply_Markdown_triggered();

    void on_actionApply_Html_triggered();

    void on_actionCustom_triggered();

    void on_actionLetter_triggered();

    void on_actionTabloid_triggered();

    void on_actionA4_triggered();

    void on_actionA5_triggered();

    void on_actionA3_triggered();

    void on_actionB4_triggered();

    void on_actionB5_triggered();

    void on_actionPrint_triggered();

    void on_actionWord_Spacing_triggered();

    void on_actionLetter_2_triggered();

    void on_actionWord_Wrap_triggered();

    void on_actionLine_Wrap_triggered();

    void on_actionReading_Mode_triggered();

    void on_actionExport_in_PDF_triggered();

    void on_actionContact_Support_triggered();

    QString removeImageTag(QString);

    void ReadImage();

    QString AddBr(QString);

    void on_actionOpen_txt_file_triggered();

    void on_actionExport_in_HTML_triggered();

    void on_actionExport_in_Markdown_triggered();

    void on_actionExport_in_TXT_triggered();

private:
    Ui::MainWindow *ui;
    QString file_path;
    QString file_name="Untitled";
    QString stylesheet;
    QString Markdown;
    QString universal_text = "Type here";
    QString Html;
    QString Image;
    Contact_Help contact;
protected:
   void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
