#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <unordered_map>
#include "ingredient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void addIngredient();
    void editIngredient();
    void removeIngredient();
    void addDish();
    void removeDish(); 
    void processOrder();

private:
    Ui::MainWindow* ui;
    QListWidget* ingredientListWidget;
    QComboBox* ingredientNameComboBox;
    QSpinBox* ingredientQuantitySpinBox;
    QPushButton* addIngredientButton;
    QPushButton* editIngredientButton;
    QPushButton* removeIngredientButton;
    QPushButton* addDishButton;
    QPushButton* removeDishButton; 
    QPushButton* processOrderButton;
    QListWidget* dishListWidget;
    QComboBox* dishNameComboBox;

    std::unordered_map<std::string, Ingredient> ingredients;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> dishRequirements;

    void initializeDishRequirements();
    void refreshIngredientList();
    void refreshDishList();
    void showMessage(const QString& message);
};

#endif // MAINWINDOW_H
