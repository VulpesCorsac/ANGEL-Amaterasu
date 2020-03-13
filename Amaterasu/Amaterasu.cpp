// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Amaterasu.h"
#include "ui_Amaterasu.h"

Amaterasu::Amaterasu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Amaterasu) {
    ui->setupUi(this);

    ui->comboBoxAnalysingMethod->addItems(analysing_method);

    loadConfig();

    on_actionSimple_mode_triggered();
//    on_actionGod_mode_triggered();

    checkLicence();
}

Amaterasu::~Amaterasu() {
    saveConfig();

    delete ui;
}

void Amaterasu::loadConfig() {
    std::fstream file;
    file.open("cfg.cfg", std::ios_base::in);

    if (!file.is_open()) {
        ui->statusBar->showMessage("Config cannot be loaded");

        return;
    }

    std::string item, value;

    while (file >> item) {
        if (item == "um") {
            continue;
        }

        file >> value;

        QString qt_item = QString(item.c_str());
        QString qt_value = QString(value.c_str());

        bool ok = true;

        if (item == "FiberName") {
            ui->lineEditFiberName->setText(qt_value);

            if (ui->lineEditFiberName->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported fiber name: " + qt_value);

                return;
            }
        } else if (item == "FiberDiameter") {
            ui->spinBoxFiberDiameter->setValue(qt_value.toInt(&ok));

            if (!ok) {
                ui->statusBar->showMessage("Unsopported fiber diameter: " + qt_value);

                return;
            }
        } else if (item == "SigmaCorner") {
            ui->spinBoxSigmaCorner->setValue(qt_value.toInt(&ok));

            if (!ok || ui->spinBoxSigmaCorner->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported sigma corner: " + qt_value);

                return;
            }
        } else if (item == "SigmaTop") {
            ui->spinBoxSigmaTop->setValue(qt_value.toInt(&ok));

            if (!ok) {
                ui->statusBar->showMessage("Unsopported sigma top: " + qt_value);

                return;
            }
        } else if (item == "CornerMin") {
            ui->doubleSpinBoxCornerRadiusMin->setValue(qt_value.toDouble(&ok));

            if (!ok || ui->doubleSpinBoxCornerRadiusMin->value() != qt_value.toDouble()) {
                ui->statusBar->showMessage("Unsopported corner min: " + qt_value);

                return;
            }
        } else if (item == "CornerMax") {
            ui->doubleSpinBoxCornerRadiusMax->setValue(qt_value.toDouble(&ok));

            if (!ok || ui->doubleSpinBoxCornerRadiusMax->value() != qt_value.toDouble()) {
                ui->statusBar->showMessage("Unsopported corner max: " + qt_value);

                return;
            }
        } else if (item == "TopMin") {
            ui->doubleSpinBoxTopRadiusMin->setValue(qt_value.toDouble(&ok));

            if (!ok || ui->doubleSpinBoxTopRadiusMin->value() != qt_value.toDouble()) {
                ui->statusBar->showMessage("Unsopported top min: " + qt_value);

                return;
            }
        } else if (item == "TopMax") {
            ui->doubleSpinBoxTopRadiusMax->setValue(qt_value.toDouble(&ok));

            if (!ok || ui->doubleSpinBoxTopRadiusMax->value() != qt_value.toDouble()) {
                ui->statusBar->showMessage("Unsopported top max: " + qt_value);

                return;
            }
        } else if (item == "InputDir") {
            ui->lineEditInputDirectory->setText(qt_value);

            if (ui->lineEditInputDirectory->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported input directory: " + qt_value);

                return;
            }
        } else if (item == "OutputDir") {
            ui->lineEditOutputDirectory->setText(qt_value);

            if (ui->lineEditOutputDirectory->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported output directory: " + qt_value);

                return;
            }
        } else if (item == "PictureMask") {
            ui->lineEditPictureNameMask->setText(qt_value);

            if (ui->lineEditPictureNameMask->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported picture mask: " + qt_value);

                return;
            }
        } else if (item == "FilenameDataSeparator") {
            ui->lineEditFilenameDataSeparator->setText(qt_value);

            if (ui->lineEditFilenameDataSeparator->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported filename data separator: " + qt_value);

                return;
            }
        } else if (item == "ClearPreviousResults") {
            if (value == "True") {
                ui->checkBoxClearPreviousResults->setCheckState(Qt::Checked);
            } else if (value == "False") {
                ui->checkBoxClearPreviousResults->setCheckState(Qt::Unchecked);
            } else {
                ui->statusBar->showMessage("Unknown clear previuos results setting: " + qt_value);
            }
        } else if (item == "WhiteColor") {
            ui->doubleSpinBoxWhiteColor->setValue(qt_value.toDouble(&ok));

            if (!ok || ui->doubleSpinBoxWhiteColor->value() != qt_value.toDouble()) {
                ui->statusBar->showMessage("Unsopported white color: " + qt_value);

                return;
            }
        } else if (item == "FiberColor") {
            ui->doubleSpinBoxFiberColor->setValue(qt_value.toDouble(&ok));

            if (!ok || ui->doubleSpinBoxFiberColor->value() != qt_value.toDouble()) {
                ui->statusBar->showMessage("Unsopported fiber color: " + qt_value);

                return;
            }
        } else if (item == "RotateFractionAnalysis") {
            ui->doubleSpinBoxRotateAnalysisFraction->setValue(qt_value.toDouble(&ok));

            if (!ok || ui->doubleSpinBoxRotateAnalysisFraction->value() != qt_value.toDouble()) {
                ui->statusBar->showMessage("Unsopported rotate fraction analysis: " + qt_value);

                return;
            }
        } else if (item == "RotateRowsCut") {
            ui->spinBoxRotateRowsCut->setValue(qt_value.toInt(&ok));

            if (!ok || ui->spinBoxRotateRowsCut->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported rotate rows cut: " + qt_value);

                return;
            }
        } else if (item == "AnalyseCurvature") {
            if (value == "True") {
                ui->checkBoxAnalyseCurvature->setCheckState(Qt::Checked);
            } else if (value == "False") {
                ui->checkBoxAnalyseCurvature->setCheckState(Qt::Unchecked);
            } else {
                ui->statusBar->showMessage("Unknown analyse curvature setting: " + qt_value);
            }
        } else if (item == "TopAsExtremum") {
            if (value == "True") {
                ui->checkBoxTopAsExtremum->setCheckState(Qt::Checked);
            } else if (value == "False") {
                ui->checkBoxTopAsExtremum->setCheckState(Qt::Unchecked);
            } else {
                ui->statusBar->showMessage("Unknown top as extremum setting: " + qt_value);
            }

        } else if (item == "RangeToEvaluateAsExtremum") {
            ui->spinBoxRangeToEvaluateAsExtremum->setValue(qt_value.toInt(&ok));

            if (!ok || ui->spinBoxRangeToEvaluateAsExtremum->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported range to evaluate as extremum: " + qt_value);

                return;
            }
        } else if (item == "RangeToAnalyseFromExtremum") {
            ui->spinBoxRangeToAnalyseFromExtremum->setValue(qt_value.toInt(&ok));

            if (!ok || ui->spinBoxRangeToAnalyseFromExtremum->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported range to analyse from extremum: " + qt_value);

                return;
            }
        } else if (item == "StepToAnalyseFromExtremum") {
            ui->spinBoxStepToAnalyseFromExtremum->setValue(qt_value.toInt(&ok));

            if (!ok || ui->spinBoxStepToAnalyseFromExtremum->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported step to analyse from extremum: " + qt_value);

                return;
            }
        } else if (item == "AnalyseCircles") {
            if (value == "True") {
                ui->checkBoxAnalyseCircles->setCheckState(Qt::Checked);
            } else if (value == "False") {
                ui->checkBoxAnalyseCircles->setCheckState(Qt::Unchecked);
            } else {
                ui->statusBar->showMessage("Unknown analyse circles: " + qt_value);
            }
        } else if (item == "ColumnsFromMedianToFindTop") {
            ui->spinBoxColumnsFromMedianToFindTop->setValue(qt_value.toInt(&ok));

            if (!ok || ui->spinBoxColumnsFromMedianToFindTop->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported columns from median to find top: " + qt_value);

                return;
            }
        } else if (item == "StepToFindFiber") {
            ui->spinBoxStepToFindFiber->setValue(qt_value.toInt(&ok));

            if (!ok || ui->spinBoxStepToFindFiber->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported step to find fiber: " + qt_value);

                return;
            }
        } else if (item == "AngleForCorner") {
            ui->doubleSpinBoxAngleForCorner->setValue(qt_value.toDouble(&ok));

            if (!ok || ui->doubleSpinBoxAngleForCorner->value() != qt_value.toDouble()) {
                ui->statusBar->showMessage("Unsopported angle for corner: " + qt_value);

                return;
            }
        } else if (item == "AngleForTop") {
            ui->doubleSpinBoxAngleForTop->setValue(qt_value.toDouble(&ok));

            if (!ok || ui->doubleSpinBoxAngleForTop->value() != qt_value.toDouble()) {
                ui->statusBar->showMessage("Unsopported angle for corner: " + qt_value);

                return;
            }
        } else if (item == "XUpperLeft") {
            ui->spinBoxXUpperLeft->setValue(qt_value.toInt(&ok));

            if (!ok || ui->spinBoxXUpperLeft->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported x upper left: " + qt_value);

                return;
            }
        } else if (item == "YUpperLeft") {
            ui->spinBoxYUpperLeft->setValue(qt_value.toInt(&ok));

            if (!ok || ui->spinBoxYUpperLeft->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported y upper left: " + qt_value);

                return;
            }
        } else if (item == "XLowerRight") {
            ui->spinBoxXLowerRight->setValue(qt_value.toInt(&ok));

            if (!ok || ui->spinBoxXLowerRight->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported x lower right: " + qt_value);

                return;
            }
        } else if (item == "YLowerRight") {
            ui->spinBoxYLowerRight->setValue(qt_value.toInt(&ok));

            if (!ok || ui->spinBoxYLowerRight->text() != qt_value) {
                ui->statusBar->showMessage("Unsopported y lower right: " + qt_value);

                return;
            }
        } else if (item == "GodPass") {
            if (value == "GeoANGELAmaterasu") {
                god_mode_enabled = true;
            } else {
                god_mode_enabled = false;
            }
        } else if (item == "License") {
            if (value == "GeoANGELAmaterasuActivated") {
                license_activated = true;
            } else {
                license_activated = false;
            }
        } else {
            ui->statusBar->showMessage("Unknown parameter: " + qt_item);

            return;
        }
    }

    ui->statusBar->showMessage("Config loaded");

    return;
}

void Amaterasu::saveConfig() {
    std::fstream file;
    file.open("cfg.cfg", std::ios_base::out);

    if (!file.is_open()) {
        ui->statusBar->showMessage("Config cannot be saved");

        return;
    }

    file << "FiberName " << ui->lineEditFiberName->text().toStdString() << "\n";
    file << "FiberDiameter " << ui->spinBoxFiberDiameter->value() << "\n";
    file << "SigmaCorner " << ui->spinBoxSigmaCorner->value() << "\n";
    file << "SigmaTop " << ui->spinBoxSigmaTop->value() << "\n";
    file << "CornerMin " << ui->doubleSpinBoxCornerRadiusMin->value() << "\n";
    file << "CornerMax " << ui->doubleSpinBoxCornerRadiusMax->value() << "\n";
    file << "TopMin " << ui->doubleSpinBoxTopRadiusMin->value() << "\n";
    file << "TopMax " << ui->doubleSpinBoxTopRadiusMax->value() << "\n";
    file << "InputDir " << ui->lineEditInputDirectory->text().toStdString() << "\n";
    file << "OutputDir " << ui->lineEditOutputDirectory->text().toStdString() << "\n";
    file << "PictureMask " << ui->lineEditPictureNameMask->text().toStdString() << "\n";
    file << "FilenameDataSeparator " << ui->lineEditFilenameDataSeparator->text().toStdString() << "\n";
    file << "ClearPreviousResults " << (ui->checkBoxClearPreviousResults->checkState() == Qt::CheckState::Checked ? "True" : "False") << "\n";
    file << "WhiteColor " << ui->doubleSpinBoxWhiteColor->value() << "\n";
    file << "FiberColor " << ui->doubleSpinBoxFiberColor->value() << "\n";
    file << "RotateFractionAnalysis " << ui->doubleSpinBoxRotateAnalysisFraction->value() << "\n";
    file << "RotateRowsCut " << ui->spinBoxRotateRowsCut->value() << "\n";
    file << "AnalyseCurvature " << (ui->checkBoxAnalyseCurvature->checkState() == Qt::CheckState::Checked ? "True" : "False") << "\n";
    file << "TopAsExtremum " << (ui->checkBoxTopAsExtremum->checkState() == Qt::CheckState::Checked ? "True" : "False") << "\n";
    file << "RangeToEvaluateAsExtremum " << ui->spinBoxRangeToEvaluateAsExtremum->value() << "\n";
    file << "RangeToAnalyseFromExtremum " << ui->spinBoxRangeToAnalyseFromExtremum->value() << "\n";
    file << "StepToAnalyseFromExtremum " << ui->spinBoxStepToAnalyseFromExtremum->value() << "\n";
    file << "AnalyseCircles " << (ui->checkBoxAnalyseCircles->checkState() == Qt::CheckState::Checked ? "True" : "False") << "\n";
    file << "ColumnsFromMedianToFindTop " << ui->spinBoxColumnsFromMedianToFindTop->value() << "\n";
    file << "StepToFindFiber " << ui->spinBoxStepToFindFiber->value() << "\n";
    file << "AngleForCorner " << ui->doubleSpinBoxAngleForCorner->value() << "\n";
    file << "AngleForTop " << ui->doubleSpinBoxAngleForTop->value() << "\n";
    file << "XUpperLeft " << ui->spinBoxXUpperLeft->value() << "\n";
    file << "YUpperLeft " << ui->spinBoxYUpperLeft->value() << "\n";
    file << "XLowerRight " << ui->spinBoxXLowerRight->value() << "\n";
    file << "YLowerRight " << ui->spinBoxYLowerRight->value() << "\n";

    if (god_mode_enabled) {
        file << "GodPass " << "GeoANGELAmaterasu" << "\n";
    }
    if (license_activated) {
        file << "License " << "GeoANGELAmaterasuActivated" << "\n";
    }

    file.flush();

    file.close();

    return;
}

void Amaterasu::checkLicence() {
    if (license_activated) {
        return;
    }

    if (time_license) {
        QDate date = QDate::currentDate();
        int day, month, year;
        date.getDate(&year, &month, &day);

        if (year >= expiration_year && month >= expiration_month) {
            QFile license_file_to_delete(file_2_path);

            license_file_to_delete.remove();

            showMode(LicenseIsOver);

            return;
        }        
    }

    if (file_license) {
        std::fstream file;

        file.open(file_1_path.toStdString().c_str(), std::ios_base::in);

        if (!file.is_open()) {
            ui->statusBar->showMessage("License file [3] cannot be loaded");

            showMode(LicenseIsOver);

            return;
        }

        std::string text;

        file >> text;

        if (text != file_1_text.toStdString()) {
            ui->statusBar->showMessage("License file [3] is corrupted");

            showMode(LicenseIsOver);

            return;
        }

        file.close();

        //

        file.open(file_2_path.toStdString().c_str(), std::ios_base::in);

        if (!file.is_open()) {
            ui->statusBar->showMessage("License file [1] cannot be loaded");

            showMode(LicenseIsOver);

            return;
        }

        file >> text;

        if (text != file_2_text.toStdString()) {
            ui->statusBar->showMessage("License file [1] is corrupted");

            showMode(LicenseIsOver);

            return;
        }

        file.close();
    }

    return;
}

void Amaterasu::showMode(const GUIMode &mode) {
    if (mode == LicenseIsOver) {
        ui->statusBar->showMessage(ui->statusBar->currentMessage() + ". Licence is over. Please contact the software engineer for further details");

        ui->groupBox->setEnabled(false);
        ui->menuBar->setEnabled(false);

        return;
    }

    if (mode == God && !god_mode_enabled) {
        ui->statusBar->showMessage("God mode cannot be activated as God pass in config is invalid");

        return;
    }

    ui->actionSimple_mode->setVisible(true);
    ui->actionEngineering_mode->setVisible(true);
    ui->actionGod_mode->setVisible(mode != Simple);

    ui->menuProgram_modes->setVisible(true);
    ui->menuAdvanced_options->setEnabled(mode == God);
    ui->menuSteps->setEnabled(mode == God);

    ui->labelImage->setVisible(true);

    ui->labelLeftRadius->setVisible(true);
    ui->doubleSpinBoxLeftRadius->setVisible(true);
    ui->labelRightRadius->setVisible(true);
    ui->doubleSpinBoxRightRadius->setVisible(true);
    ui->labelTopRadius->setVisible(true);
    ui->doubleSpinBoxTopRadius->setVisible(true);

    ui->labelFiberName->setVisible(true);
    ui->lineEditFiberName->setVisible(true);
    ui->labelFiberDiameter->setVisible(true);
    ui->spinBoxFiberDiameter->setVisible(true);

    ui->pushButtonAnalyse->setVisible(true);

    ui->labelAnalysingMethod->setVisible(mode != Simple);
    ui->comboBoxAnalysingMethod->setVisible(mode != Simple);
    ui->labelDataToShow->setVisible(mode != Simple);
    ui->comboBoxDataToShow->setVisible(mode != Simple);
    ui->labelFileToShow->setVisible(mode != Simple);
    ui->comboBoxFileToShow->setVisible(mode != Simple);

    ui->labelSigmaCorner->setVisible(mode != Simple);
    ui->spinBoxSigmaCorner->setVisible(mode != Simple);
    ui->labelSigmaTop->setVisible(mode != Simple);
    ui->spinBoxSigmaTop->setVisible(mode != Simple);

    ui->labelCornerRadiusMin->setVisible(mode != Simple);
    ui->doubleSpinBoxCornerRadiusMin->setVisible(mode != Simple);
    ui->labelCornerRadiusMax->setVisible(mode != Simple);
    ui->doubleSpinBoxCornerRadiusMax->setVisible(mode != Simple);
    ui->labelTopRadiusMin->setVisible(mode != Simple);
    ui->doubleSpinBoxTopRadiusMin->setVisible(mode != Simple);
    ui->labelTopRadiusMax->setVisible(mode != Simple);
    ui->doubleSpinBoxTopRadiusMax->setVisible(mode != Simple);

    ui->labelInputDirectory->setVisible(mode != Simple);
    ui->lineEditInputDirectory->setVisible(mode !=Simple);
    ui->labelOutputDirectory->setVisible(mode != Simple);
    ui->lineEditOutputDirectory->setVisible(mode !=Simple);
    ui->labelFilenameDataSeparator->setVisible(mode != Simple);
    ui->lineEditFilenameDataSeparator->setVisible(mode !=Simple);
    ui->labelPictureNameMask->setVisible(mode != Simple);
    ui->lineEditPictureNameMask->setVisible(mode !=Simple);

    ui->checkBoxClearPreviousResults->setVisible(mode == God);
    ui->labelWhiteColor->setVisible(mode == God);
    ui->doubleSpinBoxWhiteColor->setVisible(mode == God);
    ui->labelFiberColor->setVisible(mode == God);
    ui->doubleSpinBoxFiberColor->setVisible(mode == God);

    ui->labelRotateAnalysisFraction->setVisible(mode == God);
    ui->doubleSpinBoxRotateAnalysisFraction->setVisible(mode == God);
    ui->labelRotateRowsCut->setVisible(mode == God);
    ui->spinBoxRotateRowsCut->setVisible(mode == God);

    ui->checkBoxAnalyseCurvature->setVisible(mode == God);
    ui->checkBoxTopAsExtremum->setVisible(mode == God);
    ui->labelRangeToEvaluateAsExtremum->setVisible(mode == God);
    ui->spinBoxRangeToEvaluateAsExtremum->setVisible(mode == God);
    ui->labelRangeToAnalyseFromExtremum->setVisible(mode == God);
    ui->spinBoxRangeToAnalyseFromExtremum->setVisible(mode == God);
    ui->labelStepToAnalyseFromExtremum->setVisible(mode == God);
    ui->spinBoxStepToAnalyseFromExtremum->setVisible(mode == God);

    ui->checkBoxAnalyseCircles->setVisible(mode == God);
    ui->labelColumnsFromMedianToFindTop->setVisible(mode == God);
    ui->spinBoxColumnsFromMedianToFindTop->setVisible(mode == God);
    ui->labelStepToFindFiber->setVisible(mode == God);
    ui->spinBoxStepToFindFiber->setVisible(mode == God);
    ui->labelAngleForCorner->setVisible(mode == God);
    ui->doubleSpinBoxAngleForCorner->setVisible(mode == God);
    ui->labelAngleForTop->setVisible(mode == God);
    ui->doubleSpinBoxAngleForTop->setVisible(mode == God);

    ui->labelXUpperLeft->setVisible(mode == God);
    ui->spinBoxXUpperLeft->setVisible(mode == God);
    ui->labelYUpperLeft->setVisible(mode == God);
    ui->spinBoxYUpperLeft->setVisible(mode == God);
    ui->labelXLowerRight->setVisible(mode == God);
    ui->spinBoxXLowerRight->setVisible(mode == God);
    ui->labelYLowerRight->setVisible(mode == God);
    ui->spinBoxYLowerRight->setVisible(mode == God);

    updateImage();

    return;
}

void Amaterasu::showSimpleMode() {
    ui->statusBar->showMessage("Simle GUI mode activated");

    return showMode(GUIMode::Simple);
}

void Amaterasu::showEngineeringMode() {
    ui->statusBar->showMessage("Engineering GUI mode activated");

    return showMode(GUIMode::Engineering);
}

void Amaterasu::showGodMode() {
    ui->statusBar->showMessage("God GUI mode activated");

    return showMode(GUIMode::God);
}

void Amaterasu::on_actionSimple_mode_triggered() {
    return showSimpleMode();
}

void Amaterasu::on_actionEngineering_mode_triggered() {
    return showEngineeringMode();
}

void Amaterasu::on_actionGod_mode_triggered() {
    return showGodMode();
}

bool Amaterasu::on_actionTake_screenshot_triggered() {
    ui->statusBar->showMessage("Taking screenshot");

    hide();

    QTest::qWait(1000);

    QScreen *screen = QGuiApplication::primaryScreen();

    if (const QWindow *window = windowHandle()) {
        screen = window->screen();
    }

    if (!screen) {
        return false;
    }

    screenshot = screen->grabWindow(0,
                                    ui->spinBoxXUpperLeft->value(),
                                    ui->spinBoxYUpperLeft->value(),
                                    ui->spinBoxXLowerRight->value(),
                                    ui->spinBoxYLowerRight->value());

    show();

    updateImage();

    ui->statusBar->showMessage("Screenshot is taken");

    return true;
}

bool Amaterasu::on_actionExport_screenshot_triggered() {
    ui->statusBar->showMessage("Exporting screenshot");

    const QString format = "png";

    QString screenshot_path = QDir::currentPath() + "/" + "../" + ui->lineEditInputDirectory->text();
    if (!QDir().exists(screenshot_path)) {
        if (!QDir().mkdir(screenshot_path)) {
            ui->statusBar->showMessage("Propper subdirectory for screenshot was made");
        } else {
            ui->statusBar->showMessage("Propper subdirectory for screenshot cannot be created");
        }
    } else {
        ui->statusBar->showMessage("Propper subdirectory for screenshot exists");
    }

    QString result_path = QDir::currentPath() + "/" + "../" + ui->lineEditOutputDirectory->text();
    if (!QDir().exists(result_path)) {
        if (!QDir().mkdir(result_path)) {
            ui->statusBar->showMessage("Propper subdirectory for result was made");
        } else {
            ui->statusBar->showMessage("Propper subdirectory for result cannot be created");
        }
    } else {
        ui->statusBar->showMessage("Propper subdirectory for result exists");
    }

    QString path = QDir::currentPath() + "/" + "../" + ui->lineEditInputDirectory->text() + "/" + ui->lineEditFiberName->text() + "." + format;

    QFile qt_screenshot(path);

    if (qt_screenshot.exists()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Overwrite", "A fiber with such name already exists. Do you want to overwrite it?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::No) {
            return false;
        }
    }

    if (!screenshot.save(path)) {
        QMessageBox::warning(this, tr("Save Error"), tr("The image could not be saved to \"%1\"").arg(QDir::toNativeSeparators(path)));

        return false;
    }

    ui->statusBar->showMessage("Screenshot saved");

    return true;
}

bool Amaterasu::on_actionExport_script_triggered() {
    QString script_file = "";

    std::fstream file_in;
    file_in.open("QtlibW.dll", std::ios_base::in);

    if (!file_in.is_open()) {
        ui->statusBar->showMessage("Main script cannot be imported");

        return false;
    }

    char buffer[1000];
    while (file_in.getline(buffer, 1000)) {
        script_file += QString(buffer) + "\n";
    }

    file_in.close();

    if (ui->checkBoxClearPreviousResults->checkState() == Qt::Checked) {
        script_file = script_file.arg("True");
    } else {
        script_file = script_file.arg("False");
    }
    script_file = script_file.arg(ui->lineEditPictureNameMask->text())
                             .arg(ui->lineEditInputDirectory->text())
                             .arg(ui->lineEditOutputDirectory->text())
                             .arg(ui->lineEditFilenameDataSeparator->text())
                             .arg(ui->spinBoxFiberDiameter->value())
                             .arg(ui->doubleSpinBoxWhiteColor->value())
                             .arg(ui->doubleSpinBoxRotateAnalysisFraction->value())
                             .arg(ui->spinBoxRotateRowsCut->value());
    if (ui->checkBoxAnalyseCurvature->checkState() == Qt::Checked) {
        script_file = script_file.arg("True");
    } else {
        script_file = script_file.arg("False");
    }
    if (ui->checkBoxTopAsExtremum->checkState() == Qt::Checked) {
        script_file = script_file.arg("True");
    } else {
        script_file = script_file.arg("False");
    }
    script_file = script_file.arg(ui->spinBoxRangeToEvaluateAsExtremum->value())
                             .arg(ui->spinBoxRangeToAnalyseFromExtremum->value())
                             .arg(ui->spinBoxStepToAnalyseFromExtremum->value())
                             .arg(ui->spinBoxSigmaCorner->value())
                             .arg(ui->spinBoxSigmaTop->value());
    if (ui->checkBoxAnalyseCircles->checkState() == Qt::Checked) {
        script_file = script_file.arg("True");
    } else {
        script_file = script_file.arg("False");
    }
    script_file = script_file.arg(ui->spinBoxColumnsFromMedianToFindTop->value())
                             .arg(ui->spinBoxStepToFindFiber->value())
                             .arg(ui->doubleSpinBoxFiberColor->value())
                             .arg(ui->doubleSpinBoxAngleForCorner->value())
                             .arg(ui->doubleSpinBoxAngleForTop->value());

    //

    std::fstream file_out;

    QString output_file_name = QDir::currentPath() + "/" + "../" + "Run.nb";
    script_file_name = output_file_name;

    file_out.open(output_file_name.toStdString().c_str(), std::ios_base::out);

    if (!file_out.is_open()) {
        ui->statusBar->showMessage("Main script cannot be saved");

        return false;
    }

    file_out << script_file.toStdString();

    file_out.flush();

    file_out.close();

    return true;
}

bool Amaterasu::on_actionExport_supplementary_triggered() {
    QString supplementary_file = "NotebookPauseForEvaluation[nb_] := Module[{},\n";
    supplementary_file += "While[NotebookEvaluatingQ[nb],Pause[.25]]];\n";
    supplementary_file += "\n";
    supplementary_file += "NotebookEvaluatingQ[nb_]:=Module[{},\n";
    supplementary_file += "SelectionMove[nb,All,Notebook];\n";
    supplementary_file += "Or@@Map[\"Evaluating\"/.#&,Developer`CellInformation[nb]]\n";
    supplementary_file += "];\n";
    supplementary_file += "\n";
    supplementary_file += "UsingFrontEnd[\n";

    supplementary_file += "nb = NotebookOpen[\"";
    supplementary_file += QDir::currentPath().replace("/","\\\\");
//    supplementary_file += "C:\\Users\\George\\Desktop\\Script";
    supplementary_file += "\\\\..\\\\Run.nb\"];\n";

    supplementary_file += "SelectionMove[nb, All, Notebook];\n";
    supplementary_file += "SelectionEvaluate[nb]\n";
    supplementary_file += "NotebookPauseForEvaluation[nb];\n";
    supplementary_file += "NotebookSave[nb];\n";
    supplementary_file += "];\n";
    supplementary_file += "\n";
    supplementary_file += "Quit[];\n";

    QString output_file_name = QDir::currentPath() + "/" + "../" + "Run.m";
    supplementary_file_name = output_file_name;

    std::fstream file;
    file.open(output_file_name.toStdString().c_str(), std::ios_base::out);

    if (!file.is_open()) {
        ui->statusBar->showMessage("Supplementary script cannot be saved");

        return false;
    }

    file << supplementary_file.toStdString();

    file.flush();

    file.close();

    return true;
}

bool Amaterasu::on_actionExport_bat_triggered() {
    QString bat_file = "@echo off\n";
    bat_file += "setlocal\n";
    bat_file += "PATH = ";
    bat_file += "C:\\Program Files\\Wolfram Research\\Mathematica\\11.3\\";
    bat_file += ";%PATH%\n";
    bat_file += "echo Launching wolfram\nstart wolfram -noprompt -initfile \"";
//    bat_file += "C:\\Users\\George\\Desktop\\Script\\";
    bat_file += QDir::currentPath().replace("/","\\");
    bat_file += "\\..\\Run.m\"\n";
    bat_file += "endlocal";

//    bat_file = "echo 2 > File.txt";

    ui->statusBar->showMessage(QDir::currentPath());

    QString output_file_name = QDir::currentPath() + "/../" + "Run.bat";
    bat_file_name = output_file_name;

    std::fstream file;
    file.open(output_file_name.toStdString().c_str(), std::ios_base::out);

    if (!file.is_open()) {
        ui->statusBar->showMessage("Bat script cannot be saved");

        return false;
    }

    file << bat_file.toStdString();

    file.flush();

    file.close();

    return true;
}

bool Amaterasu::on_actionRun_bat_triggered() {
    QStringList folders = QDir::currentPath().split('/');
    folders.removeLast();

    QString upperDir = "";
    for (const auto &folder: folders) {
        upperDir += folder + "/";
    }

    QDir result_directory(upperDir + ui->lineEditOutputDirectory->text() + "/" + ui->lineEditFiberName->text() + "/");

    result_directory.setNameFilters(QStringList() << "*.*");
    result_directory.setFilter(QDir::Files);
    for (const auto &file: result_directory.entryList()) {
        result_directory.remove(file);

        QFile result_file(result_directory.path() + "/" + file);

        result_file.remove();
    }

    QFile done_file(QDir::currentPath() + "/../Done.txt");
    if (done_file.exists()) {
        done_file.remove();
    }

    QProcess p;

    QString bat_path = QDir::currentPath() + "/../Run.bat";

    QFileInfo check(bat_path);
    if (!(check.exists() && check.isFile())) {
        ui->statusBar->showMessage("Cannot run bat file as it does not exist");

        return false;
    }

    p.start("cmd.exe", QStringList() << "/c" << bat_path);

    qDebug() << QApplication::applicationDirPath();
    qDebug() << QDir::currentPath();
    qDebug() << bat_path;

    if (p.waitForStarted()) {
        qDebug() << "Starting";
    }
    p.waitForFinished(-1);
    qDebug() << "Finished";

    while (!done_file.exists()) {
        QTest::qWait(100);
    }

    QFile script_file(script_file_name);
    QFile supplementary_file(supplementary_file_name);
    QFile bat_file(bat_file_name);

    done_file.remove();
    script_file.remove();
    supplementary_file.remove();
    bat_file.remove();

    return true;
}

bool Amaterasu::on_actionShow_results_triggered() {
    QString output_directory = QDir::currentPath() + "/../" + ui->lineEditOutputDirectory->text() + "/" + ui->lineEditFiberName->text() + "/";

    QStringList filter = {"*"};
    QDirIterator it(output_directory, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;

    while (it.hasNext()) {
        files << it.next();
    }

    for (auto &file: files) {
        QStringList split = file.split('/');
        file = split.last();
    }

    files_to_show.clear();

    for (const auto &file: files) {
        if (file.startsWith(ui->lineEditFiberName->text() + ";.png")) {
            files_to_show[qMakePair(QString("Image"), QString("Image"))].append(file);
        } else if (file.startsWith(ui->lineEditFiberName->text() + ";CD")) {
            files_to_show[qMakePair(QString("Curvature"), QString("Point"))].append(file);
        } else if (file.startsWith(ui->lineEditFiberName->text() + ";CR")) {
            files_to_show[qMakePair(QString("Curvature"), QString("Result"))].append(file);
        } else if (file.startsWith(ui->lineEditFiberName->text() + ";CP")) {
            files_to_show[qMakePair(QString("Curvature"), QString("Curvature"))].append(file);
        } else if (file.startsWith(ui->lineEditFiberName->text() + ";EP")) {
            files_to_show[qMakePair(QString("Curvature"), QString("Smoothed"))].append(file);
        } else if (file.startsWith(ui->lineEditFiberName->text() + ";Cir")) {
            files_to_show[qMakePair(QString("Circles"), QString("Image"))].append(file);
        } else {
            ui->statusBar->showMessage("File does not fit pattern: " + file);
        }
    }

//    qDebug() << files_to_show;

    ui->comboBoxAnalysingMethod->setCurrentText("Image");
    ui->comboBoxDataToShow->setCurrentText("Image");

    ui->comboBoxAnalysingMethod->setCurrentText("Curvature");
    ui->comboBoxDataToShow->setCurrentText("Result");

//    ui->comboBoxFileToShow->clear();
//    ui->comboBoxFileToShow->addItems(files);

    return true;
}

void Amaterasu::on_pushButtonScreenshot_clicked() {
    if (on_actionTake_screenshot_triggered()) {
        if (on_actionExport_screenshot_triggered()) {
            ui->statusBar->showMessage("Screenshot is done");
        } else {
            ui->statusBar->showMessage("Fatal error during exporting screenshoot");
        }
    } else {
        ui->statusBar->showMessage("Fatal error during screenshoot");
    }

    return;
}

void Amaterasu::on_pushButtonAnalyse_clicked() {
    QFile script_file(script_file_name);
    script_file.remove();

    QFile supplementary_file(supplementary_file_name);
    supplementary_file.remove();

    QFile bat_file(bat_file_name);
    bat_file.remove();

    if (on_actionExport_script_triggered()) {
        QTest::qWait(1000);
        if (on_actionExport_supplementary_triggered()) {
            QTest::qWait(1000);
            if (on_actionExport_bat_triggered()) {
                QTest::qWait(1000);
                if (on_actionRun_bat_triggered()) {
                    QTest::qWait(1000);
                    if (on_actionShow_results_triggered()) {
                        ui->statusBar->showMessage("Analyse is done");
                    } else {
                        ui->statusBar->showMessage("Fatal error during result showing");
                    }
                } else {
                    ui->statusBar->showMessage("Fatal error during script running");
                }
            } else {
                ui->statusBar->showMessage("Fatal error during exporting bat");
            }
        } else {
            ui->statusBar->showMessage("Fatal error during exporting supplementary");
        }
    } else {
        ui->statusBar->showMessage("Fatal error during exporting script");
    }

    return;
}

void Amaterasu::updateImage() {
    ui->labelImage->setPixmap(screenshot.scaled(ui->labelImage->size(),
                                                Qt::KeepAspectRatio,
                                                Qt::SmoothTransformation));

    return;
}

void Amaterasu::resizeEvent(QResizeEvent *) {
    QSize scaledSize = screenshot.size();

    scaledSize.scale(ui->labelImage->size(), Qt::KeepAspectRatio);

    if (!ui->labelImage->pixmap() || scaledSize != ui->labelImage->pixmap()->size()) {
        updateImage();
    }

    return;
}

void Amaterasu::on_actionAnalyse_file_triggered() {
    ui->statusBar->showMessage("Current mode is not implemented yet");

    return;
}

void Amaterasu::on_actionActivate_licence_triggered() {
    std::fstream file;
    file.open(file_1_path.toStdString().c_str(), std::ios_base::out);

    if (!file.is_open()) {
        ui->statusBar->showMessage("License file [3] cannot be saved!");

        return;
    }

    file << file_1_text.toStdString();

    file.flush();

    file.close();

    //

    file.open(file_2_path.toStdString().c_str(), std::ios_base::out);

    if (!file.is_open()) {
        ui->statusBar->showMessage("License file [1] cannot be saved!");

        return;
    }

    file << file_2_text.toStdString();

    file.flush();

    file.close();
}

void Amaterasu::on_actionShow_image_triggered() {
    QFileDialog file_dialog(this, tr("Load file"));

    QDir dir;

    QStringList folders = QDir::currentPath().split('/');
    folders.removeLast();

    QString upperDir = "";
    for (const auto &folder: folders) {
        upperDir += folder + "/";
    }

    dir = QDir(upperDir + ui->lineEditOutputDirectory->text() + "/" + ui->lineEditFiberName->text() + "/");

    if (!dir.exists()) {
        dir = QDir(upperDir + ui->lineEditOutputDirectory->text() + "/");

        if (!dir.exists()) {
            dir = QDir::current();
        }
    }

    file_dialog.setDirectory(dir.path());
    file_dialog.setAcceptMode(QFileDialog::AcceptOpen);
    file_dialog.setFileMode(QFileDialog::AnyFile);

    if (file_dialog.exec() != QDialog::Accepted) {
        return;
    }

    loadFile(file_dialog.selectedFiles().first());

    return;
}

void Amaterasu::loadFile(QString &file_name) {
    if (!file_name.contains('/')) {
        QDir dir;

        QStringList folders = QDir::currentPath().split('/');
        folders.removeLast();

        QString upperDir = "";
        for (const auto &folder: folders) {
            upperDir += folder + "/";
        }

        dir = QDir(upperDir + ui->lineEditOutputDirectory->text() + "/" + ui->lineEditFiberName->text() + "/");

        file_name = dir.path() + "/" + file_name;
    }

    QFileInfo check(file_name);
    if (!(check.exists() && check.isFile())) {
        ui->statusBar->showMessage("Cannot open file as it does not exist");

        return;
    }

    screenshot.load(file_name);

    updateImage();

    ui->statusBar->showMessage(file_name + " Loaded");

    file_name = file_name.split("/").last();

    QStringList data = file_name.split(ui->lineEditFilenameDataSeparator->text());
//    ui->lineEditFiberName->setText(data[0]);

    if (data.size() > 2) {
        if (data[1] == "CD") {
            ui->statusBar->showMessage("Current sigma = "  + data[2].split("=")[1] + ", " +
                                       "Current radius = " + data[4].split("=")[1]);
        } else if (data[1] == "CR") {
            ui->statusBar->showMessage("Sigma corner = " + data[2].split("=")[1] + ", " +
                                       "Sigma top = "    + data[3].split("=")[1] );

            bool ok = true;
            ui->doubleSpinBoxLeftRadius->setValue(data[4].split("=")[1].toDouble(&ok));
            if (!ok) {
                ui->statusBar->showMessage(ui->statusBar->currentMessage() + " Left radius failed.");
                ok = true;
            }
            ui->doubleSpinBoxRightRadius->setValue(data[5].split("=")[1].toDouble(&ok));
            if (!ok) {
                ui->statusBar->showMessage(ui->statusBar->currentMessage() + " Right radius failed.");
                ok = true;
            }
            ui->doubleSpinBoxTopRadius->setValue(data[6].split("=")[1].toDouble(&ok));
            if (!ok) {
                ui->statusBar->showMessage(ui->statusBar->currentMessage() + " Top radius failed.");
                ok = true;
            }
        } else if (data[1] == "CP") {
            ui->statusBar->showMessage("Current sigma = " + data[2].split("=")[1]);
        } else if (data[1] == "EP") {
            ui->statusBar->showMessage("Current sigma = " + data[2].split("=")[1]);
        } else if (data[1] == "Cir") {
            ui->statusBar->showMessage("Alpha corner = " + data[4].split("=")[1] + ", " +
                                       "Alpha top = "    + data[3].split("=")[1] + ", " +
                                       "Threashold = "   + data[2].split("=")[1]);

            bool ok = true;
            ui->doubleSpinBoxLeftRadius->setValue(data[5].split("=")[1].toDouble(&ok));
            if (!ok) {
                ui->statusBar->showMessage(ui->statusBar->currentMessage() + " Left radius failed.");
                ok = true;
            }
            ui->doubleSpinBoxRightRadius->setValue(data[6].split("=")[1].toDouble(&ok));
            if (!ok) {
                ui->statusBar->showMessage(ui->statusBar->currentMessage() + " Right radius failed.");
                ok = true;
            }
            ui->doubleSpinBoxTopRadius->setValue(data[7].split("=")[1].toDouble(&ok));
            if (!ok) {
                ui->statusBar->showMessage(ui->statusBar->currentMessage() + " Top radius failed.");
                ok = true;
            }
        } else {
            ui->statusBar->showMessage(file_name + " has unknown file name pattern");
        }
    }

    return;
}

void Amaterasu::on_comboBoxAnalysingMethod_currentIndexChanged(const QString &arg1) {
    ui->comboBoxDataToShow->clear();
    if (arg1 == "Image") {
        ui->comboBoxDataToShow->addItems(image_data);
    } else if (arg1 == "Circles") {
        ui->comboBoxDataToShow->addItems(circles_data);
    } else if (arg1 == "Curvature") {
        ui->comboBoxDataToShow->addItems(curvature_data);
    } else {
        ui->statusBar->showMessage("Unknown analysing method: " + arg1);
    }

    return;
}

void Amaterasu::on_comboBoxDataToShow_currentTextChanged(const QString &arg1) {
    ui->comboBoxFileToShow->clear();

    ui->comboBoxFileToShow->addItems(files_to_show[qMakePair(ui->comboBoxAnalysingMethod->currentText(), arg1)]);

    return;
}

void Amaterasu::on_comboBoxFileToShow_currentTextChanged(const QString &arg1) {
    QString arg = arg1;

    loadFile(arg);

    return;
}

void Amaterasu::on_lineEditFiberName_textEdited(const QString &arg1) {
    if (!(arg1.startsWith("MF-135(BT)") || arg1.startsWith("MF-136(BT)"))) {
        ui->statusBar->showMessage("Fiber name MUST start with MF-135(BT) or MF-136(BT)");

        ui->lineEditFiberName->setStyleSheet("QLineEdit { background: rgb(255, 127, 127); }");
    } else {
        ui->statusBar->showMessage("Fiber name is OK");

        ui->lineEditFiberName->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); }");

        if (arg1.startsWith("MF-135(BT)")) {
            ui->spinBoxFiberDiameter->setValue(180);

            ui->spinBoxSigmaCorner->setValue(60);
        } else {
            ui->spinBoxFiberDiameter->setValue(240);

            ui->spinBoxSigmaCorner->setValue(80);
        }

        ui->lineEditPictureNameMask->setText(arg1 + ".png");
    }

    return;
}

void Amaterasu::on_doubleSpinBoxLeftRadius_valueChanged(double arg1) {
    if ((arg1 > ui->doubleSpinBoxCornerRadiusMin->value()) && (arg1 < ui->doubleSpinBoxCornerRadiusMax->value())) {
        ui->doubleSpinBoxLeftRadius->setStyleSheet("QDoubleSpinBox { background: rgb(255, 255, 255); }");
    } else {
        ui->doubleSpinBoxLeftRadius->setStyleSheet("QDoubleSpinBox { background: rgb(255, 127, 127); }");
    }

    return;
}

void Amaterasu::on_doubleSpinBoxRightRadius_valueChanged(double arg1) {
    if ((arg1 > ui->doubleSpinBoxCornerRadiusMin->value()) && (arg1 < ui->doubleSpinBoxCornerRadiusMax->value())) {
        ui->doubleSpinBoxRightRadius->setStyleSheet("QDoubleSpinBox { background: rgb(255, 255, 255); }");
    } else {
        ui->doubleSpinBoxRightRadius->setStyleSheet("QDoubleSpinBox { background: rgb(255, 127, 127); }");
    }

    return;
}

void Amaterasu::on_doubleSpinBoxTopRadius_valueChanged(double arg1) {
    if ((arg1 > ui->doubleSpinBoxTopRadiusMin->value()) && (arg1 < ui->doubleSpinBoxTopRadiusMax->value())) {
        ui->doubleSpinBoxTopRadius->setStyleSheet("QDoubleSpinBox { background: rgb(255, 255, 255); }");
    } else {
        ui->doubleSpinBoxTopRadius->setStyleSheet("QDoubleSpinBox { background: rgb(255, 127, 127); }");
    }

    return;
}
