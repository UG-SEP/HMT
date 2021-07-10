/**
 * Copyright (c) @UG-SEP. All right reserved
 * Licensed under MIT
 *
 * @brief mainwindow.cpp
 *
 * This file is the main project which control every method used in the project
 *
 */
/** Includes all the library used in the project */
#include "mainwindow.h"

#include "ui_mainwindow.h"

#include<QFileDialog>

#include<QMessageBox>

#include<QTextEdit>

#include<QTextDocument>

#include<QDateTime>

#include<QColorDialog>

#include<QColor>

#include<QFont>

#include<QFontDialog>

#include<QImageReader>

#include<QLayout>

#include<QPrinter>

#include<QPrintDialog>

#include<QInputDialog>

#include<QMargins>

#include<QPainter>

#include "contact_help.h"

#include<QTextBlock>
 // constructor of MainWindow class
MainWindow::MainWindow(QWidget * parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui -> setupUi(this);
  // Add default action properties
  this -> setCentralWidget(ui -> textEdit);
  this -> setWindowTitle(file_name);
  ui -> actionTool_Bar -> setChecked(true);
  ui -> actionStatusbar -> setChecked(true);
  ui -> actionApply_Html -> setCheckable(true);
  ui -> actionApply_Markdown -> setCheckable(true);
  this -> setWindowIcon(QIcon(":/source/Img/HMT.jpg"));
  QPalette p = ui -> textEdit -> palette();
  ui -> textEdit -> setAlignment(Qt::AlignLeft);
  p.setColor(QPalette::Base, Qt::lightGray);
  ui -> textEdit -> setPalette(p);
  ui -> actionLetter -> setEnabled(false);
  ui -> actionTabloid -> setEnabled(false);
  ui -> actionA3 -> setEnabled(false);
  ui -> actionA4 -> setEnabled(false);
  ui -> actionA5 -> setEnabled(false);
  ui -> actionB4 -> setEnabled(false);
  ui -> actionB5 -> setEnabled(false);
}
// Destructor of MainWindow class
MainWindow::~MainWindow()
{
  delete ui;
}
/**
 * @brief MainWindow::on_actionNew_triggered()
 * Function which set the properties of action
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionNew_triggered()
{
  file_path = "";
  ui -> textEdit -> resize(maximumHeight(), maximumWidth());
  ui -> textEdit -> document() -> setDocumentMargin(0);
  ui -> textEdit -> setTextBackgroundColor("white");
  ui -> textEdit -> setTextColor("black");
  ui -> textEdit -> setText("");
  ui -> textEdit -> document() -> defaultStyleSheet();
  ui -> textEdit -> setAlignment(Qt::AlignLeft);
  QPalette p = ui -> textEdit -> palette();
  p.setColor(QPalette::Base, Qt::lightGray);
  ui -> textEdit -> setPalette(p);
  Image = "";
  Html = "";
  Markdown = "";
  stylesheet = "";
  file_name = "Untitled";
  this -> setWindowTitle(file_name);
}
/**
 * @brief MainWindow::ReadImage
 * This action readtheimage in .hmt file and open that image
 * @tparam void
 * @returns void
 */
void MainWindow::ReadImage()
{
  bool ok;
  int i = 0;
  QString file, char_line;
  int line;
  while (i < Image.size())
  {
    while (Image[i] != '|' && Image.size() > i)
    {
      file.append(Image[i]);
      i++;
    }
    i += 2;
    while (Image[i] != '$' && Image.size() > i)
    {
      char_line.append(Image[i]);
      i++;
    }
    i++;
    line = char_line.toInt( & ok, 10);
    QUrl Uri(QString("file://%1").arg(file));
    QImage image = QImageReader(file).read();
    QTextDocument * textDocument = ui -> textEdit -> document();
    textDocument -> addResource(QTextDocument::ImageResource, Uri, QVariant(image));
    QTextCursor cursor(ui -> textEdit -> document() -> findBlockByLineNumber(line - 1));
    ui -> textEdit -> setTextCursor(cursor);
    QTextImageFormat imageFormat;
    imageFormat.setWidth(image.width());
    imageFormat.setHeight(image.height());
    imageFormat.setName(Uri.toString());
    cursor.insertImage(imageFormat);
    if (Image[i] == '^')
      return;
    char_line = "";
    file = "";
  }
  Image.remove("^");
}
/**
 * @brief MainWindow::on_actionOpen_triggered
 * This Action open the .hmt extension file to access the data inside it
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionOpen_triggered()
{
  int i = 0;
  QString color;
  file_path = QFileDialog::getOpenFileName(this, "Open File", "C://");
  if (!file_path.isEmpty())
  {
    QFile file(file_path);
    QTextStream in ( & file);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
      ui -> textEdit -> setReadOnly(true);
      ui -> actionReading_Mode -> setChecked(true);
      on_actionReading_Mode_triggered();
      on_actionNew_triggered();
      QString text = in .readAll();
      while (text[i] != ' ')
      {
        color.append(text[i]);
        i++;
      }
      color.append(text[i]);
      i++;
      if (text[i] != '<')
      {
        while (text[i] != '^')
        {
          Image.append(text[i]);
          i++;
        }
        Image.append(text[i]);
        text = text.remove(Image);
        text = text.remove(color);
        ui -> textEdit -> setHtml(text);
        ReadImage();
      }
      else
      {
        text = text.remove(color);
        ui -> textEdit -> setHtml(text);
      }
      color = color.remove(" ");
      QPalette p = ui -> textEdit -> palette();
      p.setColor(QPalette::Base, color);
      ui -> textEdit -> setPalette(p);
      Image.remove("^");
      file_name = QFileInfo(file).fileName();
      if (file_name.isEmpty())
        file_name = "HMT";
      this -> setWindowTitle(file_name);
    }
    file.close();
  }
}
/**
 * @brief MainWindow::removeImageTag
 * This action remove Image tag from the output code
 * @param text
 * @returns QString
 */
QString MainWindow::removeImageTag(QString text)
{
  QString img, location;
  int i = 0;
  if (Image.isEmpty() || Image.size() == 1)
    return text;
  while (Image.size() > i)
  {
    while (Image[i] != '|')
    {
      img.append(Image[i]);
      i++;
    }
    img[0] = img[0].toLower();
    img.remove(":");
    location.append("file://");
    location.append(img);
    text.remove(location);
    text.remove("img src=");
    location = "";
    img = "";
    while (Image[i] != '$')
      i++;
    i++;
  }
  return text;
}
QString MainWindow::AddBr(QString text)
{
  int i = 0;
  QString new_text;
  while (i < text.size())
  {
    while ((text[i] != '/' || text[i + 1] != '>') && i < text.size())
    {
      new_text.append(text[i]);
      i++;
    }
    if (i >= text.size())
      return new_text;
    new_text.append(text[i]);
    i++;
    new_text.append(text[i]);
    i++;
    new_text.append("<br>");
  }
  return new_text;
}
/**
 * @brief MainWindow::on_actionSave_triggered
 * The Action saves the changes done by the user in the editor
 * If the file is untitled then the Action call the MainWindow::on_actionSave_As_triggered()
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionSave_triggered()
{
  QString h;
  QString text;
  if (file_path.size() == 0)
    on_actionSave_As_triggered();
  QFile file(file_path);
  QTextStream out( & file);
  if (file.open(QFile::WriteOnly | QFile::Text))
  {
    QString code;
    code.append(ui -> textEdit -> palette().color(QPalette::Base).name(QColor::HexArgb));
    code.append(" ");
    if (!Image.isEmpty())
    {
      text = AddBr(ui -> textEdit -> toHtml());
      h = removeImageTag(text);
      code.append(Image);
      code.append("^");
      code.append(h);
    }
    else
      code.append(ui -> textEdit -> toHtml());
    out << code;
    file.flush();
    file.close();
  }
}
/**
 * @brief MainWindow::on_actionSave_As_triggered
 * This Action save the file with new file_name given by user
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionSave_As_triggered()
{
  QString h, text;
  file_path = QFileDialog::getSaveFileName(this, "Save as", "C://");
  if (QFileInfo(file_path).suffix().isEmpty() && !file_path.isEmpty())
  {
    file_path.append(".hmt");
  }
  if (!file_path.isEmpty())
  {
    QFile file(file_path);
    QTextStream out( & file);
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
      QString code;
      code.append(ui -> textEdit -> palette().color(QPalette::Base).name(QColor::HexArgb));
      code.append(" ");
      if (!Image.isEmpty())
      {
        text = AddBr(ui -> textEdit -> toHtml());
        h = removeImageTag(text);
        code.append(Image);
        code.append("^");
        code.append(h);
      }
      else
        code.append(ui -> textEdit -> toHtml());
      out << code;
      file_name = QFileInfo(file).fileName();
      this -> setWindowTitle(file_name);
    }
    file.flush();
    file.close();
  }
}
/**
 * @brief MainWindow::on_actionExit_triggered
 * This Action Exit from the editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionExit_triggered()
{
  exit(0);
}
/**
 * @brief MainWindow::on_actionCut_triggered
 * This Action cut the selected text and add it to the clipboard to use it later
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionCut_triggered()
{
  ui -> textEdit -> cut();
}
/**
 * @brief MainWindow::on_actionCopy_triggered
 * This Action copy the selected text to the clipboard
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionCopy_triggered()
{
  ui -> textEdit -> copy();
}
/**
 * @brief MainWindow::on_actionPaste_triggered
 * This action paste the text from clipboard to editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionPaste_triggered()
{
  ui -> textEdit -> paste();
}
/**
 * @brief MainWindow::on_actionUndo_triggered
 * This action undo the previous changes in the editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionUndo_triggered()
{
  ui -> textEdit -> undo();
}
/**
 * @brief MainWindow::on_actionRedo_triggered
 * This action redo the forward changes in the editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionRedo_triggered()
{
  ui -> textEdit -> redo();
}
/**
 * @brief MainWindow::on_actionFind_triggered
 * This action find the text given by user in the editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionFind_triggered()
{
  bool ok;
  bool data;
  QString text = QInputDialog::getText(this, tr("Find"), tr("Find:"), QLineEdit::Normal, universal_text, & ok);
  universal_text = text;
  if (ok && !text.isEmpty())
  {
    data = ui -> textEdit -> find(text, QTextDocument::FindBackward);
    if (!data == true)
      QMessageBox::information(this, "Not Found", "Text not Found");
  }

}
/**
 * @brief MainWindow::on_actionSelect_All_triggered
 * This action select all the animation of the editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionSelect_All_triggered()
{
  ui -> textEdit -> selectAll();
}
/**
 * @brief MainWindow::on_actionFind_Replace_triggered
 * This action Find and replace the text provided by user in editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionFind_Replace_triggered()
{
  bool ok, ok2;
  QString find = QInputDialog::getText(this, tr("Find"), tr("Find:"), QLineEdit::Normal, universal_text, & ok);
  bool data = ui -> textEdit -> find(find, QTextDocument::FindBackward);
  if (data != 1)
    QMessageBox::information(this, "Error", "Text not Found");
  else
  {
    QString replace = QInputDialog::getText(this, tr("Replace"), tr("Replace:"), QLineEdit::Normal, universal_text, & ok2);
    universal_text = replace;
    if (ok && !find.isEmpty() && ok2 && !replace.isEmpty())
    {
      QString text = ui -> textEdit -> toPlainText();
      text.replace(find, replace, Qt::CaseSensitive);
      ui -> textEdit -> setText(text);
    }
  }
}
/**
 * @brief MainWindow::on_actionFind_Next_triggered
 * This action highlight the the next same text which find action finds
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionFind_Next_triggered()
{
  ui -> textEdit -> find(universal_text);
}

/**
 * @brief MainWindow::on_actionFind_Previous_triggered
 * This action highlight the the previous same text which find action finds
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionFind_Previous_triggered()
{
  ui -> textEdit -> find(universal_text, QTextDocument::FindBackward);
}
/**
 * @brief MainWindow::on_actionTime_Date_triggered
 * This action add the current time and date in the editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionTime_Date_triggered()
{
  QString text;
  QString dt_text;
  QDateTime time;
  text = ui -> textEdit -> toPlainText();
  time = QDateTime::currentDateTime();
  dt_text = time.toString("hh:mm:ss dd/MM/yyyy");
  text.append(dt_text);
  ui -> textEdit -> setText(text);
}
/**
 * @brief MainWindow::on_actionStatusbar_triggered
 * This action show or hide the statusbar
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionStatusbar_triggered()
{
  bool check;
  check = ui -> actionStatusbar -> isChecked();
  if (check)
    ui -> statusbar -> show();
  else
    ui -> statusbar -> hide();
}
/**
 * @brief MainWindow::on_actionTool_Bar_triggered
 * This action show or hide the toolbar
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionTool_Bar_triggered()
{
  bool check;
  check = ui -> actionTool_Bar -> isChecked();
  if (check)
    ui -> toolBar -> show();
  else
    ui -> toolBar -> hide();
}
/**
 * @brief MainWindow::on_actionText_Color_triggered
 * This action change the Text color
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionText_Color_triggered()
{
  QColor color = QColorDialog::getColor(Qt::black, this, "Choose Color");
  if (color.isValid())
  {
    ui -> textEdit -> setTextColor(color);
  }
}
/**
 * @brief MainWindow::on_actionBackground_Color_triggered
 * This action change the background color of the selected text
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionBackground_Color_triggered()
{
  QColor color = QColorDialog::getColor(Qt::black, this, "Choose Color");
  if (color.isValid())
  {
    ui -> textEdit -> setTextBackgroundColor(color);
  }
}
/**
 * @brief MainWindow::on_actionLeft_triggered
 * This action left align the selected text
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionLeft_triggered()
{
  ui -> textEdit -> setAlignment(Qt::AlignLeft);
}
/**
 * @brief MainWindow::on_actionRight_triggered
 * This action right align the selected text
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionRight_triggered()
{
  ui -> textEdit -> setAlignment(Qt::AlignRight);
}
/**
 * @brief MainWindow::on_actionCenter_triggered
 * This action center align the selected text
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionCenter_triggered()
{
  ui -> textEdit -> setAlignment(Qt::AlignCenter);
}
/**
 * @brief MainWindow::on_actionJustify_triggered
 * This action justify align the selected text
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionJustify_triggered()
{
  ui -> textEdit -> setAlignment(Qt::AlignJustify);
}
/**
 * @brief MainWindow::on_actionFont_triggered
 * This action change the font style of the selected text
 * If non of the text is selected it change the font of whole text present in editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionFont_triggered()
{
  bool ok;
  QFont font;
  QString selected_text;
  font = QFontDialog::getFont( & ok, QFont("Arial", 18), this, "Choose Font");
  if (ok) {
    selected_text = ui -> textEdit -> textCursor().selectedText();
    if (selected_text.isEmpty())
      ui -> textEdit -> setFont(font);

    else {
      QTextCharFormat format;
      format.setFont(font);
      ui -> textEdit -> textCursor().mergeCharFormat(format);
    }
  }
}
/**
 * @brief MainWindow::on_actionBackground_Color_2_triggered
 * This action change the background color of the editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionBackground_Color_2_triggered()
{
  QColor color = QColorDialog::getColor(Qt::white, this);
  QPalette p = ui -> textEdit -> palette();
  p.setColor(QPalette::Base, color);
  ui -> textEdit -> setPalette(p);
}
/**
 * @brief MainWindow::on_actionLower_Roman_triggered
 * This action add a lower roman list
 * @tparam void
 * @return void
 */
void MainWindow::on_actionLower_Roman_triggered()
{
  QTextListFormat::Style style = QTextListFormat::ListLowerRoman;

  QTextCursor cursor = ui -> textEdit -> textCursor();
  QTextListFormat listFormat;
  listFormat.setStyle(style);
  cursor.createList(listFormat);
}
/**
 * @brief MainWindow::on_actionUpper_Roman_triggered
 * This action add Upper Roman list
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionUpper_Roman_triggered()
{

  QTextListFormat::Style style = QTextListFormat::ListUpperRoman;

  QTextCursor cursor = ui -> textEdit -> textCursor();
  QTextListFormat listFormat;
  listFormat.setStyle(style);
  cursor.createList(listFormat);
}
/**
 * @brief MainWindow::on_actionDecimal_triggered
 * This action add Decimal list
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionDecimal_triggered()
{

  QTextListFormat::Style style = QTextListFormat::ListDecimal;

  QTextCursor cursor = ui -> textEdit -> textCursor();
  QTextListFormat listFormat;
  listFormat.setStyle(style);
  cursor.createList(listFormat);
}
/**
 * @brief MainWindow::on_actionLower_Alphabet_triggered
 * This action Lower Alphabet list
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionLower_Alphabet_triggered()
{

  QTextListFormat::Style style = QTextListFormat::ListLowerAlpha;

  QTextCursor cursor = ui -> textEdit -> textCursor();
  QTextListFormat listFormat;
  listFormat.setStyle(style);
  cursor.createList(listFormat);
}
/**
 * @brief MainWindow::on_actionUpperAlphabet_triggered
 * This action add Upper Alphabet list
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionUpperAlphabet_triggered()
{

  QTextListFormat::Style style = QTextListFormat::ListUpperAlpha;

  QTextCursor cursor = ui -> textEdit -> textCursor();
  QTextListFormat listFormat;
  listFormat.setStyle(style);
  cursor.createList(listFormat);
}
/**
 * @brief MainWindow::on_actionDisc_triggered
 * This action add Disc list
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionDisc_triggered()
{

  QTextListFormat::Style style = QTextListFormat::ListDisc;

  QTextCursor cursor = ui -> textEdit -> textCursor();
  QTextListFormat listFormat;
  listFormat.setStyle(style);
  cursor.createList(listFormat);
}
/**
 * @brief MainWindow::on_actionCircle_triggered
 * This action add Circle list
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionCircle_triggered()
{

  QTextListFormat::Style style = QTextListFormat::ListCircle;
  QTextCursor cursor = ui -> textEdit -> textCursor();
  QTextListFormat listFormat;
  listFormat.setStyle(style);
  cursor.createList(listFormat);
}
/**
 * @brief MainWindow::on_actionSquare_triggered
 * This action add Square list
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionSquare_triggered()
{

  QTextListFormat::Style style = QTextListFormat::ListSquare;

  QTextCursor cursor = ui -> textEdit -> textCursor();
  QTextListFormat listFormat;
  listFormat.setStyle(style);
  cursor.createList(listFormat);

}
/**
 * @brief MainWindow::on_actionInsert_Table_triggered
 * This action add table in the editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionInsert_Table_triggered()
{
  bool ok, ok2;
  int r, c, i, j;
  QString box_text = ui -> textEdit -> toHtml();
  QString main_text("<p>");
  main_text.append(box_text);
  main_text.append("</p>");
  QString text("<table border='1' width='100%'>");
  QString col = QInputDialog::getText(this, tr("Columns"), tr("No. of Columns"), QLineEdit::Normal, "Type Here", & ok);
  QString row = QInputDialog::getText(this, tr("Rows"), tr("No. of Rows"), QLineEdit::Normal, "Type Here", & ok2);
  if (ok && ok2 && !col.isEmpty() && !row.isEmpty())
  {
    r = row.toInt();
    c = col.toInt();
    for (i = 0; i < r; i++)
    {
      text.append("<tr>");
      for (j = 0; j < c; j++)
      {
        text.append("<td></td>");
      }
      text.append("</tr>");
    }
    text.append("</table>");
    main_text.append(text);
    ui -> textEdit -> setHtml(main_text);
  }
}
/**
 * @brief MainWindow::on_actionInsert_Image_triggered
 * This action add a selected Image in the editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionInsert_Image_triggered()
{
  QString file = QFileDialog::getOpenFileName(this, tr("Select an image"), ".", tr("Bitmap Files (*.bmp)\n"
    "JPEG (*.jpg *jpeg)\n"
    "GIF (*.gif)\n"
    "PNG (*.png)\n"));
  if (!file.isEmpty())
  {
    QFileInfo fileInfo(file);
    bool ok = QDir("Image").exists();
    if (ok)
      QDir().mkdir("C:/Image");
    QString dest("C:/Image/" + fileInfo.fileName());
    QFile::copy(file, dest);
    if (file.size() != 0)
    {
      Image.append(dest);
      QTextCursor cur = ui -> textEdit -> textCursor();
      cur.movePosition(QTextCursor::StartOfLine);

      int lines = 1;
      while (cur.positionInBlock() > 0)
      {
        cur.movePosition(QTextCursor::Up);
        lines++;
      }
      QTextBlock block = cur.block().previous();

      while (block.isValid()) {
        lines += block.lineCount();
        block = block.previous();
      }
      Image.append("| ");
      Image.append(QString::number(lines));
      Image.append("$");
    }
    QUrl Uri(QString("file://%1").arg(dest));
    QImage image = QImageReader(file).read();
    QTextDocument * textDocument = ui -> textEdit -> document();
    textDocument -> addResource(QTextDocument::ImageResource, Uri, QVariant(image));
    QTextCursor cursor = ui -> textEdit -> textCursor();
    QTextImageFormat imageFormat;
    imageFormat.setWidth(image.width());
    imageFormat.setHeight(image.height());
    imageFormat.setName(Uri.toString());
    cursor.insertImage(imageFormat);
  }
}
/**
 * @brief MainWindow::on_actionZoom_In_triggered
 * This action zoom in
 * It works like a magnifying glass
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionZoom_In_triggered()
{
  ui -> textEdit -> zoomIn(10);
}
/**
 * @brief MainWindow::on_actionZoom_Out_triggered
 * This action zoom out the current screen
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionZoom_Out_triggered()
{
  ui -> textEdit -> zoomOut(10);
}
/**
 * @brief MainWindow::on_actionmargin_triggered
 * This action add up the margin of the editor
 * This add margin from all sides
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionmargin_triggered()
{
  bool ok;
  QString text = QInputDialog::getText(this, tr("Margin"), tr("Margin:"), QLineEdit::Normal, universal_text, & ok);
  ui -> textEdit -> document() -> setDocumentMargin(text.toInt());
}
/**
 * @brief MainWindow::on_actionApply_Markdown_triggered
 * This function convert the text of the editor to Markdown Language
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionApply_Markdown_triggered()
{
  if (!ui -> actionApply_Markdown -> isChecked())
  {
    ui -> actionApply_Markdown -> setChecked(false);
    ui -> textEdit -> setText(Markdown);
    ui -> textEdit -> setReadOnly(false);
    ui -> toolBar -> show();
    ui -> statusbar -> show();
    ui -> actionStatusbar -> setChecked(true);
    ui -> actionReading_Mode -> setChecked(false);
    ui -> actionTool_Bar -> setChecked(true);
    ui -> menuInsert -> setEnabled(true);
    ui -> menuDesign -> setEnabled(true);

  }
  else
  {
    ui -> actionApply_Markdown -> setChecked(true);
    Markdown = ui -> textEdit -> toPlainText();
    ui -> textEdit -> setMarkdown(Markdown);
    ui -> toolBar -> hide();
    ui -> statusbar -> hide();
    ui -> actionTool_Bar -> setChecked(false);
    ui -> actionStatusbar -> setChecked(false);
    ui -> actionReading_Mode -> setChecked(true);
    ui -> menuInsert -> setEnabled(false);
    ui -> menuDesign -> setEnabled(false);
    ui -> textEdit -> setReadOnly(true);
  }

}
/**
 * @brief MainWindow::on_actionApply_Html_triggered
 * This action convert the text into Html Langugage
 * It currently doesn't support too much feature
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionApply_Html_triggered()
{
  if (!ui -> actionApply_Html -> isChecked())
  {
    ui -> textEdit -> setAcceptRichText(false);
    ui -> textEdit -> setPlainText(Html);
    ui -> actionStatusbar -> setChecked(true);
    ui -> actionReading_Mode -> setChecked(false);
    ui -> actionTool_Bar -> setChecked(true);
    ui -> textEdit -> setReadOnly(false);
    ui -> menuInsert -> setEnabled(true);
    ui -> menuDesign -> setEnabled(true);
    ui -> toolBar -> show();
    ui -> statusbar -> show();
  }
  else
  {
    Html = ui -> textEdit -> toPlainText();
    ui -> textEdit -> setHtml(Html);
    ui -> toolBar -> hide();
    ui -> statusbar -> hide();
    ui -> menuInsert -> setEnabled(false);
    ui -> menuDesign -> setEnabled(false);
    ui -> actionTool_Bar -> setChecked(false);
    ui -> actionStatusbar -> setChecked(false);
    ui -> actionReading_Mode -> setChecked(true);
    ui -> textEdit -> setReadOnly(true);
  }

}
/**
 * @brief MainWindow::on_actionCustom_triggered
 * This action change the size of the textedit area as user wants
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionCustom_triggered()
{
  bool ok;
  int h, w;
  QString Text = QInputDialog::getText(this, tr("Page Size"), tr("Height: "), QLineEdit::Normal, universal_text, & ok);
  QString Text2 = QInputDialog::getText(this, tr("Page Size"), tr("Width: "), QLineEdit::Normal, universal_text, & ok);
  h = Text.toInt();
  w = Text2.toInt();
  ui -> textEdit -> resize(w, h);
}
/**
 * @brief MainWindow::on_actionLetter_triggered
 * This action change the size of the textedit area as Letter writing
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionLetter_triggered()
{
  ui -> textEdit -> resize(216 * 3.8, this -> height());
}
/**
 * @brief MainWindow::on_actionTabloid_triggered
 * This action change the size of the textedit area as a Tabloid form
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionTabloid_triggered()
{
  ui -> textEdit -> resize(279 * 3.8, this -> height());

}
/**
 * @brief MainWindow::on_actionA4_triggered
 * This action change the size of the textedit area as A4 paper
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionA4_triggered()
{
  ui -> textEdit -> resize(210 * 3.8, this -> height());

}
/**
 * @brief MainWindow::on_actionA5_triggered
 * This action change the size of the textedit area as A5 paper
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionA5_triggered()
{
  ui -> textEdit -> resize(148 * 3.8, this -> height());
  auto layout = new QHBoxLayout(this);
  layout -> setAlignment(ui -> textEdit, Qt::AlignCenter);

}
/**
 * @brief MainWindow::on_actionA3_triggered
 * This action change the size of the textedit area as A3 paper
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionA3_triggered()
{
  ui -> textEdit -> resize(297 * 3.8, this -> height());

}
/**
 * @brief MainWindow::on_actionB4_triggered
 * This action change the size of the textedit area as B4 paper
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionB4_triggered()
{
  ui -> textEdit -> resize(257 * 3.8, this -> height());

}
/**
 * @brief MainWindow::on_actionB5_triggered
 * This action change the size of the textedit area as B5 paper
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionB5_triggered()
{
  ui -> textEdit -> resize(182 * 3.8, this -> height());
}
/**
 * @brief MainWindow::on_actionPrint_triggered
 * This action helps to Print the textedit area on printer or as PDF file
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionPrint_triggered()
{
  QPrinter print;
  print.setPrinterName("UG");
  QPrintDialog dialog( & print, this);
  if (dialog.exec() == QDialog::Rejected)
    return;
  ui -> textEdit -> print( & print);
}
/**
 * @brief MainWindow::on_actionWord_Spacing_triggered
 * This action change the Word Spacing of the text
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionWord_Spacing_triggered()
{
  bool ok;
  QString Text = QInputDialog::getText(this, tr("Spacing"), tr("Word Spacing: "), QLineEdit::Normal, universal_text, & ok);
  QString main_text(" QTextEdit{word-spacing:");
  main_text.append(Text);
  main_text.append("px;}");
  stylesheet.append(main_text);
  ui -> textEdit -> setStyleSheet(stylesheet);
}
/**
 * @brief MainWindow::on_actionLetter_2_triggered
 * This action change the Letter Spacing of the text
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionLetter_2_triggered()
{
  bool ok;
  QString Text = QInputDialog::getText(this, tr("Spacing"), tr("Letter Spacing: "), QLineEdit::Normal, universal_text, & ok);
  QString main_text("QTextEdit{letter-spacing:");
  main_text.append(Text);
  main_text.append("px;}");
  stylesheet.append(main_text);
  ui -> textEdit -> setStyleSheet(stylesheet);

}
/**
 * @brief MainWindow::on_actionWord_Wrap_triggered
 * This action apply or remove the Word Wrap from the textarea
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionWord_Wrap_triggered()
{
  if (ui -> actionWord_Wrap -> isChecked())
    ui -> textEdit -> setWordWrapMode(QTextOption::WordWrap);
  else
    ui -> textEdit -> setWordWrapMode(QTextOption::NoWrap);
}
/**
 * @brief MainWindow::on_actionLine_Wrap_triggered
 * This action apply or remove the Line Wrap from the textarea
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionLine_Wrap_triggered()
{
  if (ui -> actionLine_Wrap -> isChecked())
    ui -> textEdit -> setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);
  else
    ui -> textEdit -> setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
}
/**
 * @brief MainWindow::on_actionReading_Mode_triggered
 * This action change the mode to reading mode
 * Reading Mode prevent to write text on the editor
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionReading_Mode_triggered()
{
  if (ui -> actionReading_Mode -> isChecked())
  {
    ui -> textEdit -> setReadOnly(true);
    ui -> statusbar -> hide();
    ui -> toolBar -> hide();
    ui -> actionTool_Bar -> setChecked(false);
    ui -> actionStatusbar -> setChecked(false);
  }
  else
  {
    ui -> textEdit -> setReadOnly(false);
    ui -> statusbar -> show();
    ui -> toolBar -> show();
    ui -> actionTool_Bar -> setChecked(true);
    ui -> actionStatusbar -> setChecked(true);

  }
}
/**
 * @brief MainWindow::on_actionExport_in_PDF_triggered
 * This action change the text to the PDF file
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionExport_in_PDF_triggered()
{
  QString fileName = QFileDialog::getSaveFileName((QWidget * ) 0, "Export PDF", universal_text, tr("PDF Files(*.pdf)\n"));
  if (!fileName.isEmpty())
  {
    if (QFileInfo(fileName).suffix().isEmpty())
    {
      fileName.append(".pdf");
    }
    if (!fileName.isEmpty())
    {
      QTextDocument document;
      document.setHtml(ui -> textEdit -> toHtml());
      QPrinter printer(QPrinter::PrinterResolution);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setPageSize(QPageSize(QPageSize::A4));
      printer.setOutputFileName(fileName);
      printer.setPageMargins(QMarginsF(15, 15, 15, 15));
      document.print( & printer);
      file_name = QFileInfo(fileName).fileName();
      setWindowTitle(file_name);
    }
  }
}
/**
 * @brief MainWindow::on_actionContact_Support_triggered
 * This action shows a contact_help.ui window which show contact support to user
 * @tparam void
 * @returns void
 */
void MainWindow::on_actionContact_Support_triggered()
{
  contact.setModal(true);
  contact.exec();
}
/**
 * @brief MainWindow::closeEvent
 * This action or event runs when the close button is pressed
 * It ask user to save the file,close it,or cancel the action
 * @param event
 * @returns void
 */
void MainWindow::closeEvent(QCloseEvent * event)
{
  if (file_path.isEmpty() && ui -> textEdit -> toPlainText().isEmpty() != 1)
  {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Close", "Do You Want to Save?", QMessageBox::Save | QMessageBox::Close | QMessageBox::Cancel);
    if (reply == QMessageBox::Save)
      on_actionSave_triggered();
    else if (reply == QMessageBox::Close)
      exit(0);
    else
      event -> ignore();
  }
  else
  {
    QFile file(file_path);
    QTextStream in ( & file);
    if (file.open(QFile::ReadWrite | QFile::Text))
    {
      QString text = in .readAll();
      file.close();
      if (text.compare(ui -> textEdit -> toPlainText(), Qt::CaseSensitive) != 0)
      {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Close", "Do You Want to Save?", QMessageBox::Save | QMessageBox::Close | QMessageBox::Cancel);
        if (reply == QMessageBox::Save)
          on_actionSave_triggered();
        else if (reply == QMessageBox::Close)
          exit(0);
        else
          event -> ignore();
      }
    }
  }
}
/**
 * @brief MainWindow::on_actionOpen_txt_file_triggered
 * This action used to open .html, .txt, .md file
 * @param void
 * @returs void
 */
void MainWindow::on_actionOpen_txt_file_triggered()
{
  file_path = QFileDialog::getOpenFileName(this, "Open File", "C://");
  QFile file(file_path);
  if (!file_path.isEmpty()) {
    QTextStream in ( & file);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
      QString text = in .readAll();
      ui -> textEdit -> setText(text);
      file_name = QFileInfo(file).fileName();
      if (file_name.isEmpty())
        file_name = "HMT";
      this -> setWindowTitle(file_name);

    }
  }
}
/**
 * @brief MainWindow::on_actionExport_in_HTML_triggered
 * This action helps you to Export .html files
 * @param void
 * @returns void
 */
void MainWindow::on_actionExport_in_HTML_triggered()
{
  file_path = QFileDialog::getSaveFileName(this, "Save as", "C://");
  if (QFileInfo(file_path).suffix().isEmpty() && !file_path.isEmpty())
  {
    file_path.append(".html");
  }
  if (!file_path.isEmpty())
  {
    QFile file(file_path);
    QTextStream out( & file);
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
      out << ui -> textEdit -> toHtml();
      file_name = QFileInfo(file).fileName();
      this -> setWindowTitle(file_name);
    }
  }
}
/**
 * @brief MainWindow::on_actionExport_in_Markdown_triggered
 * This action helps to export .md files
 * @param void
 * @returns void
 */
void MainWindow::on_actionExport_in_Markdown_triggered()
{
  file_path = QFileDialog::getSaveFileName(this, "Save as", "C://");
  if (QFileInfo(file_path).suffix().isEmpty() && !file_path.isEmpty())
  {
    file_path.append(".md");
  }
  if (!file_path.isEmpty())
  {
    QFile file(file_path);
    QTextStream out( & file);
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
      out << ui -> textEdit -> toMarkdown();
      file_name = QFileInfo(file).fileName();
      this -> setWindowTitle(file_name);
    }
  }
}
/**
 * @brief MainWindow::on_actionExport_in_TXT_triggered
 * This action converts documents to .txt files
 * @param void
 * @returns void
 */
void MainWindow::on_actionExport_in_TXT_triggered()
{
  file_path = QFileDialog::getSaveFileName(this, "Save as", "C://");
  if (QFileInfo(file_path).suffix().isEmpty() && !file_path.isEmpty())
  {
    file_path.append(".html");
  }
  if (!file_path.isEmpty())
  {
    QFile file(file_path);
    QTextStream out( & file);
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
      out << ui -> textEdit -> toPlainText();
      file_name = QFileInfo(file).fileName();
      this -> setWindowTitle(file_name);
    }
  }
}

/***************************************************************************************************************************************************************/
