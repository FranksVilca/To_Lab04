#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

// Función para cargar los datos desde un archivo de texto
QMap<QString, QString> cargarDatosDesdeArchivo(const QString &fileName) {
    QMap<QString, QString> dataMap;
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");  // Separar por '|' (nombre|descripción)
            if (parts.size() == 2) {
                dataMap[parts[0]] = parts[1];  // Almacenar nombre y descripción
            }
        }
        file.close();
    } else {
        QMessageBox::warning(nullptr, "Error", "No se pudo abrir el archivo: " + fileName);
    }

    return dataMap;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Ventana principal
    QWidget window;
    window.setWindowTitle("Recursos Hídricos del Pacífico");

    // Layout principal
    QVBoxLayout *layout = new QVBoxLayout(&window);

    // TextEdit para mostrar la información detallada
    QTextEdit *infoText = new QTextEdit(&window);
    infoText->setReadOnly(true); // Solo lectura
    infoText->setText("Seleccione un recurso hídrico para ver la información");

    // Botones para seleccionar los recursos
    QPushButton *cuencasButton = new QPushButton("Cuencas", &window);
    QPushButton *riosButton = new QPushButton("Ríos", &window);
    QPushButton *canalesButton = new QPushButton("Canales", &window);

    // Layout para los botones generados dinámicamente
    QVBoxLayout *dynamicButtonLayout = new QVBoxLayout();

    // Agregar los widgets al layout principal
    layout->addWidget(infoText);
    layout->addWidget(cuencasButton);
    layout->addWidget(riosButton);
    layout->addWidget(canalesButton);
    layout->addLayout(dynamicButtonLayout);  // Para botones generados dinámicamente

    // Cargar datos desde los archivos TXT
    QMap<QString, QString> cuencaInfo = cargarDatosDesdeArchivo("C:/Users/USER/OneDrive/Documentos/TO_Lab04/cuencas.txt");
    QMap<QString, QString> riosInfo = cargarDatosDesdeArchivo("C:/Users/USER/OneDrive/Documentos/TO_Lab04/Rios.txt");
    QMap<QString, QString> canalInfo = cargarDatosDesdeArchivo("C:/Users/USER/OneDrive/Documentos/TO_Lab04/canales.txt");

    // Función auxiliar para eliminar los botones dinámicos existentes
    auto clearDynamicButtons = [&]() {
        QLayoutItem *item;
        while ((item = dynamicButtonLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    };

    // Conectar señales y slots con lambdas para Cuencas
    QObject::connect(cuencasButton, &QPushButton::clicked, [&]() {
        clearDynamicButtons();  // Limpiar botones previos
        QString info = "Seleccione una cuenca del Pacífico:\n";

        // Crear un botón para cada cuenca
        for (auto it = cuencaInfo.begin(); it != cuencaInfo.end(); ++it) {
            QPushButton *cuencaButton = new QPushButton(it.key(), &window);
            dynamicButtonLayout->addWidget(cuencaButton);

            // Conectar cada botón con la información de la cuenca correspondiente
            QObject::connect(cuencaButton, &QPushButton::clicked, [&, it]() {
                infoText->setText(it.key() + ": " + it.value());
            });
        }

        infoText->setText(info);
    });

    // Conectar señales y slots con lambdas para Ríos
    QObject::connect(riosButton, &QPushButton::clicked, [&]() {
        clearDynamicButtons();  // Limpiar botones previos
        QString info = "Seleccione un río del Pacífico:\n";

        // Crear un botón para cada río
        for (auto it = riosInfo.begin(); it != riosInfo.end(); ++it) {
            QPushButton *rioButton = new QPushButton(it.key(), &window);
            dynamicButtonLayout->addWidget(rioButton);

            // Conectar cada botón con la información del río correspondiente
            QObject::connect(rioButton, &QPushButton::clicked, [&, it]() {
                infoText->setText(it.key() + ": " + it.value());
            });
        }

        infoText->setText(info);
    });

    // Conectar señales y slots con lambdas para Canales
    QObject::connect(canalesButton, &QPushButton::clicked, [&]() {
        clearDynamicButtons();  // Limpiar botones previos
        QString info = "Seleccione un canal del Pacífico:\n";

        // Crear un botón para cada canal
        for (auto it = canalInfo.begin(); it != canalInfo.end(); ++it) {
            QPushButton *canalButton = new QPushButton(it.key(), &window);
            dynamicButtonLayout->addWidget(canalButton);

            // Conectar cada botón con la información del canal correspondiente
            QObject::connect(canalButton, &QPushButton::clicked, [&, it]() {
                infoText->setText(it.key() + ": " + it.value());
            });
        }

        infoText->setText(info);
    });

    // Mostrar la ventana
    window.show();

    return app.exec();
}
