#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMessageBox>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ingredientListWidget = new QListWidget(this);
    ingredientNameComboBox = new QComboBox(this);
    ingredientQuantitySpinBox = new QSpinBox(this);
    ingredientQuantitySpinBox->setMinimum(1);

    QStringList predefinedIngredients = { "Tomato", "Cheese", "Lettuce", "Onion", "Chicken", "Beef", "Butter" };
    ingredientNameComboBox->addItems(predefinedIngredients);

    dishListWidget = new QListWidget(this);
    dishNameComboBox = new QComboBox(this);

    QStringList predefinedDishes = { "Salad", "Burger", "Pizza", "Sandwich", "Soup" };
    dishNameComboBox->addItems(predefinedDishes);

    addIngredientButton = new QPushButton("Add Ingredient", this);
    editIngredientButton = new QPushButton("Edit Ingredient", this);
    removeIngredientButton = new QPushButton("Remove Ingredient", this);
    addDishButton = new QPushButton("Add Dish", this);
    removeDishButton = new QPushButton("Remove Dish", this); 
    processOrderButton = new QPushButton("Process Order", this);

    connect(addIngredientButton, &QPushButton::clicked, this, &MainWindow::addIngredient);
    connect(editIngredientButton, &QPushButton::clicked, this, &MainWindow::editIngredient);
    connect(removeIngredientButton, &QPushButton::clicked, this, &MainWindow::removeIngredient);
    connect(addDishButton, &QPushButton::clicked, this, &MainWindow::addDish);
    connect(removeDishButton, &QPushButton::clicked, this, &MainWindow::removeDish); 
    connect(processOrderButton, &QPushButton::clicked, this, &MainWindow::processOrder);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Ingredients"));
    mainLayout->addWidget(ingredientListWidget);
    mainLayout->addWidget(new QLabel("Ingredient Name"));
    mainLayout->addWidget(ingredientNameComboBox);
    mainLayout->addWidget(new QLabel("Quantity"));
    mainLayout->addWidget(ingredientQuantitySpinBox);
    mainLayout->addWidget(addIngredientButton);
    mainLayout->addWidget(editIngredientButton);
    mainLayout->addWidget(removeIngredientButton);

    mainLayout->addWidget(new QLabel("Dishes"));
    mainLayout->addWidget(dishListWidget);
    mainLayout->addWidget(new QLabel("Dish Name"));
    mainLayout->addWidget(dishNameComboBox);
    mainLayout->addWidget(addDishButton);
    mainLayout->addWidget(removeDishButton); 
    mainLayout->addWidget(processOrderButton);

    QWidget* widget = new QWidget();
    widget->setLayout(mainLayout);
    setCentralWidget(widget);

    initializeDishRequirements();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initializeDishRequirements() {
    dishRequirements = {
        { "Salad", { { "Tomato", 2 }, { "Lettuce", 3 } } },
        { "Burger", { { "Beef", 1 }, { "Cheese", 1 }, { "Lettuce", 1 }, { "Tomato", 2 } } },
        { "Pizza", { { "Cheese", 2 }, { "Tomato", 3 }, { "Butter", 1 } } },
        { "Sandwich", { { "Chicken", 1 }, { "Lettuce", 2 }, { "Onion", 1 }, { "Tomato", 1 } } },
        { "Soup", { { "Chicken", 2 }, { "Onion", 1 }, { "Tomato", 2 }, { "Butter", 1 } } }
    };
}

void MainWindow::addIngredient() {
    QString name = ingredientNameComboBox->currentText();
    int quantity = ingredientQuantitySpinBox->value();

    if (name.isEmpty()) {
        showMessage("Ingredient name cannot be empty.");
        return;
    }

    std::string ingredientNameStr = name.toStdString();

    if (ingredients.find(ingredientNameStr) != ingredients.end()) {
        ingredients[ingredientNameStr].setQuantity(ingredients[ingredientNameStr].getQuantity() + quantity);
    }
    else {
        ingredients[ingredientNameStr] = Ingredient(ingredientNameStr, quantity);
    }

    refreshIngredientList();
    showMessage("Ingredient added successfully.");
}

void MainWindow::editIngredient() {
    QListWidgetItem* selectedItem = ingredientListWidget->currentItem();
    if (!selectedItem) {
        showMessage("No ingredient selected.");
        return;
    }

    QString name = ingredientNameComboBox->currentText();
    int quantity = ingredientQuantitySpinBox->value();

    if (name.isEmpty()) {
        showMessage("Ingredient name cannot be empty.");
        return;
    }

    ingredients[name.toStdString()] = Ingredient(name.toStdString(), quantity);
    refreshIngredientList();
    showMessage("Ingredient edited successfully.");
}

void MainWindow::removeIngredient() {
    QListWidgetItem* selectedItem = ingredientListWidget->currentItem();
    if (!selectedItem) {
        showMessage("No ingredient selected.");
        return;
    }

    QString name = selectedItem->text().split(" (").first();
    ingredients.erase(name.toStdString());
    refreshIngredientList();
    showMessage("Ingredient removed successfully.");
}

void MainWindow::addDish() {
    QString name = dishNameComboBox->currentText();

    if (name.isEmpty()) {
        showMessage("Dish name cannot be empty.");
        return;
    }

    dishListWidget->addItem(name);
    showMessage("Dish added to list.");
}

void MainWindow::removeDish() {
    QListWidgetItem* selectedItem = dishListWidget->currentItem();
    if (!selectedItem) {
        showMessage("No dish selected.");
        return;
    }

    delete selectedItem; 
    showMessage("Dish removed from list.");
}

void MainWindow::processOrder() {
    std::unordered_map<std::string, int> totalRequiredIngredients;

    
    for (int i = 0; i < dishListWidget->count(); ++i) {
        QString dishName = dishListWidget->item(i)->text();
        auto it = dishRequirements.find(dishName.toStdString());
        if (it != dishRequirements.end()) {
            for (const auto& requirement : it->second) {
                totalRequiredIngredients[requirement.first] += requirement.second;
            }
        }
    }

    
    std::vector<std::string> missingIngredients;
    for (const auto& requirement : totalRequiredIngredients) {
        const std::string& ingredientName = requirement.first;
        int requiredQuantity = requirement.second;

        if (ingredients[ingredientName].getQuantity() < requiredQuantity) {
            missingIngredients.push_back(ingredientName + " (" + std::to_string(requiredQuantity - ingredients[ingredientName].getQuantity()) + " more needed)");
        }
    }

    if (!missingIngredients.empty()) {
        QString message = "Not enough ingredients to prepare the dishes:\n";
        for (const std::string& missing : missingIngredients) {
            message += QString::fromStdString(missing) + "\n";
        }
        showMessage(message);
        return;
    }

    
    for (const auto& requirement : totalRequiredIngredients) {
        const std::string& ingredientName = requirement.first;
        int requiredQuantity = requirement.second;
        ingredients[ingredientName].setQuantity(ingredients[ingredientName].getQuantity() - requiredQuantity);
    }

    refreshIngredientList();
    showMessage("Order is being prepared.");
}

void MainWindow::refreshIngredientList() {
    ingredientListWidget->clear();
    for (const auto& pair : ingredients) {
        ingredientListWidget->addItem(QString::fromStdString(pair.first) + " (" + QString::number(pair.second.getQuantity()) + ")");
    }
}

void MainWindow::showMessage(const QString& message) {
    QMessageBox::information(this, "Information", message);
}
