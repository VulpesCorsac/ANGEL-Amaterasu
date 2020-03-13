#ifndef Amaterasu_H
#define Amaterasu_H

#include <QMainWindow>
#include <QWindow>
#include <QWidget>
#include <QScreen>
#include <QPixmap>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QProcess>
#include <QMessageBox>
#include <QDate>
#include <QTest>
#include <QFileDialog>
#include <QFileInfo>

#include <iostream>
#include <fstream>

namespace Ui {
    class Amaterasu;
}

class Amaterasu : public QMainWindow {
    Q_OBJECT

public:
    enum GUIMode {
        LicenseIsOver,
        Simple,
        Engineering,
        God
    };

    explicit Amaterasu(QWidget *parent = nullptr);
    ~Amaterasu();

    void showMode(const GUIMode &mode = Simple);

    void showSimpleMode();
    void showEngineeringMode();
    void showGodMode();

    void loadConfig();
    void saveConfig();

    void checkLicence();

private slots:
    void on_actionSimple_mode_triggered();
    void on_actionEngineering_mode_triggered();
    void on_actionGod_mode_triggered();

    bool on_actionTake_screenshot_triggered();
    bool on_actionExport_screenshot_triggered();
    bool on_actionExport_script_triggered();
    bool on_actionExport_supplementary_triggered();
    bool on_actionExport_bat_triggered();
    bool on_actionRun_bat_triggered();
    bool on_actionShow_results_triggered();

    void on_pushButtonScreenshot_clicked();
    void on_pushButtonAnalyse_clicked();
    void on_actionActivate_licence_triggered();

    void updateImage();
    void resizeEvent(QResizeEvent * event) override;

    void on_actionAnalyse_file_triggered();
    void on_actionShow_image_triggered();

    void loadFile(QString &file_name);

    void on_comboBoxAnalysingMethod_currentIndexChanged(const QString &arg1);
    void on_comboBoxDataToShow_currentTextChanged(const QString &arg1);
    void on_comboBoxFileToShow_currentTextChanged(const QString &arg1);

    void on_lineEditFiberName_textEdited(const QString &arg1);

    void on_doubleSpinBoxLeftRadius_valueChanged(double arg1);

    void on_doubleSpinBoxRightRadius_valueChanged(double arg1);

    void on_doubleSpinBoxTopRadius_valueChanged(double arg1);

private:
    Ui::Amaterasu *ui;

    QPixmap screenshot;

    QStringList analysing_method = {"Image", "Circles", "Curvature"};
    QStringList image_data = {"Image"};
    QStringList circles_data = {"Image"};
    QStringList curvature_data = {"Curvature", "Smoothed", "Point", "Result"};

    QMap < QPair < QString, QString > , QStringList > files_to_show;

    QString script_file_name = "";
    QString supplementary_file_name = "";
    QString bat_file_name = "";

    bool file_license = true;
    QString file_1_path = "C:\\Qt\\Amaterasu.txt";
    QString file_1_text = "Found_it!_[3]";
    QString file_2_path = "C:\\3sae_lfs\\lfs config\\Amaterasu.txt";
    QString file_2_text = "Found_it!_[1]";

    bool time_license = true;
    int expiration_year = 2019;
    int expiration_month = 10;

    bool god_mode_enabled = false;
    bool license_activated = true;
};

#endif // Amaterasu_H
